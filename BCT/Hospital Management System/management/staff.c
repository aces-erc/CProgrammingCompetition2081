#include "staff.h"
void add_record()
{
    staff s;
    FILE *myfile;
    printf("Enter staffid:\n");
    scanf("%d",&s.staffid);
    printf("Enter position:\n");
    scanf("%s",s.staffposition);
    printf("Enter Name\n");
    scanf("%s%s",s.firstname,s.lastname);
    printf("Enter Address\n");
    scanf("%s",s.address);
    printf("Enter Phone number:\n");
    scanf(" %lld",&s.phoneno);
    printf("Enter salary:\n");
    scanf("%f",&s.salary);

    myfile = fopen("myfile.bin","ab");
    fwrite(&s,sizeof(staff),1,myfile);
    fclose(myfile);
    printf("Record added");
}
void display_record()
{
    staff s;
    FILE *myfile;
    myfile = fopen("myfile.bin","rb");
    if(myfile==NULL)
    {
        printf("File cannot be opened!!!!1");
    }
    else{
    printf("The records are:\n");
    while(fread(&s,sizeof(staff),1,myfile)==1)
    {
        printf("Staff ID=%d\n Position =%s\n  Name=%s%s\n Address=%s\n phone no=%lld\n salary=%.2f\n",s.staffid,s.staffposition,s.firstname,s.lastname,s.address,s.phoneno,s.salary);
        printf("----------------------------------\n");
    }
    fclose(myfile);
    }
}


void update_record() {
    staff s;
    int tempno, i;
    float tempsal;
    char temp[30];
    FILE *myfile;

    myfile = fopen("myfile.bin", "r+b"); // Corrected assignment operator

    if (myfile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the staff ID: ");
    scanf("%d", &tempno);

    while (fread(&s, sizeof(staff), 1, myfile) == 1) {
        if (s.staffid == tempno) {
            printf("What would you like to update?\n");
            printf("1. Update position\n");
            printf("2. Update salary\n");
            scanf("%d", &i);

            if (i == 1) {
                printf("Enter new Position: ");
                scanf("%s", temp);
                strcpy(s.staffposition, temp);

                fseek(myfile, -sizeof(staff), SEEK_CUR);
                fwrite(&s, sizeof(staff), 1, myfile);
                printf("%s's position has been updated.\n", s.firstname);
                break;
            } else if (i == 2) {
                printf("Enter new salary: ");
                scanf("%f", &tempsal);
                s.salary = tempsal;

                fseek(myfile, -sizeof(staff), SEEK_CUR);
                fwrite(&s, sizeof(staff), 1, myfile);
                printf("%s's salary has been updated.\n", s.firstname);
                break;
            } else {
                printf("Invalid input!\n");
            }
        }
    }

    // Check if the staff ID was not found during the search
    if (feof(myfile)) {
        printf("Staff ID not found.\n");
    }

    fclose(myfile);
}

void delete_record()
{
    staff s;
    int tempno;
    FILE *myfile,*temp;
    myfile = fopen("myfile.bin","rb");
    temp = fopen("temp.bin","wb");
    printf("Enter the staff id:");
    scanf("%d",&tempno);
    while(fread(&s,sizeof(staff),1,myfile)==1)
    {
        if(s.staffid != tempno)
            fwrite(&s,sizeof(staff),1,temp);
        else
            printf("%s record is deleted\n",s.firstname);
    }
    fclose(myfile);
    fclose(temp);
    myfile = fopen("myfile.bin","wb");
    temp = fopen("temp.bin","rb");
    while(fread(&s,sizeof(staff),1,temp)==1)
    {
        fwrite(&s,sizeof(staff),1,myfile);
    }
    fclose(myfile);
    fclose(temp);
}
void search_record()
{
    staff s;
    int stid;
    int count;
    count = 0;
    FILE *myfile;
    myfile = fopen("myfile.bin","rb");
    printf("Enter Staff id:\n");
    scanf("%d",&stid);
    while(fread(&s,sizeof(staff),1,myfile)==1){
    if(s.staffid==stid)
    {
        printf("Staff ID=%d\n Position =%s\n  Name=%s%s\n Address=%s\n phone no=%lld\n salary=%.2f\n",s.staffid,s.staffposition,s.firstname,s.lastname,s.address,s.phoneno,s.salary);
        count+=1;
    }}
    if(count == 0)
    {
        printf("Record doesn't Exist");
    }
    fclose(myfile);
}
int staff_management()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("Staff Management System\n1.Add Record\n2.Display Record\n3.Update Record\n4. Delete Record\n5. Search Record\n6.Exit to Main Menu\n");
        printf("....");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1: add_record();
            break;
        case 2: display_record();
            break;
        case 3: update_record();
            break;
        case 4: delete_record();
            break;
        case 5: search_record();
             break;
         case 6:
        management_system();
            break;
        default: printf("Invalid Input\n");
        }
        getch();
    }
    return 0;
}
