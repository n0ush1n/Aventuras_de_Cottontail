#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void soundMusic(void)
{
    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 0 ] );//settings background
    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ sfx.mVolCnt ] );//music volume currently
    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ sfx.sVolCnt+7 ] );//sound volume currently

    if(app.mouse.y>CHANGE_HEIGHT(830) && app.mouse.y<CHANGE_HEIGHT(910))
	{
        if(app.mouse.x>CHANGE_WIDTH(420) && app.mouse.x<CHANGE_WIDTH(775))//go back to mainmenu
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) //mouse clicked
            {
                game.mainMenu = 1;//manimenu condition
                if(sfx.sCount) {playSound(sfx.click);}//button click sound
            }
            else 
            {
                SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 12 ] );
            }
        }   
    }
	else if (app.mouse.y>CHANGE_HEIGHT(635) && app.mouse.y<CHANGE_HEIGHT(700))
	{
        if(app.mouse.x>CHANGE_WIDTH(145) && app.mouse.x<CHANGE_WIDTH(205))//music volume decrease 
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) 
            {
                if(sfx.mVolume>3)
                {
                    sfx.mVolume = sfx.mVolume / 4;//decrease factor
                    sfx.mVolCnt--;
                    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ sfx.mVolCnt ] );
                }
                if(sfx.sCount) {playSound(sfx.click);}
            }
            SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 5 ] );//music button
        }
        if(app.mouse.x>CHANGE_WIDTH(420) && app.mouse.x<CHANGE_WIDTH(480))//increase music volume
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) 
            {
                if(sfx.mVolume<192)
                {
                    sfx.mVolume = sfx.mVolume * 4;//increase factor
                    sfx.mVolCnt++;
                    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ sfx.mVolCnt ] );
                }
                if(sfx.sCount) {playSound(sfx.click);}
            }
            SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 7 ] );//music button
        }
        if(app.mouse.x>CHANGE_WIDTH(780) && app.mouse.x<CHANGE_WIDTH(840))
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) 
            {
                if(sfx.sVolume>3)//decrease sound volume
                {
                    sfx.sVolume /= 4;//decrease factor
                    sfx.sVolCnt--;
                    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 7 + sfx.sVolCnt ] );
                }
                if(sfx.sCount) {playSound(sfx.click);}
            }
            SoundSpriteSheetTexture.render( CHANGE_WIDTH(636), 0, &SoundSpriteClips[ 13 ] );//sound button
        }
        if(app.mouse.x>CHANGE_WIDTH(1055) && app.mouse.x<CHANGE_WIDTH(1120))//increase sound volume
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) 
            {
                if(sfx.sVolume<192)
                {
                    sfx.sVolume *= 4;//increase factor
                    sfx.sVolCnt++;
                    SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 7 + sfx.sVolCnt ] );
                }
                if(sfx.sCount) {playSound(sfx.click);}
            }
            SoundSpriteSheetTexture.render( CHANGE_WIDTH(636), 0, &SoundSpriteClips[ 15 ] );//sound button
        }
        if(app.mouse.x>CHANGE_WIDTH(280) && app.mouse.x<CHANGE_WIDTH(345))//music play or pause
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) //mouse clicked
            {
                if( Mix_PlayingMusic() == 0 )//music off
                {
                    playMusic();//play music
                    sfx.mCount = 1;//music playing
                }
                else
                {
                    if( Mix_PausedMusic() == 1 )//music paused
                    {
                        Mix_ResumeMusic();//resume music
                        sfx.mCount = 1;//music playing
                    }
                    else//music playing
                    {
                        Mix_PauseMusic();//pause music
                        sfx.mCount = 0;//music paused
                    }
                }
                if(sfx.sCount) {playSound(sfx.click);}
            }
            SoundSpriteSheetTexture.render( 0, 0, &SoundSpriteClips[ 6 ] );//music button
        }
        if(app.mouse.x>CHANGE_WIDTH(915) && app.mouse.x<CHANGE_WIDTH(980))//sound play or pause
        {
            if(app.mouse.button[SDL_BUTTON_LEFT]) //mouse clicked
            {
                if(sfx.sCount)//sound on
                {
                    playSound(sfx.click);
                    sfx.sCount = 0 ;//sound off
                }   
                else//sound off
                {
                    sfx.sCount = 1 ;//sound on
                }   
            }
            SoundSpriteSheetTexture.render( CHANGE_WIDTH(636), 0, &SoundSpriteClips[ 14 ] );//sound button
        }
    }   
    Mix_VolumeMusic((MIX_MAX_VOLUME*sfx.mVolume)/(96));//change music volume
}