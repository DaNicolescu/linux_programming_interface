#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int dup_func(int fd)
{
    int new_fd;

    new_fd = fcntl(fd, F_DUPFD, 0);

    printf("dup new fd = %d\n", new_fd);

    return new_fd;
}

int dup2_func(int old_fd, int new_fd)
{
    int fcntl_fd;

    if (old_fd == new_fd)
    {
        printf("dup2 new fd = %d\n", old_fd);

        return old_fd;
    }

    close(new_fd);
    fcntl_fd = fcntl(old_fd, F_DUPFD, new_fd);

    printf("dup2 new fd = %d\n", fcntl_fd);

    return fcntl_fd;
}

int main(int argc, char *argv[])
{
    int new_fd = -1;
    int fd;
    int flags = O_RDWR | O_CREAT;
    char append_flag = 1;
    long long num_bytes;
    int ret;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s filename [new_fd]\n", argv[0]);

        return 1;
    }

    fd = open(argv[1], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        perror("open");

        return 1;
    }

    if (argc == 3)
    {
        new_fd = atoi(argv[2]);

        ret = dup2_func(fd, new_fd);
    }
    else
    {
        ret = dup_func(fd);
    }

    close(fd);

    return ret;
}
