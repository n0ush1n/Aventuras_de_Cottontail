#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include <sstream>
#include "header/all.hpp"

using namespace std ;

void level2()
{
	if(game.level[2].paused)//gamepaused
	{
		GamePaused();
	}
	else if(game.level[2].story==2)//level2 objectives
	{
		storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 4 ] );

		doInput();

		if(app.mouse.y>NEW_HEIGHT(575) && app.mouse.y<NEW_HEIGHT(655))
		{
            if(app.mouse.x>NEW_WIDTH(110) && app.mouse.x<NEW_WIDTH(408))//skip button
            {
                if(app.mouse.button[SDL_BUTTON_RIGHT])
				{
					game.level[2].story = 1;//skip objective and start game condition
					app.mouse.button[SDL_BUTTON_RIGHT] = 0;
					allTimes.startTime = SDL_GetTicks();//start game timer
					game.level[2].completed = 0;//level2 on
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
		if(game.level[2].completed==0)//playing
		{
			int cnt1 = 0;
			for(int i = 0; i < 5; i++)//check junglees are dead or not
			{
				if(game.level[2].collision.dead[i] == 0) cnt1 = 1;
			}
			if(cnt1 == 0)//all junglees are dead
			{
				SDL_RenderClear(app.renderer);
				game.level[2].completed = 2;//maze finder page condition
				SDL_StartTextInput();//get name condition

				game.enterName = 1;//name page
			}
			else if(game.level[2].collision.bullet==12)//all bullets used
			{
				game.level[2].completed = -1; //gameover condition
				Mix_PauseMusic();
				if(sfx.sCount){playSound(sfx.gameover);}//gameover sound
				score.leader = 0;//player rank now 0
			}
			jungleSpriteSheetTexture.render( 0, 0, &jungleSpriteClips[ 1 ] );//jungle

			doJunglee();//junglee move

			app.delegate.logic();//scope move
			app.delegate.draw();//scope draw

            if(allTimes.timerStart)//game after countdown
			{
				timer() ;//show score count

				bullets();//show bullets fired count
				
				doInput();//input.cpp               
			}
			else
			{
				countdown();//countdown
			}		
		}
		else if(game.level[2].completed==2)//playing part2
		{
			jungleSpriteSheetTexture.render( 0, 0, &jungleSpriteClips[ 5 ] );//background

			doPlayer2();//player move
			drawPlayer();//player draw

            timer() ;//show game score

			bullets();//show bullets remaining
				
			doInput();//input.cpp               	
		}
		else if(game.level[2].completed == 1)//level completed
		{
			storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 6 ] );

			doInput();

			if (game.enterName == 1)//get player name
			{
				Naming();			
			}
			else if(game.enterName == 2)//check if highscore
			{
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