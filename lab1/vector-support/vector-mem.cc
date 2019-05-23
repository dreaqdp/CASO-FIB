#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
 void init_vectors(float* a, float* b, float* c);
 void add_vectors( float * c, float * a, float * b );
 void mult_vectors( float * c, float * a, float * b );
};



const int N = 400000000;

void add_vectors( float * c, float * a, float * b )
{
int i;
for (i=0; i < N; i++) c[i] = a[i] + b[i];
}

void mult_vectors( float * c, float * a, float * b )
{
int i;
for (i=0; i < N; i++) c[i] = a[i] * b[i];
}


int main()
{

   float *__attribute__((aligned(128))) a, *__attribute__((aligned(128))) b, *__attribute__((aligned(128))) c;
   int res;

   res = posix_memalign((void **)&a, 128, N*sizeof(float));
   if (res != 0) { fprintf (stderr, "posix_memalign(a): %s\n", strerror(res)); exit(1); }
   res = posix_memalign((void **)&b, 128, N*sizeof(float));
   if (res != 0) { fprintf (stderr, "posix_memalign(b): %s\n", strerror(res)); exit(1); }
   res = posix_memalign((void **)&c, 128, N*sizeof(float));
   if (res != 0) { fprintf (stderr, "posix_memalign(c): %s\n", strerror(res)); exit(1); }
   init_vectors(a, b, c);

   add_vectors(c, a, b);

   mult_vectors(c, a ,b);

   return 0;
}

void init_vectors(float* a, float* b, float* c)
{
   int i;
   for (i=0; i < N; i++) a[i] = (float) i, b[i] = (float) (i+1), c[i] = 0.0;
}
