#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OFFSET_VALUE 10

int main(int argc, char *argv[])
{
    int new_fd = -1;
    int fd;
    int dup_fd;
    int open_flags = O_RDWR | O_CREAT;
    int ret;
    off_t fd_offset;
    off_t dup_fd_offset;
    int fd_flags;
    int dup_fd_flags;


    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s filename\n", argv[0]);

        return 1;
    }

    fd = open(argv[1], open_flags,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        perror("open");

        return 1;
    }

    dup_fd = dup(fd);

    if (fd == -1)
    {
        perror("dup");

        return 1;
    }

    // check that they share the same file offset

    // change offset of using fd
    fd_offset = lseek(fd, OFFSET_VALUE, SEEK_SET);

    // get the offset using dup_fd
    dup_fd_offset = lseek(dup_fd, 0, SEEK_CUR);

    if (fd_offset == dup_fd_offset)
        printf("file offsets are the same\n");
    else
        printf("file offsets are not the same\n");

    // check that they share the same file flags
    fd_flags = fcntl(fd, F_GETFD);
    dup_fd_flags = fcntl(dup_fd, F_GETFD);

    if (fd_flags == dup_fd_flags)
        printf("file flags are the same\n");
    else
        printf("file flags are not the same\n");

    close(fd);
    close(dup_fd);

    return ret;
}
