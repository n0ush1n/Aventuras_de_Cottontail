#include<SDL2/SDL.h>
#include<bits/stdc++.h>
#include "main.hpp"

using namespace std ;

int main(int argc, char *argv[])
{
	initSDL();//init.cpp

	long then = SDL_GetTicks();
	float remainder = 0;
	playMusic();

	while (1)
	{
		prepareScene();//draw.cpp
			
		if(!game.playing) {menu();}//menu
		else { app.delegate.level[game.levelNow]();}
		
    	presentScene();//draw.cpp
		capFrameRate(&then, &remainder);//capframerate.cpp
	}	
	close();
	return 0;
}