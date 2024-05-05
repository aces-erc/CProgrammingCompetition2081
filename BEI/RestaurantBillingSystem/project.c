#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct items
{
    char dishName[50];
    float price;
    int qty;
};

struct customer
{
    char customerName[100];
    int numOfItems;
    struct items menu[50];
};

void billHeader(char name[50]);
void billBody(char dishName[50], int qty, float price);
void billFooter(float total);
void saveFile(struct customer ord, float grandTotal);
void displaySave();
// modification?
void deleteFile(struct customer ord);
float calculation(float total);

int main()
{
    int n, i;
    float grandTotal;
    struct customer ord;
    char option, check, flag = 'y';

    while (flag == 'y')
    {
        system("cls");
        float total = 0;
        printf("\t====PURWANCHAL RESTAURANT====\n");
        printf("\n\tPlease Select the operation\n");
        printf("\t1.Generate Invoice\n");
        printf("\t2.Display Saved Invoices\n");
        printf("\t3.Delete Saved Invoices\n");
        printf("\t4.Exit\n");

        fflush(stdin);
        option = getch();

        switch (option)
        {
        case '1':
        {
            system("cls");
            printf("Please Enter the name of the customer\n");
            scanf("%s[^\n]", ord.customerName);
            printf("Number of the dish ordered\n");
            scanf("%d[^\n]", &n);
            ord.numOfItems = n;
            fflush(stdin);

            for (i = 0; i < n; i++)
            {
                printf("\nName of the dish %d: ", i + 1);
                scanf("%s[^\n]", ord.menu[i].dishName);
                printf("\nQuantity of the %s ordered: ", &ord.menu[i].dishName);
                scanf("%d", &ord.menu[i].qty);
                printf("\nPrice of each: ");
                scanf("%f", &ord.menu[i].price);
                fflush(stdin);

                total += ord.menu[i].qty * ord.menu[i].price;
            }

            billHeader(ord.customerName);

            for (i = 0; i < ord.numOfItems; i++)
            {
                billBody(ord.menu[i].dishName, ord.menu[i].qty, ord.menu[i].price);
            }

            grandTotal = calculation(total);

            billFooter(total);

            saveFile(ord, grandTotal);
            break;
        }
        case '2':
        {
            displaySave();
            break;
        }
        case '3':
        {
            deleteFile(ord);
            break;
        }
        case '4':
        {
            printf("------------THANK YOU-----------");
            return 0;
            break;
        }
        default:
        {
            printf("Sorry,Invalid Option");
            break;
        }
        }
        printf("\nDo you want to perform another operation? [y/n]: \n");
        fflush(stdin);
        flag = getch();
        // scanf("%c", &flag);
    }
    printf("\n\tTHANK YOU\n");
    return 0;
}

void billHeader(char name[50])
{
    ////
    system("cls");
    printf("\n\n");
    printf("\t  PURWANCHAL CAFE  \n");
    printf("----------------------------------------\n");
    printf("Date: %s\n", __DATE__);
    printf("Invoice to: %s\n", name);
    printf("\n---------------------------------------\n");
    printf("Items\t\tQty\t\tTotal\n");
    printf("-----------------------------------------\n");
    printf("\n");
}

void billBody(char dishName[50], int qty, float price)
{
    printf("%s\t\t", dishName);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

float calculation(float total)
{
    float disc = 0.1 * total;
    float netTotal = total - disc;
    float tax = 0.15 * netTotal;
    float grandTotal = netTotal + tax;
    return grandTotal;
}

void billFooter(float total)
{
    float disc = 0.1 * total;
    float netTotal = total - disc;
    float tax = 0.15 * netTotal;
    float grandTotal = netTotal + tax;

    printf("-----------------------------------------\n");
    printf("Sub-Total\t\t\t%.2f\n", total);
    printf("Discount @10%\t\t\t%.2f\n", disc);
    printf("-----------------------------------------\n");
    printf("Net-Total\t\t\t%.2f\n", netTotal);
    printf("Tax @15%\t\t\t\t%.2f\n", tax);
    printf("-----------------------------------------\n");
    printf("Grand Total\t\t\t%.2f\n", grandTotal);
}

void saveFile(struct customer ord, float grandTotal)
{
    int i;
    float tot[50];
    FILE *fp = fopen("detail.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "Customer: %s\n", ord.customerName);
    fprintf(fp, "Date: %s\n", __DATE__);
    fprintf(fp, "Items\t\tQty\t\tTotal\n");
    fprintf(fp, "------------------------------------------\n");
    for (i = 0; i < ord.numOfItems; i++)
    {
        tot[i] = ord.menu[i].price * ord.menu[i].qty;
        fprintf(fp, "%s\t\t%d\t\t%.2f\n", ord.menu[i].dishName, ord.menu[i].qty, tot[i]);
    }
    // GrandTotal
    fprintf(fp, "-----------------------------------------------\n");
    fprintf(fp, "Grand-Total(with disc. & tax)\t%.2f\n", grandTotal);
    fprintf(fp, "-----------------------------------------------\n\n");
    printf("Invoice saved to file successfully!\n");
    fclose(fp);
}

void displaySave()
{
    char line[100];
    FILE *fp = fopen("detail.txt", "r");
    fseek(fp, 0, SEEK_SET);
    if (fp == NULL)
    {
        printf("No saved file");
        return;
    }
    //
    system("cls");

    printf("\n\t  Saved Invoices\n");
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }
    fclose(fp);
}
void deleteFile(struct customer ord)
{
    FILE *fp, *fptemp;
    char choice;

    fp = fopen("detail.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    system("cls");

    printf("\n\tPlease Select tour operation\n");
    printf("\t1.Delete All\n");
    printf("\t2.Exit\n");

    fflush(stdin);
    choice = getch();

    switch (choice)
    {
    case '1':
    {

        FILE *filePtr = fopen("detail.txt", "w");
        if (filePtr == NULL)
        {
            printf("No file found!\n");
        }

        fclose(filePtr);
        printf("All saved invoices have been deleted.\n");
        break;
    }
    case '2':
    {
        printf("Thank You\n");
        return;
    }
    }
}