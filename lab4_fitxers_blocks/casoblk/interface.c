#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/blkdev.h>

#include <linux/kernel.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/vmalloc.h>

#include "interface.h"


int xrd_size = XRD_SIZE;

MODULE_LICENSE("Dual BSD/GPL");

static int max_part;
module_param(max_part, int, S_IRUGO);
MODULE_PARM_DESC(max_part, "Maximum number of partitions per RAM disk");

static int part_shift;
static unsigned long range;
#define MAX_XRD 2
static int max_xrd;

static struct xrd_struct * xrd_array[MAX_XRD];


/**************** Interficie de les funcions que heu d'implementar **********/

// funcio per demanar la memoria que mantindra les dades del disc.
// Usa p = vmalloc(PAGE_ALIGN(size)) per demanar-la al kernel
// Inicialitza la memoria fent que cada caracter valgui i%256:
//     for (i=0; i < size; ++i) p[i] = i;
char * alloc_disk_memory(unsigned long size);

// funcio per alliberar la memoria que mante les dades del disc.
// Usa vfree(p) per alliberar
void   free_disk_memory(char * disk_mem);

// funcio per retornar la geometria del disc.
// Accedeix al vostre disc (bdev->bd_disk->private_data, de tipus xrd_struct)
//  omple l'estructura que rep per referencia (geo):
///    struct hd_geometry {
///          unsigned char heads;
///          unsigned char sectors;
///          unsigned short cylinders;
///          unsigned long start;
///    };
// plena amb heads= 32
//           sectors= 128
//           cylinders= <mida del disc> / geo->heads/geo->sectors/SECTOR_SIZE
//           start= 0
// podeu trobar la mida del disc a l'estructura xrd_struct, camp "size".
// no oblideu fer un return 0; per indicar que tot ha anat be.
int xrd_getgeo(struct block_device * bdev, struct hd_geometry *geo);

// funcio per llegir del ramdisk. Rep:
//  dst: adreça en l'espai del kernel on escriure la informacio
//  xrd: punter a l'estructura del nostre disc
//  sector: sector del disc d'on s'ha de llegir
//  n: numero de bytes que volem llegir
int copy_from_xrd(void *dst, struct xrd_struct *xrd,
                        sector_t sector, size_t n);

// funcio per escriure al ramdisk. Rep:
// xrd: punter a l'estructura del nostre disc
// src: adreça en l'espai del kernel d'on llegir la informacio
// sector: sector del disc on volem escriure
// n: numero de bytes que volem escriure
int copy_to_xrd(struct xrd_struct *xrd, void *src,
                        sector_t sector, size_t n);


/****************************************************************************/


/***** Funcions de la interficie d'operacions del dispositiu de bloc ********/
/*                    NO les heu de canviar                                 */
/*             Nomes son aqui per veure quan es criden                      */

static int xrd_ioctl(struct block_device *bdev, fmode_t mode,
                       unsigned int cmd, unsigned long arg)
{
   int error;
   printk(KERN_DEBUG "xrd_ioctl cmd %u argd %ld (BLKFLSBUF %u)\n", cmd, arg,
           BLKFLSBUF);

   if (cmd != BLKFLSBUF) return -ENOTTY;

   error = -EBUSY;
   if (bdev->bd_openers <= 1) {
      error = 0;
      printk(KERN_DEBUG "should destroy/create\n");
   }
   return 0;
}

static int xrd_compat_ioctl(struct block_device * bdev, fmode_t mode, unsigned cmd, unsigned long arg)
{
   printk(KERN_DEBUG "xrd_compat_ioctl cmd %u argd %ld\n", cmd, arg);
   return -ENOTTY;
}

static unsigned int xrd_check_events(struct gendisk *disk,unsigned int clearing)
{
   printk(KERN_DEBUG "xrd_check_events clearing %d\n", clearing);
   return -ENOTTY;
}

static int xrd_media_changed (struct gendisk *gd)
{
   printk(KERN_DEBUG "xrd_media_changed\n");
   return -ENOTTY;

}

static void xrd_unlock_native_capacity (struct gendisk * gd)
{
   printk(KERN_DEBUG "xrd_unlock_native_capacity\n");
   return;
}


#ifdef CONFIG_BLK_DEV_XIP
#error "XIP"
static int xrd_direct_access(struct block_device *bdev, sector_t sector,
                                  void **kaddr, unsigned long *pfn)
{
   struct xrd_struct *xrd = bdev->bd_disk->private_data;
   if (xrd == NULL) return -ENODEV;
   printk (KERN_DEBUG "xrd_direct_access num %d major %d minor %d sector %ld\n", 
           xrd->xrd_num, xrd->major, xrd->first_minor, sector);
   if (kaddr != NULL) {
      printk (KERN_DEBUG "    kaddr %p pfn %p\n", *kaddr, pfn);
   }
   else {
      printk (KERN_DEBUG "    kaddr <n/a> pfn %p\n", pfn);
   }
   return -EINVAL;
}
#endif

int xrd_open(struct block_device * bdev, fmode_t mode)
{
   printk(KERN_DEBUG "open disk\n");
   return 0;
}

void xrd_release (struct gendisk * gd, fmode_t mode)
{
   printk(KERN_DEBUG "close disk\n");
   return;
}



int xrd_revalidate(struct gendisk * disk)
{
   printk(KERN_DEBUG "revalidate\n");
   return -EIO;
}

static void xrd_swap_slot_free_notify(struct block_device * bdev, unsigned long arg)
{
   printk(KERN_DEBUG "xrd_swap_slot_free_notify arg %ld\n", arg);
}



static const struct block_device_operations xrd_fops = {
        .owner =                THIS_MODULE,
	.open =                 xrd_open,
	.release =		xrd_release,
        .ioctl =                xrd_ioctl,
	.compat_ioctl =		xrd_compat_ioctl,
	.getgeo = 		xrd_getgeo,
	.revalidate_disk =       xrd_revalidate,
	.check_events =		xrd_check_events,
	.media_changed =	xrd_media_changed,
	.unlock_native_capacity = xrd_unlock_native_capacity,
	.swap_slot_free_notify = xrd_swap_slot_free_notify,
#ifdef CONFIG_BLK_DEV_XIP
        .direct_access =        xrd_direct_access,
#endif
};

/*                                                                         */
/*                                                                         */
/************* Final de les funcions del dispositiu de bloc ****************/

/***************************************************************************/
/**************** Funcions de suport a la gestio del disc ******************/
/*                       NO les heu de canviar                             */


/*
 * Process a single bvec of a bio.
 */
static int xrd_do_bvec(struct xrd_struct *xrd, struct page *page,
                        unsigned int len, unsigned int off, int rw,
                        sector_t sector)
{
        void *mem;
        int err = 0;

#ifdef DEBUG
	printk(KERN_DEBUG "xrd_do_bvec starts on %p off %d\n", xrd, off);
#endif
        if (rw != READ) {
#ifdef DEBUG
		printk(KERN_DEBUG "xrd_do_bvec WRITE should setup\n");
#endif
                //err = copy_to_brd_setup(brd, sector, len);
                //err = -ENOMEM;
                if (err)
                        goto out;
        }

        mem = kmap_atomic(page);
        if (rw == READ) {
                err = copy_from_xrd(mem + off, xrd, sector, len);
                flush_dcache_page(page);
        } else {
		// should not happen
		flush_dcache_page(page);
		err = copy_to_xrd(xrd, mem + off, sector, len);
	}
	kunmap_atomic(mem);
out:
	return err;
}

char blank_page[4096];
//static void xrd_make_request(struct request_queue *q, struct bio *bio)
static blk_qc_t xrd_make_request(struct request_queue *q, struct bio *bio)
{
   //struct block_device *bdev = bio->bi_bdev;
   struct gendisk * bdev = bio->bi_disk;
   sector_t sector;
   int err = -EIO;

#ifdef DEBUG
printk(KERN_DEBUG "xrd_make_request starts\n");
#endif

   sector = bio->bi_iter.bi_sector;
   if ((sector + (bio->bi_iter.bi_size >> SECTOR_SHIFT)) <= 
                                          get_capacity(bdev))
   {
      if(bio_op(bio)!=REQ_OP_DISCARD) {
      //if (! (bio->bi_rw & REQ_DISCARD)) {
         struct xrd_struct *xrd = bdev->private_data;
         int rw;
         struct bio_vec bvec;
         struct bvec_iter i;
         rw = bio_op(bio);
         if (bio->bi_opf & REQ_RAHEAD) rw = 0;
#ifdef DEBUG
	 printk(KERN_DEBUG "xrd_make_request xrd %p\n", xrd);
         if (xrd!=NULL) 
	      printk(KERN_DEBUG "xrd disk_memory %p\n", xrd->disk_memory);
#endif
         bio_for_each_segment(bvec, bio, i) {
                unsigned int len = bvec.bv_len;
#ifdef DEBUG
		printk("   Processing %s request %d, sector %ld, page %p\n",
                    (rw==READ)? "READ" : "WRITE", i, sector, bvec.bv_page);
#endif

                err = xrd_do_bvec(xrd, bvec.bv_page, len,
                                       bvec.bv_offset, rw, sector);
                if (err)
                        break;
                sector += len >> SECTOR_SHIFT;
         }
      }
      else {
         struct xrd_struct *xrd = bdev->private_data;
         int n;
         err = 0;
         printk (KERN_DEBUG "must discard request %d (sector %ld, size %d)!!!\n",
			  bio->bi_vcnt, sector,
                         bio->bi_iter.bi_size);
	 
         //discard_from_brd(xrd, sector, bio->bi_size);
	 n = bio->bi_iter.bi_size;
	 while (n >= PAGE_SIZE) {
		 //brd_zero_page(
		//err = copy_to_xrd(xrd, mem + off, sector, len);
                   copy_to_xrd(xrd, blank_page, sector, PAGE_SIZE);
                   sector += PAGE_SIZE >> SECTOR_SHIFT;
                   n -= PAGE_SIZE;
         }
      }
   }

#ifdef DEBUG
   printk (KERN_DEBUG "xrd_make_request returns %d\n", err);
#endif
   bio_endio(bio); //, err);
   return BLK_QC_T_NONE;
}


static struct xrd_struct * xrd_alloc(int i)
{
   struct xrd_struct * xrd;
   struct gendisk *disk;
   xrd = kzalloc(sizeof(*xrd), GFP_KERNEL);
   if (xrd!=NULL) {
#ifdef DEBUG
    printk(KERN_DEBUG "alloc_disk_memory %d\n", XRD_SIZE*1024);
#endif
    xrd->disk_memory = alloc_disk_memory(XRD_SIZE*1024);
#ifdef DEBUG
    printk(KERN_DEBUG "alloc_disk_memory returns %p\n", xrd->disk_memory);
#endif
    if (xrd->disk_memory != NULL) {
      xrd->size = XRD_SIZE*1024;
      xrd->xrd_num = i;
      xrd->major = XRD_MAJOR;
      xrd->first_minor = i << part_shift;
      xrd->xrd_queue = blk_alloc_queue(GFP_KERNEL);
      if (xrd->xrd_queue!=NULL) {
#ifdef DEBUG
         printk(KERN_DEBUG "xrd_alloc will return %p (%p)\n", xrd, xrd->disk_memory);
#endif
         blk_queue_make_request(xrd->xrd_queue, xrd_make_request);
         blk_queue_max_hw_sectors(xrd->xrd_queue, 1024);
         blk_queue_bounce_limit(xrd->xrd_queue, BLK_BOUNCE_ANY);
         xrd->xrd_queue->limits.discard_granularity = PAGE_SIZE;
         xrd->xrd_queue->limits.max_discard_sectors = UINT_MAX;
         //xrd->xrd_queue->limits.discard_zeroes_data = 1;
         queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, xrd->xrd_queue);
         
         disk = xrd->xrd_disk    = alloc_disk(1 << part_shift);
#ifdef DEBUG
         printk(KERN_DEBUG "xrd_alloc will return %p (%p)\n", xrd, xrd->disk_memory);
#endif
         if (disk != NULL) {
            disk->major             = XRD_MAJOR;
            disk->first_minor       = i << part_shift;
            disk->fops              = &xrd_fops;
            disk->private_data      = xrd;
            disk->queue             = xrd->xrd_queue;
            disk->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
            sprintf(disk->disk_name, "xrd%d", i);
            set_capacity(disk, xrd_size * 2);
            printk(KERN_DEBUG "xrd_alloc returns %p (%p)\n", xrd, xrd->disk_memory);
            return xrd;
         }
         else {
            blk_cleanup_queue(xrd->xrd_queue);
            free_disk_memory(xrd->disk_memory);
            kfree(xrd);
            xrd = NULL;
         }
      }
      else {
         free_disk_memory(xrd->disk_memory);
         kfree(xrd);
         xrd = NULL;
      }
    }
    else {
      kfree(xrd);
      xrd = NULL;
    }
   }
   return xrd;
}

static void xrd_free(struct xrd_struct *xrd)
{
   put_disk(xrd->xrd_disk);
   blk_cleanup_queue(xrd->xrd_queue);
   kfree(xrd);
}

static struct kobject *xrd_probe(dev_t dev, int *part, void *data)
{
   struct kobject *kobj = ERR_PTR(-ENOMEM);

   printk(KERN_DEBUG "xrd_probe %d:%d\n", MAJOR(dev), MINOR(dev));

   if (MINOR(dev) < MAX_XRD) {
      kobj = get_disk (xrd_array[MINOR(dev)]->xrd_disk);
   }

   printk(KERN_DEBUG "xrd_probe returns %p\n", kobj);
   return kobj;
}


/***************************************************************************/
/***************** Funcio d'inicialitzacio del modul ***********************/
/*                        NO l'heu de canviar                              */

static int myblk_init(void) 
{
  int i, res = 0;

  max_xrd = MAX_XRD;

   // minim, per defecte tindrem capacitat per tres particions
   // max_part = 2 significa que tenim dos bits per representar cada disc:
   //      00    tot el disc   
   //      01    particio 1
   //      10    particio 2
   //      11    particio 3
  if (max_part == 0) max_part = 2;

  part_shift = fls (max_part);
  max_part = (1<< part_shift) - 1;
  range = max_xrd << part_shift;
  printk(KERN_DEBUG "Hello world! max_part %d part_shift %x range %lx\n",
      max_part, part_shift, range);

  if ((1 << part_shift) > DISK_MAX_PARTS)
     return -EINVAL;

   // enregistrem el dispositiu de bloc
  res = register_blkdev(XRD_MAJOR, "xrd");
  if (res != 0) return -EIO;

   // demanem memoria per cada disk, incloent els 16Mb per les dades
  for (i = 0; i < max_xrd; i++) {
      xrd_array[i] = xrd_alloc(i);
      if (xrd_array[i]==NULL) break;
      printk(KERN_DEBUG "After xrd_alloc memory %p\n", xrd_array[i]->disk_memory);
  }
  if (i>=max_xrd) { // no error in previous loop, allocation succeeded
     for (i = 0; i < max_xrd; i++) {
         // afegim el disc a la infrastructura de discos del sistema
        printk(KERN_DEBUG "adding_disk %d\n", i);
        add_disk(xrd_array[i]->xrd_disk);
        printk(KERN_DEBUG "added_disk %d\n", i);
     }
      // enregistrem el rang de minor numbers, com a que pertanyen a aquest dev
     printk(KERN_DEBUG "region range %ld\n", range);
     blk_register_region(MKDEV(XRD_MAJOR, 0), range,
                         THIS_MODULE, xrd_probe, NULL, NULL);
     printk(KERN_DEBUG "region added\n");
  }
  else {     // error
     for (--i; i>=0; i--) {
        xrd_free(xrd_array[i]);
     }
     unregister_blkdev(XRD_MAJOR, "xrd");
     res = -ENOMEM;
  }
  printk (KERN_DEBUG "init returns %d\n", res);
  return res;
}


/***************************************************************************/
/****************** Funcio de finalitzacio del modul ***********************/
/*                        NO l'heu de canviar                              */

static void myblk_exit(void) 
{
  int i;
  printk(KERN_DEBUG "Bye, ...\n");

   // alliberem els discos en ordre
  for (i=0; i < max_xrd; i++) {
     printk(KERN_DEBUG "xrdisk %d\n", i);
     del_gendisk(xrd_array[i]->xrd_disk);
     printk(KERN_DEBUG "free xrdisk %d\n", i);
     xrd_free(xrd_array[i]);
  }
  printk(KERN_DEBUG "Freeing region range %ld\n", range);
  blk_unregister_region(MKDEV(XRD_MAJOR, 0),range);
  printk(KERN_DEBUG "Freeing blkdev\n");
  unregister_blkdev(XRD_MAJOR, "xrd");
  printk(KERN_DEBUG "Bye, cruel world\n");
}

module_init(myblk_init);
module_exit(myblk_exit);
