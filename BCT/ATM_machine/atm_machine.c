#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX 100

// User manager
typedef struct Account {
    int accountNumber;
    int balance;
    char pin[5];
    int wrongPin; // no of wrong pin entered
    int cardBlocked;
    int Withdrawalperday;
    struct tm lastWithdrawalDate;  //to track  last withdrawal date
}USER;


// prototype

void scanUSER(USER accounts[], int *num_of_user); // read all accounts from accounts.txt  
void printUSER(USER accounts[], int num_of_user); // Write accounts to accounts.txt 


void Range( int *k, int *m, int *n);        // give range for withdrawal
int Pincheck(const char *enteredPin, const USER *account);  //check entered pin is correct or not
int verifyAdmin(const char *userId, const char *password);


void updateTransactionHistory(int accountNumber, int withdrawalAmount, int balance, const char *transactionmade) ; // update transaction history
void showTransactionHistory(int accountNumber, int numTransactionsToDisplay);


void changeATMBalance(int *amountInATM);
void createUSER(USER accounts[], int *num_of_user); // create new account
void deleteUSER(USER accounts[], int *num_of_user); // delete account
void unblockCard(USER accounts[], int num_of_user);


//mother 
int main()
{
    system("cls");
    USER accounts[MAX];
    int num_of_user = 0;
    int authorizedAccountIndex = -1;
    int  k, m, n;   // limiter
    int cardInserted = 0;
    int amountInATM;

    scanUSER(accounts, &num_of_user);
    Range( &k, &m, &n);

    FILE *fp=fopen("money.txt","r");
    if (fp == NULL) 
    {
        printf("Error opening the file.\n");
        exit(1);
    }
    fscanf(fp,"%d",&amountInATM);
    fclose(fp);

    printf("\n\n\n-----------------------------------------------------------------------------\n"); 
    printf("\t\t\tWELCOME TO THE ATM\n");
    printf("-----------------------------------------------------------------------------\n"); 
    getch();


    while(1)
    {
        system("cls");
       printf("-----------------------------------------------------------------------------\n"); 
      printf("\t\t\tPlease clarify your identity:\n");   
       printf("-----------------------------------------------------------------------------\n"); 
      printf("Choice:\n1. User\n2. Admin\n3. Exit\n-------------------------\nATM Balance: %d\n-------------------------\nSelect a choice: ", amountInATM);
      int userchoice;
      scanf("%d", &userchoice);
        switch(userchoice)
        {              
         case 1:
            {
                // USER section
             system("cls");
             while (1)
                {
                    system("cls");

                 if (cardInserted==0) 
                    {
                     printf("\n-------------------------\n Choice:\n-------------------------\n1. Insert Cash Card\n2. Exit\n\n\n-------------------------\nATM Balance: %d\n-------------------------\nSelect an option: ", amountInATM);  // Display ATM balance
                     int choice;
                     scanf("%d", &choice);

                     switch (choice)
                        {
                           
                          case 1:
                            {
                             system("cls");
                             cardInserted = 1;
                             char enteredCardNumber[10], enteredPin[5];

                              // Ask for the card number of the account
                             
                              printf("---------------------------------------------------------------------------------------\n");
                              printf("\nEnter the card number of the account : ");
                              scanf("%s", enteredCardNumber);
                              int enteredAccountNumber;

                              if (sscanf(enteredCardNumber, "%d", &enteredAccountNumber) != 1) 
                                {
                                 printf("\nInvalid card number format. Please provide bank issue atm card number .\n");
                                 printf("\nNote: It only take integers value. Please dont provide other character.Thank you\n");
                                 printf("---------------------------------------------------------------------------------------\n");
                                 cardInserted = 0; 
                                 getch();
                                 break;
                                }
                                

                               // call the specific account
                             for (int i = 0; i < num_of_user; i++)
                                {
                                 if (enteredAccountNumber == accounts[i].accountNumber)
                                    {
                                      authorizedAccountIndex = i;
                                      break;
                                    }
                               }

                              if (authorizedAccountIndex >= 0)
                                {
                                  if (accounts[authorizedAccountIndex].cardBlocked)
                                    {
                                     printf("\nYour card has been blocked. Please call the bank for assistance.\n");
                                     printf("---------------------------------------------------------------------------------------\n");
                                     cardInserted = 0;
                                     authorizedAccountIndex = -1;
                                     getch();
                                     break;
                                    } 
                                  else
                                    {
                                                               
                                     // PIN verification
                                     int pinAttempts = 0;

                                     while (pinAttempts < 3)
                                        {
                                         printf("Enter your PIN: ");
                                         scanf("%s", enteredPin);       
                                        
                                         if (Pincheck(enteredPin, &accounts[authorizedAccountIndex]))
                                           {
                                              // Reset wrong PIN attempts on successful login
                                              accounts[authorizedAccountIndex].wrongPin = 0;
                                              printf("Authorization successful.\n");                                     
                                               printf("---------------------------------------------------------------------------------------\n");
                                              getch();

                                              accounts[authorizedAccountIndex].Withdrawalperday = 0;
                                              time_t currentTime;
                                              time(&currentTime);
                                              accounts[authorizedAccountIndex].lastWithdrawalDate = *localtime(&currentTime);
                                              break;
                                            } 
                                         else
                                            {
                                             // Increment wrong PIN attempts on unsuccessful login
                                             accounts[authorizedAccountIndex].wrongPin++;
                                             pinAttempts++;
                                             if (pinAttempts < 3)
                                                {
                                                 printf("Invalid PIN. Please try again.\n");
                                                } 
                                             else
                                                {
                                                 printf("Invalid PIN. Your card has been blocked. Please call the bank for assistance.\n");
                                                 accounts[authorizedAccountIndex].cardBlocked = 1; // Set cardBlocked 
                                                 printUSER(accounts, num_of_user); 
                                                 printf("-----------------------------------------------------------------------------\n"); 
                                                 getch();
                                                 cardInserted = 0;
                                                 authorizedAccountIndex = -1;                                                
                                                 break;
                                                }

                                            }
                                        }
                                     if (accounts[authorizedAccountIndex].cardBlocked)
                                        {
                                         break;  // Return to the main menu
                                        } 

                                     while (1)
                                        { 
                                            // actual user menu
                                         system("cls");
                                         printf("\n-------------------------\nChoice:\n-------------------------\n\n1. Show Transaction History\n2. Withdraw amount\n3. Display Account Balance\n4. Deposit Amount\n5. Exit\n\n-------------------------\nATM Balance: %d\n-------------------------\n", amountInATM);  // Display ATM balance
                                         printf("\nSelect your choice: ");
                                         int userchoice;
                                         scanf("%d", &userchoice);
                                         int numTransactionsToDisplay;
                                         
                                         switch (userchoice)
                                            {
                                              system("cls");
                                             case 1:
                                              system("cls");
                                              if (authorizedAccountIndex >= 0) 
                                                {
                                                 int numTransactionsToDisplay;
                                                 printf("-----------------------------------------------------------------------------------------------\n"); 
                                                 printf("Enter the number of previous transactions to display: ");
                                                 
                                                 scanf("%d", &numTransactionsToDisplay);
                                                 printf("-----------------------------------------------------------------------------------------------\n");
                                                 printf("Transaction History:\n");
                                                 showTransactionHistory(accounts[authorizedAccountIndex].accountNumber, numTransactionsToDisplay);
                                                 printf("-----------------------------------------------------------------------------------------------\n"); 
                                                }
                                              else
                                                {
                                                 printf("You are not logged in. Please insert your card to access transaction history.\n");
                                                 printf("-----------------------------------------------------------------------------------------------\n"); 
                                                 getch();
                                                }
                                                getch();
                                              break;

                                             case 2: 
                                                {
                                                    // withdrawal money
                                                    system("cls");
                                                 int withdrawalAmount;
                                                 printf("----------------------------------------------------------------------------------------\n"); 
                                                 printf("Enter the withdrawal amount: ");
                                                 scanf("%d", &withdrawalAmount);

                                                 if (withdrawalAmount <= accounts[authorizedAccountIndex].balance) 
                                                    {
                                                     if (withdrawalAmount <= amountInATM) 
                                                        {
                                                         if (withdrawalAmount >= n) //n=1000 min value
                                                            {
                                                             if (withdrawalAmount > m) // m=10000 max money to be withdrawl per transition
                                                                {
                                                                 printf("Maximum withdrawal limit per transaction exceeded. Please try a smaller amount.\n");
                                                                printf("----------------------------------------------------------------------------------------\n"); 
                                                                getch(); 
                                                                }
                                                             else 
                                                             if (amountInATM - withdrawalAmount < n)
                                                                {
                                                                 printf("Minimum ATM balance should exist is 1000, and your withdrawal is exceeding the limit.\n");
                                                                 printf("----------------------------------------------------------------------------------------\n"); 
                                                                 getch();
                                                                }
                                                             else 
                                                                {
                                                                 // Get the current time
                                                                 time_t currentTime;
                                                                 time(&currentTime);
                                                                 struct tm *localTime = localtime(&currentTime);                             
                                                                 int daysDifference = localTime->tm_mday - accounts[authorizedAccountIndex].lastWithdrawalDate.tm_mday;                                                              
                                                                 if (daysDifference != 0) 
                                                                    {
                                                                     accounts[authorizedAccountIndex].Withdrawalperday = 0;
                                                                    }

                                                                 if (accounts[authorizedAccountIndex].Withdrawalperday + withdrawalAmount > k) // k = 25000 max limit to be withdrawl per day
                                                                    {
                                                                      printf("Withdrawal amount exceeds the daily limit. You can withdraw a maximum of %d tomorrow.\n", k - accounts[authorizedAccountIndex].Withdrawalperday);
                                                                      printf("----------------------------------------------------------------------------------------\n"); 
                                                                      getch();
                                                                    }
                                                                 else 
                                                                    {
                                                                        
                                                                     accounts[authorizedAccountIndex].balance -= withdrawalAmount;
                                                                     accounts[authorizedAccountIndex].Withdrawalperday += withdrawalAmount;
                                                                     accounts[authorizedAccountIndex].lastWithdrawalDate = *localTime;
                                                                     amountInATM -= withdrawalAmount;                                  
                                                                     printf("Withdrawal Successful. New Balance: %d\n", accounts[authorizedAccountIndex].balance);
                                                                     printf("----------------------------------------------------------------------------------------\n\n"); 
                                                                    
                                                                     // Update ATM balance in the file
                                                                     FILE *file = fopen("money.txt", "w");
                                                                     if (file == NULL) 
                                                                        {
                                                                         printf("Error opening the file.\n");
                                                                         exit(1);
                                                                        }
                                                                     fprintf(file, "%d", amountInATM);
                                                                     fclose(file);

                                                                     // Update transaction description
                                                                     char transactionmade[100];
                                                                     snprintf(transactionmade, sizeof(transactionmade), "Withdrawal of %d", withdrawalAmount);
                                                                     updateTransactionHistory(accounts[authorizedAccountIndex].accountNumber,withdrawalAmount,accounts[authorizedAccountIndex].balance,transactionmade);
                                                                     printUSER(accounts, num_of_user);
                                                                    }
                                                                }
                                                            
                                                            }
                                                         else
                                                            { 
                                                             printf("Minimum cash in the ATM required to permit a transaction is 1000. Please try again later.\n");
                                                             printf("----------------------------------------------------------------------------------------\n"); 
                                                            }
                                                        } 
                                                     else
                                                        {
                                                         printf("Insufficient funds in the ATM. Please try a smaller amount.\n");
                                                         printf("----------------------------------------------------------------------------------------\n"); 
                                                        }
                                                    } 
                                                 else
                                                    {
                                                     printf("Insufficient balance. Please try a smaller amount.\n");
                                                     printf("----------------------------------------------------------------------------------------\n"); 
                                                    }
                                                    getch();
                                                 break;
                                                }

                                             case 3:
                                                {
                                                    system("cls");
                                                    printf("----------------------------------------------------------------------------------------\n"); 
                                                 printf("Account Balance: %d\n", accounts[authorizedAccountIndex].balance);
                                                 printf("----------------------------------------------------------------------------------------\n");
                                                 getch();
                                                 break;
                                                }
                                            
                                             case 4:
                                                { 
                                                 // Deposite money
                                                 system("cls");
                                                 int depositAmount;
                                                 printf("----------------------------------------------------------------------------------------\n");
                                                 printf("Enter the deposit amount: ");
                                                 scanf("%d", &depositAmount);
                                            
                                                 if (depositAmount > 0)
                                                    {
                                                     accounts[authorizedAccountIndex].balance += depositAmount;
                                                     printf("Deposit successful. New Balance: %d\n", accounts[authorizedAccountIndex].balance);
                                                     printf("----------------------------------------------------------------------------------------\n\n"); 
                                            
                                                     // Update transaction 
                                                     char transactionmade[100];
                                                     snprintf(transactionmade, sizeof(transactionmade), "Deposit of %d", depositAmount);
                                                      updateTransactionHistory(accounts[authorizedAccountIndex].accountNumber,depositAmount, accounts[authorizedAccountIndex].balance,transactionmade);                                                                                               
                                                     printUSER(accounts, num_of_user); 
                                                     getch();
                                                     break;
                                                    }
                                                 else 
                                                   {
                                                     printf("Invalid deposit amount. Please enter a positive amount.\n");
                                                      printf("----------------------------------------------------------------------------------------\n\n"); 
                                                     getch();
                                                     break;
                                                    } 
                                                      
                                                 break;              
                                                 
                                                }
                                              case 5:
                                                {
                                                
                                                 cardInserted = 0;
                                                 authorizedAccountIndex = -1;
                                                  printf("\n----------------------------------------------------------------------------------------\n"); 
                                                 printf("You have logged out from the account.\n");
                                                 printf("\tThanks for visiting. ");
                                                  printf("\n----------------------------------------------------------------------------------------\n"); 
                                                 getch();
                                                 return 0;
                                                }   
                                             default:  printf("Invalid option. Please try again.\n");
                                             return 0;
                                            }
                                         
                                        }
                                    }
                                } 
                                else
                                {
                                 printf("Invalid card number. Please try again.\n");
                                 cardInserted = 0;
                                 getch();
                                }
                             break;
                           }
                         case 2:
                                {
                                printUSER(accounts, num_of_user);
                                printf("\nThank you for visiting.");
                                printf("\n-------------------------");
                                return 0;
                                }
                         default: printf("Invalid option. Please try again.\n"); 
                         break;
                        }
                    }
                }
                return 0;
            }
         case 2:
            {
             // Admin section
              while (1)
                {
                    system("cls");
                 printf("\n----------------------------\n\tChoice:\n----------------------------\n1. Login to the Bank system\n2. Exit\n----------------------------\n\nSelect your option: ");
                 int Adminchoice;
                 scanf("%d", &Adminchoice);
                 switch (Adminchoice)
                    {
                     case 1:
                        {
                            system("cls");
                          printf("\n------------------------------------------------\n");
                          printf("\t\tAdmin Login");
                          printf("\n------------------------------------------------\n");
                          char enteredUserId[50], enteredPassword[50];
                          printf("Enter User ID: ");
                          scanf("%s", enteredUserId);
                          printf("Enter Password: ");
                          scanf("%s", enteredPassword);
                         if (verifyAdmin(enteredUserId, enteredPassword))
                            {
                             printf("\n Login successful!");
                             printf("\n------------------------------------------------\n");
                             getch();
                              while (1)  
                                {
                                    system("cls");
                                 printf("\n--------------------------------------\nChoice:\n--------------------------------------\n1. Create an account\n2. Delete an account\n3. Update ATM Balance\n4. Unblock Card\n5. Exit\n--------------------------------------\n\nSelect an option: ");
                                 int Admin_MENU;
                                 scanf("%d", &Admin_MENU);
                                 switch (Admin_MENU)
                                    {
                                     case 1: 
                                        {
                                            system("cls");
                                         createUSER(accounts, &num_of_user);
                                         printUSER(accounts, num_of_user);
                                         getch();
                                         break;
                                        }

                                     case 2:
                                        {
                                            system("cls");
                                         deleteUSER(accounts, &num_of_user);
                                         printUSER(accounts, num_of_user);
                                          getch();
                                         break;
                                        }
                                     case 3: 
                                        {
                                            system("cls");
                                         changeATMBalance(&amountInATM);
                                          getch();
                                         break;
                                        }
                                     case 4:
                                        {
                                            system("cls");
                                         unblockCard(accounts, num_of_user);
                                         printUSER(accounts, num_of_user);
                                          getch();
                                         break;
                                        }
                                     case 5:
                                        {
                                         printf("\n--------------------------------------\n");
                                         printf("You have logged out from the account.\n");
                                         printf("\tThanks for visiting. ");
                                         printf("\n--------------------------------------");
                                         getch();
                                         return 0;
                                        }
                                     default:
                                        {
                                         printf("Invalid option. Please try again.\n");
                                         getch();
                                         break;
                                        }
                                    }
                                
                                }
                            } 
                            else
                            {
                             printf("Invalid User ID or Password. Admin login failed.\n");
                             printf("\n------------------------------------------------\n");
                             getch();
                            }
                         break;
                        }
                     case 2:
                        {
                         break;
                        }
                     default: 
                        {
                         printf("Invalid option. Please try again.\n");
                         getch();
                         break;
                        }
                    }
                 if (Adminchoice == 2) 
                    {
                     break;  // Exit the loop and return to the main menu
                    }
                }
             break;
            }       
         case 3:
            { 
             printUSER(accounts, num_of_user);
             printf("\nThank you for using the ATM. Goodbye!\n");
              printf("-----------------------------------------------------------------------------\n");
             return 0;
            }    
         default:
         printf("\nInvalid option. Please try again.\n");
         break;
        }
    }
}





void scanUSER(USER accounts[], int *num_of_user) 
{
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    *num_of_user = 0;

    while (*num_of_user < MAX && fscanf(file, "%d %d %4s %d",&accounts[*num_of_user].accountNumber,&accounts[*num_of_user].balance,accounts[*num_of_user].pin,&accounts[*num_of_user].cardBlocked) == 4) 
    {
        accounts[*num_of_user].wrongPin = 0;
        (*num_of_user)++;
    }

    fclose(file);
}

void printUSER(USER accounts[], int num_of_user) 
{
    FILE *file = fopen("user.txt", "w");
    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    for (int i = 0; i < num_of_user; i++) 
    {
        fprintf(file, "%d %d %s %d\n",accounts[i].accountNumber,accounts[i].balance,accounts[i].pin,accounts[i].cardBlocked); 
        
    }

    fclose(file);
}


void Range( int *k, int *m, int *n) 
{
     
    *k = 25000;   //daily withdrawal per day 
    *m = 15000;   //maximum withdrawl per transaction
    *n = 1000;    //Minimum cash for withdrawal
}


int Pincheck(const char *enteredPin, const USER *account) 
{
    return strcmp(account->pin, enteredPin) == 0;
}

void updateTransactionHistory(int accountNumber, int withdrawalAmount, int balance, const char *transactionmade) 
{
    FILE *file = fopen("history.txt", "a");
    if (file == NULL) 
    {
        printf("Error opening the history file.\n");
        exit(1);
    }

    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

    printf("\n\t\tRECEIPTS\n");
    printf("-------------------------------------------------\n");
    printf("Account Number   : %d\n", accountNumber);
    printf("Account Balance  : %d\n", balance);
    printf("Amount           : %d\n", withdrawalAmount);
    printf("Transaction Date: %02d:%02d:%02d\n", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    printf("\n\tThanks you for visiting\n");

    printf("-------------------------------------------------\n");

    fprintf(file, "AccountNumber:%d Withdraw:%d Balance:%d %s Time:%02d:%02d:%02d\n",accountNumber, withdrawalAmount, balance, transactionmade, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    fclose(file);
}

void showTransactionHistory(int accountNumber, int numTransactionsToDisplay) 
{
    FILE *file = fopen("history.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening the history file.\n");
        exit(1);
    }

    char box[100];
    int transactionsDisplayed = 0;
    int historyAccountNumber;

    while (fgets(box, sizeof(box), file) && transactionsDisplayed < numTransactionsToDisplay) 
    {
        
        if (sscanf(box, "AccountNumber:%d", &historyAccountNumber) == 1 && historyAccountNumber == accountNumber) 
        {
            printf("%s", box);
            transactionsDisplayed++;
        }
    }

    fclose(file);
}

int verifyAdmin(const char *userId, const char *password) 
{
    FILE *file = fopen("Admin.txt", "r");
    if (file == NULL) {
        printf("Error opening the bank user file.\n");
        exit(1);
    }

    char line[100];
    char storedUserId[50], storedPassword[50];
    
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%s %s", storedUserId, storedPassword) == 2) 
        {
            if (strcmp(storedUserId, userId) == 0 && strcmp(storedPassword, password) == 0) 
            {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

void createUSER(USER accounts[], int *num_of_user) 
{
    system("cls");
    if (*num_of_user >= 100) 
    {
        printf("Cannot create more users. The maximum limit has been reached.\n");
        getch();
        return;
    }

    int newUSER = 10000000 + rand() % 90000000;
    int newPIN = 1000 + rand() % 9000;

    for (int i = 0; i < *num_of_user; i++) 
    {
        if (accounts[i].accountNumber == newUSER) 
        {
            newUSER = 10000000 + rand() % 90000000;
            i = -1;
        }
    }
    // Inside the createBankAccount function
    accounts[*num_of_user].accountNumber = newUSER;
    accounts[*num_of_user].balance = 0;
    sprintf(accounts[*num_of_user].pin, "%04d", newPIN);
    accounts[*num_of_user].wrongPin = 0;

    accounts[*num_of_user].cardBlocked = 0; // Initialize as unblocked
    accounts[*num_of_user].Withdrawalperday = 0;
    (*num_of_user)++;

    printf("-----------------------------------------------------------------------------\n");
    printf("Account created successfully:\n");
    printf("Account Number: %d\n", newUSER);
    printf("PIN: %04d\n", newPIN);
    printf("-----------------------------------------------------------------------------\n");
    
}


void deleteUSER(USER accounts[], int *num_of_user)
{
    system("cls");
    int USER;
    printf("-----------------------------------------------------------------------------\n");
    printf("Enter the account number to delete: ");
    scanf("%d", &USER);

    int accountIndex = -1;
    for (int i = 0; i < *num_of_user; i++)
    {
        if (accounts[i].accountNumber == USER)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex >= 0)
    {
        for (int i = accountIndex; i < *num_of_user - 1; i++)
        {
            accounts[i] = accounts[i + 1];
        }
        (*num_of_user)--;
        printf("User with account number %d has been deleted.\n", USER);
        printf("-----------------------------------------------------------------------------\n");
       
    }
    else
    {
        printf("User number not found. Account deletion failed.\n");
        printf("-----------------------------------------------------------------------------\n");
        
    }
}


void changeATMBalance(int *amountInATM)
{
    system("cls");
    printf("-----------------------------------------------------------------------------\n");
    printf("Current ATM Balance: %d\n", *amountInATM);
    printf("-----------------------------------------------------------------------------\n");


    // Get the amount to add to the ATM balance
    int addedAmount;
    printf("Enter the amount to add to the ATM Balance: ");
    scanf("%d", &addedAmount);
    
    if (addedAmount >= 0) 
    {
        *amountInATM += addedAmount; 
        printf("ATM Balance updated successfully. New ATM Balance: %d\n", *amountInATM);
        printf("-----------------------------------------------------------------------------\n");
        FILE *file = fopen("money.txt", "w");
        if (file == NULL) 
        {
            printf("Error opening the file.\n");
            exit(1);
        }
        fprintf(file, "%d", *amountInATM);
        fclose(file);
    } else 
    {
        printf("Invalid amount. Please enter a non-negative value.\n");
        printf("-----------------------------------------------------------------------------\n");
        getch();
    }
}

void unblockCard(USER accounts[], int num_of_user) 
{
    system("cls");
    int accountNumber;
    printf("-----------------------------------------------------------------------------\n");
    printf("Enter the account number to unblock the card: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < num_of_user; i++) 
    {
        if (accounts[i].accountNumber == accountNumber) 
        {
            if (accounts[i].cardBlocked == 1) 
            { // Check if the card is blocked
                accounts[i].cardBlocked = 0; // Unblock the card
                printf("Card with account number %d has been unblocked.\n", accountNumber);
                 printf("-----------------------------------------------------------------------------\n");
                 
                return;
            } else {
                printf("Card with account number %d is already unblocked.\n", accountNumber);
                printf("-----------------------------------------------------------------------------\n");
               
                return;
            }
        }
    }
    printf("Account number not found. Card unblocking failed.\n");
    printf("-----------------------------------------------------------------------------\n");
    
}


