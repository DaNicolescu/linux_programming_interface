#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int create_sparse_file(char *file_name, uint64_t size)
{
    int fd;

    fd = open(path, O_RDWR | O_CREAT, 0666);

    if (fd == -1) {
        return -1;
    }
    if (lseek(fd, size - 1, SEEK_CUR) == -1) {
        return -1;
    }
    write(fd, "\0", 1);
    close(fd);
    return 0;
}

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
    int input_file_flags = O_WRONLY | O_CREAT | O_TRUNC;
    int output_file_flags = O_RDONLY;
    char buffer[BUFSIZ];
    ssize_t num_bytes_read;
    int ret;

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

    //    ret = write_data(STDOUT_FILENO, buffer, (size_t)num_bytes_read);

    //    if (ret)
    //        return 1;

    //    ret = write_data(fd, buffer, (size_t)num_bytes_read);

    //    if (ret)
    //        return 1;

    //}

    //if (close(fd) != 0)
    //{
    //    perror("close");

    //    return 1;
    //}

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
