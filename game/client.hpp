#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "constants.hpp"

#define SERVER_PORT 1234

void prepare_client(int *sock, struct sockaddr_in *client_addr);
void send_to_server(int sock, struct sockaddr_in serv_addr, int16_t id, int16_t keys[7]);
int client_listen(int sock, int16_t *tab);

void prepare_client(int *sock, struct sockaddr_in *client_addr) {
    if ((*sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client socket failed");
    }

    if (bind(*sock, (struct sockaddr*)client_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind client error");
    }
}

void send_to_server(int sock, struct sockaddr_in serv_addr, int16_t id, int16_t keys[7]) {
    short tab[8];
    tab[0] = id;
    for(int i=0;i<7;i++)
    {
    	tab[i+1] = keys[i];
    	cerr << keys[i] << " ";
    }
    socklen_t serv_addr_size = sizeof(struct sockaddr);
    if (sendto(sock, tab, sizeof(short) * 8, 0, (struct sockaddr *) &serv_addr, serv_addr_size) < 0) {
        perror("sendto error");
    }
 
}

int client_listen(int sock, int16_t *tab){
    int length = recvfrom(sock, tab, sizeof(int16_t) * BUF_MAX, 0, NULL, 0);
    for(int i=0;i<length;i++)
    {
    	cerr << tab[i];
    }
    return length;
}
