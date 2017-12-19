#include "client.h"
#include "gestionSocket.h"
#include "utils.h"

int main(void)
{
    int tube[2];
    pipe(tube);
    int nbServeurs = sizeof(listServ) / sizeof(char[9]);
    int *pid = malloc(nbServeurs * sizeof(int));
    int pidGP = getppid();
    
    for (int i = 0; i < nbServeurs; i++)
    {
        int socket = connexion(listServ[i], PORT);
        if (socket < 0)
            perror("erreur connect\n");

        if(getppid()==pidGP){
            pid[i] = fork();
            if(pid[i] < 0){
                perror("Erreur fork");
            }
        }
        else{
            printf("enfant %d\n", i);
            break;
        }
    }
    if (getppid() == pidGP)
    {
        char rep = -1;
        do
        {
            
            printf("Bonjour, que souhaitez vous ? \n 1) Etablir un contrat \n 2) Voir mes contrats actuels\n");
            rep = getchar();
        } while (rep < '1' || rep > '2');
        if (rep == '2')
        {
            char immat[8];
            do
            {
                printf("Entrez votre plaque d'immatriculation\n Exemple : AA135BC\n");
                viderBuffer();
                fgets(immat, 8, stdin);
            } while (isImmat(immat) < 0);
        }
    }
}