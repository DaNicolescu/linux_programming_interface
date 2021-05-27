#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

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

int copy_file(char *input_file_name, char *output_file_name)
{
    int input_fd, output_fd;
    int input_file_flags = O_RDONLY;
    int output_file_flags = O_WRONLY | O_CREAT | O_TRUNC;
    char buffer[BUFSIZ];
    ssize_t num_bytes_read;
    size_t bytes_to_write;
    size_t empty_space;
    size_t i;
    int buffer_start;
    int ret;
    off_t lseek_ret;

    input_fd = open(input_file_name, input_file_flags);

    if (input_fd < 0)
    {
        perror("input file open");

        return 1;
    }

    output_fd = open(output_file_name, output_file_flags,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);

    if (output_fd < 0)
    {
        perror("output file open");

        return 1;
    }

    while (1)
    {
        num_bytes_read = read(input_fd, buffer, BUFSIZ);

        if (num_bytes_read < 0)
        {
            perror("read");

            return 1;
        }
        else if (num_bytes_read == 0)
        {
            break;
        }

        bytes_to_write = 0;
        buffer_start = -1;
        empty_space = 0;
        for (i = 0; i < num_bytes_read; i++)
        {
            if (buffer[i] != '\0')
            {
                if (buffer_start < 0)
                    buffer_start = i;

                ++bytes_to_write;

                if (empty_space > 0)
                {
                    lseek_ret = lseek(output_fd, empty_space, SEEK_CUR);

                    if (lseek_ret == -1)
                    {
                        perror("lseek");

                        return 1;
                    }

                    empty_space = 0;
                }
            }
            else
            {
                if (bytes_to_write > 0)
                {
                    ret = write_data(output_fd, buffer + buffer_start,
                                     bytes_to_write);

                    if (ret)
                        return 1;

                    bytes_to_write = 0;
                    buffer_start = -1;
                }

                ++empty_space;
            }
        }

        if (bytes_to_write > 0)
        {
            ret = write_data(output_fd, buffer + buffer_start, bytes_to_write);

            if (ret)
                return 1;
        }

        if (empty_space > 0)
        {
            lseek_ret = lseek(output_fd, empty_space, SEEK_CUR);

            if (lseek_ret == -1)
            {
                perror("lseek");

                return 1;
            }

            empty_space = 0;
         }
    }

    if ((close(input_fd) != 0) || (close(output_fd) != 0))
    {
        perror("close");

        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    char *input_file_name = NULL;
    char *output_file_name = NULL;

    if (argc < 3)
    {
        printf("Not enough arguments\n");

        return 1;
    }

    input_file_name = argv[1];
    output_file_name = argv[2];

    copy_file(input_file_name, output_file_name);

    return 0;
}
