#include "serveur.h"

int main(int argc, char *argv[])
{
    printf("debut\n");
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 6)) < 0)
    {
        perror("Erreur socket");
        exit(-1);
    }
    struct sockaddr_in serv, client;
    socklen_t taille = sizeof(struct sockaddr_in);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)&serv, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Erreur bind");
        exit(-1);
    }

    if (listen(sock, 10) < 0)
    {
        perror("Erreur listen");
        exit(-1);
    }

    do
    {
        int clientSock;
        if ((clientSock = accept(sock, (struct sockaddr *)&client, &taille)) < 0)
        {
            perror("Erreur accept");
            exit(-1);
        }
        int pid = fork();
        if (pid < 0)
        {
            perror("Erreur fork");
            exit(-1);
        }
        else if (pid == 0)
        {
            printf("enfant \n");
            int type;
            recv(clientSock,&type, sizeof(type), 0);
            type = ntohl(type);
            if(type == 2){
                char immat[8];
                recv(clientSock, immat, sizeof(immat),0);
                printf("immatriculation = %s\n",immat);
                int indice = findImmat(immat, listVoiture, nbVoiture);
                if(indice == -1){
                    int tmp = htonl(indice);
                    send(clientSock, &tmp, sizeof(tmp), 0);
                    exit(0);
                }
                else{
                    send(clientSock, &listCate[indice], sizeof(listCate[indice]),0);
                    send(clientSock, nomServ, sizeof(nomServ), 0);
                    int tmp = htonl(listTemps[indice]);
                    send(clientSock,&tmp , sizeof(tmp), 0);
                    tmp = htonl(prixForfait['a' - listCate[indice]]);
                    send(clientSock,&tmp , sizeof(tmp), 0);
                    tmp = htonl(prixForfaitHT['a' - listCate[indice]]);
                    send(clientSock, &tmp, sizeof(tmp), 0);
                    tmp = htonl(tempsForfait['a' - listCate[indice]]);
                    send(clientSock,&tmp , sizeof(tmp), 0);

                    printf("fin enfant\n");
                    exit(0);
                }
            }else{
                printf("Dans 1\n");
                int err;
                int duree;
                int tmp;
                char cat;
                err = recv(clientSock, &cat, sizeof(cat), 0);
                if(err < 0) perror("erreur recv");
                err = recv(clientSock, &duree, sizeof(duree), 0);
                if (err < 0)
                    perror("erreur recv");
                duree = ntohl(duree);
                if (nbVoiture >= VOITMAX || tempsForfait['a' - cat]<duree)
                {
                    char message = '\0';
                    send(clientSock,&message, sizeof(message),0);
                    exit(0);
                }else{
                    send(clientSock,nomServ,sizeof(nomServ),0);
                    tmp = htonl(prixForfait['a' - cat]);
                    send(clientSock, &tmp, sizeof(tmp), 0);
                    tmp = htonl(prixForfaitHT['a' - cat]);
                    send(clientSock, &tmp, sizeof(tmp), 0);
                    tmp = htonl(tempsForfait['a' - cat]);
                    send(clientSock, &tmp, sizeof(tmp), 0);
                    exit(0);
                }
            }
        }
        else
            printf("parent\n");
    } while (1);
    return 0;
}