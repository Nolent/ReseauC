#include "gestionSocket.h"

int connexion(char ip[9],int port){
    printf("%s \n",ip);
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 6)) < 0)
    {
        perror("Erreur socket\n");
        return -1;
    }
    
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = inet_addr(ip);

    return connect(sock, (struct sockaddr *)&serv, sizeof(struct sockaddr_in));
}

void handUSR1()
{
    exit(0);
}

void mainProc(int sock, int tube[2]){

    signal(SIGUSR1, handUSR1);
    
}