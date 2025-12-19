#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[])
{
    char *ptr[MAX_ALLOCS];
    int free_step;
    int free_min;
    int free_max;
    int block_size;
    int num_allocs;
    int j;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]);

        return 1;
    }

    num_allocs = atoi(argv[1]);

    if (num_allocs <= 0 || num_allocs > MAX_ALLOCS)
    {
        printf("invalid num-allocs (must be > 0 and < %d)\n", MAX_ALLOCS);

        return 1;
    }

    block_size = atoi(argv[2]);

    if (block_size <= 0)
    {
        printf("invalid block-size (must be > 0)\n");

        return 1;
    }

    free_step = (argc > 3) ? atoi(argv[3]) : 1;
    free_min = (argc > 4) ? atoi(argv[4]) : 1;
    free_max = (argc > 5) ? atoi(argv[5]) : num_allocs;

    if (free_step <= 0 || free_min <= 0 || free_max <= 0
        || free_min > free_max || free_max > num_allocs)
    {
        printf("invalid optional arguments\n");

        return 1;
    }

    printf("Initial program break: %10p\n", sbrk(0));
    printf("Allocating %d bytes %d number of times\n", block_size, num_allocs);

    for (j = 0; j < num_allocs; ++j)
    {
        ptr[j] = malloc(block_size);

        if (!ptr[j])
        {
            perror("malloc");

            return 2;
        }

        printf("program break: %10p\n", sbrk(0));
    }

    printf("Freeing blocks from %d to %d in steps of %d\n", free_min,
           free_max, free_step);

    for (j = free_min - 1; j < free_max; j += free_step)
        free(ptr[j]);

    printf("After free(), program break is: %10p\n", sbrk(0));

    return 0;
}
