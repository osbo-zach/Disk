#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) 
{
    char * inputFile = argv[1];
    char * method = argv[2];
    char * offset = argv[3];
    int offsetNum = atoi(offset);
    int methodInt;
    
    if (strcmp(method, "skew") == 0 || strcmp(method, "Skew") == 0)
    {
        methodInt = 0;
    }
    else if (strcmp(method, "interleaving") == 0 || strcmp(method, "Interleaving") == 0)
    {
        methodInt = 1;
    }
    else
    {
        printf("INVALID INPUT: ");
        printf("%s\n", method);
        return 0;
    }
    
    FILE *in = fopen(inputFile, "r"); 
    if (in == NULL) return;
    
    char str[10000];
    char line[100];
    int length;
    char editLine[100];
    int i;
    int j;
    int k;
    int a;
    int b;

 while (fgets(line, 100, in) != NULL) 
    {
        length = strlen(line) - 1;
        if (offsetNum > length)
        {
            offsetNum = offsetNum % length;
        }
        switch(methodInt)
        {
            case 0:
                for (i = 0; i < offsetNum; i++)
                {
                    editLine[i] = line[i + (length - offsetNum)];
                }
                for (j = offsetNum; j < length; j++)
                {
                    editLine[j] = line[j - offsetNum];
                }
                editLine[length] = '\n';
            break;
            
            case 1:
            k = 0;
            a = 0;
            b = 3;
            
                if (offsetNum == 1)
                {
                    for (i = 0; i < length; i++)
                    {
                        if (i % 2 == 0)
                        {
                            editLine[i] = line[a];
                            a++;
                        }
                        else
                        {
                            editLine[i] = line[(length/2) + k];
                            k++;
                        }
                    }
                    editLine[length] = '\n';
                }
                
                else if (offsetNum == 2)
                {
                    for (i = 0; i < length; i++)
                    {
                        if (i % 3 == 0)
                        {
                            editLine[i] = line[a];
                            a++;
                        }
                        else if ((i - 1) % 3 == 0)
                        {
                            editLine[i] = line[(length/2 - 1) + k];
                            k++;
                        }
                        else if ((i + 1) % 3 == 0)
                        {
                            editLine[i] = line[length/2 - 1 + b];
                            b++;
                        }
                    }
                    editLine[length] = '\n';
                }
                
                else
                {
                    printf("INVALID OFFSET FOR INTERLEAVING");
                    return 0;
                }
            break;
        }
        strcat(str, editLine);
    }
printf("%s", str);

char filename[20];

strcpy(filename, inputFile);
strcat(filename, method);

FILE *fp;
fp = fopen(filename,"w+");
fputs(str,fp);
fclose(fp);


    return 0;
}