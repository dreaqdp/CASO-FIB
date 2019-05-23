#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 10000

int main(int argc, char * argv [])
{
   int res;
   int * wstatus;
   long long *p;
   struct timespec ts0, ts1;
   double secs, secs2;

   if (argc !=  1) {
      fprintf(stderr, "Us: %s, inc\n", argv[0]);
      exit(1);
   }
   /* Fake call to warm-up */
   res = fork();
   if (res==0) exit(1);
   while (waitpid(-1,wstatus, 0) <= 0);

   double totalsecs = 0.0;
   for (int k=0;k<N;++k) {
	
   res = clock_gettime(CLOCK_REALTIME, &ts0);
   if (res < 0) { 
      perror ("clock_gettime");
   }
   res = fork();
   if (res==0) exit(1);
   if (res<0){
   	printf("fork/waitpid return -1\n");
	exit(1);
   }
   while (waitpid(-1,wstatus, 0) <= 0);
   res = clock_gettime(CLOCK_REALTIME, &ts1);
   if (res < 0) {
      perror ("clock_gettime");
   }

   ts1.tv_sec -= ts0.tv_sec;
   ts0.tv_sec = 0;

   // correct formula!!
   secs = (((double)ts1.tv_sec*1000000000.0 + (double)ts1.tv_nsec) - 
          ((double)ts0.tv_sec*1000000000.0 + (double)ts0.tv_nsec))/1000000000.0;
   // comprovar overflow nanosegons
/*   if (ts1.tv_nsec-ts0.tv_nsec < 0){
   	printf("ns overflow\n");
	exit(1);
   }*/
   totalsecs += secs;
   //printf (" secs   %.24lf s. \n", secs);
   }
   printf (" mean secs   %.24lf s. \n", totalsecs/N);
}
