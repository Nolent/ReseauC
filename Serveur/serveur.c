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
    printf("apres sock\n");
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

    printf("avant boucle\n");

    do
    {
        if (accept(sock, (struct sockaddr *)&client, &taille) < 0)
        {
            perror("Erreur accept");
            exit(-1);
        }
        printf("apres accept\n");
        int pid = fork();
        if (pid < 0)
        {
            perror("Erreur fork");
            exit(-1);
        }
        else if (pid == 0)
        {
            printf("enfant Client connecté\n");
        }
        else
            printf("parent\n");
    } while (1);
    return 0;
}