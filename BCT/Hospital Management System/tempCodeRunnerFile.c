#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "login.h"


int account() {
    pas p[size];
    int log;
    while (1) {
        system("cls");
        printf("-----------------------------------------------------\n");
        printf("WELCOME TO R.S.R.P. HOSPITAL\n");
        printf("-----------------------------------------------------\n");
        printf("\n\n\n");
        printf("1. LOGIN\n");
        printf("2. CREATE AN ACCOUNT\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &log);
        switch (log) {
            case 1:
                login(p);
                break;
            case 2:
                create(p);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("INVALID INPUT!!!!\n");
        }
    }
}