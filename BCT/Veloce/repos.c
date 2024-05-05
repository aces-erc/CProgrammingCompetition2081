#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h.>
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

struct user usr;
int openflag = 0;

int repo(struct user, struct repos *);
void create_repo();
void view_repos();
void open_repo();

void create_repo()
{
    system("cls");
    FILE *fptr;
    struct repos r;
    fptr = fopen("repos.dat", "ab+");
    if (fptr == NULL)
    {
        printf("An unexpected error occured");
        exit(0);
    }
    printf("Enter repository name:\n>>>\t");
    scanf(" %[^\n]", r.name);
    printf("Enter an id for your repository. Don't use same id on two repositories to avoid conflicts.\n>>>\t");
    scanf("%d", &r.rid);
    strcpy(r.uid, usr.uid);
    r.initialized = 0;
    random(r.id);
    if (fwrite(&r, sizeof(r), 1, fptr) == 1)
    {
        printf("\nRepository succesfully created!");
        fclose(fptr);
    }
    else
    {
        fclose(fptr);
        printf("\nFailed to create repository!");
    }
}

void view_repos()
{
    system("cls");

    FILE *fptr;
    struct repos r;
    fptr = fopen("repos.dat", "rb");
    if (fptr == NULL)
    {
        printf("An unexpected error occured");
        exit(0);
    }
    printf("List of all your repositories:\n");
    while (fread(&r, sizeof(r), 1, fptr) == 1)
    {
        if (strcmp(r.uid, usr.uid) == 0)
        {
            printf("%d\t%s\n", r.rid, r.name);
        }
    }
}
void open_repo(struct repos *rid)
{
    system("cls");
    FILE *fptr;
    struct repos r;
    int flag = 1;
    int temp_id;
    fptr = fopen("repos.dat", "rb");
    if (fptr == NULL)
    {
        printf("An unexpected error occured");
        exit(0);
    }
    printf("Enter the id of the repository you want to open: ");
    scanf(" %d", &temp_id);
    while (fread(&r, sizeof(r), 1, fptr) == 1)
    {
        if (temp_id == r.rid && strcmp(r.uid, usr.uid) == 0)
        {
            printf("Opening repository %s", r.name);
            *rid = r;
            flag = 0;
            openflag = 1;
            break;
        }
    }
    if (flag)
    {
        printf("Repository not found!");
    }
}

int repo(struct user u, struct repos *rid)
{
    int ch;
    usr = u;
    while (1)
    {
        system("cls");
        printf("--------------------------------------------------------------\n");
        printf("____    ____  _______  __        ______     ______  _______\n");
        printf("\\   \\  /   / |   ____||  |      /  __  \\   /      ||   ____|\n");
        printf(" \\   \\/   /  |  |__   |  |     |  |  |  | |  ,----'|  |__\n");
        printf("  \\      /   |   __|  |  |     |  |  |  | |  |     |   __|\n");
        printf("   \\    /    |  |____ |  `----.|  `--'  | |  `----.|  |____\n");
        printf("    \\__/     |_______||_______| \\______/   \\______||_______|\n");
        printf("--------------------------------------------------------------\n");
        printf("\nWelcome %s, how's it going?\n", u.name);
        printf("1) Create a repository\n2) View Repositories\n3) Open Repository\n4) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            create_repo();
            break;
        case 2:
            view_repos();
            break;
        case 3:
            open_repo(rid);
            break;
        case 4:
            exit(0);
        default:
            printf("Please enter a valid choice!");
            getch();
        }
        if (openflag)
        {
            break;
        }
        printf("\nPress any key to continue: ");
        getch();
    }
}