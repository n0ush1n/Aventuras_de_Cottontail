#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void instructions(void)
{
    if(game.instructions)//1st page of instructions
    {
        instructionsSpriteSheetTexture.render( 0, 0, &instructionsSpriteClips[ 1 ] );
        if(app.mouse.x>NEW_WIDTH(21) && app.mouse.x<NEW_WIDTH(65) && app.mouse.y>NEW_HEIGHT(620) && app.mouse.y<NEW_HEIGHT(700))//next page button
	    {
            if (app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
            {
                if(sfx.sCount)
                {
                    playSound(sfx.click);
                }
                game.instructions = 0 ;//go to second page
            }
            else
            {
                instructionsSpriteSheetTexture.render( 0,0, &instructionsSpriteClips[ 3 ] );
            }		
        }
        else if(app.mouse.x>NEW_WIDTH(21) && app.mouse.x<NEW_WIDTH(65)&& app.mouse.y>NEW_HEIGHT(13) && app.mouse.y<NEW_HEIGHT(90))//menu button
	    {
            if (app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
            {
                if(sfx.sCount)
                {
                    playSound(sfx.click);
                }
                game.mainMenu = 1;//go back to menu
            }
            else
            {
                instructionsSpriteSheetTexture.render( 5, 0, &instructionsSpriteClips[ 2 ] );
            }	
        }
    }
    else
    {
        instructionsSpriteSheetTexture.render( 0, 0, &instructionsSpriteClips[ 0 ] );
        if(app.mouse.x>NEW_WIDTH(21) && app.mouse.x<NEW_WIDTH(65) && app.mouse.y>NEW_HEIGHT(620) && app.mouse.y<NEW_HEIGHT(700))//previous page button
	    {
            if (app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
            {
                if(sfx.sCount)
                {
                    playSound(sfx.click);
                }
                game.instructions = 1 ;//go back to 1st page
            }
            else
            {
                instructionsSpriteSheetTexture.render( 0, 0, &instructionsSpriteClips[ 4 ] );
            }		
        }
    }
}