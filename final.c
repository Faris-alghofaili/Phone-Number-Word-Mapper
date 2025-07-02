#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void writeWordsToFile(char* phoneNumber, char* split1, char* split2, FILE* file, FILE* dictFile);
int binarySearchWord(char* word, FILE* dictFile);
int binarySearchSplit1(char* w1, FILE* dictfile);
int binarySearchSplit2(char* w2, FILE* dictfile);


int main() 
{
        char split1[4];
        char split2[5];
        char phoneNumber[8];
        char tempPhoneNumber[9];
        FILE* file;
        FILE* dictFile;

        printf("Enter a seven-digit phone number (avoid 0 and 1 in the format xxx-xxxx): ");
        scanf("%8s", tempPhoneNumber);

       
        if (strlen(tempPhoneNumber) != 8 || tempPhoneNumber[3] != '-') {
            printf("Invalid input format. Please use the format xxx-xxxx.\n");
            return 1;
        }

    
        strncpy(phoneNumber, tempPhoneNumber, 3);
        strncpy(phoneNumber + 3, tempPhoneNumber + 4, 4);



        phoneNumber[7] = '\0'; 

        strncpy(split1, phoneNumber, 3);
        strncpy(split2, phoneNumber + 3, 4);

        split1[3] = '\0';
        split2[4] = '\0';


        file = fopen("output.txt", "w");
        dictFile = fopen("dict.txt", "r"); 

        if (file == NULL || dictFile == NULL) 
        {
            printf("Error opening file(s).\n");
            return 1;
        }

 
        writeWordsToFile(phoneNumber, split1, split2, file, dictFile);
        fclose(file);
        fclose(dictFile);


        return 0;
}

void writeWordsToFile(char* phoneNumber, char* split1, char* split2, FILE* file, FILE* dictFile) 
{
    char letters[10][4] = { "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY" };


    for (int i = 0; i < 7; i++) 
    {
        if (phoneNumber[i] == '0' || phoneNumber[i] == '1') 
        {
            fprintf(file, "Invalid input. Avoid phone numbers with 0 and 1.\n");
            return;
        }
    }


    for (int i0 = 0; i0 < 3; i0++) 
    {
        for (int i1 = 0; i1 < 3; i1++) 
        {
            for (int i2 = 0; i2 < 3; i2++) 
            {
                for (int i3 = 0; i3 < 3; i3++) 
                {
                    for (int i4 = 0; i4 < 3; i4++) 
                    {
                        for (int i5 = 0; i5 < 3; i5++) 
                        {
                            for (int i6 = 0; i6 < 3; i6++) 
                            {
                                char word[8];
                                sprintf(word, "%c%c%c%c%c%c%c",
                                    letters[phoneNumber[0] - '0'][i0],
                                    letters[phoneNumber[1] - '0'][i1],
                                    letters[phoneNumber[2] - '0'][i2],
                                    letters[phoneNumber[3] - '0'][i3],
                                    letters[phoneNumber[4] - '0'][i4],
                                    letters[phoneNumber[5] - '0'][i5],
                                    letters[phoneNumber[6] - '0'][i6]);

                                char w1[4];
                                char w2[5];

                                sprintf(w1, "%c%c%c",
                                    letters[phoneNumber[0] - '0'][i0],
                                    letters[phoneNumber[1] - '0'][i1],
                                    letters[phoneNumber[2] - '0'][i2]);

                                sprintf(w2, "%c%c%c%c",
                                    letters[phoneNumber[3] - '0'][i3],
                                    letters[phoneNumber[4] - '0'][i4],
                                    letters[phoneNumber[5] - '0'][i5],
                                    letters[phoneNumber[6] - '0'][i6]);


                                for (int j = 0; j < 7; j++) 
                                {
                                    word[j] = tolower(word[j]);
                                }

                                for (int j1 = 0; j1 < 3; j1++)
                                {
                                    w1[j1] = tolower(w1[j1]);
                                }

                                for (int j2 = 0; j2 < 4; j2++)
                                {
                                    w2[j2] = tolower(w2[j2]);
                                }

                                fprintf(file, "%s\n", word);
                                
                                rewind(dictFile);
                                if (binarySearchWord(word, dictFile))
                                {
                                    printf("%s\n", word);
                                }
                                if (binarySearchSplit1(w1, dictFile) && binarySearchSplit2(w2, dictFile))
                                {
                                    printf("%s%s\n", w1,w2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int binarySearchWord(char* word, FILE* dictFile) 
{
    long fileSize, left, right, middle;

    fseek(dictFile, 0, SEEK_END);
    fileSize = ftell(dictFile);
    rewind(dictFile);

    left = 0;
    right = fileSize;

    while (left <= right) 
    {
        middle = (left + right) / 2;
        fseek(dictFile, middle, SEEK_SET);

        while (fgetc(dictFile) != '\n' && ftell(dictFile) < fileSize);

        char currentWord[256];
        fscanf(dictFile, "%255s", currentWord);

        int cmp = strcmp(currentWord, word);

        if (cmp == 0) 
        {
            return 1;
        }
        else if (cmp < 0) 
        {
            left = ftell(dictFile);
        }
        else 
        {
            right = middle - 1;
        }
    }

    return 0; 
}


int binarySearchSplit1(char* w1, FILE* dictFile)
{
    long fileSize, left, right, middle;

    fseek(dictFile, 0, SEEK_END);
    fileSize = ftell(dictFile);
    rewind(dictFile);

    left = 0;
    right = fileSize;

    while (left <= right)
    {
        middle = (left + right) / 2;
        fseek(dictFile, middle, SEEK_SET);

        while (fgetc(dictFile) != '\n' && ftell(dictFile) < fileSize);

        char currentWord[256];
        fscanf(dictFile, "%255s", currentWord);

        int cmp1 = strcmp(currentWord, w1);

        if (cmp1 == 0)
        {
            return 1;
        }
        else if (cmp1 < 0)
        {
            left = ftell(dictFile);
        }
        else
        {
            right = middle - 1;
        }
    }

    return 0;
}

int binarySearchSplit2(char* w2, FILE* dictFile)
{
    long fileSize, left, right, middle;

    fseek(dictFile, 0, SEEK_END);
    fileSize = ftell(dictFile);
    rewind(dictFile);

    left = 0;
    right = fileSize;

    while (left <= right)
    {
        middle = (left + right) / 2;
        fseek(dictFile, middle, SEEK_SET);

        while (fgetc(dictFile) != '\n' && ftell(dictFile) < fileSize);

        char currentWord[256];
        fscanf(dictFile, "%255s", currentWord);

        int cmp2 = strcmp(currentWord, w2);

        if (cmp2 == 0)
        {
            return 1;
        }
        else if (cmp2 < 0)
        {
            left = ftell(dictFile);
        }
        else
        {
            right = middle - 1;
        }
    }

    return 0;
}

