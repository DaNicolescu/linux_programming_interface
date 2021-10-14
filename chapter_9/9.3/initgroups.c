#include <stdio.h>
#include <string.h>
#include <grp.h>
#include <limits.h>

int my_initgroups(const char *user, gid_t group)
{
    struct group *grp;
    size_t list_size = 0;
    gid_t groups_list[NGROUPS_MAX + 1];
    char already_added = 0;
    int ret;

    while ((grp = getgrent()) != NULL) {
        size_t i = 0;
        printf("group name: %s\n", grp->gr_name);

        while (grp->gr_mem[i]) {
            printf("crt user: %s\n", grp->gr_mem[i]);
            if (!strcmp(user, grp->gr_mem[i])) {
                printf("match\n");

                if (list_size >= NGROUPS_MAX + 1)
                    return -1;

                groups_list[list_size] = grp->gr_gid;
                list_size++;

                if (grp->gr_gid == group)
                    already_added = 1;

                break;
            }

            i++;
        }
    }

    endgrent();

    if (!already_added) {
        if (list_size < NGROUPS_MAX + 1) {
            groups_list[list_size] = group;
            list_size++;
        } else {
            return -1;
        }
    }

    ret = setgroups(list_size, groups_list);

    if (ret == -1)
        return -1;

    return 0;
}

int main()
{
    printf("ret: %d\n", my_initgroups("test_usr", 138));
}
