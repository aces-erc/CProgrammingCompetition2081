#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a bank account
typedef struct BankAccount {
    int accountNumber , Age;
    char FirstName[50] , LastName[50] , Address[50] , FatherName[50], Gender[10] ,Trustee[50] , ContactNo[50] , Email[50];
    double balance;
}stb;

// Function prototypes
void createAccount(stb accounts[], int *numAccounts);
void deposit(stb accounts[], int numAccounts);
void withdraw(stb accounts[], int numAccounts);
void transferMoney(stb accounts[], int numAccounts);
void saveAccounts(stb accounts[], int numAccounts);
void loadAccounts(stb accounts[], int *numAccounts);
void deleteAccount(stb accounts[], int *numAccounts, int acc_to_del);
void displayAccountDetails(stb accounts[], int numAccounts, int accountNumber);
void creators();

// Main function
int main() {
    stb accounts[50];
    int numAccounts = 0;
    int choice;
    int accountNumber;

    // Load accounts from file
    loadAccounts(accounts, &numAccounts);

    do {
        // Display menu
        printf("\n    ***********************************\n");
        printf("    *          C-Bank Menu            *\n");
        printf("    ---------------------------------\n");
        printf("    * 1. Create Account               *\n");
        printf("    ---------------------------------\n");
        printf("    * 2. Deposit Money                *\n");
        printf("    ---------------------------------\n");
        printf("    * 3. Withdraw Money               *\n");
        printf("    ---------------------------------\n");
        printf("    * 4. Transfer Money               *\n");
        printf("    ---------------------------------\n");
        printf("    * 5. Account Details              *\n");
        printf("    ---------------------------------\n");
        printf("    * 6. Delete Account               *\n");
        printf("    ---------------------------------\n");
        printf("    * 7. Exit Menu                    *\n");
        printf("    ***********************************\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user choice
        switch (choice) {
            case 1:
                createAccount(accounts, &numAccounts);
                break;
            case 2:
                deposit(accounts, numAccounts);
                break;
            case 3:
                withdraw(accounts, numAccounts);
                break;
            case 4:
                transferMoney(accounts, numAccounts);
                break;

             case 5:
                printf("\nEnter account number: ");
                scanf("%d", &accountNumber);
                displayAccountDetails(accounts, numAccounts, accountNumber);
            break;

            case 6:
                printf("\nEnter Account Number To Delete\n");
                int acc_to_del;
                scanf("%d",&acc_to_del);
                deleteAccount (accounts,&numAccounts,acc_to_del);
            break;

            case 7:
                creators();
                // Save accounts to file before exiting
                saveAccounts(accounts, numAccounts);
                break;
            default:
                printf("\nInvalid choice.\n Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to create a new bank account
void createAccount(stb accounts[], int *numAccounts) {
    printf("\n   .................................\n");
    printf("   .      Creating New Account     .\n");
    printf("   .................................\n\n");
    printf("\n Enter Account Holder Details: \n\nFirst Name and Last Name : ");
    scanf("%s %s", accounts[*numAccounts].FirstName , accounts[*numAccounts].LastName );
    printf("Father Name : ");
    scanf("%s", accounts[*numAccounts].FatherName);
    printf("Adress : ");
    scanf("%s", accounts[*numAccounts].Address);
    printf("Gender : ");
    scanf("%s", accounts[*numAccounts].Gender);
    printf("Age : ");
    scanf("%d", &accounts[*numAccounts].Age);
    printf("Contact No : ");
    scanf("%d", &accounts[*numAccounts].ContactNo);
    printf("Email : ");
    scanf("%s", accounts[*numAccounts].Email);
    printf("Trustee Name : ");
    scanf("%s", accounts[*numAccounts].Trustee);

    accounts[*numAccounts].accountNumber = 10203004 + *numAccounts; // Generate account number
    accounts[*numAccounts].balance = 0.0;
    printf("Account created successfully! \nAccount number: %d\n", accounts[*numAccounts].accountNumber);
    (*numAccounts)++;
}

// Function to handle deposits
void deposit(stb  accounts[], int numAccounts) {
    int accountNumber, index;
    double amount;
    printf("\n   ...................................\n");
    printf("   .            Deposit              .\n");
    printf("   ...................................\n\n");
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (index = 0; index < numAccounts; index++) {
        if (accounts[index].accountNumber == accountNumber) {
            printf("Enter deposit amount: ");
            scanf("%lf", &amount);
            if (amount > 0) {
                accounts[index].balance += amount;
                printf("Deposit successful.\nCurrent balance: Rs %.2lf\n", accounts[index].balance);
            } else {
                printf("Invalid amount.\nPlease enter a positive value.\n");
            }
            return;
        }
    }
    printf("Account not found.\nPlease enter a valid account number.\n");
}

// Function to handle withdrawals
void withdraw(stb accounts[], int numAccounts) {
    int accountNumber, index;
    double amount;
    printf("\n   ...................................\n");
    printf("   .           Withdraw              .\n");
    printf("   ...................................\n\n");
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (index = 0; index < numAccounts; index++) {
        if (accounts[index].accountNumber == accountNumber) {
            printf("Enter withdrawal amount: ");
            scanf("%lf", &amount);
            if (amount > 0 && amount <= accounts[index].balance) {
                accounts[index].balance -= amount;
                printf("Withdrawal successful. \nCurrent balance: Rs %.2lf\n", accounts[index].balance);
            } else if (amount <= 0) {
                printf("Invalid amount.\nPlease enter a positive value.\n");
            } else {
                printf("Insufficient balance. \nWithdrawal not allowed.\n");
            }
            return;
        }
    }
    printf("Account not found.\nPlease enter a valid account number.\n");
}


// Function to transfer money from one account to another
void transferMoney(stb accounts[], int numAccounts) {
    int fromAccountNumber, toAccountNumber, fromIndex = -1, toIndex = -1;
    double amount;

    // Get the source account number
    printf("\n   ...................................\n");
    printf("   .         Transfer Money          .\n");
    printf("   ...................................\n\n");
    printf("Enter source account number: ");
    scanf("%d", &fromAccountNumber);

    // Find the source account
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == fromAccountNumber) {
            fromIndex = i;
            break;
        }
    }
    if (fromIndex == -1) {
        printf("Source account not found.\nPlease enter a valid account number.\n");
        return;
    }

    // Get the destination account number
    printf("Enter destination account number: ");
    scanf("%d", &toAccountNumber);

    // Find the destination account
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == toAccountNumber) {
            toIndex = i;
            break;
        }
    }
    if (toIndex == -1) {
        printf("Destination account not found. \nPlease enter a valid account number.\n");
        return;
    }

    // Get the amount to transfer
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    // Validate the amount and perform the transfer
    if (amount <= 0) {
        printf("Invalid amount.\nPlease enter a positive value.\n");
    } else if (accounts[fromIndex].balance < amount) {
        printf("Insufficient balance in the source account.\nTransfer not allowed.\n");
    } else {
        // Perform the transfer
        accounts[fromIndex].balance -= amount;
        accounts[toIndex].balance += amount;
        printf("Transfer successful! \n");
       printf("Source account balance: Rs %.2lf\n", accounts[fromIndex].balance);
        printf("Destination account balance: Rs %.2lf\n", accounts[toIndex].balance);
    }
}

void creators(){

                printf("\n\nExiting Bank Simulator. Thank you!\n");
                printf("\n  ......................................\n");
                printf("  .            Created By              .\n");
                printf("  .------------------------------------.\n");
                printf("  . Ashish Bhattarai       Aman Kulung .\n");
                printf("  . Arjun Gautam      Shishir Bhandari .\n");
                printf("  ......................................\n");

}

// Function to save bank account data to a file
void saveAccounts(stb accounts[], int numAccounts) {
    FILE *file = fopen("accounts.dat", "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(accounts, sizeof(stb), numAccounts, file);
    fclose(file);
    printf("\nBank accounts saved successfully.\n");
}

// Function to load bank account data from a file
void loadAccounts(stb accounts[], int *numAccounts) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("No existing account data found.\n");
        return;
    }
      *numAccounts = fread(accounts, sizeof(stb), 50, file);
    fclose(file);
    printf("\n    %d bank accounts loaded successfully\n", *numAccounts);
}

// Function to delete an account by account number
void deleteAccount(stb accounts[], int *numAccounts, int acc_to_del) {
    int indexToDelete = -1;

    // Find the account to delete
    for (int i = 0; i < *numAccounts; i++) {
        if (accounts[i].accountNumber == acc_to_del) {
            indexToDelete = i;
            break;
        }
    }

    // If the account is found, remove it
    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < *numAccounts - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        (*numAccounts)--;

        printf("\nAccount %d deleted successfully.\n", acc_to_del);
        }
}

// Function to display account details by account number
 void displayAccountDetails(stb accounts[], int numAccounts, int accountNumber) {
    int index;

    // Find the account with the specified account number
    for (index = 0; index < numAccounts; index++) {
        if (accounts[index].accountNumber == accountNumber) {
            // Account found, display the details
            printf("\nAccount Details:\n");
            printf("Account Number: %d\n", accounts[index].accountNumber);
            printf("Customer Name: %s %s\n",accounts[index].FirstName ,accounts[index].LastName);
            printf("fatherr Name: %s \n",accounts[index].FatherName);
            printf("address: %s \n",accounts[index].Address);
            printf("gender: %s \n",accounts[index].Gender);
            printf("age: %d \n",accounts[index].Age);
            printf("Contact no: %d \n",accounts[index].ContactNo);
            printf("enail : %s \n",accounts[index].Email);
            printf("trustee  :  %s \n",accounts[index].Trustee);
            printf("Current Balance: Rs %.2lf\n", accounts[index].balance);
            return;
        }
    }
    printf("\nAccount not found.\n Please enter a valid account number.\n");

}