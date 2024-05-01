#include<time.h>
#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> ///for windows related functions 
#include <string.h>  ///string operations
#include <math.h>
void gotoxy();
void show();
void headerfooter();
void bill();
void customer_details();
char choice();
void add_customer_detail();
void room_available();
int prdR=5,prR=10,dxR=15,totalrevs=0,size=90;//prdR=Presidential suite,prR=premium room,dxr=deluxe room

struct Booking
{
  char cusname[40],roomtype,emailId[40];
  int rD,rM,rY,perday,no_of_person,no_of_room,rever_ID;
  float bill_amount;
}q[90];
void gotoxy(int x,int y)// creation of gotoxy function for position of cursor
{
  COORD c;
  c.X=x;
  c.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//1.Handle 2.COORD
}
void show()       //initial page view
{
  int i,j;
  gotoxy(9,3);//(X,Y)
  printf("----------------------------------------------------------------------------------");
    for(j=4;j<=23;j++)
    {
    gotoxy(9,j);
    printf("%c",4);
    }
    for(j=4;j<=22;j++)
    {
    gotoxy(90,j);
    printf("%c",4);
    }
     gotoxy(9,20);
     printf("----------------------------------------------------------------------------------");
     gotoxy(9,12);
     printf("%c                      $$  WELCOME TO HOTEL PARADISE  $$                       ",4);
     gotoxy(9,21);
     printf("%c         please visit us %c at: www.hotel paradise.com                        ",4,3);
     gotoxy(9,22);
     printf("----------------------------------------------------------------------------------");
     gotoxy(9,23);
     printf("                         Press any key to enter!!!");
     getch();
}

void headerfooter()
{
  system("cls");
  int i;
  for(i=9;i<=90;i++)
  {
  gotoxy(i,5);
  printf("=");
  }
  gotoxy(9,6);
  printf("                              HOTEL PARADISE Pvt.LTD                                  ");
  for(i=9;i<=90;i++)
  {
  gotoxy(i,7);
  printf("=");
  }
  for(i=9;i<=90;i++)
  {
  gotoxy(i,27);
  printf("_");
  }
  gotoxy(9,28);
  printf("           please visit us %c at: www.hotel paradise.com                         ",3);
  for(i=9;i<=90;i++)
  {
  gotoxy(i,29);
  printf("_");
  }
  

}
char choice()  //second page view
{
  int i,x;
  headerfooter();
  for(i=29;i<=70;i++)
  {
  gotoxy(i,9);
  printf("_");
  }
  gotoxy(30,10);
  printf("|  A: Book room ");
  for(i=29;i<=70;i++)
  {
  gotoxy(i,11);
  printf("_");
  }
  gotoxy(30,12);
  printf("|  B: Use our financial services ");
  for(i=29;i<=70;i++)
  {
  gotoxy(i,13);
  printf("_");
  }
  gotoxy(30,14);
  printf("|  C: Already have a reservation ");
  for(i=29;i<=70;i++)
  {
  gotoxy(i,15);
  printf("_");
  }
  gotoxy(30,16);
  printf("|  D: For Employees only  ");
  for(i=29;i<=70;i++)
  { 
  gotoxy(i,17);
  printf("_");
  }
  gotoxy(30,18);
  printf("|  E: About us ");
  for(i=29;i<=70;i++)
  {
  gotoxy(i,19);
  printf("_");
  }
  gotoxy(30,20);
  printf("|  F: Exit ");
  for(i=29;i<=70;i++)
  {
  gotoxy(i,21);
  printf("_");
  }
  gotoxy(30,23);
  printf("Enter the choice:");
  return (getche());
}
void customer_details()  //in (only for employees) displaying customer details
{
  FILE *cus;
  int i;
  cus=fopen("customer_detail.txt","r");
  if(cus==NULL)
  {
    printf("File cannot be opened\n");
    exit(0);
  }
  if(totalrevs<0)
  {system("cls");
  printf("\n No Details to Display");}
  else
  {
    { while(fscanf(cus, "%s%s%d",q[totalrevs].cusname,q[totalrevs].emailId,&q[totalrevs].rever_ID)!=EOF)
      {
            
                printf("  Name:%s\n Email ID:%s\n Reservation ID :%d \n",q[totalrevs].cusname,q[totalrevs].emailId,q[totalrevs].rever_ID);
        printf("\n_");
        totalrevs++;
      }
    }
    
  }
  
  fclose(cus);
}
void add_customer_details()   // extract details of customer
{
  char choice,s[20];
  FILE *cus;
  cus=fopen("customer_detail.txt","w");
  headerfooter();
  gotoxy(9,9);
  printf("Enter Your Name:");
  gotoxy(25,9);
  //fflush(stdin);
  gets(q[totalrevs].cusname);fflush(stdin);
  fprintf(cus,"%s\n",q[totalrevs].cusname);
  gotoxy(9,10);
  printf("Enter your email:");
  gotoxy(26,10);
  //fflush(stdin);
  gets(q[totalrevs].emailId);fflush(stdin);
  fprintf(cus,"%s\n",q[totalrevs].emailId);
  fclose(cus);
  gotoxy(9,11);
  printf("Enter Date:dd/mm/yy");
  gotoxy(20,11);
  scanf("%d",&q[totalrevs].rD);fflush(stdin);
  gotoxy(23,11);
  scanf("%d",&q[totalrevs].rM);fflush(stdin);
  gotoxy(26,11);
  scanf("%d",&q[totalrevs].rY); fflush(stdin);
  gotoxy(9,12);
  printf("Enter no. of days:");
  gotoxy(27,12);
  scanf("%d",&q[totalrevs].perday);  fflush(stdin);
  gotoxy(9,13);
  printf("Enter no. of persons:");
  gotoxy(30,13);
  scanf("%d",&q[totalrevs].no_of_person);  fflush(stdin);
  gotoxy(9,14);
  printf("Enter the type of room");
  gotoxy(10,15);
  printf(" A. Presidential suite ");
  gotoxy(10,16);
  printf(" B. Premium room ");
  gotoxy(10,17);
  printf(" C. Deluxe suite ");
  gotoxy(11,18);
  printf("Enter your choice:");
  scanf("%c",&choice);
  switch(choice)
  {
    case 'a':case 'A':
    q[totalrevs].roomtype='a';
    break;
    case 'b':case 'B':
    q[totalrevs].roomtype='b';
    break;
    case 'c':case 'C':
    q[totalrevs].roomtype='c';
    break;
  }
  q[totalrevs].no_of_room=1;
  if(q[totalrevs].no_of_person>3)
  {
    q[totalrevs].no_of_room=0;
    q[totalrevs].no_of_room=q[totalrevs].no_of_room+q[totalrevs].no_of_person/3;
    if(q[totalrevs].no_of_person%3!=0)
    q[totalrevs].no_of_room++;
  }
  bill();
}

void room_available()  // to Display available rooms
{
  headerfooter();
  gotoxy(29,10);
  printf("Room INformation:");
  gotoxy(34,12);
  printf("Presidential Suite=%d",prdR);
  gotoxy(34,13);
  printf("Premium room=%d",prR);
  gotoxy(34,14);
  printf("Deluxe room=%d",dxR);
  gotoxy(17,23);
  printf("Press any key to enter!!!");
  getch();
}

void bill()
{
 headerfooter();
  char st[40];
  int i,a;
  float amt;
  FILE *cus;

  switch(q[totalrevs].roomtype)
  {
    case 'a':
    strcpy(st,"Presidential_Suite");
    amt=10000;
    prdR=prdR-q[totalrevs].no_of_room;
    break;
    case 'b':
    strcpy(st,"Premium_Room");
    amt=5000;
    prR=prR-q[totalrevs].no_of_room;
    break;
    case 'c':
    strcpy(st,"Deluxe_Room");
    amt=3000;
    dxR=dxR-q[totalrevs].no_of_room;
    break;

  }
  q[totalrevs].bill_amount=q[totalrevs].perday*amt*q[totalrevs].no_of_room;
  gotoxy(10,9);
  printf("BILL:");
  for(i=10;i<=84;i++)
  {
  gotoxy(i,10);
  printf("_");
  }
  gotoxy(10,11);
  printf("|     Room Type     |  Total Days  |  per day  |  No.of Rooms  |  Price  |");
  for(i=10;i<=84;i++)
  {
  gotoxy(i,12);
  printf("_");
  }
  gotoxy(10,13);
  printf("|  %18s|       %4d   |  %5.f |       %3.d       |      %8.f  |",st,q[totalrevs].perday,amt,q[totalrevs].no_of_room,q[totalrevs].bill_amount);
  for(i=10;i<=84;i++)
  {
  gotoxy(i,14);
  printf("_");
  }
  gotoxy(10,15);
  printf("|   Total Bill:                                               %8.0f",q[totalrevs].bill_amount);
  for(i=10;i<=84;i++)
  {
  gotoxy(i,16);
  printf("_");
  }
  q[totalrevs].rever_ID=rand();
  cus=fopen("customer_detail.txt","a");
  fflush(stdin);
  fprintf(cus,"%d",q[totalrevs].rever_ID);
  gotoxy(10,18);
  printf("Your room has been successfully booked %c%c",3,3);
  gotoxy(10,19);
  printf("Your reservation number = %d",q[totalrevs].rever_ID);
  fclose(cus);
  
}


struct user
{
  char phone[50];
  char ac[50];
  char password[50];
  float balance;
};
void bank()
{
  struct user usr, usr1;
  FILE *fp;
  char filename[50], phone[50], pword[50];
  int opt, choice;
  char cont = 'y';
  float amount;

  printf("\nWhat do you want to do?");
  printf("\n\n1. Register an account");
  printf("\n2. Login to an account");
  printf("\n3. Exit");
  printf("\n\nYour choice:\t");
  scanf("%d", &opt);

  if (opt == 1)
  {
    system("cls");
    printf("Enter your account number:\t");
    scanf("%s", usr.ac);
    printf("Enter your phone number:\t");
    scanf("%s", usr.phone);
    printf("Enter your new password:\t");
    scanf("%s", usr.password);
    usr.balance = 0;
    strcpy(filename, usr.phone);
    fp = fopen(strcat(filename, ".dat"), "w");
    fwrite(&usr, sizeof(struct user), 1, fp);
    if (fwrite != 0)
    {
      printf("\n\nAccount succesfully registered");
    }
    else
    {
      printf("\n\nSomething went wrong please try again");
    }
    fclose(fp);
  }
  if (opt == 2)
  {
    system("cls");
    printf("\nPhone number:\t");
    scanf("%s", phone);
    printf("Password:\t");
    scanf("%s", pword);
    strcpy(filename, phone);
    fp = fopen(strcat(filename, ".dat"), "r");
    if (fp == NULL)
    {
      printf("\nAccount number not registered");
    }
    else
    {
      fread(&usr, sizeof(struct user), 1, fp);
      fclose(fp);
      if (!strcmp(pword, usr.password))
      {
        printf("\n\t\tWelcome %s", usr.phone);
        ;
        while (cont == 'y')
        {
          system("cls");
          printf("\n\nPress 1 for balance inquiry");
          printf("\nPress 2 for depositing cash");
          printf("\nPress 3 for cash withdrawl");
          printf("\nPress 4 for online transfer");
          printf("\nPress 5 for password change");
          printf("\n\nYour choice:\t");
          scanf("%d", &choice);

          switch (choice)
          {
          case 1:
            printf("\nYour current balance is Rs.%.2f", usr.balance);
            break;
          case 2:
            printf("\nEnter the amount:\t");
            scanf("%f", &amount);
            usr.balance += amount;
            fp = fopen(filename, "w");
            fwrite(&usr, sizeof(struct user), 1, fp);
            if (fwrite != NULL)
              printf("\nSuccesfully deposited.");
            fclose(fp);
            break;
          case 3:
            printf("\nEnter the amount:\t");
            scanf("%f", &amount);
            usr.balance -= amount;
            fp = fopen(filename, "w");
            fwrite(&usr, sizeof(struct user), 1, fp);
            if (fwrite != NULL)
              printf("\nYou have withdrawn Rs.%.2f", amount);
            fclose(fp);
            break;

          case 4:
            printf("\nPlease enter the phone number to transfer the balance:\t");
            scanf("%s", phone);
            printf("\nPlease enter the amount to transfer:\t");
            scanf("%f", &amount);
            strcpy(filename, phone);
            fp = fopen(strcat(filename, ".dat"), "r");
            if (fp == NULL)
              printf("\nAccount number not registered");
            else
            {
              fread(&usr1, sizeof(struct user), 1, fp);

              fclose(fp);
              if (amount > usr.balance)
                printf("\nInsufficient balance");
              else
              {

                fp = fopen(filename, "w");
                usr1.balance += amount;
                fwrite(&usr1, sizeof(struct user), 1, fp);

                fclose(fp);
                if (fwrite != NULL)
                {
                  printf("\nYou have succesfully transfered Rs.%.2f to %s", amount, phone);
                  strcpy(filename, usr.phone);
                  fp = fopen(strcat(filename, ".dat"), "w");
                  usr.balance -= amount;
                  fwrite(&usr, sizeof(struct user), 1, fp);
                  fclose(fp);
                }
              }
              break;
            case 5:
              printf("\nPlease enter your new password:\t");
              scanf("%s", pword);
              fp = fopen(filename, "w");
              strcpy(usr.password, pword);
              fwrite(&usr, sizeof(struct user), 1, fp);
              if (fwrite != NULL)
                printf("\nPassword succesfully changed");
            }
            break;
            if (opt == 3)
            {
                exit(0);
            }
          default:
            printf("\nInvalid option");
          }

          printf("\nDo you want to continue the transaction [y/n]\t");
          scanf("%s", &cont);
        }
      }
      else
      {
        printf("\nInvalid password");
      }
    }
  }
}

struct visitor
{
    int id;
    char name[20];
    char address[20];
    int number;
    char bookname[20];
    char date[12];
}v;

struct books
{
    int bookid;
    char bookname[50];
    char authorname[50];
    char date[12];

}b;

void addbook()
{
    FILE *fp;
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.bookid);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookname);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorname);

    printf("Book Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void booklist()
{
FILE *fp;
system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.bookid, b.bookname, b.authorname, b.date);
    }

    fclose(fp);
}
void removebook()
{
    FILE *fp;
 int id, f=0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.bookid){
            f=1;
        }else{

            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");


}
void issuebook()
{
FILE *fp;
char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(v.date, myDate);

    int f=0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &v.id);

    //Check if we have book of given id
    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.bookid == v.id){
            strcpy(v.bookname, b.bookname);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Visitor Name: ");
    fflush(stdin);
    gets(v.name);

    printf("Enter Visitor number: ");
    scanf("%d", &v.number);

    printf("Enter Visitor address: ");
    fflush(stdin);
    gets(v.address);

    printf("Enter Visitor Id: ");
    scanf("%d", &v.id);

    printf("Book Issued Successfully\n\n");

    fwrite(&v, sizeof(v), 1, fp);
    fclose(fp);
}
void issuebooklist()
{
    FILE *fp;
 system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-20s %-20s %-40s \n\n", "V.id", "Name", "Address","Number", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
   while(fread(&v, sizeof(v), 1, fp) == 1){
        printf("%-10d %-30s %-20s %-20d %-20s %-40s\n",v.id,v.name,v.address,v.number,v.bookname,v.date);
    }

    fclose(fp);


}
void library()
{
int choice;
while(1)
{
system("cls");
printf("-------------------WELCOME TO PURWANCHAL LIBRARY----------------------------\n");
printf("1.Add Book\n");
printf("2.Books List\n");
printf("3.Remove Book\n");
printf("4.Issue Book\n");
printf("5.Issued Book List\n");
printf("6.Exit\n\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice)
{

    case 1:
    addbook();
    break;

    case 2:
    booklist();
    break;

    case 3:
    removebook();
    break;

    case 4:
    issuebook();
    break;

    case 5:
    issuebooklist();
    break;

   case 6:
    exit(0);

    default:
    printf("Your choice is invalid\n");
   
  


}
printf("Press any to continue");
getch();

}
}


/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/


/** Sub function started */

void employee()
{
    FILE *fp, *ft; /// file pointers
    char another, choice;

    /** structure that represent a employee */
    struct emp
    {
        char name[40]; ///name of employee
        int age; /// age of employee
        float bs; /// basic salary of employee
    };

    struct emp e; /// structure variable creation

    char empname[40]; /// string to store name of the employee

    long int recsize; /// size of each record of employee

    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }

    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(e);

    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls"); ///clear the console window
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Add Record"); /// option for add record
        gotoxy(30,12);
        printf("2. List Records"); /// option for showing existing record
        gotoxy(30,14);
        printf("3. Modify Records"); /// option for editing record
        gotoxy(30,16);
        printf("4. Delete Records"); /// option for deleting record
        gotoxy(30,18);
        printf("5. Exit"); /// exit from the program
        gotoxy(30,20);
        printf("Your Choice: "); /// enter the choice
        fflush(stdin); /// flush the input buffer
        choice  = getche(); 
        switch(choice)
        {
        case '1': 
            system("cls");
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while(another == 'y')  /// if user want to add another record
            {
                printf("\nEnter name: ");
                scanf("%s",e.name);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                printf("\nEnter basic salary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); /// write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp); ///this moves file cursor to start of the file
            while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s %d %.2f",e.name,e.age,e.bs); /// print the name, age and basic salary
            }
            getch();
            break;

        case '3':  /// if user press 3 then do editing existing record
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  /// fetch all record from file
                {
                    if(strcmp(e.name,empname) == 0)  ///if entered name matches with that in file
                    {
                        printf("\nEnter new name,age and bs: ");
                        scanf("%s%d%f",e.name,&e.age,&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); /// override the record
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(e.name,empname) != 0)  /// if the entered record match
                    {
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(fp);  /// close the file
            exit(0); /// exit from the program
        }
    }
    
}

int usrScore = 0,compScore = 0;
void checkOptions(int usr,int comp){
	// 1 = scissor 2= paper 3=rock
	if(usr == comp){
		printf(" --------------------\n");
		printf("|    Its a tie       |\n");
		printf(" --------------------\n");
	}
	else if(usr == 1){
		if(comp == 2){
			printf(" --------------------\n");
			printf("|      You Won :)    |\n");
			printf("| You : Scissor      |\n");
			printf("| Computer : Paper   |\n");
			printf(" --------------------\n");
			usrScore++;
			
		}
		else {
			printf(" --------------------\n");
			printf("|     You Lose :(    |\n");
			printf("| You : Scissor      |\n");
			printf("| Computer : Rock    |\n");
			printf(" --------------------\n");
			
			compScore++;
		}
	}
	else if(usr == 2){
		if(comp == 1){
			printf(" --------------------\n");
			printf("|      You Lose :(   |\n");
			printf("| You : Paper        |\n");
			printf("| Computer : Scissor |\n");
			printf(" --------------------\n");
		    compScore++;
		}
		else {
			printf(" --------------------\n");
			printf("|     You Won :)     |\n");
			printf("| You : Paper        |\n");
			printf("| Computer : Rock    |\n");
			printf(" --------------------\n");
			
			usrScore++;
		}
	}
	else if(usr == 3){
		if(comp == 1){
			printf(" --------------------\n");
			printf("|      You Won :)    |\n");
			printf("| You : Rock        |\n");
			printf("| Computer : Scissor |\n");
			printf(" --------------------\n");
			usrScore++;
		}
		else {
			printf(" --------------------\n");
			printf("|     You Lose :(    |\n");
			printf("| You : Rock         |\n");
			printf("| Computer : Paper    |\n");
			printf(" --------------------\n");
			
			compScore++;
		}
	}
	else if(usr == 4){
		printf(" --------------------\n");
		if(usrScore > compScore)
		printf("|      You Won :)    |\n");
		else if (usrScore < compScore)
		printf("|     You Lose :(    |\n");
		else 
		printf("|      Its a tie     |\n");
		printf("|     Final Score    |\n");
		printf("| You : %d            |\n",usrScore);
		printf("| Computer: %d        |\n",compScore);
		printf(" --------------------\n");
		printf("\a");
	}
	else {
		Beep(750,500);
		printf("\n Invalid Option");
	}

}
void rps() {
int userChoice,compChoice;
srand(time(0));
printf("\t\t\t\t==========Welcome to Rock, Paper & Scissor Game==========");
while(userChoice != 4){
printf("\nPlease select the option: ");
printf("\n1.Scissor");
printf("\n2.Paper");
printf("\n3.Rock");
printf("\n4.Quit\n");
scanf("%d",&userChoice);

compChoice = (rand() % 3) + 1;
checkOptions(userChoice,compChoice);
}


}

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
// functions to generate bills
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t  Rato Bhale Restaurant");
    printf("\n\t----------------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[20], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float vat = 0.09 * netTotal, grandTotal = netTotal + vat;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nVAT @9%s\t\t\t\t%.2f", "%", vat);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}
void restraurant()
{

    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;
    // dashboard
    while (contFlag == 'y')
    {
        system("cls");
        float total = 0;
        int invoiceFound = 0;
        printf("\t============RATO BHALE RESTAURANT============");
        printf("\n\nPlease select your prefered operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);
        switch (opt)
        {
        case 1:
            system("cls");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, _DATE_);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &n);
            ord.numOfItems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                    printf("\nSuccessfully saved");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

        case 2:
            system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n  ****Your Previous Invoices\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the name of the customer:\t");
            // fgetc(stdin);
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            printf("\t**Invoice of %s", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s doesnot exists", name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Thank you :)\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");


}

typedef struct logging
{
    char phone[50];
    char ac[50];
    char password[50];

} g1;

void kaushal()
{
    g1 usr;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int opt, choice;
    char cont = 'y';
    system("cls");
    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d", &opt);

    if (opt == 1)
    {
        system("cls");

        printf("Enter your phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);

        strcpy(filename, usr.phone);
        fp = fopen(strcat(filename, ".dat"), "w");
        fwrite(&usr, sizeof(g1), 1, fp);
        if (fwrite != 0)
        {
            printf("\n\nAccount succesfully registered");
        }
        else
        {
            printf("\n\nSomething went wrong please try again");
        }
        fclose(fp);
    }
    if (opt == 2)
    {
        system("cls");
        printf("\nPhone number:\t");
        scanf("%s", phone);
        printf("Password:\t");
        scanf("%s", pword);
        strcpy(filename, phone);
        fp = fopen(strcat(filename, ".dat"), "r");
        if (fp == NULL)
        {
            printf("\nAccount number not registered");
        }
        else
        {
            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);
            if (!strcmp(pword, usr.password))
            {
                printf("\n\t\tWelcome %s", usr.phone);
                ;
                while (cont == 'y')
                {

                    {
                        system("cls");
                        printf("\nPress 1 for password change");
                        printf("\n Press 2 to play ROCK PAPER SCISSORS ");
                        printf("\n Press 3 to go to Library");
                        printf("\n Press 4 to go to Restraurant");
                        printf("\nPress 5 for Exit");
                        printf("\n\nYour choice:\t");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:

                            printf("\nPlease enter your new password:\t");
                            scanf("%s", pword);
                            fp = fopen(filename, "w");
                            strcpy(usr.password, pword);
                            fwrite(&usr, sizeof(g1), 1, fp);
                            if (fwrite != NULL)
                                printf("\nPassword succesfully changed");

                            break;
                        case 2:
                            rps();
                            break;
                        case 3:
                            library();
                            break;
                        case 4:
                            restraurant();

                            break;
                        case 5:
                            exit(0);
                            break;
                        default:
                            printf("\nInvalid option");
                        }

                        printf("\nDo you want to continue the program [y/n]\t");
                        scanf("%s", &cont);
                    }
                }
            }
        }
    }
}

void karki()
{
headerfooter();
  
  char ch;
  char stt[30];
  system("cls");
  printf(" \t  ==----------Logging  Management System----------==\n ");
  printf("\t |                                                  |\n");
  printf("\t |                   1: Employee datafile           |\n");
  printf("\t |                   2: client datafile             |\n");
  printf("\t |                                                  |\n");
  printf("\t  ================================================== \n");

 char hotel_pass[]="hotel@123";
  printf("Enter The Choice of Action:===> \t");
  scanf("%d", &ch);
  if (ch == 1)
  {
     printf("Enter the Login password\n");
     scanf("%s" ,stt);
     if (!strcmp(stt,hotel_pass)){
  employee();
  
  }
  else 
  { printf("No Access to the Information\n");
  }
  }
  if (ch == 2)
  {
    system("cls");
     customer_details();
    }
  
  
}




/** Main function started */


int main()
{
  char option;
  system("cls");
  system("color 2F");
  show();
  do
  {
  option=choice();
  switch(option)
  {
    case 'a':case 'A':
    room_available();
    add_customer_details();
    break;
    case 'b':case 'B':
         bank();
     break;
    case 'c':case 'C':
     kaushal();
     break;
    case 'd':case 'D':
     karki();
    break;
    case 'e':case 'E':
    system("cls");
       printf("\n\t\t\t\t\t=========Welcome to Hotel Paradise Pvt. Ltd.=============\n\t\t\t\tNestled in the heart of Pokhara, Nepal, where nature's embrace meets unparalleled luxury. Our serene location, surrounded by breathtaking natural beauty, sets the stage for an unforgettable getaway. At Hotel Paradise, we offer a range of services tailored to exceed your expectations. From seamless financial services to ensure a hassle-free stay, to our meticulously curated room booking experience, every detail is crafted with your comfort in mind. Indulge in the ultimate relaxation with our luxurious accommodations. Choose from our opulent Presidential Suite, offering unrivaled elegance and comfort, our chic Premium Rooms, or our cozy Deluxe Rooms, each designed to provide a blissful retreat after a day of exploration. But the experience doesn't end there. Immerse yourself in our vibrant e-library and e-games, perfect for unwinding and entertainment. Whether you seek adventure or tranquility, Hotel Paradise is your haven in the midst of nature's splendor. ""Embrace our theme, We create love in nature,"" as you create unforgettable memories with your loved ones amidst the serenity of Pokhara. Welcome to a paradise unlike any other."); 
     break;
    case 'f':case 'F':
    gotoxy(13,25);
    printf("Thank You for Your Valuable Time");
    gotoxy(13,26);
    printf("....VISIT AGAIN....%c\n",3);

  }
  getch();
  } while (option!='f'&&option!='F');
 

return 0;
}
