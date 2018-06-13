#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 4096
#define NAME "shm_mem"
 
int main()
{
    int shm_fd;
    void* ptr;

    /* open the shared memory */
    shm_fd = shm_open(NAME, O_RDONLY, 0666);
	if (shm_fd == -1)
		error(1, errno, "failed to open shm");
 
    /* memory map the shared memory */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED)
		error(1, errno, "failed to mmap");

	printf("%s\n", (char*)ptr);

    /* remove the shared memory */
   shm_unlink(NAME);
    return 0;
}
