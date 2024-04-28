#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_MOBILE_LENGTH 15
#define MENU_FILE "menu.txt"
#define ORDERS_FILE "orders.txt"
#define CUSTOMERS_FILE "customers.txt"
#define MESSAGES_FILE "messages.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

typedef struct {
    int menuNumber;
    int quantity;
    float totalPrice;
} Order;

typedef struct {
    char mobile[MAX_MOBILE_LENGTH];
    char name[MAX_NAME_LENGTH];
    float totalSpent;
    int totalOrders;
} Customer;

MenuItem menu[MAX_ITEMS];
int menuSize = 0;
Order orders[MAX_ITEMS];
int orderCount = 0;

void loadMenu() {
    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", MENU_FILE);
        exit(1);
    }

    while (fscanf(file, "%s %f\n", menu[menuSize].name, &menu[menuSize].price) != EOF) {
        menuSize++;
    }

    fclose(file);
}

void displayMenu() {
    printf("Menu:\n");
    for (int i = 0; i < menuSize; i++) {
        printf("%d. %s - Rs %.2f\n", i + 1, menu[i].name, menu[i].price);
    }
}

void displayOrder(Order order) {
    printf("\nOrdered: %d x %s\n", order.quantity, menu[order.menuNumber - 1].name);
    printf("Price: Rs %.2f\n", order.totalPrice);
}

Customer findCustomer(char *mobile) {
    FILE *customersFile = fopen(CUSTOMERS_FILE, "r");
    if (customersFile == NULL) {
        printf("Error opening file %s\n", CUSTOMERS_FILE);
        exit(1);
    }

    Customer customer;
    while (fscanf(customersFile, "%s %s %f %d\n", customer.mobile, customer.name, &customer.totalSpent, &customer.totalOrders) != EOF) {
        if (strcmp(customer.mobile, mobile) == 0) {
            fclose(customersFile);
            return customer;
        }
    }

    fclose(customersFile);
    strcpy(customer.mobile, "");
    return customer;
}

void updateCustomer(Customer customer, float totalBill, int totalQuantity) 
{
    FILE *customersFile = fopen(CUSTOMERS_FILE, "r+");
    if (customersFile == NULL) {
        printf("Error opening file %s\n", CUSTOMERS_FILE);
        exit(1);
    }

    float updatedTotalSpent = customer.totalSpent + totalBill;
    int updatedTotalOrders = customer.totalOrders + 1;

    // File ma Customer ko position record find garcha,
    long pos = ftell(customersFile); //long pos le file ko specific position herna bhanda paila current file position lai save garcha
    fseek(customersFile, pos - strlen(customer.mobile) - strlen(customer.name) - sizeof(float) - sizeof(int) - 3, SEEK_SET);

    // file ma updated values rakhcha
    fprintf(customersFile, "%s %s %.2f %d\n", customer.mobile, customer.name, updatedTotalSpent, updatedTotalOrders);
    fclose(customersFile);
}

void placeOrder() {
    float totalBill = 0.0;
    int totalQuantity = 0;
    char mobile[MAX_MOBILE_LENGTH];
    char name[MAX_NAME_LENGTH];

    while (1) {
        int menuNumber, quantity;
        printf("Enter item number and quantity (0 0 to finish order): ");
        if (scanf("%d %d", &menuNumber, &quantity) != 2) {
            printf("Invalid input\n");
            
            while (getchar() != '\n');
            continue;
        }
        if (menuNumber == 0) {
            break; // loop close (order close) garcha
        }
        if (menuNumber < 1 || menuNumber > menuSize) {
            printf("Invalid menu number\n");
            continue; //(avoiding the errors)
        }
        MenuItem item = menu[menuNumber - 1];
        float totalPrice = item.price * quantity;
        totalBill += totalPrice;
        totalQuantity += quantity;
        printf("\nOrdered: %d x %s\n", quantity, item.name);
        printf("Price: Rs %.2f\n", totalPrice);
        printf("Total Bill : Rs %.2f\n", totalBill);
    }
   
    float discount = 0.0;
    if (totalBill > 500.0) {
        discount = totalBill * 0.10; // 10% discount dincha
    }

    float finalPrice = totalBill - discount;

    printf("\nTotal Discount: Rs %.2f\n", discount);
    printf("Final Total Bill: Rs %.2f\n", finalPrice);

    printf("Enter your mobile number: ");
    scanf("%s", mobile);

    Customer customer = findCustomer(mobile);
    if (strcmp(customer.mobile, "") == 0) {
        printf("Enter your name: ");
        scanf("%s", name);
        strcpy(customer.mobile, mobile);
        strcpy(customer.name, name);
        customer.totalSpent = 0.0;
        customer.totalOrders = 0;
    }

    updateCustomer(customer, finalPrice, totalQuantity);

    FILE *ordersFile = fopen(ORDERS_FILE, "a");
    if (ordersFile == NULL) {
        printf("Error opening file %s\n", ORDERS_FILE);
        exit(1);
    }
    fprintf(ordersFile, "%s %.2f %.2f %d\n", mobile, finalPrice, discount, totalQuantity);
    fclose(ordersFile);
    printf("Your order is placed successfully!\n");
}

void displayPurchaseHistory() {
    char mobile[MAX_MOBILE_LENGTH];
    printf("Enter your mobile number to display purchase history: ");
    scanf("%s", mobile);

    Customer customer = findCustomer(mobile);
    if (strcmp(customer.mobile, "") == 0) {
        printf("Customer not found\n");
        return;
    }

    printf("Purchase History for %s:\n", customer.name);
    printf("Total Spent: Rs %.2f\n", customer.totalSpent);
    printf("Total Orders: %d\n", customer.totalOrders);
}

char* getRandomMessage() {
    FILE* file = fopen("messages.txt", "r");
    if (file == NULL) {
        printf("Error opening file messages.txt\n");
        exit(1);
    }
    // Generates  a random line number
    srand(time(NULL)); // Seed the random number generator
    int randomLine = rand() % 10;
    // Read the random line from the file
    char message[100];
    for (int i = 0; i <= randomLine; i++) {
        if (fgets(message, sizeof(message), file) == NULL) {
            break;
        }
    }
    fclose(file);
    return strdup(message);
}

int main() {
    loadMenu();

    int choice;
    while (1) {
        printf("\nBakery Management System\n");
        printf("1. Display Menu\n");
        printf("2. Place Order\n");
        printf("3. Display Purchase History\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                placeOrder();
                break;
            case 3:
                displayPurchaseHistory();
                break;
            case 4:
                printf("%s\n", getRandomMessage());
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
