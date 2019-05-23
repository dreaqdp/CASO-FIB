#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include<errno.h>

#define N 2 

void error_exit(char* msg ) {
	printf("%s\n",msg);
	exit(1);
}


int main(int argc, char* argv[]) {
	int size, res;
	struct timespec ts0, ts1;
	double secs, secs2;

	if (argc != 3) 
		error_exit("Usage: file size.");

	/* Fake call to warm-up */
	res = clock_gettime(CLOCK_REALTIME, &ts0);
	if (res < 0) 
		error_exit ("clock_gettime");

	// fake call to warm-up
	int fd = open(argv[1], O_RDWR, S_IRWXU);
	char tmp;
	res = read(fd, &tmp, 1);
	if (res < 0) 
		error_exit("Read failed 0");
	res = close(fd);

	size = atoi(argv[2]);
	int block_size;
	int step = 1<<10;
	for (block_size=(1<<10); block_size<=10*step; block_size+=step){
		secs = 0.0;
		char buff[block_size];
		for (int j = 0; j < N; j++) {
			fd = open(argv[1], O_RDONLY, S_IRWXU);
			if (fd < 0)
				error_exit("Open failed");

			res = clock_gettime(CLOCK_REALTIME, &ts0);
			if (res < 0) { 
				error_exit ("clock_gettime");
			}
			while((res=read(fd,buff,block_size))>0) {
				tmp += buff[block_size-1];
			}
			if (res < 0) 
				error_exit("Read failed 2");

			system("sync");
			res = clock_gettime(CLOCK_REALTIME, &ts1);
			if (res < 0) 
				error_exit ("clock_gettime");

			res = close(fd);
			if (res < 0) 
				error_exit("close failed");

			secs += (((double)ts1.tv_sec*1000000000.0 + (double)ts1.tv_nsec) - 
					((double)ts0.tv_sec*1000000000.0 + (double)ts0.tv_nsec))/1000000000.0;

		}
		secs /= N;
		printf("%.24lf ", secs);
		printf("%.24lf\n", size/(secs*1000000));
	}
	printf("%c\n",tmp);
}
