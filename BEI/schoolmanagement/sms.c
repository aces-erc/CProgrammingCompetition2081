#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define PASSWORD "erc_dharan"

typedef struct student {
    int rno;
    char name[20];
    struct subject {
        int scode;
        char sname;
        int mark;
    } sub[6];
    int total;
    float per;
} student;
int compare(const void *a, const void *b) {
    return ((student *)a)->rno - ((student *)b)->rno;
}
void sms();
void create();
void display();
void append();
void noofrecord();
void search();
void update();
void delete();
void sort();

int main() {
    char password[20];
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password. Exiting...\n");
        return 1;
    }

   
    int ch;
    do {
        system("cls");
         sms();
        printf("\n1.Create record");
        printf("\n2.Display records");
        printf("\n3.Add");
        printf("\n4.No of record");
        printf("\n5.Search record(by rollno)");
        printf("\n6.Update record");
        printf("\n7.Delete record");
        printf("\n8.See your rank");
        printf("\n0.Exit");

        printf("\nEnter what you want:");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            create();
            break;

        case 2:
            display();
            break;

        case 3:
            append();
            break;

        case 4:
            noofrecord();
            break;

        case 5:
            search();
            break;

        case 6:
            update();
            break;

        case 7:
            delete();
            break;

        case 8:
            sort();
            break;
        }

        printf("\nPress any key to continue...");
        getch(); 
    } while (ch != 0);
    return 0;
}

void sms() {
    printf("***WELCOME TO SCHOOL MANAGEMENT SYSTEM!!!***");
    printf("\n\n");
}

void create()
{

	student *s;
	FILE *fp;
	int n,i,j;
	printf("Enter the number of student you want to record:");
	scanf("%d",&n);
	s = (student*)calloc(n,sizeof(student));
	fp = fopen("mystudent.txt","w");

	for (i=0;i<n;i++)
	{
		printf("Enter roll no:");
		scanf("%d",&s[i]);
		fflush(stdin);

		printf("Enter Name :");
		scanf("%[^\n]s",s[i].name);
		fflush(stdin);

		for (j=0;j<6;j++)
		{
			printf("Enter the marks of subject %d ",j+1);
			scanf("%d",&s[i].sub[j].mark);
			s[i].total+=s[i].sub[j].mark;

		}
		s[i].per = s[i].total / 6.00;
		fwrite(&s[i],sizeof(student),1,fp);
	}
fclose(fp);
}


void display() {
    student s1;
    int i,j, count = 0;
    FILE *fp;
    fp = fopen("mystudent.txt", "r");
    
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    
    while (fread(&s1, sizeof(student), 1, fp)) {
        count++;
    }
    rewind(fp);

    
    student *students = malloc(count * sizeof(student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }

    count = 0;
    while (fread(&s1, sizeof(student), 1, fp)) {
        students[count++] = s1;
    }
    fclose(fp);

    
    qsort(students, count, sizeof(student), compare);

    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\n| Roll No |      Name       | Sub1 | Sub2 | Sub3 | Sub4 | Sub5 | Sub6 | Total | Percentage |");
    printf("\n--------------------------------------------------------------------------------------------------------");

   
    for (i = 0; i < count; i++) {
        printf("\n| %-7d| %-16s|", students[i].rno, students[i].name);
        
        for (j = 0; j < 6; j++) {
            printf(" %-5d|", students[i].sub[j].mark);
        }

        printf(" %-5d| %-10.2f%%|", students[i].total, students[i].per);
    }

    printf("\n--------------------------------------------------------------------------------------------------------");

    
    free(students);
}

void append()
{

	student *s;
	FILE *fp;
	int n,i,j;
	printf("Enter how many students you want:");
	scanf("%d",&n);
	s = (student*)calloc(n,sizeof(student));
	fp = fopen("mystudent.txt","a");

	for (i=0;i<n;i++)
	{
		printf("Enter roll no:");
		scanf("%d",&s[i]);
		fflush(stdin);

		printf("Enter Name :");
		scanf("%[^\n]s",s[i].name);

		for (j=0;j<6;j++)
		{
			printf("Enter the marks of subject %d " ,j+1);
			scanf("%d",&s[i].sub[j].mark);
			s[i].total+=s[i].sub[j].mark;

		}
		s[i].per = s[i].total / 6.00;
		fwrite(&s[i],sizeof(student),1,fp);
	}
fclose(fp);

}
void noofrecord()
{
	student s1;
	FILE *fp;
	fp = fopen("mystudent.txt","r");
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(student);
	printf("\n \n NO OF RECORDS = %d",n);
	fclose(fp);
}
void search()
{
    student s1;
    int j,rno;
    int found = 0;
    FILE *fp;
    fp = fopen("mystudent.txt","r");
    
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\n| Roll No |      Name       | Sub1 | Sub2 | Sub3 | Sub4 | Sub5 | Sub6 | Total | Percentage |");
    printf("\n--------------------------------------------------------------------------------------------------------");

    printf("\nEnter roll no to search: ");
    scanf("%d", &rno);
    
    while(fread(&s1,sizeof(student),1,fp))
    {
        if (s1.rno == rno)
        {
            found = 1 ;
            printf("\n| %-7d| %-16s|", s1.rno, s1.name);
            
            for (j = 0; j < 6; j++)
            {
                printf(" %-5d|", s1.sub[j].mark);
            }
            
            printf(" %-5d| %-10.2f%|", s1.total, s1.per);
        }
    }
    
    if (!found)
        printf("\nRecord not found. Enter a valid roll no.");

    printf("\n--------------------------------------------------------------------------------------------------------");
    fclose(fp);
}

void update() {
    student s1;
    int j, rno;
    int found = 0;
    FILE *fp, *fp1;
    fp = fopen("mystudent.txt", "r");
    fp1 = fopen("temp.txt", "w");

    printf("Enter roll no to update:");
    scanf("%d", &rno);

    while (fread(&s1, sizeof(student), 1, fp)) {
        if (s1.rno == rno) {
            found = 1;
            fflush(stdin);
            printf("Enter new Name: ");
            scanf(" %[^\n]s", s1.name);

            s1.total = 0;
            for (j = 0; j < 6; j++) {
                printf("Enter the new marks of subject %d: ", j + 1);
                scanf("%d", &s1.sub[j].mark);
                s1.total += s1.sub[j].mark;
            }
            s1.per = s1.total / 6.00;
            fwrite(&s1, sizeof(student), 1, fp1);
        } else {
            fwrite(&s1, sizeof(student), 1, fp1); // Write unchanged record to temp file
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        fp = fopen("temp.txt", "r");
        fp1 = fopen("mystudent.txt", "w");

        while (fread(&s1, sizeof(student), 1, fp)) {
            fwrite(&s1, sizeof(student), 1, fp1);
        }

        fclose(fp);
        fclose(fp1);
    } else {
        printf("\nRecord not found. Enter a valid roll no.\n");
    }
}


void delete()
{


    student s1;
	int j,rno;
	int found = 0;
	FILE *fp,*fp1;
	fp = fopen("mystudent.txt","r");
	fp1 = fopen("temp.txt","w");

	printf("Enter roll no to delete:");
	scanf("%d",&rno);
	while(fread(&s1,sizeof(student),1,fp))
	{
		if (s1.rno == rno){
		found =1 ;

        }
        else
        fwrite(&s1,sizeof(student),1,fp1);
	}

	fclose(fp);
	fclose(fp1);

	if (found)
	{
		fp = fopen("temp.txt","r");
		fp1 = fopen("mystudent.txt","w");

		while(fread(&s1,sizeof(student),1,fp))
		{
			fwrite(&s1,sizeof(student),1,fp1);
		}

		fclose(fp);
		fclose(fp1);
	}
	else

		printf("\nRecord not found \n Enter valid roll no\n");

}
void sort()
{
    student *s, s1;
    FILE *fp;
    int i,j;
    fp = fopen("mystudent.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    s = (student*)calloc(n,sizeof(student));

    rewind(fp);
    for (i = 0; i < n; i++)
        fread(&s[i], sizeof(student), 1, fp);

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i].total < s[j].total)
            {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }

    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\n| Rank | Roll No |      Name       | Sub1 | Sub2 | Sub3 | Sub4 | Sub5 | Sub6 | Total | Percentage |");
    printf("\n--------------------------------------------------------------------------------------------------------");

    for (i = 0; i < n; i++)
    {
        printf("\n| %-4d | %-7d| %-16s|", i+1, s[i].rno, s[i].name);

        for (j = 0; j < 6; j++)
        {
            printf(" %-5d|", s[i].sub[j].mark);
        }

        printf(" %-5d| %-10.2f%|", s[i].total, s[i].per);
    }

    printf("\n--------------------------------------------------------------------------------------------------------");
    fclose(fp);
}
