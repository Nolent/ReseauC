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
void entrerPlaque(char immat[8])
{
    do
    {
        printf("Entrez votre plaque d'immatriculation\n Exemple : AA135BC\n");
        viderBuffer();
        fgets(immat, 8, stdin);
    } while (isImmat(immat) < 0);
}

char entrerCat(){
    char cat;
    do
    {
        char tmp[2];
        printf("Entrez la catégorie du véhicule (lettre minuscule)\n");
        viderBuffer();
        fgets(tmp, 2, stdin);
        cat = tmp[0];
        printf("cat = %c\n",cat);
    } while (cat > 122 || cat < 97);
    return cat;
}

int entrerDuree(){
    char *n = NULL;
    int duree;
    do
    {
        char tmp[3];
        printf("Entrez la durée\n");
        viderBuffer();
        fgets(tmp, 3, stdin);
        duree = strtol(tmp,&n,10);
        printf("dureefont = %d", duree);
    } while (*n != '\n');
    return duree;
}