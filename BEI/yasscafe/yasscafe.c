//Main Project
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<stdlib.h>



int  i, choice;
struct details{
    char name[20];
    double Phone_no;
    char address[30];
    
};

void mainmenu();
void customer();
void aboutus();
void items();

void cus_details(int);
void admin();

int main(){
    mainmenu();
    return 0;
}

void mainmenu(){
    system("cls");
    char de;
    up:
    printf("  \t#***************************************************************#\n");
    printf("\t\t\t WELCOME TO YASS CAFE\n");
    printf("  \t#***************************************************************#\n\n");
    printf("\t\t   1.Customer Section \n\t\t   2.Administration Section \n\t\t   3.About Us \n\t\t   4.Exit\n");
    printf("\t\tEnter your choice-->  ");
    scanf("%d", &choice);

    if(choice==1){
        customer();
    }
    else if(choice==3){
        aboutus();
     }
    else if(choice==2){
        admin();
    }
    else if(choice==4){
    system("cls");
    printf("\n\n\n\n  \t\t#************************************************#\n");
    printf("\t\t\t\t THANK YOU !!!!\n");
    printf("\t\t\t\t Visit us Again\n");
    printf("  \t\t#************************************************#\n\n");
    getchar();
    getchar();
    }
    else{
        system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        goto up;
    }
}

void customer(){
    system("cls");
    printf("\n\tWELCOME TO CUSTOMER SECTION\n");
    printf("\n\tWe have following services for you::\n");
    printf("\t\t1. Items\n\t\t2.Back to main menu\n");
    printf("\t   Enter your choice-->  ");
    scanf("%d", &choice);

    if(choice==1){
       items();
    }
    else if(choice==2){
       mainmenu();
     }
    
    else{
        system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        customer();
    }
}
void items() {
int code, qty;
float price, amt, totalAmt, cash;
char addAnother;

// do-while loop -> post-test

do {
 system("cls");

      printf("====================");
    printf("\nFOOD AND DRINKS MENU\n");
	printf("====================\n\n");
	
    printf ("[1]   PIZZA\t\tRS 1050.00\n");
    printf ("[2]   SANDWICH\t\tRS 780.00\n");
    printf ("[3]   BIRYANI\t\tRS 730.00\n");
    printf ("[4]   MOMO \t\tRS 250.00\n");
    printf ("[5]   FRENCH FRIES\tRS 320.00\n");
    printf ("[6]   SIZZLERS\t\tRS 875.00\n");
    printf ("[7]   COFFEE\t\tRS 600.00\n");
    printf ("[8]   TEA\t\tRS 50.00\n");
    printf ("[9]   LASSI\t\tRS 400.00\n");
    printf ("[10]  BEER\t\tRS 1000.00\n");
		
	printf ("\n ENTER CODE\t:");
	scanf("%d",&code);
	printf ("\n ENTER QUANTITY\t:");
	scanf("%d",&qty);
	
      switch (code) {

         case 1: price =1050.00;
    	break;
	    case 2: price =780.00;
	    break;	
	    case 3: price =730.00;
		break;
	    case 4: price =250.00;
		break;
		case 5: price =320.00;
		break;
		case 6: price =875.00;
		break;
		case 7: price =600.00;
		break;
		case 8: price =50.00;
		break;
		case 9: price =400.00;
		break;
		case 10: price =1000.00;
		break;

}
     amt= price* qty;
     printf("\nAmount\t\t: %.2f", amt);

     totalAmt= totalAmt + amt;
     printf("\nTotal Amount\t: %.2f", totalAmt);
     
     printf("\nAdd another order (y/n)?");
     addAnother = getche();
}while (addAnother == 'y' || addAnother == 'Y');



	
	 
	
	printf("\n please enter following details\n");
	cus_details(totalAmt);
	
	}




void cus_details(int totalAmt){
	
    struct details s1;
    printf("\tPlease Enter Your Name\t:");
    getchar();
    scanf("%[^\n]s", s1.name);
    //printf("%s", s1.name);
    printf("\tYour Phone Number::\t");
    getchar();
    scanf("%lf", &s1.Phone_no);
    printf("\tYour address::\t");
    getchar();
    scanf("%[^\n]s", s1.address);
   
    FILE *nt;
    nt=fopen("details.txt","a");
    fprintf(nt,"Name: %s\nPhone no: %.0lf\nAddress:  %s\nTotal Sum: %d\n\n", s1.name,s1.Phone_no, s1.address, totalAmt);
    fclose(nt);
    printf("\n \t\t Your order will be delivered as soon as possible.!!");
    printf("\n\n We are going back to main menu. THANK YOU!!!\n Press enter key to continue\n");
    getchar();
    getchar();
    system("cls");
    mainmenu();
}

void aboutus(){
    system("cls");
  
    
    printf("\n\n\n\n\t\t\t  Contact us:\n");
    printf("\t\t OPEN 7 DAYS A WEEK\n");
    printf("\t\t   Phone no.= 9812345678\n");
    printf("\t  Visit our website: www.yasscafe.com.np\n");
    printf("\n\n\nPress enter key to go to mainmenu\n");
    getchar();
    getchar();
    mainmenu();
}

void admin(){
        char de;
        system("cls");
        up:
        printf("\t    ADMINISTRATION SECTION\n");
        printf("\n\t1.Customer Details \n\t2.Back to main menu\n");
        printf("\t Choose an option-->   ");
        scanf("%d", &i);
        if(i==1){
            FILE *np;
            np=fopen("details.txt","rt");
            while((de=getc(np))!=EOF){
                printf("%c",de);
            }
            printf("Press enter key to go to administration section\n");
        getchar();
        getchar();
        system("cls");
        //goto up;
        admin();
      
        }
        else if(i==2){
            mainmenu();
        }
        else{
            system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        goto up;
        }
}
