#include "gestionSocket.h"

int connexion(char ip[9],int port){
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

    int error = connect(sock, (struct sockaddr *)&serv, sizeof(struct sockaddr_in));
    if(error <0){
         perror("Erreur connexion");
         return -1;}
    else return sock;
}
