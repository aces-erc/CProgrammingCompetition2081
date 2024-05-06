#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "vcs.h"

struct user
{
    char name[30];
    char username[15];
    char password[50];
    char sec_qstn[100];
    char ans[30];
    char uid[17];
};

struct repos
{
    char uid[17];
    char name[50];
    int rid;
    char id[17];
    int initialized;
    char fpath[250];
};

int main()
{
    struct user u;
    struct repos r;
    int rid;
    system("cls");
    printf("\033[44m");
    printf("\033[0;36m");
    load();
    verify_auth(&u);
    while (1)
    {
        repo(u, &r);
        comm(&r);
    }
    printf("\033[0m");
    return 0;
}
