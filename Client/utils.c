#include "utils.h"

int isImmat(char immat[8]){
    for(int i = 0; i<1; i++){
        if (immat[i] < 65 || immat[i] > 90){
            return -1;
        }
        else if (immat[i] == 'O' || immat[i] == 'I' || immat[i] == 'U') return -1;
    }

    for(int i = 2; i<5;i++){
        if (immat[i] < 48 || immat[i] > 57) return -1;
    }

    for (int i = 6; i < 7; i++)
    {
        if (immat[i] < 65 || immat[i] > 90)
        {
            return -1;
        }
        else if (immat[i] == 'O' || immat[i] == 'I' || immat[i] == 'U')
            return -1;
    }
    return 0;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}