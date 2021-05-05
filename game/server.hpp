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

void prepare_server(int *sock, struct sockaddr_in *server_sock);
void send_data(int sock, struct sockaddr_in client, int16_t tab[], int size);
void* server_receive_loop(void *arg);
void* server_send_loop(void *arg);
int its_an_old_client(int client_pos);
void add_adr_to_list(int client_pos, struct sockaddr_in *client_addr);
void prepare_server(int *sock, struct sockaddr_in *server_sock);
void send_data(int sock, struct sockaddr_in client, int16_t tab[], int size);
void* server_receive_loop(void *arg);
void* server_send_loop(void *arg);
int its_an_old_client(int client_pos);
void add_adr_to_list(int client_pos, struct sockaddr_in *client_addr);


struct sockaddr_in clients_addresses[MAX_PLAYERS];
int number_of_connected_clients = 0;
short send_event[TAB_SIZE][2];

void prepare_server(int *sock, struct sockaddr_in *server_sock) {
    memset(clients_addresses, 0, sizeof(struct sockaddr_in) * MAX_PLAYERS);
    if ((*sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket failed");
    }
    if (bind(*sock, (struct sockaddr*) server_sock, sizeof(struct sockaddr)) < 0) {
        perror("bind server error");
    }
}

struct sockaddr_in receive_data(int sock, int16_t data[]) {
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr);
    recvfrom(sock, data, sizeof(int16_t) * (TAB_SIZE+1), 0, (struct sockaddr*)&addr, &addr_size);
    return addr;
}

void send_data(int sock, struct sockaddr_in client, int16_t data[], int size) {
    socklen_t addr_size = sizeof(struct sockaddr);
    sendto(sock, data, sizeof(int16_t) * size, 0, (struct sockaddr*)&client, addr_size);
}

void* server_receive_loop(void *arg) {
    int socket = *((int *) arg);
    int client_pos = 0;
    struct sockaddr_in client_addr;
    short tab[(TAB_SIZE+1)];
    while (1) {
        client_addr = receive_data(socket, tab);
        client_pos = addr_pos_in_tab(client_addr, clients_addresses, number_of_connected_clients);
        if (its_an_old_client(client_pos)) {
        	if(tab[0] == 1)
        	{
        		send_data(socket,clients_addresses[1],tab1,(TAB_SIZE+1));
        		send_data(socket,clients_addresses[1-client_pos],tab,(TAB_SIZE+1));
        		/*cerr << "Client : "<<client_pos << " ";
        		for(int i=0;i<(TAB_SIZE+1);i++)
        		{
        			cerr << tab[i] << " ";
        		}
        		cerr << "\n";
        		//cerr << "Send data is working";*/
        	}
        }
        if (tab[0] == -1 && client_pos < MAX_PLAYERS) {
            add_adr_to_list(client_pos, &client_addr);
            int16_t tab[3];
            tab[0] = -1;
            tab[1] = client_pos;
            connected += 1;
            send_data(socket, clients_addresses[client_pos], tab, (TAB_SIZE+1));
        }
        usleep(50);
    }
}

int its_an_old_client(int client_pos) {
    return (client_pos < number_of_connected_clients && client_pos >= 0);
}

void add_adr_to_list(int client_pos, struct sockaddr_in *client_addr) {
    if (client_pos >= number_of_connected_clients) {
        clients_addresses[number_of_connected_clients++] = *client_addr;
    }
}
