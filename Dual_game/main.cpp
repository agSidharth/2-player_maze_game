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

#include "player.hpp"
#include "network.hpp"
#include "client.hpp"
#include "server.hpp"
#include "game.hpp"

using namespace std;

int total_bullets = 0;
short my_id = -1;		//server has id 0 and client has 1
//int in_c_loop =0;
void receive_new_id(int id) {
    my_id = id;
    //number_of_players = id;
    cout << "my_id is now: "<<my_id<<"\n";
}

bool start = false;

Game* game = nullptr;
void* client_loop(void *arg) {
    int socket = *((int *) arg);
    short tab[BUF_MAX];
    int id;
    //in_c_loop = 1;
    while (1) {
        client_listen(socket, tab);
        id = tab[0];
        if (id == -1) {
            receive_new_id(tab[1]);
            seeed = tab[2];
            //cout <<"CL"<< tab[2]<< endl;
        }
        if(tab[0]==1 && start)
        {
            game -> eventsFromClient(tab);
        }
        if(tab[0]==0 && start)
        {
            game -> eventsFromServer(tab);
        }
        usleep(50);
    }
}

int main(int argc, char* argv[])
{
	seeed = time(0);
    //cout << seeed<<endl;
	if( (argc <2 || argc >4)  )
	{
		cout << "Pass s/c for server or client and server address in case you are client.. Can also pass seed";
		return 1;
	}
    int seed = 32;
    //int var_seed = 32;
    srand(seed);
    string c = "y";
    int score[2] = {0};
    if (argv[1][0] == 'c')
    {
        if(argc == 4) seed = atoi(argv[3]);
        seeed = seed;
        srand(seed);
    }
    if (argv[1][0] == 's')
    {
        if(argc == 3) seed = atoi(argv[2]);
        seeed = seed;
        srand(seed);
    }


    while(c=="y" || c=="Y")
    {
        sockaddr_in server_addr, client_addr;
        int sock_server, sock_client;
        char *server_ip_addr = NULL;

       // seed = var_seed;
        if (argv[1][0] == 'c') {
        	my_id = -1;
            //usleep(200);
            //cerr << "Does it reach here";
        	server_ip_addr = (char*)(malloc(16 * sizeof(char)));
            server_ip_addr = argv[2];
            
        }
        
        pthread_t thread_id_server, thread_id_client;
        server_addr = server_sock_addr(server_ip_addr);
        client_addr = client_sock_addr();

        if(argv[1][0] == 's') {
            //cerr << "and here";
        	my_id = -1;
            prepare_server(&sock_server, &server_addr);
            pthread_create(&thread_id_server, NULL, server_receive_loop, &sock_server);
        }
        prepare_client(&sock_client, &client_addr);
        pthread_create(&thread_id_client, NULL, client_loop, &sock_client);
        short dummy[(TAB_SIZE)];
        send_to_server(sock_client, server_addr, my_id, dummy);
        while(my_id == -1)
        {
        	usleep(30);
        }
        //srand(seeed);
        if(my_id == 0)
        {
        	while(number_of_connected_clients != 2)
        	{
        		usleep(30);
        	}
        }
       
        string title = "PLAYER";
        int won,rep = 0;
        
        char char_title[8];
        title = title + to_string(my_id+1);
        string begin;

        seeed = (4*seeed)/3;
        srand(seeed);
    	game = new Game(my_id);
            
        strcpy(char_title,title.c_str());
        game ->init(char_title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);
        start = true;
        //cout <<"MAIn"<< seeed <<endl;;
    	while(game->end_time>0)
    	{	
    		TIME++;
    		frameStart = SDL_GetTicks();

   			if(my_id == 0)
   			{
    			game->handleEventsforServer();
                send_to_server(sock_client, server_addr, my_id, game->send_event);
              
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

            if(!game->isRunning) game->end_time--;

            if(game->end_time<=0) {sleep(2); break;}
    	}

    	won = game ->clean();
        score[won]++;
        rep++;
        start = false;
        game = nullptr;
        
        cout<<"\n\nFINAL SCORES :\nPLAYER1 : "<<score[0]<<"\nPLAYER2 : "<<score[1]<<endl;
        if(score[0]>score[1]) cout<<"PLAYER1 WON THE GAME";
        else if(score[0]<score[1]) cout<<"PLAYER2 WON THE GAME";
        else cout<<"TIE";

        cout<<"\n........GAME OVER...........\n";
        cout << "___PLAY_AGAIN(Y/N)___\n";

        close(sock_client);
        if(my_id == 0) close(sock_server);
        pthread_cancel(thread_id_client);
        if(my_id == 0)pthread_cancel(thread_id_server);
        number_of_connected_clients = 0;
        //c = "n";
       // var_seed = (var_seed*4)/3;
        
        //cout << "a" <<endl;
        cin>>c;
        //cout << "HI"<<endl;
    }
}