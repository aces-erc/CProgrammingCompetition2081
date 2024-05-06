#include <stdio.h>
#include <stdlib.h>
struct patient
{
    int pnum;
    char name[50];
    char add[50];
    int age;
    int amt;
    int bill;
    int choice;
};
struct staff
{
    int id;
    char name[50];
    char address[50];
    int salary;
};
int n, data, s, result, i, j, data2;

// adding patient data

void addpatient(struct patient p[])
{
    FILE *fptr;
    fptr = fopen("C Project.txt", "w");
    if (fptr == NULL)
    {
        printf("file cannot opened");
        exit(0);
    }
    if (n > data)
    {
        printf("Enter the patient number,name,age and address of the patient.\n");
        scanf("%d%s%d%s", &p[data].pnum, p[data].name, &p[data].age, p[data].add);
        fprintf(fptr, "Patient Number:%d\tName:%s\t\tAge:%d\t\tAddress:%s\n", p[i].pnum, p[i].name, p[i].age, p[i].add);
        fclose(fptr);
        data++;
    }
    else
    {
        printf("You cannot add more data");
    }
}

// Making the bill of the patient

void makebill(struct patient p[])
{
    FILE *fptr;
    fptr = fopen("C Project.txt", "a");
    if (fptr == NULL)
    {
        printf("file cannot opened");
        exit(0);
    }
    if (data > 0)
    {
        static int i;
        int choice;
        int j = 201;
        printf("What do you want to do\n");

        // asking to the patient

        printf("1.Counselling to Doctor\n2.Labratory test\n3.Emergency Admit in the hospital\n");
        printf("Enter your choice\n");
        scanf("%d", &p[i].choice);
        if (p[i].choice == 1)
        {
            int j = 201;
            printf("Enter the fee for only conselling to the doctor:\n");
            scanf("%d", &p[i].amt);
            printf("Go to room number %d\n", j);
            printf("Doctor:Enter the days that patient should admit\n");

            // Doctor should enter the days.

            scanf("%d", &result);
        }
        else if (p[i].choice == 2)
        {
            printf("What do you want to do?\n");
            printf("1.Blood test\n2.Urine test\n.3.Video Xray\n4.Endoscopy\n5.Liver Function test\n6.All\n");
            printf("Enter your choice\n");
            scanf("%d", &choice);
            switch (choice)
            {
                printf("Go to room number %d", j + 1);
            case 1:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;

            case 2:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;
            case 3:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;
            case 4:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;
            case 5:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;
            case 6:
                printf("Enter the fee:\n");
                scanf("%d", &p[i].amt);
                break;
            default:
                printf("**Invalid choice**\n");
            }
        }
        else if (p[i].choice == 3)
        {
            printf("Go to the room number:%d\n", j + 2);
            printf("Enter the fee for emergency admitting the patient:\n");
            scanf("%d", &p[i].amt);
            printf("Doctor:Enter the days that patient should admit\n");

            // Doctor should enter the days.

            scanf("%d", &result);
            printf("If everything goes normal then for %d days\n", result);
        }
        else
        {
            printf("Invalid choice\n");
        }
        i++;
        fprintf(fptr, "room number: %d\n", j);
    }
    else
    {
        printf("***NO any patient details***\n");
        fprintf(fptr, "No input data");
    }
    fclose(fptr);
}

// Accepting the payment from the staff

void acceptfee(struct patient p[])
{
    static int i;
    if ((data > 0) && (p[i].amt > 0))
    {
        if (result > 0)
        {
            printf("You were admitted to the hospital for %d days\n", result);
            p[i].amt = p[i].amt + result * 5000;
            printf("Your bill is :%d\n", p[i].amt);
        }
        else
        {
            printf("Your bill is %d\n", p[i].amt);
        }
        do
        {
            // checking whether balance is suffcient or not.
            printf("Please do the payment\n");
            scanf("%d", &p[i].bill);
        } while (p[i].bill < p[i].amt);
        printf("\t***Your payment is accepted***\n");
        i++;
    }
    else
    {
        printf("***No patient details***\n");
    }
}

// Checking the details of the patient

void patientdetail(struct patient p[])
{
    int i;
    if (data > 0)
    {
        printf("The details of the patient are:\n");
        for (i = 0; i < data; i++)
        {
            printf("Patient Number:%d\tName:%s\t\tAge:%d\t\tAddress:%s\n", p[i].pnum, p[i].name, p[i].age, p[i].add);
        }
    }
    else
    {
        printf("***NO data***\n");
    }
}

// About the staff of the hospital

void addstaff(struct staff s1[])
{
    printf("Enter the id,name,address and salary of the staff\n");
    scanf("%d%s%s%d", &s1[data2].id, s1[data2].name, s1[data2].address, &s1[data2].salary);
    data2++;
}

// Updating the salary of the staff of the hospital.

void updatesal(struct staff s1[])
{
    FILE *fptr;
    fptr = fopen("C Project.txt", "a");
    if (fptr == NULL)
    {
        printf("file cannot opened");
        exit(0);
    }
    int num, j;
    printf("Enter the id number of the staff\n");
    scanf("%d", &num);
    for (j = 0; j < data2; j++)
    {
        if (s1[j].id == num)
        {
            s1[j].salary = s1[j].salary + 0.1 * s1[j].salary;
            printf("Salary updated by 10 percent");
            fprintf(fptr, "Updated salary:%d\n", s1[i].salary);
            break;
        }
    }
    fclose(fptr);
}

// Checking the details of the staff of the hospital.

void staffdetail(struct staff s1[])
{
    FILE *fptr;
    fptr = fopen("C Project.txt", "a");
    if (fptr == NULL)
    {
        printf("file cannot opened");
        exit(0);
    }
    int i;
    if (data2 > 0)
    {
        printf("The details of the Staff are:\n");
        for (i = 0; i < data2; i++)
        {
            printf("Id number:%d\tName:%s\tAddress:%s\tSalary:%d\n", s1[i].id, s1[i].name, s1[i].address, s1[i].salary);
            fprintf(fptr, "Id Number:%d\tName:%s\t\t\tAddress:%s\t\tSalary:%d\n", s1[i].id, s1[i].name, s1[i].address, s1[i].salary);
        }
    }
    else
    {
        printf("***NO data***\n");
        fprintf(fptr, "No staff of the data");
    }
    fclose(fptr);
}
int main()
{
    system("cls");
    int choice;
    printf("\tWelcome to the Hospital Management System\n\n");
    printf("Enter the number of the patient which you want to add\n");
    scanf("%d", &n);
    struct patient p[n];
    printf("Enter the number of the staffs\n");
    scanf("%d", &s);
    struct staff s[n];
    printf("You can do the following tasks\n");
    while (1)
    {
        system("cls");
        printf("1.Add patient\n2.Make the Bill\n3.Accept payment\n4.Add staff\n5.Update salary of the staff\n6.Check Patient details\n7.Check Staff details\n8.Exit the program\n\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addpatient(p);
            break;
        case 2:
            makebill(p);
            break;
        case 3:
            acceptfee(p);
            break;
        case 4:
            addstaff(s);
            break;
        case 5:
            updatesal(s);
            break;
        case 6:
            patientdetail(p);
            break;
        case 7:
            staffdetail(s);
            break;
        case 8:
            printf("Program is terminated");
            exit(0);
        deafult:
            printf("Choice invalid!!!");
        }
    }
    return 0;
}