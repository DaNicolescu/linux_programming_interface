#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s pathname\n", argv[0]);

        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_APPEND);

    if (fd == -1)
    {
        perror("open");

        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek");

        return 1;
    }

    if (write(fd, "test", 4) == -1)
    {
        perror("write");

        return 1;
    }

    return 0;
}
