#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

#include "constants.hpp"
short tab1[(TAB_SIZE+1)];

#include "player.hpp"
#include "network.hpp"
#include "client.hpp"
#include "server.hpp"
#include "game.hpp"

using namespace std;

int total_bullets = 0;
int16_t my_id = -1;		//server has id 0 and client has 1
//int in_c_loop =0;
void receive_new_id(int id) {
    my_id = id;
    //number_of_players = id;
    cout << "my_id is now: "<<my_id<<"\n";
}

Game* game;
void* client_loop(void *arg) {
    int socket = *((int *) arg);
    int16_t tab[BUF_MAX];
    int id;
    //in_c_loop = 1;
    while (1) {
        client_listen(socket, tab);
        id = tab[0];
        if (id == -1) {
            receive_new_id(tab[1]);
            //connected = 1;
        }
        if(tab[0]==1)
        {
            game -> eventsFromClient(tab);
        }
        if(tab[0]==0)
        {
            game -> eventsFromServer(tab);
        }
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
    srand(50);
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
    pthread_t thread_id_server, thread_id_client;
    server_addr = server_sock_addr(server_ip_addr);
    client_addr = client_sock_addr();

    if(argv[1][0] == 's') {
    	my_id = -1;
        prepare_server(&sock_server, &server_addr);
        pthread_create(&thread_id_server, NULL, server_receive_loop, &sock_server);
        cerr << "HIII" << connected;
    }
    cerr << "B";
    prepare_client(&sock_client, &client_addr);
    cerr << "B";
    pthread_create(&thread_id_client, NULL, client_loop, &sock_client);
    short dummy[(TAB_SIZE)];
    send_to_server(sock_client, server_addr, my_id, dummy);
    while(my_id == -1)
    {
    	usleep(30);
    }
    if(my_id == 0)
    {
    	while(number_of_connected_clients != 2)
    	{
    		usleep(30);
    	}
    }
   
    //cerr << "k";
    string title = "PLAYER";
    char char_title[8];
    {
		game = new Game(my_id);
        title = title + to_string(my_id+1);
        strcpy(char_title,title.c_str());
        game ->init(char_title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);

		while(game->running())
		{	
			TIME++;
			frameStart = SDL_GetTicks();

			if(my_id == 0)
			{
				game->handleEventsforServer();
                cerr << "check send to server";
                for(int i=0;i<(TAB_SIZE);i++)
                {
                    cerr << game->send_event[i] << " ";
                }
                send_to_server(sock_client, server_addr, my_id, game->send_event);
                tab1[0] = my_id;
                for(int i=0;i<(TAB_SIZE);i++)
                {
                    tab1[i+1] = game -> send_event[i];
                }
                cerr << "can send to server";
			}
			if(my_id == 1)
			{
				game -> handleEventsforClient();
                send_to_server(sock_client, server_addr, my_id, game->send_event);
			}
			game->update();
			game->render();

			frameTime = SDL_GetTicks() - frameStart;

			difference = frameDelay - frameTime;
			if(difference>0)
			{
				SDL_Delay(difference);
			}
		}

		game ->clean();
    }

    close(sock_client);
    close(sock_server);
    pthread_cancel(thread_id_client);
    pthread_cancel(thread_id_server);
}