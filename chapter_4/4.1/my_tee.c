#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int read_data(char *file_name, int append_flag)
{
    int fd;
    int flags = O_WRONLY | O_CREAT;

    if (append_flag)
        flags |= O_APPEND;

    fd = open(file_name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP
              | S_IROTH);

    if (fd < 0)
    {
        perror("open");

        return 1;
    }

    if (close(fd) != 0)
    {
        perror("close");

        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int c;
    int append_flag = 0;
    char *file_name = NULL;

    if (argc < 2)
    {
        printf("Not enough arguments\n");

        return 1;
    }

    while ((c = getopt (argc, argv, "l:")) != -1)
    {
        switch (c)
        {
        case 'l':
            append_flag = 1;
            file_name = optarg;

            break;
        case '?':
            printf("Invalid flag\n");

            return 1;
        }
    }

    if (!append_flag)
        file_name = argv[1];

    read_data(file_name, append_flag);

    return 0;
}
