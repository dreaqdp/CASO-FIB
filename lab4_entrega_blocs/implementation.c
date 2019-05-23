#include <linux/blkdev.h>

#include <linux/kernel.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>

#include <linux/vmalloc.h>

#include "interface.h"

char * alloc_disk_memory(unsigned long size)
{
   char * p = NULL;

   // la vostra implementacio va aqui
   p = vmalloc(PAGE_ALIGN(size));
   if (p<0) {
   	printk("vmalloc unable to allocate memory, returned %d",(int)p);
	return p;
   }
   int i;
   for(i=0; i<PAGE_ALIGN(size); ++i) 
	   p[i]=i%256; //per comprovar que hem reservat correctament
   // fi de la vostra implementacio

   printk(KERN_DEBUG "alloc_disk_memory %ld address %p\n", size, p);
   // retorna el punter a la memoria del kernel per guardar les dades del disc
   return p;
}

void   free_disk_memory(char * disk_mem)
{
   // la vostra implementacio va aqui
   vfree(disk_mem);
   // fi de la vostra implementacio
   printk(KERN_DEBUG "free_disk_memory %p\n", disk_mem);
}


int xrd_getgeo(struct block_device * bdev, struct hd_geometry *geo)
{
   int res = -EIO;

   // la vostra implementacio va aqui
   struct xrd_struct * privdata = (struct xrd_struct *)bdev->bd_disk->private_data;
   size_t size = privdata->size;
   geo->heads=32;
   geo->sectors=128;
   geo->cylinders = size / geo->heads/geo->sectors/SECTOR_SIZE;
   geo->start=0;
   res = 0;
   // fi de la vostra implementacio

   // un resultat = 0 indica tot correcte
   printk (KERN_DEBUG "xrd_getgeo returns %d", res);
   return res;
}


int copy_from_xrd(void *dst, struct xrd_struct *xrd,
                        sector_t sector, size_t n)
{
   int res = -ENODEV;

   // la vostra implementacio va aqui
   memcpy(dst,xrd->disk_memory+sector*SECTOR_SIZE, n);
   res = 0;
   // fi de la vostra implementacio

   printk(KERN_DEBUG "copy_from_xrd retorna %d\n", res);
   // un resultat = 0 indica tot correcte
   return res;
}

int copy_to_xrd(struct xrd_struct *xrd, void *src,
                        sector_t sector, size_t n)
{
   int res = -ENODEV;
   
   // la vostra implementacio va aqui
   memcpy(xrd->disk_memory+sector*SECTOR_SIZE, src, n);
   res = 0;
   // fi de la vostra implementacio

  printk(KERN_DEBUG "copy_to_xrd retorna %d\n", res);
   // un resultat = 0 indica tot correcte
   return res;
}


