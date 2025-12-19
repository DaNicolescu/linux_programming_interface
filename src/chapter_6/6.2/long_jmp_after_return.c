#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void dummy_function()
{
    printf("entered dummy function\n");
}

static void unnested_function()
{
    int a = 50;

    printf("entered unnested function, calling setjmp\n");

    switch (setjmp(env))
    {
    case 0:
        printf("initial call of setjmp\n");
        printf("a = %d\n", a);

        break;
    case 1:
        printf("jumped back to unnested_func\n");
        printf("a = %d\n", a);

        break;
    }
}

static void f2()
{
    longjmp(env, 1);
}

static void f1()
{
    f2();
}

int main(int argc, char *argv[])
{
    unnested_function();
    dummy_function();

    // try to jump back to unnested_function after it has returned
    // a will change its value to garbage
    f1();

    return 0;
}
