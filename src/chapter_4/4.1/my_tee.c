#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int write_data(int fd, char *buffer, size_t n)
{
    size_t total_bytes_written = 0;
    size_t crt_bytes_written;

    while (total_bytes_written < n)
    {
        crt_bytes_written = write(fd, buffer + total_bytes_written,
                                  n - total_bytes_written);

        if (crt_bytes_written < 0)
        {
            perror("write");

            return 1;
        }

        total_bytes_written += (size_t) crt_bytes_written;
    }

    return 0;
}

int read_data(char *file_name, int append_flag)
{
    int fd;
    int flags = O_WRONLY | O_CREAT;
    char buffer[BUF_SIZE];
    ssize_t num_bytes_read;
    int ret;

    if (append_flag)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;

    fd = open(file_name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP
              | S_IROTH);

    if (fd < 0)
    {
        perror("open");

        return 1;
    }

    while (1)
    {
        num_bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE);

        if (num_bytes_read < 0)
        {
            perror("read");

            return 1;
        }
        else if (num_bytes_read == 0)
        {
            break;
        }

        ret = write_data(STDOUT_FILENO, buffer, (size_t)num_bytes_read);

        if (ret)
            return 1;

        ret = write_data(fd, buffer, (size_t)num_bytes_read);

        if (ret)
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

    while ((c = getopt (argc, argv, "a:")) != -1)
    {
        switch (c)
        {
        case 'a':
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
