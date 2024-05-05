#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
typedef struct staff
{
    int staffid;
    char staffposition[30];
    long long int phoneno;
    char address[30];
    char firstname[30],lastname[30];
    float salary;
}staff;

int staff_management();
int staff_management();
void delete_record();
void update_record();
void display_record();
void add_record();