#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include <sstream>
#include "header/all.hpp"

using namespace std ;

void level3()
{
	if(game.level[game.levelNow].paused)//gamepaused
	{
		GamePaused();
	}
	else if(game.level[3].story==2)//level 3 objetives
	{
		storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 5 ] );

		doInput();

		if(app.mouse.y>NEW_HEIGHT(575) && app.mouse.y<NEW_HEIGHT(655))
		{
            if(app.mouse.x>NEW_WIDTH(110) && app.mouse.x<NEW_WIDTH(408))//skip button
            {
                if(app.mouse.button[SDL_BUTTON_RIGHT])//mouse clicked
				{
					game.level[3].story = 1;//objective skip and game play condition
					app.mouse.button[SDL_BUTTON_RIGHT] = 0;
					allTimes.startTime = SDL_GetTicks();//start timer
				}
				else
				{
					storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 3 ] );
				}
            }   
        }
	}
	else
	{
		if(game.level[game.levelNow].completed==0)//playing
		{
			mazeSpriteSheetTexture.render( 0, 0, &mazeSpriteClips[ 0 ] );//maze background

			app.delegate.logic();//player, items and enemy move

			app.delegate.draw();//draw everything

			if(allTimes.timerStart)//game after countdown
			{
				timer() ;//score show
				
				doInput();//input.cpp
			}
			else//countdown
			{
				countdown();
			}
		}
		else if(game.level[3].completed == 1)//level completed
		{
			storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 6 ] );

			doInput();

			if (game.enterName == 1)//get player name
			{
				Naming();			
			}
			else if(game.enterName == 2)//check if highscore
			{
				cout << score.recent<<endl;
				loadscore();
			}
			else//level complete page
			{
				levelCompleted();		
			}	
		}
		else//gameover
		{
			doInput();
			gameoverSpriteSheetTexture.render( 0, 0, &gameoverSpriteClips[ 0 ] );
				
			Gameover();	
		}
	}
}