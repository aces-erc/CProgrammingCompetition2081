#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
char check;
void login();
void begin(); //function declarations
void program();
void show_details();
void complaints_suggestions();
void book_room();
void foodmenu();
void storedata();
struct { //structure that stores details of persons
    char name[20];
    char address[50];
    char email_id[30];
    char nationality[25];
    int roomno;
    char *roomtype;
    int billprice;
    char *program;
}person;
 int main(){
    person.roomno =0;
    person.billprice =0;
    person.program = "notchose\n";
         printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n");
         printf("\t\t*                                           *\n");
         printf("\t\t*       ----------------------------        *\n");
         printf("\t\t*        HAMRO HOTEL AND RESTAURANT         *\n");
         printf("\t\t*       ----------------------------        *\n");
         printf("\t\t*                                           *\n");
         printf("\t\t*                                           *\n");
         printf("\t\t*                                           *\n");
         printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n\n\n");
         printf(" Please enter your details before moving to the main page!\n");
         printf(" please enter your name:");
              gets(person.name);
         printf(" enter your address:");
              gets(person.address);
         printf(" enter your nationality:");
              gets(person.nationality);
         printf(" enter your email_id:");
              gets(person.email_id);
  system("cls");
          begin();
return 0;

}

void begin(){
    system("cls");
    int decide;
        printf("   ****************************  |MAIN MENU|  *************************** \n");

    printf("\n1.Book a room\n");
    printf("----------------------------------");
    printf("\n2.Program");
    printf("\n----------------------------------");
    printf("\n3.show details(for staff only)\n");
    printf("----------------------------------");
    printf("\n4.order food\n");
    printf("----------------------------------");
    printf("\n5.complaints or suggestions\n");
    printf("----------------------------------");
    printf("\n6.check out\n");
    printf("----------------------------------");
    printf("\n7.about us\n");
    printf("Enter your choice : ");

        scanf("%d",&decide);
    switch(decide)
{

case 1:

     book_room();
     break;

case 2:

     program();
     break;
case 3:

     show_details();
     break;
case 4:
     foodmenu();
     break;
case 5:

     complaints_suggestions();
             printf("Thank you for your valuable suggestions!\n");
    begin();
     break;
case 6:
             storedata();
             printf("Visit again!\n");
             printf("Your total bill is %d.Please pay it in reception.",person.billprice);

             printf("\nThank you for trusting our service.\n");
             getche();
     break;
case 7:

             printf("WELCOME TO HAMRO HOTEL AND RESTAURENT:\n");

printf(" A beautiful cosmopolitan destination for a picturesque natural scenario, a blend of Natural and Artificial effort located on the border of");
printf("Chitwan National park (A UNESCO Natural Heritage Site) allows you to enjoy the breeze of Rapti River flowing through the lap of  Chitwan National Park.");
printf("Enjoying the spectacular sunset and its reflection on Rapti River along with grazing of deer,Elephant , different types of Crocodile on the bank by relaxing on   our rugged cottages");

printf("is the memorable experience you could enjoy only at HAMRO HOTEL AND RESTAURENT.\n");
printf("We would be more than happy to experience you Jungle Safari, canoe ride to Jeep drive and Tharu special cultural shows..");
printf("Clean and comfortable room,hot and cold water facilities, beautiful garden, family    environment, local food are our salient features to give you taste of our Nepalese Culture.");
printf("Satisfying you totally with our unique culture is our primary motto.\n");
getche();
begin();
break;


default:
begin();
}}


void book_room(void) {
    srand(time(NULL));
    system("cls");
    
    if (person.roomno == 0) {
        char choice;
        
        do {
            int type_of_rooms;
            char c;

            printf("\nWhat type of room do you want to book?\n");
            printf("\n1. Basic Room    Rs 1000\n2. Medium room   Rs 2000\n3. DELUXE ROOM   Rs 3000\n4. Exit\n");
            scanf("%d", &type_of_rooms);
            fflush(stdin); // Clear input buffer
            
            if (type_of_rooms >= 1 && type_of_rooms <= 3) {
                printf("\nDo you accept this room? (y/n)\n");
                scanf(" %c", &c); // Note the space before %c to consume any leading whitespace

                if (c == 'y') {
                    system("cls");

                    if (type_of_rooms == 1) {
                        printf("\nYou choose basic room. Call the administration in 9744****** to check if the room is available.\n");
                        person.roomno = rand() % 20 + 100;
                        person.billprice += 1000;
                        person.roomtype = "basic";
                    } else if (type_of_rooms == 2) {
                        printf("\nYou choose medium room. Call the administration in 9744****** to check if the room is available.\n");
                        person.roomno = rand() % 10 + 120;
                        person.billprice += 2000;
                        person.roomtype = "medium";
                    } else if (type_of_rooms == 3) {
                        printf("\nYou choose deluxe room. Call the administration in 9744****** to check if the room is available.\n");
                        person.roomno = rand() % 5 + 230;
                        person.billprice += 3000;
                        person.roomtype = "deluxe";
                    }

                    printf("Your room number is %d\n", person.roomno);
                }
            } else if (type_of_rooms == 4) {
                break; // Exit the loop if the user chooses to exit
            } else {
                printf("Invalid choice. Please choose a valid option.\n");
            }

            printf("\nDo you want to book another room? (y/n)\n");
            scanf(" %c", &choice); //  the space before %c to consume any leading whitespace
            
        } while (choice == 'y');
    }
     else {
       printf("You have already booked a room.\n");
    }
    
    printf("Press any key to continue...\n");
    begin();
    getche(); // Wait for user to press any key
}


void program(void){ system("cls");
int p;
int n;

printf("\nWhich program do you want to choose(only enter number assigned)?\n");

printf("\n 1.Jungle Walk   1000 \n 2.Jungle Jeep Drive  2000\n 3.Canoe ride   800\n 4. Cultural show   1000\n 5. Exit\n");
 scanf("%d",&p);
switch(p)
{ case 1:

system("cls");

printf("\nYou choose jungle walk\n");

person.program = "Jungle walk";
printf("No of tickets: ");
scanf("%d",&n);
person.billprice += n*1000;
printf(" You have booked %d tickets.Enjoy the walk",n);
getche();

begin();
 break;
case 2:

printf("\nYou choose jungle jeep drive\n");
person.program = "Jeep Drive";
printf("No of tickets: ");
scanf("%d",&n);
person.billprice += n*2000;
printf("You have booked %d tickets.Enjoy the drive..",n);
getche();

begin();
break;
case 3:
printf("\nYou choose canoe ride\n");
person.program = "Canoe Ride";
printf("No of tickets: ");
scanf("%d",&n);

person.billprice+= n*800;
printf("You have booked %d tickets.Enjoy the ride..",n);
getche();

begin();
break; 
case 4:

printf("\nYou choose cultural show\n");
person.program = "Cultural show";
printf("No of tickets: ");
scanf("%d",&n);
person.billprice+= n*1000;
printf("You have booked %d tickets. Enjoy the show..",n);
getche();

begin();
break;
case 5:
begin();

}

}

void show_details(void){
    storedata();
    system("cls");
char details[225];
time_t timer = time(NULL);
FILE *ifp;
ifp = fopen("file.txt","r");
 if(ifp == NULL){
printf("file cant be opened\n");

}

else{
    login();
     if (check=='o')
      {while(fgets(details,225 , ifp)!=0) {   

    printf("%s\n", details);  
      }
}
getch();
    }

begin();
}
void login() {
    char username[20] = "hotel";
    char password[20] = "hamrohotel";
    char inputUsername[20];
    char inputPassword[20];

    printf("\nEnter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        printf("Logged in\n");
        check='o';
    } else {
        printf("Login failed\n");
    }

    
}
void storedata(){
    system("cls");
time_t timer = time(NULL);

FILE *ifp;
ifp = fopen("file.txt","a+");
 if(ifp == NULL){
printf("file can't be opened\n");

}

else{


fprintf(ifp,"         DETAILS	\n");
fprintf(ifp,"Name	: %s\n",person.name);
fprintf(ifp,"Nationality : %s\n",person.nationality);
fprintf(ifp,"Email id	: %s\n",person.email_id);
fprintf(ifp,"Address		: %s\n",person.address);
fprintf(ifp,"Arrival time: %s\n",ctime(&timer));
fprintf(ifp,"Roomno			: %d\n",person.roomno);
fprintf(ifp,"Roomtype				: %s\n",person.roomtype);
if(strcmp(person.program,"notchosen") != 0){
fprintf(ifp,"Program	: %s\n",person.program);

}

fprintf(ifp,"Billprice:  %d\n",person.billprice);

fclose(ifp);


}

}
void foodmenu(){

    system("cls");
      int a;
      char ch;
       printf("\n	FOOD MENU\n\n");
       printf("\n  FOOD              price");
       printf("\n1.PIZZA             500\n2.CHICKEN MOMO      250\n3.C MOMO            300\n4.CHOWMEIN          150\n5.NEWARI KHAJA SET  600\n6.CRUNCHY CHICKEN   300\n7.ROTI TAKARI       200\n8.BEER(small)       250\n");
       scanf("%d",&a);

       fflush(stdin);
       switch(a){
   case 1:
    printf("Did you order this food?(y/n)");

    scanf("%c",&ch);

    if(ch=='y'){
        person.billprice+=500;
        printf("your order will arrive soon");
     printf("\npress any key to continue");
    }getche();
      begin();
      break;
      case 2:
   printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=300;
        printf("your order will arrive soon");
    printf("\npress any key to continue");      }
       getche();
       begin();
      break;
   case 3:
   printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=250;
        printf("your order will arrive soon");
    printf("\npress any key to continue");      }
       getche();
       begin();
      break;
    case 4:
    printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=150;
        printf("your order will arrive soon");
    printf("\npress any key to continue");
    }  getche();
       begin();
      break;
    case 5:
    printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=600;
        printf("your order will arrive soon");
    printf("\npress any key to continue");
    }  getche();
       begin();
      break;
      case 6:
    printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=300;
        printf("your order will arrive soon");
    printf("\npress any key to continue");
    } getche();
      begin();
      break;
  case 7:
    printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=200;
        printf("\nyour order will arrive soon");
    printf("press any key to continue");
    }
     getche();
       begin();
      break;
     case 8:
    printf("Did you order this food?(y/n)");
    scanf("%c",&ch);
    if(ch=='y'){
        person.billprice+=1000;
        printf("your order will arrive soon");
        printf("\npress any key to continue");
    }
     getche();
      begin();
      break;




       }






}

void complaints_suggestions(void){ system("cls");
char complain[500];
FILE *fpt;
fpt = fopen("complain.txt","a+");
if(fpt == NULL){

printf("file cant be opened\n");

}

printf("please enter your complaints or suggestions\n");
fflush(stdin);
gets(complain);


 fputs(complain,fpt);
fclose(fpt);

}
