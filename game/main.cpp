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

void* client_loop(void *arg) {
    int socket = *((int *) arg);
    int16_t tab[BUF_MAX];
    int length;
    int id, bullets_in_array;
    //in_c_loop = 1;
    while (1) {
        length = client_listen(socket, tab);
        id = tab[0];
        if (id == -1) {
            receive_new_id(tab[1]);
            //connected = 1;
        }
        //cerr << "HIIIII";
        //game -> eventsFromServer(tab);
        /*
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
    	my_id = -1;
        prepare_server(&sock_server, &server_addr);
        pthread_create(&thread_id_server, NULL, server_receive_loop, &sock_server);
        pthread_create(&thread_id_server_send, NULL, server_send_loop, &sock_server);
        cerr << "HIII" << connected;
    }
    cerr << "B";
    prepare_client(&sock_client, &client_addr);
    cerr << "B";
    pthread_create(&thread_id_client, NULL, client_loop, &sock_client);
    send_to_server(sock_client, server_addr, my_id, 0);
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
   
    cerr << "k";
    //usleep(40000000);
   	//while (1)
   	 {
    	Game* game;
		game = new Game();
		game ->init(TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);

		while(game->running())
		{	
			TIME++;
			frameStart = SDL_GetTicks();

			if(my_id == 0)
			{
				game->handleEventsforServer();
			}
			if(my_id == 1)
			{
				game -> handleEventsforClient();
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
        //send_to_server(sock_client, server_addr, my_id, 0);
        //usleep(30);
    }

        /*
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