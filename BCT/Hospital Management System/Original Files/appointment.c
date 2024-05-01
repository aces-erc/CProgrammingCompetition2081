#include "appointment.h"

int appointment()
{
    //USING MAIN FUNTION TO ONLY CALL THE OTHER FUNCTIONS
    system("color 02");
    system("cls");
    app_display();
    app_choice();
    return 0;
}

void app_choice()
{
    //TO CHOSSE WHAT TO DO
    int app_choice;
    printf("---------------------------------------------\nEnter your choice\n---------------------------------------------\n--> ");
    scanf("%d", &app_choice);
    switch (app_choice)
    {
    case 1:
        new_app();
        break;
    case 2:
        cng_app();
        break;
    case 3:
        view_app();
        break;
    case 4:
        cancel_app();
        break;
    case 5:
        management_system();
            break;
    default:
        printf("Invalid choice\n");

        break;
    }
}

void app_display()
{
    //TO DISPLAY MAIN MENU
    printf("----------APPOINTMENT AND SCHEDULE------------\n");
    printf("1. Make a new appointment with the doctor.\n2. Change your appointment schedule.\n3. View your appointment details.\n4. Cancel an appointment.\n5. Exit to Main Menu\n");
}

void new_app()
{
    int i = 0, j = 1, choose;
    appnmt ap;
    // TO ADD NEW APPOINTMENTS OF PATIENTS
    printf("Enter the name of patient(NAME_LASTNAME): ");
    scanf("%s", ap.pat_name);
    printf("Enter the age of the patient: ");
    scanf("%d", &ap.pat_age);
    printf("Enter the address of patient: ");
    scanf("%s", ap.pat_address);
    printf("Enter the date for appointment(DD/MM/YY): ");
    scanf(" %s", ap.app_date);
    printf("Choose your appointment time (HH/MM): ");
    scanf(" %s", ap.app_time);

    FILE *appdet = fopen("realappn.txt", "a");//TO open new file to store data of new appointments
    if (appdet == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    fprintf(appdet, "%s\t%d\t%s\t   %s  \t   %s\n", ap.pat_name, ap.pat_age, ap.pat_address, ap.app_date, ap.app_time);
    fclose(appdet);

    printf("------------------------RECORDS SUCCESSFULLY ADDED--------------------------\n");
    while (i < j)//TO GO TO MAIN FUNCTION
    {
        printf("CLICK 1 TO GO MAIN MENU :\n");
        scanf("%d", &choose);
        if (choose == 1)
        {
            system("cls");
            main();
            i++;
        }
        else
        {
            printf("INVALID INPUT\n\n");
            i++;
            j++;
        }
    }
}

void cng_app() {
    int temp_age, i = 0, j = 1, choose1, b = 1;
    char temp_name[30], temp_address[30], temp_date[20], temp_time[20];
    appnmt ap;
    FILE *olddet;
    olddet = fopen("realappn.txt", "r");
    if (olddet == NULL) {
        printf("Failed to open file\n");
        return;
    }
     printf("\n\t\t\tPATIENT DETAILS TO CHANGE APPONTMENTS\n\n");//TO SHOW ADDED APPOINTMENTS
     printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-30s | %-13s | %-20s |\n", "SN", "Patient Name", "Patient Address", "Patient Age", "Date Appointed");
    printf("----------------------------------------------------------------------------------------------------------\n");

    while (fscanf(olddet, "%s %d %s %s %s", ap.pat_name, &ap.pat_age, ap.pat_address, ap.app_date, ap.app_time) != EOF) {
        printf("| %-3d | %-20s | %-30s | %-13d | %-20s |\n", b, ap.pat_name, ap.pat_address, ap.pat_age, ap.app_date);
        b++;
    }
     printf("----------------------------------------------------------------------------------------------------------\n");
    fclose(olddet);
    olddet = fopen("realappn.txt", "r+");
    if (olddet == NULL) {
        printf("Failed to open file\n");
        return;
    }
    
    
    printf("Enter the name of patient whose details you want to change: ");
    scanf("%s", temp_name);
    
    // Temporary file to store changed data
    FILE *tempfile = fopen("temp.txt", "w");
    if (tempfile == NULL) {
        printf("Failed to create temporary file\n");
        fclose(olddet);
        return;
    }

    // TO find the patient to edit using while
    while (fscanf(olddet, "%s %d %s %s %s ", ap.pat_name, &ap.pat_age, ap.pat_address, ap.app_date, ap.app_time) != EOF) {
        if (strcmp(ap.pat_name, temp_name) == 0) {
            printf("Enter new name of patient: ");
            scanf("%s", temp_name);
            printf("Enter new address of patient: ");
            scanf("%s", temp_address);
            printf("Enter new age of patient: ");
            scanf("%d", &temp_age);
            printf("Enter new date of appointment: ");
            scanf("%s", temp_date);
            printf("Enter new time for appointment: ");
            scanf("%s", temp_time);

            // to put changed data to temporary file
            fprintf(tempfile, "%s %d %s %s %s\n", temp_name, temp_age, temp_address, temp_date, temp_time);
            printf("SUCCESSFULLY CHANGED THE APPOINTMENT DETAILS\n");
        } else {
            // Write unchanged data to temporary file
            fprintf(tempfile, "%s %d %s %s %s\n", ap.pat_name, ap.pat_age, ap.pat_address, ap.app_date, ap.app_time);
        }
    }
    
    // Close both files
    fclose(olddet);
    fclose(tempfile);
//RENAME AND REMOVING FILES
    remove("realappn.txt");
    rename("temp.txt", "realappn.txt");


    while (i < j)//TO GO TO MAIN FUNCTION
    {
        printf("CLICK 1 TO GO MAIN MENU :\n");
        scanf("%d", &choose1);
        if (choose1 == 1)
        {
            system("cls");
            main();
            i++;
        }
        else
        {
            printf("INVALID INPUT\n\n");
            i++;
            j++;
        }
    }
}
void view_app()
{
    int i = 0, j = 1, choose2, a = 1;
    appnmt ap;
    FILE *olddet = fopen("realappn.txt", "r");//OPENING THE FILE WHERE DATA ARE STORED
    if (olddet == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    printf("\n\t\t\t\t\tPATIENT DETAILS\n\n");//TO VIEW THE DATAS
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-30s | %-13s | %-20s |\n", "SN", "Patient Name", "Patient Address", "Patient Age", "Date Appointed");
    printf("----------------------------------------------------------------------------------------------------------\n");
    
    while (fscanf(olddet, "%s %d %s %s %s", ap.pat_name, &ap.pat_age, ap.pat_address, ap.app_date, ap.app_time) != EOF) {
        printf("| %-3d | %-20s | %-30s | %-13d | %-20s |\n", a, ap.pat_name, ap.pat_address, ap.pat_age, ap.app_date);
        a++;
    }
    
    printf("----------------------------------------------------------------------------------------------------------\n\n");
    
    fclose(olddet);
    while (i < j)//TO GO TO MAIN FUNCTION
    {
        printf("CLICK 1 TO GO MAIN MENU :\n");
        scanf("%d", &choose2);
        if (choose2 == 1)
        {
            system("cls");
            main();
            i++;
        }
        else
        {
            printf("INVALID INPUT\n\n");
            i++;
            j++;
        }
    }
}

void cancel_app()
{
    appnmt ap;
    int choose3, i = 0, j = 1, c = 1;
    char tempname[20];

    FILE *olddet = fopen("realappn.txt", "r");
    if (olddet == NULL)
    {
        printf("Failed to open file\n");
        return;
    }
     printf("\n\t\t\tPATIENT DETAILS TO CANCEL APPONTMENTS\n\n");//TO SHOW THE PREVIOUS DATAS
     printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-30s | %-13s | %-20s |\n", "SN", "Patient Name", "Patient Address", "Patient Age", "Date Appointed");
    printf("----------------------------------------------------------------------------------------------------------\n");
    
    while (fscanf(olddet, "%s %d %s %s %s", ap.pat_name, &ap.pat_age, ap.pat_address, ap.app_date, ap.app_time) != EOF) {
        printf("| %-3d | %-20s | %-30s | %-13d | %-20s |\n", c, ap.pat_name, ap.pat_address, ap.pat_age, ap.app_date);
        c++;
    }
    printf("----------------------------------------------------------------------------------------------------------\n\n");
    fclose(olddet);
    FILE *mainfile, *tempfile;//CREATING TEMPORARY FILES TO STORED THE DATA OF APPOINTMENTS 
    mainfile = fopen("realappn.txt", "r");
    tempfile = fopen("tempdata.txt", "w");
    printf("Choose an appointment that you want to Cancel: \nEnter patient name: \n");
    scanf(" %s", tempname);
    while ((fscanf(mainfile, "%s %d %s   %s  %s  ", ap.pat_name, &ap.pat_age, ap.pat_address, ap.app_date, ap.app_time) != EOF))//READING THE FILES FROM FILE
    {
        if (strcmp(ap.pat_name, tempname) != 0) // to compare the name in the file with guven name
        {
            fprintf(tempfile, "%s %d %s   %s  %s\n", ap.pat_name, ap.pat_age, ap.pat_address, ap.app_date, ap.app_time);
        }
        else
        {
            printf(" %s appointment has been canceled\n", ap.pat_name);
        }

        printf("ERROR 404: Patient name not found\n");
    }
    fclose(mainfile);
    fclose(tempfile);
    remove("realappn.txt");                 // Remove the original appointment file
    rename("tempdata.txt", "realappn.txt"); // Rename the temporary file to replace the original one

    while (i < j)//TO GOTO MAIN FUNCTION    
    {
        printf("CLICK 1 TO GO MAIN MENU :\n");
        scanf("%d", &choose3);
        if (choose3 == 1)
        {
            system("cls");
            main();
            i++;
        }
        else
        {
            printf("INVALID INPUT\n\n");
            i++;
            j++;
        }
    }
}