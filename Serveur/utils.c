#include "utils.h"


void getImmat(char message[]){
    char immat[8];
    for(int i =0; i< 7; i++){
        immat[i] = message[i]; 
    }
    strcpy(message,immat);
}

int findImmat(char immat[8],char listVoiture[][9] , int nbVoiture){
    for(int i = 0; i<nbVoiture; i++){
        int diff = 0;
        for(int j = 0; j<8;j++){
            if (immat[j] != listVoiture[i][j]) diff++;
        }
        if(diff == 0) return i;
    }return -1;
}



