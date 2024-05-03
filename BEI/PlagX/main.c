#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

#define maxWords 1000
#define maxWordLen 50

int i,j;

void removePunctuation(char *);
void lowercase(char *);
float checkSimilarity( FILE *, FILE *);

int main()
{
    FILE *file1;
    FILE *file2;
    FILE *output;
    char file1Name[20],file2Name[20];
    float similarityPercent;

    printf("\n\t\t\t\t\t");
	printf("\033[1mPlagX\033[0m\n\n");
	printf("\t\t\t\t");

    printf("Loading");
    fflush(stdout);


    for (i=0; i<10; i++)
        {
            usleep(500000);
            printf(".");
            fflush(stdout);
        }

    system("cls");
    printf("\t \t \t \t ");
	printf("\033[1mPlagX\033[0m\n\n");

    printf("Enter the name of first file: ");
    scanf("%s",file1Name);
    printf("Enter the name of second file: ");
    scanf("%s",file2Name);

    file1=fopen(file1Name,"r");
    file2=fopen(file2Name,"r");
    output=fopen("result.txt","a");

    if(file1==NULL || file2==NULL)
    {
        printf("Error opening files\n");
        exit(1);
    }

    similarityPercent=checkSimilarity(file1, file2);
    fprintf(output, "Similarity between %s and %s = %.2f%%\n", file1Name,file2Name,similarityPercent);
    printf("Similarity Percentage= %.2f%%",similarityPercent);

    fclose(file1);
    fclose(file2);
    return 0;
}

void removePunctuation(char *word)
{
    int len;

    len=strlen(word);
    for(i=0;i<len;i++)
    {
        if(ispunct(word[i]))
        {
            for(j=i;j<len-1;j++)
            {
                word[j]=word[j+1];
            }
            len=len-1;
            word[len]='\0';
        }
    }
}

void lowercase(char *word)
{
    for(i=0;word[i]!='\0';i++)
    {
        word[i]=tolower(word[i]);
    }
}

float checkSimilarity(FILE *file1, FILE *file2)
{
    char word1[maxWordLen], word2[maxWordLen];
    char words1[maxWords][maxWordLen];
    char words2[maxWords][maxWordLen];
    int numOfWords1=0, numOfWords2=0;
    int commonWords=0;
    float similarityPercent;

    while(fscanf(file1,"%s",word1)==1)
    {
        removePunctuation(word1);
        lowercase(word1);
        strcpy(words1[numOfWords1],word1);
        numOfWords1=numOfWords1+1;
    }

     while(fscanf(file2,"%s",word2)==1)
    {
        removePunctuation(word2);
        lowercase(word2);
        strcpy(words2[numOfWords2],word2);
        numOfWords2=numOfWords2+1;

        for(i=0;i<numOfWords1;i++)
        {
            if(strcmp(words1[i],word2)==0)
            {
                commonWords=commonWords+1;
                break;
            }
        }
    }

    similarityPercent=((float)commonWords/numOfWords2)*100;
    return(similarityPercent);
}