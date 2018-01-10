#include "client.h"
#include "gestionSocket.h"
#include "utils.h"

int main(void)
{

    int nbServeurs = sizeof(listServ) / sizeof(char[9]);

    char rep = -1;
    do
    {

        printf("Bonjour, que souhaitez vous ? \n 1) Etablir un devis \n 2) Voir mes contrats actuels\n");
        rep = getchar();
    } while (rep < '1' || rep > '2');
    if (rep == '2')
    {
        char immat[8];
        entrerPlaque(immat);

        char categorie;
        char nomServ[10];
        int temps;
        int prixForfait;
        int prixForfaitHT;
        int tempsForfait;

        for (int i = 0; i < nbServeurs; i++)
        {
            int socket = connexion(listServ[i], listPort[i]);
            int type = 2;
            type = htonl(type);
            if (send(socket, &type, sizeof(type), 0) < 0)
                perror("erreur send");

            send(socket, immat, sizeof(immat),0);

            recv(socket, &categorie, sizeof(categorie), 0);
            if (categorie != -1)
            {
                recv(socket, nomServ, sizeof(nomServ), 0);
                recv(socket, &temps, sizeof(temps), 0);
                recv(socket, &prixForfait, sizeof(prixForfait), 0);
                recv(socket, &prixForfaitHT, sizeof(prixForfaitHT), 0);
                recv(socket, &tempsForfait, sizeof(tempsForfait), 0);
                nomServ[sizeof(nomServ)] = '\0'; 
                temps = ntohl(temps);
                prixForfait = ntohl(prixForfait);
                prixForfaitHT = ntohl(prixForfaitHT);
                tempsForfait = ntohl(tempsForfait);
                break;
            }
        }
        if(categorie == -1){ printf("Voiture non trouvée\n");}
        else{
            printf("parking = %s\n", nomServ);
            printf("Durée actuelle = %d\n", temps);
            printf("Durée max = %d\n", tempsForfait);
            int prix;
            if(temps < tempsForfait) {prix = temps*prixForfait;}
            else
                prix = tempsForfait * prixForfait +(temps-tempsForfait)*prixForfaitHT;
            printf("Prix a payé = %d\n", prix);
        }
    }else {
        char immat[8];
        entrerPlaque(immat);
        printf("immat = %s\n",immat);
        char cat;
        cat = entrerCat();
        printf("cat1 = %c\n",cat);
        int duree;
        duree = entrerDuree();
        printf("duree = %d\n", duree);

        char nomServ[10];
        int prixForfait;
        int prixForfaitHT;
        int tempsForfait;

        for (int i = 0; i < nbServeurs; i++)
        {
            int socket = connexion(listServ[i], listPort[i]);
            int type = 1;
            type = htonl(type);
            if (send(socket, &type, sizeof(type), 0) < 0)
            perror("erreur send");
            
            send(socket,&cat, sizeof(cat),0);
            int convDuree = htonl(duree);
            send(socket,&convDuree,sizeof(convDuree),0);

            recv(socket, nomServ, sizeof(nomServ), 0);
            if(nomServ[0] != '\0'){
                recv(socket, &prixForfait, sizeof(prixForfait), 0);
                recv(socket, &prixForfaitHT, sizeof(prixForfaitHT), 0);
                recv(socket, &tempsForfait, sizeof(tempsForfait), 0);

                prixForfait = ntohl(prixForfait);
                prixForfaitHT = ntohl(prixForfaitHT);
                tempsForfait = ntohl(tempsForfait);

                printf("%s propose %d€ pendant %d heures puis %d par heure. Cela fait %d€ pour le temps demandé, %d€ pour une heure de retard et %d€ pour %dH de retard \n",nomServ,prixForfait, tempsForfait, prixForfaitHT, prixForfait*tempsForfait, prixForfait*tempsForfait+prixForfaitHT, prixForfait*tempsForfait+prixForfaitHT*tempsForfait, tempsForfait*2);
            }
            printf("fin boucle \n");
        }
    }
}