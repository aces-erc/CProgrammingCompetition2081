#include"patient.h"

int add_patient_record(pr pat[]) {
    system("cls");
    printf("NOTE: Input patient name in firstname_lastname format \n\t Input Diagnosed disesase in same format\n\n");
    printf("Enter the Patient Details:\n");
    printf("Enter patient ID:");
    scanf(" %s", pat[pat_data].pat_id);
    printf("Enter patient name:");
    scanf(" %s", pat[pat_data].pat_name);
    printf("Enter patient age:");
    scanf("%d", &pat[pat_data].pat_age);
    printf("Enter patient sex:\n  M for male\n  F for female\n......");
    scanf(" %c", &pat[pat_data].sex);

    // Validate patient sex input
    if (pat[pat_data].sex == 'm' || pat[pat_data].sex == 'M' || pat[pat_data].sex == 'F' || pat[pat_data].sex == 'f') {
        printf("Enter patient blood group:");
        scanf(" %s", pat[pat_data].blood_grp);
        printf("Enter the patient address:");
        scanf(" %s", pat[pat_data].address);
        printf("Enter the patient phone number:");
        scanf(" %s", pat[pat_data].phone_no);
        printf("Enter the patient disease:");
        scanf(" %s", pat[pat_data].disease);
        printf("Patient Status:\n 0 for discharged\n 1 for O.P.D\n 2 for Emergency\n.....");
        scanf("%d", &pat[pat_data].status);
        printf("Enter the patient date of admitted[dd/mm/yy]: ");
        scanf(" %s", pat[pat_data].admitted_date);

        // Open files for appending
        patient = fopen("Patient_Record.txt", "a+");
        record = fopen("record.txt", "a");
        if (patient == NULL || record == NULL) {
            printf("Error opening file!\n");
            return 0;
        }

        // Write patient record to both files
        fprintf(patient, "%-10s %-20s %-3d %-5c %-15s %-10s %-5s  %-15s %-4d %-10s\n",
        pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
        pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
        pat[pat_data].blood_grp,  pat[pat_data].disease,
        pat[pat_data].status, pat[pat_data].admitted_date);

        fprintf(record, "%-10s %-20s %-3d %-5c %-15s %-10s %-5s  %-15s %-4d %-10s\n",
        pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
        pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
        pat[pat_data].blood_grp,  pat[pat_data].disease,
        pat[pat_data].status, pat[pat_data].admitted_date);


        fclose(record);
        fclose(patient);

        printf("Patient record added successfully\n");
        pat_data++; // Increment pat_data counter
    } else {
        printf("Wrong input..\n");
        // Consider removing getch() for better portability
        getch();
    }
    // Consider removing getch() for better portability
    getch();
    return 0;
}



int display_patient_record(pr pat[]) {
    FILE *patient; // Declare a file pointer
    int pat_data = 0; // Initialize pat_data counter

    // Open the file for reading
    patient = fopen("Patient_record.txt", "r");
    if (patient != NULL) {
        printf("The Patient Records Are:\n");
        printf("Id\tName\t\t\tAge\tSex\tAddress\t\tPhone No\tBlood_grp\tDisease\t\tStatus\t Admitted Date\n");

        // Loop to read records from the file
        while (fscanf(patient, "%s %s %d %c %s %s %s %s %d %s",
               pat[pat_data].pat_id, pat[pat_data].pat_name, &pat[pat_data].pat_age,
               &pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
               pat[pat_data].blood_grp,  pat[pat_data].disease,
               &pat[pat_data].status, pat[pat_data].admitted_date) != EOF) {

            // Print the patient record
            printf("%s\t%s\t%d\t%c\t%s\t\t%s\t%s\t\t%s\t\t%d\t %s\n",
                   pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
                   pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
                   pat[pat_data].blood_grp, pat[pat_data].disease,
                   pat[pat_data].status, pat[pat_data].admitted_date);

            pat_data++; // Increment pat_data counter
        }

        fclose(patient); // Close the file
        getch(); // Pause the console output
    } else {
        printf("Failed to open the file.\n");
        getch(); // Pause the console output
    }
    return 0;
}





int search_patient_record(pr pat[]) {
    char id[20];int found = 0;
    printf("Enter the patient ID:");
    scanf("%s", id);
    printf("Id\t\tName\t\tAge\tSex\tAddress\t\tPhone No\tBlood_grp\tDisease\t\tStatus\tAdmitted Date\n");
    patient = fopen("Patient_Record.txt", "r");
    if (patient != NULL) {
        int pat_data = 0;
        while (fscanf(patient, "%s %s %d %c %s %s %s %s %d %s",
               pat[pat_data].pat_id, pat[pat_data].pat_name, &pat[pat_data].pat_age,
               &pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
               pat[pat_data].blood_grp, pat[pat_data].disease,
               &pat[pat_data].status, pat[pat_data].admitted_date) != EOF) {
            if (strcmp(pat[pat_data].pat_id, id) == 0) {
                printf("%s\t%s\t%3d\t%c\t%-12s\t%10s\t%-5s\t%-12s\t%d\t%s\n",
                       pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
                       pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
                       pat[pat_data].blood_grp, pat[pat_data].disease,
                       pat[pat_data].status, pat[pat_data].admitted_date);
                found = 1;
                break;
            }
            pat_data++;
        }
        if (!found) {
            printf("The patient record not found\n");
        }
        fclose(patient);
        getch();
    } else {
        printf("Failed to open the file.\n");
        getch();
    }
    return 0;
}
int edit_record(pr pat[],int index) {
    int choose;
    printf("1. Change the diagnosed disease\n2. Change the age\n3. Change the phone number\n");
    scanf("%d", &choose); // Corrected the format specifier
    switch(choose) {
        case 1:
            printf("Enter new diagnosed disease:");
            scanf("%s", pat[index].disease);
            break;
        case 2:
            printf("Enter New age:");
            scanf("%d", &pat[index].pat_age);
            break;
        case 3:
            printf("Enter the new phone number:");
            scanf("%s", pat[index].phone_no);
            break;
        default:
            printf("Error Input!!!!");
            return 0; // Return 0 indicating failed edit
    }
    return 1; // Return 1 indicating successful edit
}

int edit_patient_record(pr pat[]) {
    char id[20];
    int found = 0;
    FILE *temp_file; // Declare FILE pointer

    printf("Enter the patient ID:");
    scanf("%s", id);
    temp_file = fopen("Temporary.txt", "w"); // Open a temporary file for writing

    patient = fopen("Patient_Record.txt", "r");
    if (patient != NULL) {
        while (fscanf(patient, "%s %s %d %c %s %s %s %s %d %s",
                      pat[pat_data].pat_id, pat[pat_data].pat_name, &pat[pat_data].pat_age,
                      &pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
                      pat[pat_data].blood_grp, pat[pat_data].disease,
                      &pat[pat_data].status, pat[pat_data].admitted_date) != EOF) {
            if (strcmp(pat[pat_data].pat_id, id) == 0) {
                // Found the record to edit
                if (edit_record(pat,pat_data)) {
                    // If editing was successful, write the updated record to the temporary file
                    fprintf(temp_file, "%-10s %-20s %-3d %-5c %-15s %-10s %-5s  %-15s %-4d %-10s\n",
                            pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
                            pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
                            pat[pat_data].blood_grp, pat[pat_data].disease,
                            pat[pat_data].status, pat[pat_data].admitted_date);
                    found = 1;
                }
            } else {
                // Write the unchanged record to the temporary file
                fprintf(temp_file, "%-10s %-20s %-3d %-5c %-15s %-10s %-5s  %-15s %-4d %-10s\n",
                        pat[pat_data].pat_id, pat[pat_data].pat_name, pat[pat_data].pat_age,
                        pat[pat_data].sex, pat[pat_data].address, pat[pat_data].phone_no,
                        pat[pat_data].blood_grp, pat[pat_data].disease,
                        pat[pat_data].status, pat[pat_data].admitted_date);
            }
        }
        fclose(patient); // Close the patient record file
        fclose(temp_file); // Close the temporary file

        // Rename the temporary file to replace the original file
        remove("Patient_Record.txt");
        rename("Temporary.txt", "Patient_Record.txt");

        if (found) {
            printf("Record Updated Successfully\n");
        } else {
            printf("The patient record was not found\n");
        }
    } else {
        printf("Failed to open the file.\n");
    }
    getch(); // Pause the console output
    return 0; // Return from function
}





int patient_management()
{
    pr pat[max];
    int choice;
    while (1) {
        homepage();
        printf("Welcome to patient record:\n Choose the following number to proceed.....\n");
        printf(" 1.Add Patient Record\n 2.Display Patient Record\n 3.Search Patient Record in database\n 4.Edit Patient Record \n 5.Main Menu\n ");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            add_patient_record(pat);
            break;
            case 2:
            display_patient_record(pat);
            break;
            case 3:
            search_patient_record(pat);
            break;
            case 4:
            edit_patient_record(pat);
            break;
            case 5:
            management_system();
            break;
            default:
            printf("Invalid Input....");
        }

    }
    return 0;
}
