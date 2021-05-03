#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include "player.hpp"
#include "constants.hpp"
#include "network.hpp"
#include "client_server.hpp"

using namespace std;

player ser(0,0);
player cli(0,0);
int total_bullets = 0;
int16_t my_id = -1;		//server has id 0 and client has 1
int in_c_loop =0;
void receive_new_id(int id) {
    my_id = id;
    //number_of_players = id;
    printf("my_id is now: %d\n", my_id);
}

void* client_loop(void *arg) {
    int socket = *((int *) arg);
    int16_t tab[BUF_MAX];
    int length;
    int id, bullets_in_array;
    in_c_loop = 1;
    while (1) {
        length = client_listen(socket, tab);
        id = tab[0];
        if (id == -1) {
            receive_new_id(tab[1]);
            //connected = 1;
        }
        /*
        if (id >= 0) {
            check_if_its_new_player(id);
            players[id].position.x = tab[1];
            players[id].position.y = tab[2];
            players[id].kills = tab[3];
            players[id].deaths = tab[4];
        }
        if (id == -2) {
            bullets_in_array = (length - sizeof(int16_t)) / (sizeof(int16_t) * 2);
            memcpy(bullets_client, tab + 1, sizeof(int16_t) * 2 * bullets_in_array);
            bullets_number = bullets_in_array;
        }*/
        usleep(50);
    }
}

int main(int argc, char* argv[])
{
	cerr << "A";
	if( (argc <2 || argc >3)  )
	{
		cout << "Pass s/c for server or client and server address in case you are client";
		return 1;
	}
	sockaddr_in server_addr, client_addr;
    int sock_server, sock_client;
    char *server_ip_addr = NULL;
    cerr << "A";

    if (argv[1][0] == 'c') {
    	my_id = -1;
    	server_ip_addr = (char*)(malloc(16 * sizeof(char)));
        server_ip_addr = argv[2];
    }
    cerr << "A";
    pthread_t thread_id_server, thread_id_client, thread_id_server_send;
    server_addr = server_sock_addr(server_ip_addr);
    client_addr = client_sock_addr();

    if(argv[1][0] == 's') {
    	my_id = 0;
        prepare_server(&sock_server, &server_addr);
        pthread_create(&thread_id_server, NULL, server_receive_loop, &sock_server);
        pthread_create(&thread_id_server_send, NULL, server_send_loop, &sock_server);
        cerr << "HIII" << connected;
        while(connected != 1)
    	{
    		usleep(100);
    		//cout << connected;
    	}
    }
    cerr << "B";
    prepare_client(&sock_client, &client_addr);
    cerr << "B";
    pthread_create(&thread_id_client, NULL, client_loop, &sock_client);
    SDL_Event e;
    while (1) {
        send_to_server(sock_client, server_addr, my_id, 0);
        usleep(30);}/*
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, map, NULL, NULL);
        for (i = 0; i <= number_of_players; i++) {
            SDL_RenderCopy(renderer, tex, NULL, &players[i].position);
        }

        disp_text(renderer, "kills", font, 400, 10);
        for (i = 0; i <= number_of_players; i++) {
            char kills[10] = {};
            sprintf(kills, "%d", players[i].kills);
            disp_text(renderer, kills, font, 400, 30 + i * 20);
        }

        disp_text(renderer, "deaths", font, 460, 10);
        for (i = 0; i <= number_of_players; i++) {
            char deaths[10] = {};
            sprintf(deaths, "%d", players[i].deaths);
            disp_text(renderer, deaths, font, 460, 30 + i * 20);
        }

        for (i = 0; i < bullets_number; i++) {
            bullet_pos.x = bullets_client[i*2];
            bullet_pos.y = bullets_client[i*2 + 1];
            SDL_RenderCopy(renderer, bullet, NULL, &bullet_pos);
        }
        SDL_RenderPresent(renderer);
    }
*/
    close(sock_client);
    close(sock_server);
    pthread_cancel(thread_id_client);
    pthread_cancel(thread_id_server);
    pthread_cancel(thread_id_server_send);
  /*  SDL_DestroyTexture(tex);
    SDL_DestroyTexture(bullet);
    SDL_DestroyTexture(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;*/
}