#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int my_unsetenv(const char *name)
{
    char **env_ptr = environ;
    char **old_environ = environ;
    char **new_env_ptr;
    size_t name_len = strlen(name);
    size_t environ_size = 0;

    for (; *env_ptr != NULL; ++env_ptr)
    {
        if (!(!strncmp(name, *env_ptr, name_len)
            && (*env_ptr)[name_len] == '='))
            ++environ_size;
    }

    environ = malloc((environ_size + 1) * sizeof(char *));

    if (!environ)
    {
        environ = old_environ;

        return -1;
    }

    new_env_ptr = environ;
    env_ptr = old_environ;

    while (*env_ptr != NULL)
    {
        if (!strncmp(name, *env_ptr, name_len)
            && (*env_ptr)[name_len] == '=')
        {
            ++env_ptr;
        }
        else
        {
            *new_env_ptr = *env_ptr;

            ++env_ptr;
            ++new_env_ptr;
        }
    }

    *new_env_ptr = NULL;

    return 0;
}

int my_setenv(const char *name, const char *value, int overwrite)
{
    char *env_variable_value = getenv(name);
    char *new_env_variable;
    size_t new_env_variable_size;
    int ret;

    if (env_variable_value)
    {
        if (overwrite == 0)
            return 0;

        ret = my_unsetenv(name);

        if (ret != 0)
            return ret;
    }

    new_env_variable_size = strlen(name) + strlen(value) + 2;
    new_env_variable = malloc(new_env_variable_size);

    if (!new_env_variable)
        return -1;

    snprintf(new_env_variable, new_env_variable_size, "%s=%s", name, value);

    return putenv(new_env_variable);
}

void display_environ()
{
    char **env_ptr;

    for (env_ptr = environ; *env_ptr != NULL; env_ptr++)
        printf("%s\n", *env_ptr);
}

void usage(char *program_name)
{
    printf("usage:\n");
    printf("show environment variables: %s -s\n", program_name);
    printf("add environment variable (-o to overwrite):"
           " %s -a NAME VALUE [-o]\n", program_name);
    printf("delete environment variable: %s -d NAME\n", program_name);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);

        return 1;
    }

    if (!strcmp(argv[1], "-s"))
    {
        display_environ();
    }
    else if (!strcmp(argv[1], "-a"))
    {
        if (argc == 5)
        {
            if (!strcmp(argv[4], "-o"))
            {
                my_setenv(argv[2], argv[3], 1);
            }
            else
            {
                usage(argv[0]);

                return 1;
            }
        }
        else
        {
            my_setenv(argv[2], argv[3], 0);
        }

        display_environ();
    }
    else if (!strcmp(argv[1], "-d"))
    {
        my_unsetenv(argv[2]);
        display_environ();
    }
    else
    {
        usage(argv[0]);
    }

    return 1;
}
