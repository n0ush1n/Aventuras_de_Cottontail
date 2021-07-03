#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include <sstream>
#include "header/all.hpp"

using namespace std ;

void level1()
{
	if(game.level[1].paused)//gamepaused
	{
		GamePaused();
	}
	else if(game.level[1].story==0)//show story
	{
		storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 0 ] );

		doInput();

		if(app.mouse.y>NEW_HEIGHT(575) && app.mouse.y<NEW_HEIGHT(655))
		{
            if(app.mouse.x>NEW_WIDTH(110) && app.mouse.x<NEW_WIDTH(408))//continue button
            {
                if(app.mouse.button[SDL_BUTTON_RIGHT])//mouse clicked
				{
					game.level[1].story = 2;//go to level1 objectives
					app.mouse.button[SDL_BUTTON_RIGHT] = 0;
				}
				else
				{
					storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 2 ] );
				}
            }   
        }
	}
	else if(game.level[1].story==2)//show level1 objectives
	{
		storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 1 ] );

		doInput();

		if(app.mouse.y>NEW_HEIGHT(575) && app.mouse.y<NEW_HEIGHT(655))
		{
            if(app.mouse.x>NEW_WIDTH(110) && app.mouse.x<NEW_WIDTH(408))//skip button
            {
                if(app.mouse.button[SDL_BUTTON_RIGHT])//mouse clicked
				{
					game.level[1].story = 1;//skip objective and start game
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
		if(game.level[1].completed==0)//playing
		{
			if( (game.level[1].collision.check[1]==1))//map collected
			{
				if(player->y<CHANGE_HEIGHT(80))//player reached the other side of the road
				{
					Mix_HaltMusic();
					SDL_RenderClear(app.renderer);
					game.level[1].completed = 1;//level completed
					if(sfx.sCount) {playSound(sfx.levelComplete);}//play level complete sound
					SDL_StartTextInput();//get name
					game.enterName = 1;//enter player name page
					
				}				
			}
			roadSpriteSheetTexture.render( 0, 0, &roadSpriteClips[ 0 ] );//road
				
			app.delegate.logic();//player and cars move

			app.delegate.draw();//draw polayer , cars and items

			if(allTimes.timerStart)//start game after countdown
			{
				timer() ;//count score
				
				doInput();//input.cpp
			}
			else
			{
				countdown();//countdown before starting the game
			}
			roadSpriteSheetTexture.render( 0, 0, &roadSpriteClips[ 9 ] );//black border
		}
		else if(game.level[1].completed==1)//level completed
		{
			storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 6 ] );//level completed page
			doInput();

			if (game.enterName == 1)//enter player name
			{
				Naming();			
			}
			else if(game.enterName == 2)//load score to see if player got place in leaderboard
			{
				loadscore();
			}
			else//level complete option
			{
				levelCompleted();		
			}
		}
		else//gameover
		{
			doInput();
			gameoverSpriteSheetTexture.render( 0, 0, &gameoverSpriteClips[ 0 ] );//gameover page
				
			Gameover();	
		}
	}
}