#define SECTOR_SHIFT            9
#define SECTOR_SIZE             (1 << SECTOR_SHIFT)
#define PAGE_SECTORS_SHIFT      (PAGE_SHIFT - SECTOR_SHIFT)
#define PAGE_SECTORS            (1 << PAGE_SECTORS_SHIFT)


#define XRD_MAJOR 240
#define XRD_SIZE  16384
#define DEBUG 0

// Estructura que defineix el nostre disc
struct xrd_struct {
   int                     xrd_num;        // numero del disc, 0, 1...
   struct request_queue  * xrd_queue;      // cua de peticions
   int                     major;          // numero major
   int                     first_minor;    // primer minor per aquest disc
   struct gendisk        * xrd_disk;       // punter a un disc generic
   char                  * disk_memory;    // punter a les dades del disc
   size_t		   size;           // mida total de les dades del disc
};

extern int xrd_size;



