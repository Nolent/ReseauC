#ifndef def
#define def def

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

#define IP "127.0.0.1"
#define PORT 86
#define VOITMAX 4 

char listVoiture[VOITMAX][9] = {"AA135BC", "AA136BC", "QA628BZ"};
char listCate[VOITMAX] = {'a','b','c'};
int listTemps[VOITMAX] = {3,8,1};
int nbVoiture = 3;
int prixForfait[] = {1,1.3,2};
int tempsForfait[] = {4,3,8};
int prixForfaitHT[] = {2,4,6};
char nomServ[] = "serveur 1";


#endif