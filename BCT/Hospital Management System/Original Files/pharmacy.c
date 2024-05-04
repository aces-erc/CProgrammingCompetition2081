#include "pharmacy.h"

int pharmacy_management()
 {
    system("cls");
    FILE *file = fopen("medicine_data.dat", "ab+");//opens the file in append mode
    if (file == NULL) //checks if the file opening was right
    {
        printf("failed in opening file.\n");
        return 1;
    }

    int choice;
    do        //used of loop
    {
        choice = menu();
        switch (choice) {
            case 1:
                addMedicine(file);
                break;
            case 2:
                displayMedicine(file);
                break;
            case 3:
                updateMedicine(file);
                break;
            case 4:
                printf("Exiting.......press any key..\n");
                getch();
                management_system();
            break;
                break;
            default:
                printf("Invalid choice. \n");
        }
    } while (choice != 4);

    fclose(file);//closes the file once the program has finished using it
    return 0;
}

int menu() 
{
    int choice;
    system("cls");
    printf("\n***********Pharmacy Management System************\n");
    printf("1. Add Medicine\n");
    printf("2. Display Medicine\n");
    printf("3. Update Medicine\n");
    printf("4. Exit to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void addMedicine(FILE *file)//function defination for adding medicine
 {
    system("cls");
    struct Medicine m;
    printf("Enter medicine name: ");
    scanf("%s", m.name);
    printf("Enter stock level: ");
    scanf("%d", &m.stockLevel);
    printf("Enter manufacture date: ");
    scanf("%s", m.manufactureDate);
    printf("Enter expiry date: ");
    scanf("%s", m.expiryDate);

    fwrite(&m, sizeof(struct Medicine), 1, file);//function call to write a data to a file
    printf("Medicine is added successfully!\n");
}

void displayMedicine(FILE *file) 
{
    struct Medicine m;
    rewind(file);
    printf("\nMedicine List:\n");
    printf("--------------------------------------------------\n");
    printf("| %-20s | %-10s | %-12s | %-12s |\n", "Name", "Stock", "Manuf. Date", "Expiry Date");
    printf("--------------------------------------------------\n");
    while (fread(&m, sizeof(struct Medicine), 1, file)) {
        printf("| %-20s | %-10d | %-12s | %-12s |\n", m.name, m.stockLevel, m.manufactureDate, m.expiryDate);
    }
    printf("--------------------------------------------------\n");
}

void updateMedicine(FILE *file) 
{
    char searchName[50];
    printf("Enter the name of the medicine to update: ");
    scanf("%s", searchName);

    struct Medicine m;
    int found = 0;
    rewind(file);//rewind the file pointer to the begginning

    while (fread(&m, sizeof(struct Medicine), 1, file)) //function call to read data from a file
    {
        if (strcmp(m.name, searchName) == 0) //function compares the strings m.name and search name
        {
            found = 1;
            printf("Enter new stock level: ");
            scanf("%d", &m.stockLevel);
            printf("Enter new manufacture date: ");
            scanf("%s", m.manufactureDate);
            printf("Enter new expiry date: ");
            scanf("%s", m.expiryDate);
            fseek(file, -sizeof(struct Medicine), SEEK_CUR);//serves to move the file pointer backward by the size of one struct Medicine from its current position within the file.
            fwrite(&m, sizeof(struct Medicine), 1, file);
            printf("Medicine is updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Medicine is not found.\n");
    }
}


