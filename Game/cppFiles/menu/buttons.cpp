#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void button_functions(int y)
{
	if(y>(NEW_HEIGHT(240)) && y<(NEW_HEIGHT(330)))	//play 
	{
       	if(app.mouse.button[SDL_BUTTON_LEFT])//if mouse clicked
     	{
			if(sfx.sCount) //sound on
			{
				playSound(sfx.click); // click sound
			}
			game.playing = 1;//go to the level functions and start the game
			game.levelNow = 0;// new game or saved game menu
    	}
        else
    	{
            menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 5 ] );
        }	
	}
	
	if(y>(NEW_HEIGHT(355)) && y<(NEW_HEIGHT(445))) //instruction button
	{
		if(app.mouse.button[SDL_BUTTON_LEFT])//if mouse clicked
	    {
	    	if(sfx.sCount) //sound on
			{
				playSound(sfx.click); // click sound
			}
	     	
			game.mainMenu = 2; // instruction menu
           	game.instructions = 1 ;//1st page of instruction
     	}
        else
    	{
        	menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 6 ] );
        }		
	}

	if(y>(NEW_HEIGHT(480)) && y<(NEW_HEIGHT(575))) // leaderboard
	{
		if(app.mouse.button[SDL_BUTTON_LEFT])//if mouse clicked
	    {
	    	if(sfx.sCount) //sound on
			{
				playSound(sfx.click); // click sound
			}
	     	
           game.mainMenu = 3 ;// leaderboard menu
		   game.leaderBoard = 1;//1st page of leaderboards
     	}
        else
    	{
        	menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 7 ] );
        }		
	}
	
	if(y>(NEW_HEIGHT(610)) && y<(NEW_HEIGHT(705))) //quit
	{
		if(app.mouse.button[SDL_BUTTON_LEFT])//if mouse clicked
	    {
            if(sfx.sCount) //sound on
			{
				playSound(sfx.click); // click sound
			}
		    
            exit(0);//exit
	    }
    	else
        {
        	menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 8 ] );
        }	
	}
}
