#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 10000

int create_sparse_file(char *file_name)
{
    char buffer[BUFFER_SIZE];
    int fd;
    int file_flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH;

    fd = open(file_name, file_flags, file_mode);

    if (fd < 0) {
        perror("open");

        return 1;
    }

    memset(buffer, 1, BUFFER_SIZE);

    write(fd, buffer, 5000);

    if (lseek(fd, 2000000, SEEK_CUR) == -1) {
        return 1;
    }

    write(fd, buffer, 10000);

    if (lseek(fd, 1000000, SEEK_CUR) == -1) {
        return 1;
    }

    write(fd, buffer, 20);

    if (lseek(fd, 5000000, SEEK_CUR) == -1) {
        return 1;
    }

    write(fd, buffer, 45);

    close(fd);

    return 0;
}

int main(int argc, char **argv)
{
    char *input_file = "sparse_file.txt";

    create_sparse_file(input_file);
}
