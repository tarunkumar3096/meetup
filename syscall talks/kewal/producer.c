// Producer process
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>

#define SIZE 4096
#define NAME "shm_mem"

int main()
{
	int ret;
	int shm_fd;
	void* ptr;

	/* create the shared memory */
	shm_fd = shm_open(NAME, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (shm_fd == -1)
		error(1, errno, "failed to open shm");

	/* configure the size of the shared memory */
	ret = ftruncate(shm_fd, SIZE);
	if (ret == -1)
		error(1, errno, "failed to truncate");

	/* memory map the shared memory */
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED)
		error(1, errno, "failed to mmap");

	scanf("%[^\n]", (char *)ptr);

#if 0
	/* re-write in shared memory*/
	getchar();
	scanf("%[^\n]", (char *)ptr);
#endif

	return 0;
}


