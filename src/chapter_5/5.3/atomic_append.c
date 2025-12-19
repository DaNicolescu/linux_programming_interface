#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SEEK_FILE 1
#define NO_SEEK_FILE 2

int write_data(int fd, long long num_bytes, char seek_end)
{
    char data = 'a';

    for (long long i = 0; i < num_bytes; i++)
    {
        if (seek_end == SEEK_FILE)
        {
            if (lseek(fd, 0, SEEK_END) == -1)
            {
                perror("lseek");

                return 1;
            }
        }

        if(write(fd, &data, 1) == -1)
        {
            perror("write");

            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int fd;
    int flags = O_WRONLY | O_CREAT;
    char append_flag = 1;
    long long num_bytes;
    int ret;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s filename num-bytes [x]\n", argv[0]);

        return 1;
    }

    num_bytes = atoll(argv[2]);

    if (argc == 4)
    {
        if (strcmp(argv[3], "x") == 0)
        {
            append_flag = 0;
        }
        else
        {
            printf("%s filename num-bytes [x]\n", argv[0]);

            return 1;
        }
    }
    else
    {
        flags |= O_APPEND;
    }

    fd = open(argv[1], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        perror("open");

        return 1;
    }

    if (append_flag)
        ret = write_data(fd, num_bytes, NO_SEEK_FILE);
    else
        ret = write_data(fd, num_bytes, SEEK_FILE);

    return ret;
}
