#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int login()
{
    char *username;
    char *password;
    char *encrypted;
    char *p;
    struct passwd *pwd;
    struct spwd *spwd;
    size_t len;
    long lnmax;

    lnmax = sysconf(_SC_LOGIN_NAME_MAX);

    if (lnmax == -1)
        lnmax = 256;

    username = malloc(lnmax);

    if (!username)
    {
        perror("malloc");

        return 1;
    }

    printf("username: ");
    fflush(stdout);
    if (!fgets(username, lnmax, stdin))
    {
        printf("could not read username\n");

        return 1;
    }

    len = strlen(username);

    if (username[len - 1] == '\n')
        username[len - 1] = '\0';

    // get user from /etc/passwd
    pwd = getpwnam(username);

    if (!pwd)
    {
        printf("Could not retrieve password record\n");

        return 1;
    }

    // get user from /etc/shadow
    spwd = getspnam(username);

    if (!spwd && errno == EACCES)
    {
        perror("no permission to read shadow password file");

        return 1;
    }

    // if there is a shadow password recored, use it
    if (spwd)
        pwd->pw_passwd = spwd->sp_pwdp;
    
    password = getpass("Password: ");

    encrypted = crypt(password, pwd->pw_passwd);

    // immediately remove the unencrypted password from the memory
    for (p = password; *p != '\0'; ++p)
        *p = '\0';

    if (!encrypted)
    {
        perror("crypt");

        return 1;
    }

    if (!strcmp(encrypted, pwd->pw_passwd))
    {
        printf("Successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);
    }
    else
    {
        printf("Incorrect password\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    return login();
}
