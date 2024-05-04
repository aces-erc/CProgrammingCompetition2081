#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define size 100
#define size1 100
typedef struct user
{
  char username[size];
  char password[20];
  char fname[size];
  char lname[size];
  int age;
  char nationality[50];
  int way;
  int num_travelers;
  int transcode;
  int payment;
  int cost;
  float vat;
} user;
typedef struct flight
{
  char no[10];
  char from[size1];
  char to[size1];
  char day[size1], month[size1], year[size1];
  char time[size1], timediv[size1];
  int cost;
} flights;
typedef struct passenger
{
  char fname[size], lname[size];
  int age, phoneno, citizenshipno;
} passenger;
passenger p[size];
flights fl[size];
user u[size];
void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}
void entrypattern() // for entry pattern in the main console
{
  printf("\n******************************************************\nAirline Ticketing\nDomestic flight\n******************************************************\n");
  printf("1. Book a new flight\n");
  printf("2. Update\n");
  printf("3. view old tickets\n");
  printf("4. delete data records\n");
  printf("5. logout\n");
  printf("\n*******************************************************\n");
}
void login(int *);
void signup(int *);
void clear();
void booking(); // main module to reserve tickeet
void input_basic_details();
void flight(flights fl[], int *);
void service_selection(int *);
void vip(); // to print pattern of seat and read seat no
void economy();
void pass_details();
void payment();
void update(int*);
void input_log();
void printout_log();
int usersn = 1, seatno, flightno;
char seattype[50]="vip";
int main()
{
  int choice1, choice2, flag2 = 1, flag = 0;
  do
  {
     system("cls");
    printf("******************************************************\nAirline Ticketing\nDomestic flight\n******************************************************\n");
    printf("1 -->login\n2 -->register\n3 -->exit\n");
    printf("*******************************************************\n");
    scanf(" %d", &choice1);
    if (choice1 == 1)
    {
      login(&flag);
    }
    else if (choice1 == 2)
    {
      signup(&flag);
    }
    else if (choice1 == 3)
    {
      exit(0);
    }
    else
    {
      printf("enter valid choice");
      clearBuffer();
      continue;
    }
    clearBuffer();
    getch();
    while (flag2 == 1 && flag == 1)
    {
        system("cls");
      entrypattern();
      printf("\nEnter your choice: ");
      scanf(" %d", &choice2);
      switch (choice2)
      {

      case 1:
        booking();
        break;
      case 2:
        update(&flag);
        break;
      case 3:
        printout_log();
        break;
         case 4:
        clear();
        break;
      case 5:
        flag2 = 0;
        flag = 0;
        break;
      default:
        printf("enter valid choice");
        flag2 = 1;
        break;
      }
      getch();
    }
  } while (flag == 0);
  return 0;
}

void signup(int *flag)
{
  FILE *signup;
  // Open the file for appending
  signup = fopen("signup_file.txt", "a");
  if (signup == NULL)
  {
    printf("Error: Unable to open file for writing.\n");
    return;
  }

  // Prompt for user details
  printf("Enter your first name: ");

  scanf("%s", u[usersn].fname);
  printf("Enter your last name: ");

  scanf("%s", u[usersn].lname);
  printf("Enter your username: ");
  scanf("%s", u[usersn].username);
  printf("Enter your password: ");
  scanf("%s", u[usersn].password);
  // Write user data to file
  fprintf(signup, "%s %s %s %s\n", u[usersn].fname, u[usersn].lname, u[usersn].username, u[usersn].password);
  // Close the file
  fclose(signup);
}

void login(int *flag)
{
  char username[size], password[size];
  char file_username[size], file_password[size];
  char ch;
  int found = 0;

  // Open the file for reading
  FILE *signup = fopen("signup_file.txt", "r");
  if (signup == NULL)
  {
    printf("Error opening user_personal_file");
    *flag = 0; // Set status to indicate failure
    return;
  }
  // Prompt for username and password
  printf("Enter your username: ");
  scanf("%s", username);
  printf("Enter your password: ");
  scanf("%s", password);

  // Read each line from the file and compare with the input
  while (fscanf(signup, "%s %s", file_username, file_password) == 2)
  {
    if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
    {
      printf("Welcome back, %s!\n", username);
      found = 1;
      break;
    }
  }

  // If user not found, display error message
  if (!found)
  {
    printf("Invalid username or password. Please try again.\n");
  }

  *flag = found;

  // Close the file
  fclose(signup);
}
void input_basic_details()
{
  static int i = 0;
  i = usersn;
  printf("one way\t| two way\n1 -->one way\n2 -->two way\n");
  scanf(" %d", &u[i].way);
  printf("Enter nationality: ");
  scanf(" %s", u[i].nationality);
  printf("Enter total number of travelers: ");
  scanf("%d", &u[i].num_travelers);
  // printf("\n\nfrom-->");
  // printf("\nBiratnager\tdharan\t kathmandu\tbhairava\tbharatpur\nenter the name of place\n");
  // scanf(" %s", u[i].from);
  // printf("to--> ");
  // printf("\nBiratnager\tdharan\t kathmandu\tbhairava\tbharatpur\nenter the name of place\n");
  // scanf(" %s", u[i].to);
  i += 1;
}
void booking() // main module to reserve tickeet
{
  int numFlights = 0, service_choice;
  input_basic_details();
  flight(fl, &numFlights);
  printf("enter the sn for selection:");
  scanf("%d", &flightno);
  service_selection(&service_choice);
  pass_details();
  payment();
  input_log();
  printout_log();
}
void update(int *flag)
{
  system("cls");
  {
    char username[size], password[size], new_username[size], new_password[size];
    char file_username[size], file_password[size];
    int found = 0;

    // Open the file for reading and writing
    FILE *signup = fopen("signup_file.txt", "r+");
    if (signup == NULL)
    {
      perror("Error opening user_personal_file");
      *flag = 0; // Set status to indicate failure
      return;
    }

    // Prompt for username and password
    printf("Enter your current username: ");
    scanf("%s", username);
    printf("Enter your current password: ");
    scanf("%s", password);

    // Read each line from the file and compare with the input
    while (fscanf(signup, "%s %s", file_username, file_password) == 2)
    {
      if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
      {
        printf("Enter your new username: ");
        scanf("%s", new_username);
        printf("Enter your new password: ");
        scanf("%s", new_password);

        // Move the file pointer back to the beginning of the line
        fseek(signup, -strlen(file_username) - strlen(file_password), SEEK_CUR);

clearBuffer();
        // Write the new username and password to the file
        fprintf(signup, "%s %s\n", new_username, new_password);
        printf("Username and password changed successfully.\n");
        found = 1;
        break;
      }
    }

    // If user not found, display error message
    if (!found)
    {
      printf("Invalid username or password. Please try again.\n");
    }

    *flag = found;

    // Close the file
    fclose(signup);
  }
}
void printout_log()
{
system("cls");
  char ch;
  int line_count = 0;
    FILE *passenger = fopen("passenger.txt", "r");
    if (passenger == NULL) {
        printf("Error: Unable to open passenger file.\n");
        return;
    }
    if((ch = fgetc(passenger)) == EOF)
    {
      printf("NO data!");
      return;
    }

    // Read and print lines up to 7
    while ((ch = fgetc(passenger)) != EOF) {
        printf("%c", ch);
        if (ch == '\n') {
            line_count++;
        }
    }

  fclose(passenger);
}

void pass_details()
{
  int static j = 1;
  int i;
  for ( i = j; i <= u[usersn].num_travelers; i++)
  {
    printf("for passenger no:%d\n",i);
    printf("enter your first name:");
    scanf(" %s", p[i].fname);
    printf("enter your last name:");
    scanf(" %s", p[i].lname);
    printf("enter your age:");
    scanf(" %d", &p[i].age);
    printf("enter your citizenship no:");
    scanf(" %d", &p[i].citizenshipno);
    printf("enter your phone number:");
    scanf(" %d", &p[i].phoneno);
  }
  j=i;
}
void input_log()
{
  int static j = 1;
  int i;
  FILE *passenger = fopen("passenger.txt", "a");
  if (passenger == NULL)
  {
    printf("Error: Unable to open passenger file for writing.\n");
    return;
  }

  for (i = j; i <= u[usersn].num_travelers; i++)
{
    fprintf(passenger, "\nticket no: %d\n", i);
    fprintf(passenger, "Name: %s %s\ncitizen no: %d\nphoneno: %d\n", p[i].fname, p[i].lname, p[i].citizenshipno, p[i].phoneno);
    fprintf(passenger, "Flight No: %s\tseat no: %d\nDepart Date: %s %s %s\nfrom: %s to: %s\n", fl[flightno-1].no, seatno, fl[flightno-1].day, fl[flightno-1].month, fl[flightno-1].year, fl[flightno-1].from, fl[flightno-1].to);
    seatno++;
}

  j = i;
  fclose(passenger);
}

void flight(flights fl[], int *numFlights)
{
  FILE *file = fopen("flights.txt", "r");
  if (file == NULL)
  {
    printf("Error: Unable to open file.\n");
    exit(1);
  }
  *numFlights = 0;
rewind(file);
  while (fscanf(file, "%s %s %s %d %s %s %s %s %s", fl[*numFlights].no, fl[*numFlights].from, fl[*numFlights].to, &fl[*numFlights].cost,
                fl[*numFlights].month, fl[*numFlights].day, fl[*numFlights].year, fl[*numFlights].time, fl[*numFlights].timediv) != EOF)
  {
    (*numFlights)++;
    if (*numFlights >= 100)
    {
      printf("Error: Maximum number of flights exceeded.\n");
      break;
    }
  }

  fclose(file);
  printf("Flight Details:\n    Flight No\t\tFrom\t\t\tTo\t\t\tCost\t\tDate\t\t\tTime\n");
  for (int i = 0; i < *numFlights; i++)
  {
    printf("%d\t%s \t\t%s    \t\t%s    \t\t%d\t\t%s %s %s\t\t%s %s\t\t", i+1 , fl[i].no, fl[i].from, fl[i].to, fl[i].cost, fl[i].day, fl[i].month, fl[i].year, fl[i].time, fl[i].timediv);
    printf("\n");
  }
}

void payment()
{
  int static i=0;
  i++;
  int j,choice;
  printf("Payment:\nTrip summary\n");
  printf("package cost(for one traveller)\t\tNPR %d\n", fl[usersn].cost);
  u[i].vat = 0.13 * (float)fl[usersn].cost;
  printf("Vat(13 percent)\t\t\t\tNPR %.2f\n", u[i].vat);
  u[i].payment = u[usersn].vat*u[usersn].num_travelers+fl[usersn].cost * u[usersn].num_travelers * u[usersn].way;
  // printf("%")
  printf("No of passenger:\t\t\t%d (%s)\nway:\t\t\t\t\t%d way\n",u[usersn].num_travelers,seattype,u[usersn].way);
  printf("Total charges\t\t\t\tNPR %.2d\n",  u[i].payment);
  j = 1;
  while (j >= 1)
  {
    printf("Which platform do wish to use \n1. esewa \n2. khalti\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("enter the transaction code:");
      scanf("%d", &u[usersn].transcode);
      j = 0;
      break;
    case 2:
      printf("enter the transaction code:");
      scanf("%d", &u[usersn].transcode);
      j = 0;
      break;
    default:
      printf("Invalid input. Please enter 1 or 2.\n");
      clearBuffer();
      break;
    }
  }
  printf("Payment Successful!");
}
void service_selection(int *service_choice)
{
  int i = 0;
  // do
  // {
  while (1)
  {
    printf("\nchoose \n1 -->VIP class\n2 -->Economy class\n");
    scanf("  %d", service_choice);
    printf("\ninput the seat no \n");
    if (*service_choice == 1)
    {
      strcpy(seattype, "vip seat");
      vip();
      do
      {
        scanf("%d", &seatno);
        if (seatno <= 6 && seatno >= 1)
        {
          break;
        }
        else
        {
          printf("enter accurate seat no:");
        }
      } while (1);
      break;
    }
    else if (*service_choice == 2)
    {
      economy();
      do
      {
        scanf("%d", &seatno);
        if ((seatno > 6) && (seatno <= 46))
        {
          strcpy(seattype, "economy seat");
          break;
        }
        else
        {
          printf("enter accurate seat no:");
        }
      } while (1);
      break;
    }
    else
    {
      printf("enter valid choice");
    }
  }
}
void vip()
{
  int i, j;
  seatno = 1;
  for (i = 1; i < 4; i++)
  {
    for (j = 1; j < 3; j++)
    {
      printf("%d\t", seatno);

      seatno += 1;
    }
    printf("\n");
  }
}
void economy()
{
  int i, j;
  seatno = 7;
  for (i = 1; i < 11; i++)
  {
    for (j = 1; j < 3; j++)
    {
      printf("%d\t", seatno);
      seatno += 1;
    }
    printf("%d\t%d\t", seatno + 18, seatno + 19);
    printf("\n");
  }
}
void clear()
{system("cls");
  FILE *passenger = fopen("passenger.txt", "w");
  fclose(passenger);
  printf("Successfully cleared!");
}