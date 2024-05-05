#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define max 100
int pat_data;

FILE *patient;
FILE *record;

typedef struct patient_record{
    char pat_id[20];
    char pat_name[30];
    int pat_age;
    char sex;
    char address[50];
    char phone_no[15];
    char blood_grp[6];
    char disease[50];
    int status;
    char admitted_date[40];
}pr;
int patient_management();
int add_patient_record(pr pat[]);
int display_patient_record(pr pat[]);
int search_patient_record(pr pat[]);
int edit_patient_record(pr pat[]);
int edit_record(pr pat[],int index);
