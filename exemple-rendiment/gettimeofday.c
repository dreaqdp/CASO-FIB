#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(int argc, char * argv [])
{
   int res;
   void *p;
   struct timeval tv0, tv1;
   double secs, secs2;
   int n = 2, i;
   int howmuch = 10; //499850;

   if (argc > 1) {
      fprintf(stderr, "Us: %s\n", argv[0]);
      exit(1);
   }

   /* Fake call to warm-up */
   res = gettimeofday(&tv0, NULL);
   if (res < 0) { 
      perror ("gettimeofday");
   }
   /* Fake call to warm-up */
   usleep(100);

   printf ("Reports errors when the \"secs2\" computation is different from\n"
           "the correct time in \"secs\"\n");

   for (;;) {

   printf ("Will sleep for %d microsecs per usleep\n", howmuch);

   res = gettimeofday(&tv0, NULL);
   if (res < 0) { 
      perror ("gettimeofday");
   }

   for (i=0; i < n; i++) {
      res = usleep(howmuch);
      if (res < 0) {
         perror ("sleep");
      }
   }

   res = gettimeofday(&tv1, NULL);
   if (res < 0) {
      perror ("gettimeofday");
   }

   // correct formula!!
   secs = (((double)tv1.tv_sec*1000000.0 + (double)tv1.tv_usec) - 
          ((double)tv0.tv_sec*1000000.0 + (double)tv0.tv_usec))/1000000.0;

   //// incorrect formula!!!!
   secs2 = (tv1.tv_sec - tv0.tv_sec) + ((tv1.tv_usec - tv0.tv_usec)/1000000.0);

   if (secs!=secs2) {
      printf ("  Error %.24lf\n      %.24lf!!!\n", secs, secs2);
      printf ("  tv0      %d      %d\n", tv0.tv_sec, tv0.tv_usec);
      printf ("  tv1      %d      %d\n", tv1.tv_sec, tv1.tv_usec);
      printf ("  diff     %d      %d\n", tv1.tv_sec - tv0.tv_sec, tv1.tv_usec - tv0.tv_usec);
   }
   if (tv1.tv_usec - tv0.tv_usec < 0) printf ("   Negative!!   %d     %d     %d\n", tv0.tv_usec, tv1.tv_usec, tv1.tv_usec - tv0.tv_usec);
   printf (" secs   %.8lf s. (%le s/sleep)\n", secs, secs / n );
   printf (" secs2  %.8lf s. (%le s/sleep)\n", secs2, secs2 / n );
   printf("\n");

   howmuch += 100300;
   }

}
