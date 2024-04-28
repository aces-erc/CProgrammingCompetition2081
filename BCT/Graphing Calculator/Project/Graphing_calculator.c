#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a;
    char r1;
    FILE *repo1;
    printf("1.Enter the function\n2.Help\n");
    scanf("%d",&a);
    switch(a)
    {
        case 1:
            system("editfun.exe");
            break;
        case 2:
            if(repo1==NULL)
            {
                printf("File doesnot exist");
            }
            repo1=fopen("function-repo.txt","r");
            while(fscanf(repo1,"%c",&r1)!=EOF)
            {

                printf("%c",r1);
            }
            getch();
            fclose(repo1);
                }
    return 0;
}