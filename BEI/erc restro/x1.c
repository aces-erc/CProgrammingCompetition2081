#include<stdio.h>
#include<string.h>
#include<math.h>


void mainmenu();
void display_menu();
void contact();
void about_us();
void exit_it();
void menucard();
  struct info{ 
  char name[50];
  int age;
  char gender;
  }  s[1];
  int main()
  {  
  
  
   printf("\t\t\t\t<<<-----  FOOD ORDER C PROJECT------>>>\n\n\n");

   printf("\t\t\t<<<     WELCOME TO OUR ERC RESTRO      >>> \n ");
   printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t            A place where you can have quality time and foood :)\n\n");

   printf ("\n\n HELLO! ENTER YOUR NAME : ");
   gets(s[1].name);
   printf ("\n\n ENTER YOUR AGE : ");
   scanf ("%d",&s[1].age);
   printf ("\n\n ENTER YOUR GENDER  ( M  /  F ): ");
   scanf ("%s",&s[1].gender);
   
   if (s[1].gender=='M'|| s[1].gender=='m')
   {
   printf ("\n\n\t<----WELCOME TO OUR RESTRO Mr. %s---->\n\t",s[1].name);
   }
   else if (s[1].gender=='F'|| s[1].gender=='f')
   {
   printf ("\n\n\t<----WELCOME TO OUR STORE Miss. %s---->\n\t",s[1].name);
   }
   else
   {
   printf("\n\n\t<----Invalid INPUT---->\n\t"); 
      }
	  mainmenu();
	      return 0;
		  }
           void mainmenu()
		   {
		   int choice;
		   printf ("\n1.DISPLAY MENU \n2.CONTACT \n3.ABOUT US \n4.EXIT");
		   printf ("\nCHOOSE ANY OPTION YOU WANT : ");
		   scanf ("%d",&choice);
		   switch (choice)
		   
		   {
		   	case 1:
			   display_menu();
			   break;
			case 2:
			   contact();
			   break;
			case 3:
			   about_us();
			   break;
			case 4:
			   exit_it();
			   break;
			default:
				printf("\n Please enter a valid option");
		   }
	}
	void contact()
	{
	printf ("\n\n\t<<FOR DELIVERY>>\n\n\t");
	printf ("\n\tYOU CAN CALL US AT ---> 9810000000 ");
	printf ("\n\tYOU CAN contact US AT ---> ercrestro@gmail.com");
	printf ("\n\t OR VISIT OUR WEBSITE:");
	printf ("\t www.ERCrestro.com");
	printf ("\n\n");
	mainmenu();
	}
	void about_us()
	{
	printf ("\n\n\t<<<ABOUT US>>>\t");
	printf("\n<<<---WE AIM TO PROVIDE BEST FOOD FOR OUR CUSTOMERS--->>>");
	printf ("\n\n\t---TIMINGS---\n");
	printf ("\nMON - FRI:  10AM - 9PM");
	printf ("\nSAT - SUN:  12PM - 12PM");
	printf ("\n\n");
	mainmenu();
	}
	void exit_it()
	{
	printf ("\nHOPE TO SEE YOU AGAIN. :) ");
	}
	void display_menu()
	{
	printf ("\n\n\t<<<<<          MENU           >>>>>\n");
	printf("-------------------------------------------\n");
	
	printf ("\nS#  ITEMS                  |        PRICE");
	printf("\n----------------------------------------------\n");
	printf ("\nD1. Chicken Momo           |        Rs.100/-");
	printf ("\nD2. Chicken Burger         |        Rs.200/-");
	printf ("\nD3.  Chicken lolipop       |        Rs.300/-");
	printf ("\nD4. Buttter Chicken        |        Rs.400/-");
	printf ("\nD5. Chicken Pizza          |        Rs.500/-");
	printf ("\nD6. Burger+Pizza(offer)    |        Rs.600/-");
	int select;
	printf ("\n\n\n<<< 1.SELECT YOUR ORDER \n\n\n<<< 2.GO BACK");
	    printf ("\n\nCHOOSE YOUR PREFERRED OPTION : "); 
		   scanf ("%d",&select);
		   switch (select)
		   {
		    case 1:
		       menucard();
		       break;
		    case 2:
		       mainmenu();
			   break;
			default:
			printf("\n\n\t<<<INVALID INPUT>>>\n\n");
			}
			}
	/// @brief 
	void menucard()
		{ 
			
			int n,order[n];
			float total;
			int b,i,serial;
				printf("\nPLESE ENTER THE NUMBER OF ITEMS YOU WANT TO ORDER  : "); 
				scanf("%d",&n);
			    if(n<=0)
			    exit_it();
				   else {
				       for( i=0;i<n;i++)
					   {
					   
					   
					     printf ("\n\nPLEASE ENTER THE SERIAL NUMBER (S#) OF YOUR ITEM NUMBER  %d:\tD",i+1);
					     scanf ("%d",&serial);
						 order[i]=serial*100;
						  
						  }
						  for(i=0;i<n;i++)
						  {
						  total+=order[i];
						  }
						  printf("\n\n\t\t YOUR BILL WITHOUT TAX IS = %.2frs",total );
						  printf ("\n\n\t YOUR TOTAL AMOUNT AFTER 10 PERCENT SERVICE CHARGE = %.4frs",total+=total*0.10);
						  printf ("\n\n\n\t<<<<<YOUR ORDER HAS BEEN RECIEVED. PLEASE WAIT 10 MINUTES FOR YOUR ORDER>>>>>");
						  printf ("\n\n\n\t     ---Pay your bill at the cash counter & Enjoy your meal :)  \n\n\n\t\t\t");
						  printf("\n\n\n THANK YOU!   \n\n\n\t");
						  exit_it();
						   }
}