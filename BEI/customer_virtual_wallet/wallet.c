#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 10
#define FILENAME "custome.txt"

struct Customer {
    int id;
    char name[50];
    float balance;
};

struct Customer customers[MAX_CUSTOMERS];
int customer_count = 0;


void saveCustomersToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
        {
        printf("Error opening file for writing.Create a new one\n");
        printf("Enter the data:\n");
       return;
    }

    for (int i = 0; i < customer_count; i++) {



            fprintf(file, "customer id:%d\n customer name:%s\n total customer balance:%.2f\n ", customers[i].id, customers[i].name, customers[i].balance);
        }
    }




    fclose(file);



void loadCustomersFromFile()
 {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
        {
        printf("File not found. Starting with empty customer database.\n");
  return ;
    }

    while (fscanf(file, "%d %s %f", &customers[customer_count].id, customers[customer_count].name, &customers[customer_count].balance) != EOF)
        {
        customer_count++;
        if (customer_count >= MAX_CUSTOMERS)
            {
            printf("Maximum number of customers reached. Some data may not be loaded.\n");
            break;
        }
    }

    fclose(file);
}

void addCustomer() {
    if (customer_count < MAX_CUSTOMERS)
        {
        printf("Enter customer name: ");
        scanf("%s", customers[customer_count].name);
        customers[customer_count].id = customer_count + 1;
        customers[customer_count].balance = 0;
        customer_count++;
        printf("Customer added successfully.\n");
    } else {
        printf("Maximum number of customers reached.\n");
    }
}


void deposit()
{
    int customer_id;
    float amount;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if (customer_id >= 1 && customer_id <= customer_count)
        {
        customers[customer_id - 1].balance += amount;
        printf("Deposit successful.\n");
    } else
     {
        printf("Invalid customer ID.\n");
    }
}

void withdraw()
{
    int customer_id;
    float amount;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if (customer_id >= 1 && customer_id <= customer_count)
        {
        if (customers[customer_id - 1].balance >= amount)
        {
            customers[customer_id - 1].balance -= amount;
            printf("Withdrawal successful.\n");
        } else {
            printf("Insufficient balance.\n");
        }
    }
    else
    {
        printf("Invalid customer ID.\n");
    }
}




void deleteCustomer()
{
    int customer_id;
    printf("Enter customer ID to delete: ");
    scanf("%d", &customer_id);

    if (customer_id >= 1 && customer_id <= customer_count)
        {

        for (int i = customer_id - 1; i < customer_count - 1; i++)
            {
            customers[i] = customers[i + 1];
        }
        customer_count--;
        printf("Customer deleted successfully.\n");
    } else
     {
        printf("Invalid customer ID.\n");
    }
}

void displayBalance()
{
    int customer_id;
   printf("\nID   Name          Balance\n");
    printf("----------------------------\n");
    for (int i = 0; i < customer_count; i++) {


        {
        printf("%d\t %s\t RS%.2f\n", customers[i].id, customers[i].name, customers[i].balance);


}
    }
}


int main()
 {
    loadCustomersFromFile();

    int choice;
    do {
        printf("\nCustomer Virtual Wallet\n");
        printf("1. Add Customer\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Delete Customer \n");
        printf("5. Display Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                deleteCustomer();
                break;
            case 5:
               displayBalance();
                break;

            case 6:
                 printf("Exit\n");
                 break;


            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    saveCustomersToFile();

    return 0;
}
