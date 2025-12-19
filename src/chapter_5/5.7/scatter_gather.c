#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

struct test_struct
{
    int first_arg;
    int second_arg;
};

struct iovec
{
    void *iov_base;
    size_t iov_len;
};

ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t total_bytes_read = 0;
    ssize_t buffer_offset;
    ssize_t bytes_to_be_read;
    ssize_t crt_bytes_read;

    for (int i = 0; i < iovcnt; i++)
    {
        bytes_to_be_read = iov[i].iov_len;
        buffer_offset = 0;

        while (1)
        {
            if (bytes_to_be_read == 0)
                break;

            crt_bytes_read = read(fd, iov[i].iov_base + buffer_offset,
                                  bytes_to_be_read);

            if (crt_bytes_read == -1)
            {
                perror("read");

                return crt_bytes_read;
            }
            else if (crt_bytes_read == 0)
            {
                return total_bytes_read;
            }

            bytes_to_be_read -= crt_bytes_read;
            buffer_offset += crt_bytes_read;
            total_bytes_read += crt_bytes_read;
        }
    }

    return total_bytes_read;
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t total_bytes_written = 0;
    ssize_t buffer_offset;
    ssize_t bytes_to_be_written;
    ssize_t crt_bytes_written;

    for (int i = 0; i < iovcnt; i++)
    {
        bytes_to_be_written = iov[i].iov_len;
        buffer_offset = 0;

        while (1)
        {
            if (bytes_to_be_written == 0)
                break;

            crt_bytes_written = write(fd, iov[i].iov_base + buffer_offset,
                                      bytes_to_be_written);

            if (crt_bytes_written == -1)
            {
                perror("read");

                return crt_bytes_written;
            }

            bytes_to_be_written -= crt_bytes_written;
            buffer_offset += crt_bytes_written;
            total_bytes_written += crt_bytes_written;
        }
    }

    return total_bytes_written;
}

int main(int argc, char *argv[])
{
    int fd;
    int open_flags = O_RDWR | O_CREAT;
    int ret = 0;
    struct iovec *iovec_arr;
    struct test_struct my_struct = {.first_arg = 1, .second_arg = 2};
    uint64_t my_variable = 5;
    char my_buffer[BUFSIZ];
    ssize_t read_res;
    ssize_t write_res;

    memset(my_buffer, 0, BUFSIZ);

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

    iovec_arr = malloc(3 * sizeof(struct iovec));

    if (!iovec_arr)
    {
        perror("malloc");

        return 1;
    }

    iovec_arr[0].iov_base = &my_struct;
    iovec_arr[0].iov_len = sizeof(struct test_struct);

    iovec_arr[1].iov_base = my_buffer;
    iovec_arr[1].iov_len = BUFSIZ;

    iovec_arr[2].iov_base = &my_variable;
    iovec_arr[2].iov_len = sizeof(uint64_t);

    write_res = writev(fd, iovec_arr, 3);

    ret = lseek(fd, SEEK_SET, 0);

    read_res = readv(fd, iovec_arr, 3);

    if (my_struct.first_arg == 1 && my_struct.second_arg == 2)
        printf("my struct copied successfully\n");
    else
        printf("my struct copied unsuccessfully\n");

    if (my_variable == 5)
        printf("my variable copied successfully\n");
    else
        printf("my variable copied unsuccessfully\n");

    close(fd);

    return ret;
}
