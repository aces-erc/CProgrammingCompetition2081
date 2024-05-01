#include<stdio.h>

int num;
#define size 100

FILE *user;

int log_data;
typedef struct
{
    char name[30];
    char username[20];
    char email[50];
    char password[20];
}pas;
int account();
int login(pas p[]);
int create(pas p[]);

