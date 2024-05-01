#include<stdio.h>
#include <stdlib.h>
#include <string.h>
// Define a structure for Medicine
struct Medicine {
    char name[50];
    int stockLevel;
    char manufactureDate[20];
    char expiryDate[20];
};

// Function prototypes
void addMedicine(FILE *file);
void displayMedicine(FILE *file);
void updateMedicine(FILE *file);
int menu();
int pharmacy_management();
