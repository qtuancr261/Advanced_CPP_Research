#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


int genRandomBytesInSecure(void *buf, size_t len) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
	printf("Open /dev/urandom failed");
	return -1;
    }
    printf("Open /dev/urandom as fd: %d \n", fd);
    read(fd, buf, len);
    printf("Ran bytes: %s", (char*)buf);
    close(fd);
    return 0;
}

int main() {
    char array[10];
    genRandomBytesInSecure(array, 9);
    return 0;
}
