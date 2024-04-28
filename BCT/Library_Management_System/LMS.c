#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
typedef struct books{
    int id;
    char bookName[100];
    char Author[100];
    char date[12];
}lib;
 typedef struct student{
    int id;
    char sName[50];
    char sFaculty[50];
    int sRoll;
    char bookName[50];
    char date[12];
}stud;

void add_book();
void booksList();
void remove_book();
void issueBook();
void issueList();
void searchBook();
 
 
int main()
 {
    
    while(1)
    {
         system("cls");
         int choice;
        printf("<================= LIBRARY MANAGEMENT SYSTEM ================>\n\n");
        printf("1.Add Book\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("6.Search Book\n");
        printf("7.Exit\n");
        printf("Enter your choice :");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:add_book();
            break;

            case 2:booksList();
            break;

            case 3:remove_book();
            break;
             case 4:issueBook();
             break;
             case 5:issueList();
             break;
             case 6:searchBook();
             break;
             case 7:exit(0);
            break;


            default:printf("Invalid Input\n");
        }
        printf("Press any key to continue");
        getch();
        
    }
      return 0;
        }
    void add_book()
    {


        lib b;
        char myDate[12];
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
         sprintf(myDate, "%02d/%02d/%d", tm.tm_mday , tm.tm_mon+1, tm.tm_year + 1900);
         strcpy(b.date, myDate);
        FILE *fp;

        fp=fopen("book.txt","ab");

        printf("Enter book id: ");
        scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);
    printf("Enter Author name: ");
    fflush(stdin);
    gets(b.Author);

 printf("Book Added Successfully \n");

    fwrite(&b, sizeof(lib), 1, fp);

        fclose(fp);
       
    }

    void booksList()
    {
        system("cls");
        lib b;
        FILE *fp;
        
        printf("<==    The Available Books are: ==>   \n");
    
        printf("%-10s %-30s %-20s %s\n\n", "Book id ", "Book Name", "Author", "Date");

        printf("----------------------------------------------------------------------------------\n");
         fp=fopen("book.txt","rb");
        while(fread(&b,sizeof(lib),1,fp)==1)
         {
             printf("%-10d %-30s %-20s %s\n\n",b.id,b.bookName,b.Author ,b.date);
              printf("----------------------------------------------------------------------------------\n");
    }
    fclose(fp);
        }

        void remove_book()
        {
            lib b;
            int tempno;
            FILE *fp,*temp;
            fp=fopen("book.txt","rb");
            temp=fopen("temp.txt","wb");
            printf("Enter the book number to be removed");
            scanf("%d",&tempno);
            while(fread(&b,sizeof(lib),1,fp)==1)
            {
                if(b.id!=tempno)
                 fwrite(&b,sizeof(lib),1,temp);
                else
                printf("%s record is deleted\n",b.bookName);

            }


            fclose(fp);
            fclose(temp);
            fp=fopen("book.txt","wb");
            temp=fopen("temp.txt","rb");
            while(fread(&b,sizeof(lib),1,temp)==1)
            {
        fwrite(&b,sizeof(lib),1,fp);
            }
            fclose(fp);
            fclose(temp);
}
      void issueBook(){
        lib b;
        stud s;
      FILE *fp;
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id

    fp = fopen("book.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
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

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);
    printf("Enter Student Faculty: ");
    fflush(stdin);
    gets(s.sFaculty);
    printf("Enter Student Roll: ");
    scanf("%d",&s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
      }

      void issueList(){
        stud s;
        FILE *fp;

    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-20s %-10s %-10s %-15s %-5s\n\n", "S.id", "Name", "Faculty", "Roll", "Book Name", "Date");
       printf("----------------------------------------------------------------------------------\n");
    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        
    printf("%-10d %-20s %-10s %-10d %-15s %-15s\n", s.id, s.sName, s.sFaculty, s.sRoll, s.bookName, s.date);
       printf("----------------------------------------------------------------------------------\n");
    } 
    fclose(fp);

}
void searchBook() {
    char keyword[100];
    printf("Enter the keyword to search (book name or author): ");
    fflush(stdin);
    gets(keyword);
    FILE *fp;
    lib b;
    int found = 0;
    fp = fopen("book.txt", "rb");
    printf("\n<== Search Results ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");
    printf("--------------------------------------------------------------------------\n");
    while(fread(&b, sizeof(lib), 1, fp) == 1) {
        if(strstr(b.bookName, keyword) != NULL || strstr(b.Author, keyword) != NULL) {
            printf("%-10d %-30s %-20s %s\n\n", b.id, b.bookName, b.Author , b.date);
            printf("--------------------------------------------------------------------------\n");
            found = 1;
        }
    }
    fclose(fp);
    if(!found) {
        printf("No books found matching the keyword '%s'\n\n", keyword);
    }
}
 