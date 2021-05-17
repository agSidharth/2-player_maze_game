# 2-player_maze_game
This program is a two player shooting maze game involving features like invisibility, teleportation, reflecting bullets, random map generation all blended together to give a wonderfull gaming experience to the user.

## Libraries Needed
* This program requires the SDL2 library, along with SDL2_image, SDL2_mixer, SDL2_ttf.
* Instructions to download required libraries are explained in detail in this [link](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)

## Instructions
Run the program write the following commands on your terminal
* `$ make` to compile main.cpp.
* If you are a server use the command `$ ./game s` to host the server for client.
* If you are a client then use the command `$ ./game c <key>` after the server has hosted the network.
* To continue playing after the game finishes the server must first press the key `y` followed by the client.
* To provide seed to generate another random game `$ ./game s <seed>` and `./game c <seed>` with both seeds being the same.
* Further details of gameplay can be found in ` ./Dual_game/gameplay.pdf`.

## UseFull Links
* To get the complete details of the project see [Task2 - SubTask1](https://www.cse.iitd.ac.in/~rijurekha/cop290_2021.html)
* For SDL tutorials we used [Lazy Foo Tutorials](https://lazyfoo.net/tutorials/SDL/index.php) and the [Youtube Playlist](https://www.youtube.com/watch?v=QQzAHcojEKg&list=RDCMUCAM9ZPgEIdeHAsmG50wqL1g&start_radio=1&rv=QQzAHcojEKg&t=0)
* For socket programming we reffered the [github repo](https://github.com/maciejspychala/sdl-game)
* In resources we used the following links for [icons](https://www.iconsdb.com/), [font](https://www.1001freefonts.com/), [sounds](https://www.soundjay.com/)

