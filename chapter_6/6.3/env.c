#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int my_unsetenv(const char *name)
{
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

int main(int argc, char *argv[])
{
    display_environ();

    return 0;
}
