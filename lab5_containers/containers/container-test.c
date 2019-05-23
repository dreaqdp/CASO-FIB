#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// this function seems not to be declared in Ubuntu
extern int clone (int (*__fn) (void *__arg), void *__child_stack,
                  int __flags, void *__arg, ...) __THROW;


char stack_area[65536] __attribute__((aligned(16)));
void * stack = &stack_area[60*1024];

int func(void * arg)
{
   // let parent to print values
   sleep (1);

   printf ("child: parent pid %d, child %d\n", getppid(), getpid());
   return 0;
}

int main()
{
   int pid, status, res;

printf (" -------------   fork test   --------------\n");

   pid = fork();
   if (pid < 0) perror ("fork");
   else if (pid==0) { func(0); return 0; }
   else {
      printf ("Parent: parent %d, child %d, waiting...\n", getpid(), pid);
      res = wait(&status);
      if (res < 0) {
         perror ("wait");
      }
   }
   printf ("Parent: finishing\n");


printf (" -------------  clone test   --------------\n");

   pid = clone(func, stack, CLONE_NEWCGROUP |
             CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | 
             CLONE_NEWUSER | CLONE_NEWUTS | SIGCHLD, 0);
   if (pid < 0) perror ("clone");
   else {
      printf ("Parent: parent %d, child %d, waiting...\n", getpid(), pid);
      res = wait(&status);
      if (res < 0) {
         perror ("wait");
      }
   }
   printf ("Parent: finishing\n");
   return 0;
}
