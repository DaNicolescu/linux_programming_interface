#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>

struct passwd *my_getpwnam(const char *name)
{
    struct passwd *pwd = NULL;

    if (!name || strlen(name) == 0)
        return NULL;

    while ((pwd = getpwent()) != NULL)
    {
        if (!strcmp(pwd->pw_name, name))
            break;
    }

    endpwent();

    return pwd;
}

int main(int argc, char *argv[])
{
    struct passwd *pwd;

    if (argc != 2)
    {
        printf("%s name\n", argv[0]);

        return 1;
    }

    pwd = my_getpwnam(argv[1]);

    if (pwd)
    {
        printf("Found the name, UID=%ld\n", (long)pwd->pw_uid);

        return 0;
    }
    
    printf("Did not find the name\n");

    return 1;
}