int positionCodeGenetator(char[]);
int letterIndex(char ch);
int lastLetterIndex(char ch);
void postitionCodeDecoder(int, char*);
char positionPrefix(int, int);
int positionCodeGenetator(char moveFromTo[])
{
    // In this function position of each block is generated in code.
    char prefix;
    // converting the board number position as character into integer.
    int suffix = (moveFromTo[1] - '0');

    prefix = moveFromTo[0];
    int i, j, k, position, last;
    for (i = suffix; i >= 1; i--)
    {
        for (j = prefix; j <= (prefix + 8); j++)
        {
            position = ((((9 - suffix) * 10000) + 1000) + (letterIndex(prefix) * 100)) + lastLetterIndex(prefix);
            return position;
        }
    }
}

int letterIndex(char ch)
{
    // Returning the corresponding code of characters.
    if (ch == 'a' || ch == 'b')
    {
        return 0;
    }
    else if (ch == 'c' || ch == 'd')
    {
        return 1;
    }
    else if (ch == 'e' || ch == 'f')
    {
        return 2;
    }
    else if (ch == 'g' || ch == 'h')
    {
        return 3;
    }
}
int lastLetterIndex(char ch)
{
    // Returning the corresponding code of characters.
    if (ch == 'a' || ch == 'c' || ch == 'e' || ch == 'g')
    {
        return 30;
    }
    else if (ch == 'b' || ch == 'd' || ch == 'f' || ch == 'h')
    {
        return 11;
    }
}

void postitionCodeDecoder(int positionCode, char *position)
{
    int i = 0,j,k,pos[6];
    while(i != 5)
    {
        pos[i] = positionCode % 10;
        positionCode /= 10;
        i++;
    }
    // Finding the actual value of position j.
    pos[1] = (pos[1] * 10) + pos[0];
    printf("\n%d\n",pos[1]);

    // Finding the actual value of position of row form bottom to top in ascending order.
    pos[4] = 9 - pos[4];
    printf("\n%d\n",pos[4]);

    *(position + 0) = positionPrefix(pos[2],pos[1]);
    *(position + 1) = pos[4] + '0';
    *(position + 2) = '\0';


}

char positionPrefix(int k, int j)
{
    if(k == 0)
    {
        if(j == 30)
           return 'a';
        else
           return 'b';   
    }
    else if(k == 1)
    {
         if(j == 30)
           return 'c';
        else
           return 'd';  
    }
    else if(k == 2)
    {
         if(j == 30)
           return 'e';
        else
           return 'f';  
    }
    else if(k == 3)
    {
         if(j == 30)
           return 'g';
        else
           return 'h';  
    }
}