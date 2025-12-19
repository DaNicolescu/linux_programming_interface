#include <stdio.h>
#include <stdlib.h>

char globBuf[65536]; // uninitialized data segment
int primes[] = {2, 3, 5, 7}; // initialized data segment

static int square(int x) // allocated only for function scope
{
    int result; // function scope

    result = x * x;
    return result;
}

static void doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000)
    {
        int t; // allocated in frame for doCalc

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main(int argc, char *argv[])
{
    static int key = 9973; // initialized data segment
    static char mbuf[10240000]; // uninitialized data segment
    // (mbuf will not occupy this actual big space in the executable)

    char *p;

    p = malloc(1024); // memory in heap segment

    doCalc(key);

    exit(EXIT_SUCCESS);
}

