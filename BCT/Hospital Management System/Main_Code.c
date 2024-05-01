#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "login.h"
#include "management/patient.h"
#include "management/staff.h"
#include "management/appointment.h"
#include "management/pharmacy.h"

int homepage();
int management_system();

int homepage() {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("WELCOME TO R.S.R.P. HOSPITAL\n");
    printf("-----------------------------------------------------\n");
    printf("\n\n\n");
}

int management_system() {
    int select=0;
    homepage();
    while(1) {
        printf(" 1.Patient Management\n 2.Staff Managemenet\n 3.Appointment And Scheduling\n 4.Pharmacy Management \n 5.Exit\n .......");
        scanf("%d",&select);
        switch(select) {
            case 1:
            {
                patient_management();
                break;
            }
            case 2:
            {
                staff_management();
                break;
            }
            case 3:
            {
                appointment();
                break;
            }
            case 4:
            {
                pharmacy_management();
                break;
            }
            case 5:
            {
                printf("\n\t\t\tThank you for using our service.. %c%c%c\n\n\n",1,1,1);
                exit(0);
            }
            default:
                printf("Input Error....!!!!\n");
        }
    }
}

int main() {
    system("color 02");
    pas p[size];
    int log;
    while (1) {
        homepage();
        printf("1. LOGIN\n");
        printf("2. CREATE AN ACCOUNT\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &log);
        switch (log) {
            case 1:
                if(login(p)) {
                    system("cls");
                    management_system();
                } else {
                    printf("INVALID USERNAME OR PASSWORD\n");
                }
                break;
            case 2:
                create(p);
                break;
            case 3:
                printf("Exiting...press any key to continue....\n");
                getch();
                exit(0);
            default:
                printf("INVALID INPUT!!!!\n");
        }
    }
}
