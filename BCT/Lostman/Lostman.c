#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#define SIZE 15


#define MAX_USERS 10
#define USERNAME_LEN 30


typedef struct {
    char username[USERNAME_LEN];    
} User;

User users[MAX_USERS];
int userCount = 0;





void welcome();
void start();
void clrscr();
void f(char *s);
void print_board();
void foundWord();


void welcome (){
    system("cls");
    printf("                                        +------------------------------------------------------------+\n");
    f(" ");
    f(" ");
    f(" ");
    f(" DANGER");
    f(" DANGER ");
    f(" DANGER ");
    f(" ");
    f(" ");
    f(" ");
    f(" ");
    f(" ");
    printf("                                        +------------------------------------------------------------+\n");
    sleep(4);




}
void print_board() {
    char words[9][9] =       {'P', 'C', 'I',   'R', 'C', 'L',   'E', 'M', 'Q',

                              'Z', 'D', 'O',   'R', 'L', 'I',   'V', 'E', 'F',

                              'L', 'T', 'L',   'O', 'L', 'H',   'O', 'F', '0',

                              'L', 'H', 'Y',   'P', 'A', 'O',   'S', 'A', 'D',

                              'B', 'E', 'P',   'E', 'Z', 'P',   'T', 'X', 'S',

                              'I', 'A', 'G',   'E', 'F', 'S',   'V', 'F', 'H',

                              'B', 'T', 'W',   'A', 'R', 'I',   'T', 'Y', 'A',

                              'O', 'R', 'B',   'O', 'W', 'S',   'K', 'X', 'R',

                              'Y', 'E', 'N',   'I', 'S', 'S',   'O', 'A', 'P',};
   
    int i,j,a ;
    system("cls"); 
    printf("                                     PHASE 1");
    printf ("\n                                                              THE WORD SEARCH\n");
    printf("\n");
    
    printf("                                             ");
    for (i = 0; i < 9; i++) {
        printf("+----");
    }
    printf("+\n");

    
    for (i = 0; i < 9; i++ ){
       printf("                                           ");
        for (j = 0; j < 9; j++) {
             if (j == 0)
             printf("  ");
             else if ((j) % 1 == 0)
                printf("");
            printf("| %c  ", words[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");

        
        printf("                                             ");
        for (j = 0; j < 9; j++) {
            printf("+----");
        }
        printf("+\n");     
    }
  }


bool starting_screen(){
    char d;
    int count = 0;
    system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f("\e[1m >START \e[0m      ");
                f(" EXIT ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
    while (1){
        d = getch();
        if (d!=13){
            count = count + 1;    
            switch (count % 2){
                case 0:
                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f("\e[1m >START \e[0m      ");
                f(" EXIT ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                break;

                case 1:
                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" START ");
                f(" \e[1m >EXIT \e[0m ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                break;
            }
        }else{
            return (count % 2);
        }
    }
    

}


void start() {
    User newUser;
    char d;
    int count = 0; 
    char name[30];
               system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" ");
                f(" \e[1m > ENTER YOUR NAME \e[0m ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
               
    while (1){
        d = getch();
        if (d!=13){
            
            count = count + 1;  
            
            switch (count){
                case 1:
                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" ");
                f(" \e[1m > ENTER YOUR NAME \e[0m ");
                f(" ");
                f(" ");
                f(" ");
                f(" "); 
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                scanf(" %s", newUser.username);

                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" YOU ARE IN OUR TERRITORY ");
                f(" ");
                 printf("                                        |                          %s !                          |\n", newUser.username );
                f(" ");
                f(" ");
                f(" "); 
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                sleep(2);

                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" SOLVE TO GET OUT ");
                f(" ");
                f(" ");
                f(" ");
                f(" ");
                f(" "); 
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                sleep(2);
                system("cls");
                printf("                                        +------------------------------------------------------------+\n");
                f(" ");
                f(" LOST MAN ");
                f(" ");
                f(" ");
                f(" ");
                f(" FIRST PHASE ");
                f(" ");
                f(" ");
                f(" ");
                f(" "); 
                f(" ");
                printf("                                        +------------------------------------------------------------+\n");
                sleep(2);      
                return;
            }
        }
    }
    
}

int level_1(){
    int i,j;
    print_board();
    
    
    char* words[SIZE] = {"CIRCLE", "SAD", "BOY", "LIVE", "HOP", "SHARP", "THEATRE", "ROPE", "BOW", "WAR", "SOAP", "EAT", "AGE","HEAT",};
    char guess[10];
    int score = 0;
    printf("\n");
    printf("                                               SEARCH WORDS FROM THE GRID AND MOVE AHEAD\n");
    
    for (i=0; i<SIZE && score<5; i++ )
         { printf("                                                       Enter YOUR WORD : ");
         scanf("%s", guess);
        for (j=0; j<SIZE; j++){
        if (strcmp(guess, words[j]) == 0){
                if (guess == "CIRCLE")

            break;
        }
        }
        score=score+1;
     }
   
        system ("cls");
        
    return 0;
}

void f(char *s)
{
printf("                                        %c%*s%*s%c\n",179,30+strlen(s)/2,s,30-strlen(s)/2,"",179);
}
 
void riddle() {
    char guess[20];
    int i, p = 0;
    char *clues[] = {
        "The more you take, the more you leave behind.?", 
        "I'm tall when I'm young, and I'm short when I'm old. What am I?", 
        "What has keys, but can't open locks?" 
    };

    char *answers[] = {
        "footsteps", 
        "candle",    
        "piano"      
    };


     for (i = 0; i < 3; i++) {
        while(1) {
            system("cls");
            printf("Level %d: %s\n", i + 1, clues[i]);
            printf("Enter your answer: ");
            scanf("%19s", guess); 

            if (strcmp(guess, answers[i]) == 0) {
                printf("Level %d is completed\n", i + 1);
                sleep(3);
                p++;
                break;
            } else {
                      printf("You are in danger, haha hahaha");
                            
                sleep(3);
            }
        }
    }
    
    if (p == 3) {
        printf("\n");
    }
    return;
}

int main()
{
    FILE*project;
    project=fopen("FINAL.txt","w");
    if(project==NULL)
    {
        printf("file cannot be opened\n");
        exit(0);
    }
    else{

int i;
    welcome();
    if (starting_screen()){
        system("cls");
        printf("                                        +------------------------------------------------------------+\n");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        f(" THANK YOU! ");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        printf("                                        +------------------------------------------------------------+\n");
        exit(1);
    } 

 
    } 
    start();
    level_1();
     system("cls");
     printf("                                        +------------------------------------------------------------+\n");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        f(" SECOND PHASE ");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        printf("                                        +------------------------------------------------------------+\n");
        sleep(2);

    riddle();

    system("cls");
     printf("                                        +------------------------------------------------------------+\n");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        f(" YOU HAVE SURVIVED ");
        f(" ");
        f(" ");
        f(" ");
        f(" ");
        printf("                                        +------------------------------------------------------------+\n");
        


    return 0;
}