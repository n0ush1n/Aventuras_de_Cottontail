#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#include<bits/stdc++.h>
#include <sstream>
#include "menu.hpp"

void menu(void)
{
    doInput();

    if(game.save) {saveOrNot();}	
    else
    {
        if(game.mainMenu==1)//mainmenu
        {
            menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 0 ] );
        
            if(app.mouse.x>NEW_WIDTH(160) && app.mouse.x<NEW_WIDTH(383))//buttons
            {
                button_functions(app.mouse.y) ;//play,instructions,highscore,quit
            }
            if(app.mouse.y>NEW_HEIGHT(615) && app.mouse.y<NEW_HEIGHT(700))//sound and music settings
            {
                if(app.mouse.x>NEW_WIDTH(26) && app.mouse.x<NEW_WIDTH(65))
                {
                    if(app.mouse.button[SDL_BUTTON_LEFT]) 
                    {
                        game.mainMenu = 4;//settings condition
                        if(sfx.sCount) {playSound(sfx.click);}
                    }
                    else 
                    {
                        menuSpriteSheetTexture.render( CHANGE_WIDTH(3), 0, &menuSpriteClips[ 2 ] );
                    }
                }   
            }
        }
        else if(game.mainMenu==2)//instructions 
        {
            instructions();
        }
        else if(game.mainMenu==3)//leaderboard
        {
        LeaderboardMenu();
        }
        else if(game.mainMenu==4)//settings
        {
            soundMusic();
        }
        drawCursor();//draw cursor
        app.mouse.button[SDL_BUTTON_LEFT] = 0;
    }
}