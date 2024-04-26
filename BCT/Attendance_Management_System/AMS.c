#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>

typedef struct student {
    int roll;
    char name[25];
    char faculty[10];
    char sec[10];
    char ph[10];
    char attendance;
    char date[20];
} stu;

void add() {
    system("cls");

    stu s;
    FILE *fptr;

    printf("Enter RollNo:\n");
    scanf("%d", &s.roll);
    printf("Enter Name:\n");
    scanf("%s", s.name);
    printf("Enter faculty:\n");
    scanf("%s", s.faculty);
    printf("Enter Section\n");
    scanf("%s", s.sec);
    printf("Enter Phone_No:\n");
    scanf("%s", s.ph);

    fptr = fopen("record.txt", "a");
    if (fptr == NULL) {
        printf("File cannot be created!!!\n");
        return;
    }
    fprintf(fptr, "%d %s %s %s %s\n", s.roll, s.name, s.faculty, s.sec, s.ph);
    fclose(fptr);
    printf("Record Added Successfully.");
}

void display() {
    system("cls");

    stu s;
    FILE *fptr;

    fptr = fopen("record.txt", "r");
    if (fptr == NULL) {
        printf("File cannot be opened!!!\n");
        return;
    }

    printf("Displaying Records\n\n");
    printf("Roll_NO\t\t Name\t\t       FACULTY\t SECTION\t PHONE_NO\n\n");
    printf("---------------------------------------------------------------------------\n");

    while (fscanf(fptr, "%d %s %s %s %s", &s.roll, s.name, s.faculty, s.sec, s.ph) != EOF) {
        printf("%d\t\t%s\t\t%s\t   %s\t\t%s\n\n\n", s.roll, s.name, s.faculty, s.sec, s.ph);

    }
    fclose(fptr);
}

void search() {
    system ("cls");
    stu s;
    int roll, flag = 0;
    FILE *fptr;
    fptr = fopen("record.txt", "r+");
    if (fptr == NULL)
        printf("File cannot be open.\n");
    printf("\t\t\t\tEnter roll_no of student:");
    scanf("%d", &roll);

    while (fscanf(fptr, "%d %s %s %s %s", &s.roll, s.name, s.faculty, s.sec, s.ph) != EOF) {
        if (s.roll == roll) {
            flag = 1;
            printf("\n\n\tRecord Found.\n\n");
            printf("\tRoll_NO\t\t Name   \t     FACULTY      SECTION\t PHONE_NO\n");
            printf("\t---------------------------------------------------------------------------\n");
            printf("\t%d\t\t%s\t\t%s\t   %s\t\t%s\n\n", s.roll, s.name, s.faculty, s.sec, s.ph);
        }
    }
    if (flag == 0) {
        printf("Record not Found.\n");
    }
    fclose(fptr);
}

void delete() {
    stu s;
    system("cls");
    FILE *fp1, *fp2;
    int temp_roll, flag = 0;
    int del;
    fp1 = fopen("record.txt", "r");
    fp2 = fopen("tempo.txt", "w");
    if (fp1 == NULL) {
        printf("File cannot be opened.");
        return;
    }
    printf("Enter the roll no to delete the record of the student:");
    scanf("%d", &temp_roll);
    while (fscanf(fp1, "%d %s %s %s %s", &s.roll, s.name, s.faculty, s.sec, s.ph) != EOF) {
        if (temp_roll == s.roll)
            continue;
        else
            fprintf(fp2, "%d %s %s %s %s\n", s.roll, s.name, s.faculty, s.sec, s.ph);
    }
    printf("\nThe record of student of roll %d is deleted!", temp_roll);
    fclose(fp1);
    fclose(fp2);
    remove("record.txt");
    rename("tempo.txt", "record.txt");
}

void update() {
    stu s;
    system("cls");
    FILE *fptr, *temp_file;
    int temp_roll, flag = 0;
    int upd;
    fptr = fopen("record.txt", "r+");
    temp_file = fopen("temp.txt", "w");
    if (fptr == NULL) {
        printf("File cannot be opened.");
        return;
    }
    printf("Enter the roll no to update:");
    scanf("%d", &temp_roll);
    while (fscanf(fptr, "%d %s %s %s %s", &s.roll, s.name, s.faculty, s.sec, s.ph) != EOF) {
        if (temp_roll == s.roll) {
            flag = 1;
            start:
            printf("UPDATE");
            printf("\n\n\n\t\t\t\t\t ==> 1. Name\n\t\t\t\t\t ==> 2. Faculty\n\t\t\t\t\t ==> 3. Section\n\t\t\t\t\t ==> 4.Phone_No\n\t\t\t\t ==> 5.Update Next Data\n\t\t\t\t ==> 6.exit\n");
            scanf("%d", &upd);
            switch (upd) {
                case 1:
                    printf("\n\t\t\t\t\tEnter New Name:");
                    scanf("%s", s.name);
                    break;
                case 2:
                    printf("\n\t\t\t\t\tEnter New faculty:");
                    scanf("%s", s.faculty);
                    break;
                case 3:
                    printf("\n\t\t\t\t\tEnter New Section:");
                    scanf("%s", s.sec);
                    break;
                case 4:
                    printf("\n\t\t\t\t\tEnter New Phone_No:");
                    scanf("%s", s.ph);
                    break;
                case 5:
                    goto start;
                    break;
                default:
                    printf("INVALID ENTRY!!!");
                    break;
            }
            fprintf(temp_file, "%d %s %s %s %s\n", s.roll, s.name, s.faculty, s.sec, s.ph);
        } else {
            fprintf(temp_file, "%d %s %s %s %s\n", s.roll, s.name, s.faculty, s.sec, s.ph);
        }
    }
    if (flag == 0) {
        printf("Roll No not found.\n");
    }
    fclose(fptr);
    fclose(temp_file);
    remove("record.txt");
    rename("temp.txt", "record.txt");
}

void mark_attendance() {
    system("cls");
    stu students[100]; // Assuming a maximum of 100 students

    int totalAbsent, absentRolls[100], totalStudents = 0;
    FILE *fptr_record, *fptr_attendance;

    // Open record.txt for reading student records
    fptr_record = fopen("record.txt", "r");
    if (fptr_record == NULL) {
        printf("Error opening record file.\n");
        return;
    }

    // Read student records into an array
    while (fscanf(fptr_record, "%d %s %s %s %s", &students[totalStudents].roll, students[totalStudents].name, students[totalStudents].faculty, students[totalStudents].sec, students[totalStudents].ph) != EOF) {
        totalStudents++;
    }

    fclose(fptr_record);

    // Prompt for total number of absent students
    printf("\n\t\t\t\tEnter the total number of absent students: ");
    scanf("%d", &totalAbsent);

    // Prompt for absent students' roll numbers
    printf("Enter the roll numbers of absent students:\n");
    for (int i = 0; i < totalAbsent; i++) {
        printf("\n\t\tAbsent student %d: ", i + 1);
        scanf("%d", &absentRolls[i]);
    }

    // Open attendance.txt for writing attendance records
    fptr_attendance = fopen("attendance.txt", "a");
    if (fptr_attendance == NULL) {
        printf("Error opening attendance file.\n");
        return;
    }

    // Get today's date
    printf("\n\t\t\t\tEnter today's Date (DD/MM/YYYY): ");
    scanf("%s",students->date);

    // Write attendance records to the file
    fprintf(fptr_attendance, "Date:%s\n", students->date);


    for (int i = 0; i < totalStudents; i++) {
        // Check if current student is absent
        char attendance = 'P'; // Assume present
        for (int j = 0; j < totalAbsent; j++) {
            if (students[i].roll == absentRolls[j]) {
                attendance = 'A'; // Mark as absent
                break;
            }
        }
        fprintf(fptr_attendance, "%d %s %s %s %c\n", students[i].roll, students[i].name, students[i].faculty, students[i].sec, attendance);
    }

    fclose(fptr_attendance);

    printf("Attendance recorded successfully.\n");
}

void display_attendance() {
    FILE *file;
    stu students;
    char temp_date[20];
    file = fopen("attendance.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
   // fread(students.date,sizeof(students.roll),1,file);
   fscanf(file,"%s",&students.date);
   printf("%s\n",students.date);


    printf("Roll_NO\t\tName\t\t    FACULTY\t   SECTION\t\tAttendance\n");
    printf("------------------------------------------------------------------------------------\n");

     while(fscanf(file,"%d %s %s %s %c",&students.roll, students.name, students.faculty, students.sec, &students.attendance)!=EOF) {


     printf("%d\t\t%s\t\t%s\t\t%s\t\t%c\n", students.roll, students.name, students.faculty, students.sec, students.attendance);



    }


    fclose(file);
}




int main() {
   int choice;
    int choice1;
    int choice2;
    int choice3;
    char id_ad[]="admin";
    char pw_ad[]="admin";
    char id_tea[]="teacher";
    char pw_tea[]="teacher";

    char tempid_ad[100];
    char temppw_ad[100];
    char tempid_tea[100];
    char temppw_tea[100];

    char ch;

    system("cls");
    system("color 37");

    while(1) {
        start:
        printf("\n\n\n\t\t                                WELCOME TO    \n                       \n");
        printf("\t                               Attendnace Management SYSTEM             \n\n\n");

        printf("\t\t\t\t\t ==> 1. Login as Admin\n\n\n\t\t\t\t\t ==> 2. Login as Teacher\n\n\n\t\t\t\t\t ==> 3. Exit\n\n");

        scanf("%d",&choice);

        switch (choice) {
            case 1:
                printf("Enter id\n");
                scanf("%s",tempid_ad);
                int i=0;
                printf("Enter password\n");
                while ((ch=_getch())!= 13)
                {
                    temppw_ad[i]=ch;
                    i++;
                    printf("*");
                }
                temppw_ad[i]='\0';
        if (strcmp(tempid_ad, id_ad) == 0 && strcmp(temppw_ad, pw_ad) == 0) {

                while(1)
                {



                            // system("cls");
                            printf("\n\n\n\t\t\t\t\t Logged in as admin\n");
                            printf("\n\n\n\t\t\t\t\t ==> 1. Add data\n\t\t\t\t\t ==> 2. Display data\n\t\t\t\t\t ==> 3. Search data\n\t\t\t\t\t ==> 4. Update data\n\t\t\t\t\t ==> 5. Delete data\n\t\t\t\t\t ==> 6. Go back\n");
                            scanf("%d",&choice1);
                            switch (choice1)
                            {
                                case 1:
                                    add();
                                    break;
                                case 2:
                                    display();
                                    break;
                                case 3:
                                    search();
                                    break;
                                case 4:
                                    update();
                                    break;
                                case 5:
                                    delete();
                                    break;
                                case 6:
                                    goto start;
                                default:
                                    printf("Invalid input !!! Please enter correction choice !!!");
                                    break;
                            }

                        }


                }
                 else{
                        printf("\n\nEnter correct id or password");
                    }
                break;


            case 2:

                printf("Enter id\n");
                scanf("%s",tempid_tea);
                i=0;
                printf("Enter password\n");
                while ((ch=_getch())!= 13)
                {
                    temppw_tea[i]=ch;
                    i++;
                    printf("*");
                }
                temppw_tea[i]='\0';


                    if (strcmp(tempid_tea,id_tea)==0 && strcmp(temppw_tea,pw_tea)==0){

                while(1)
                {




                            printf("\n\n\n\t\t\t\t\t Logged in as Teacher\n");
                            printf("\n\n\n\t\t\t\t\t ==> 1. Mark Attendance\n\t\t\t\t\t ==> 2. Display Attendance\n\t\t\t\t\t  ==> 3. Go back\n");
                            scanf("%d",&choice2);
                            switch (choice2)
                            {
                                case 1:
                                    mark_attendance();
                                    break;
                                case 2:
                                   display_attendance();
                                    break;
                                case 3:
                                    goto start;
                                    break;

                                default:
                                    printf("Invalid input !!! Please enter correction choice !!!");
                                    break;
                            }


                    }

                }
                else{
                        printf("\n\nEnter correct id or password");
                    }
                break;
            case 3:
                 exit(0);
                break;

            default:
                printf("Invalid input !!! Please enter correction choice !!!");
                break;
        }
    }
    return 0;
}


