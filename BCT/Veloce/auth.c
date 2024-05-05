#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct user
{
    char name[30];
    char username[15];
    char password[50];
    char sec_qstn[100];
    char ans[30];
    char uid[17];
};

struct user *user_ptr;

void enter_password(char[]);
void login(struct user *);
void signup(struct user *);
void verify_auth(struct user *);
void reset_pwd();
char random_char(int);
void random(char[]);

char random_char(int index)
{
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return charset[index];
}

void random(char str[17])
{
    srand(time(NULL));
    int i, index;
    for (i = 0; i < 16; i++)
    {
        index = rand() % 62;
        str[i] = random_char(index);
    }
    str[i] = '\0';
}

void enter_password(char pwd[])
{
    char ch;
    int i = 0;

    while ((ch = getch()) != 13 && i < 50)
    {
        if (ch == '\b')
        {
            printf("\b \b");
            continue;
        }
        pwd[i++] = ch;
        printf("*");
    }

    pwd[i] = '\0';
}

void reset_pwd()
{
    system("cls");
    FILE *fptr;
    struct user u;
    fptr = fopen("user.dat", "rb+");
    if (fptr == NULL)
    {
        printf("An internal error occured!");
        exit(0);
    }
    int flag = 0;
    char username[15], answer[30], temp_pass[50], ch;
    printf("Enter your username:\n>>>\t");
    scanf("%s", username);
    while (fread(&u, sizeof(u), 1, fptr) == 1)
    {
        if (strcmp(username, u.username) == 0)
        {
            flag = 1;
            printf("%s\n>>>\t", u.sec_qstn);
            scanf("%s", answer);
            if (strcmp(answer, u.ans) == 0)
            {
                printf("Verification succesful\n");
                printf("Enter new password:\n>>>\t");
                enter_password(temp_pass);
                strcpy(u.password, temp_pass);
                fseek(fptr, -sizeof(u), SEEK_CUR);
                fwrite(&u, sizeof(u), 1, fptr);
                fclose(fptr);
                break;
            }
        }
    }
    fclose(fptr);
    if (!flag)
    {
        printf("No user found with given username.");

        getch();
    }
    verify_auth(user_ptr);
}

void login(struct user *usr)
{
    system("cls");
    int flag = 1, choice;
    FILE *fptr;
    struct user u;
    char uname[50];
    fptr = fopen("user.dat", "rb+");
    if (fptr == NULL)
    {
        printf("An internal error occured");
        exit(0);
    }
    char password[50];
    printf("Enter your username:\n>>>\t");
    scanf("%s", uname);
    printf("Password:\n>>>\t");
    enter_password(password);
    printf("\n");
    while (fread(&u, sizeof(u), 1, fptr) == 1)
    {
        if (strcmp(password, u.password) == 0 && strcmp(uname, u.username) == 0)
        {
            printf("Login Succesful\n");
            *usr = u;
            flag = 0;
            break;
        }
    }
    fclose(fptr);
    if (flag)
    {
        printf("Your credentials don't match any data in our database. Would you like to:\n1) Re-enter password\n2) Reset Password\n3) Back to main menu\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            login(usr);
            break;
        case 2:
            reset_pwd(usr);
            break;
        case 3:
            verify_auth(usr);
            break;
        default:
            login(usr);
            break;
        }
    }
}

void signup(struct user *usr)
{
    system("cls");
    FILE *fptr;
    fptr = fopen("user.dat", "ab+");
    struct user u;
    printf("Welcome to Veloce\n");
    printf("Create an accout to get started\n");
    printf("Enter your username:\n>>>\t");
    scanf(" %s", u.username);
    printf("Enter your password:\n>>>\t");
    enter_password(u.password);
    printf("\n");
    printf("Enter your name:\n>>>\t");
    scanf(" %[^\n]", u.name);
    printf("Enter a security question:\n>>>\t");
    scanf(" %[^\n]", u.sec_qstn);
    printf("Enter the answer(Make sure you don't forget it, it is the only way to reset your password):\n>>>\t");
    scanf(" %[^\n]", u.ans);
    random(u.uid);
    if (fwrite(&u, sizeof(u), 1, fptr) == 1)
    {
        fclose(fptr);
        printf("Creating user succesful");
        *usr = u;
    }
    else
    {
        fclose(fptr);
        printf("Failed to create user");
    }
}

void verify_auth(struct user *usr)
{
    user_ptr = usr;
    int ch;
    system("cls");
    printf("1) Login\n2) Signup\n3) Exit\n");
    printf("Please enter your choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        login(usr);
        break;
    case 2:
        signup(usr);
        break;
    case 3:
        exit(0);
    default:
        printf("Enter a valid choice");
        verify_auth(usr);
        break;
    }
}