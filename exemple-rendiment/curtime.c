#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char * argv [])
{
   int res;
   struct timeval tv0;
   time_t now;
   struct tm *nowtm;
   char tmbuf[64];

   if (argc > 1) {
      fprintf(stderr, "Us: %s\n", argv[0]);
      exit(1);
   }


   res = gettimeofday(&tv0, NULL);
   if (res < 0) { 
      perror ("gettimeofday");
   }

   printf ("ticks %lld\n", tv0.tv_sec * 1000000 + tv0.tv_usec);

   now = tv0.tv_sec;
   nowtm = localtime(&now);
   strftime(tmbuf, sizeof(tmbuf), "%A %B %d (%Y-%m-%d) %H:%M:%S", nowtm);
   printf ("%s.%06d\n", tmbuf, tv0.tv_usec);

}
