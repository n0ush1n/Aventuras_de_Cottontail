#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void loadSounds(void)
{
	sfx.click = Mix_LoadWAV("res/sounds/click.wav");
	sfx.collect = Mix_LoadWAV("res/sounds/newitem.wav");//collect item
	sfx.gameover = Mix_LoadWAV("res/sounds/gameover.wav");
	sfx.gunshot = Mix_LoadWAV("res/sounds/GunShotSnglShotEx PE1097508.wav");
	sfx.levelComplete = Mix_LoadWAV("res/sounds/levelcomplete.wav");
	sfx.scream = Mix_LoadWAV("res/sounds/scream.wav");//junglee screa
}

void loadmusic(void)
{
	sfx.music = Mix_LoadMUS( "res/music/melodyloops-preview-african-trip-1m0s.mp3" );
	sfx.roadmusic = Mix_LoadMUS("res/music/Monplaisir_-_03_-_Level_0.mp3");
	sfx.jungle = Mix_LoadMUS("res/music/06 Dashing Through New Lands (loop)_Live Orchestral Adventure.mp3");
	sfx.maze = Mix_LoadMUS("res/music/monkeys-spinning-monkeys-by-kevin-macleod-from-filmmusic-io.mp3"); 
}

void playSound(Mix_Chunk *sound)//play sounds
{
	Mix_PlayChannel(1, sound, 0);
	Mix_VolumeChunk(sound, (MIX_MAX_VOLUME*sfx.sVolume)/(96));//change sound volume
}

void playMusic(void)//play music
{
	if(game.playing)
	{
		if(game.levelNow==1)
		{
			Mix_PlayMusic(sfx.roadmusic, -1 );
		}
		else if(game.levelNow==2)
		{
			Mix_PlayMusic(sfx.jungle,-1);
		}
		else if(game.levelNow==3)
		{
			Mix_PlayMusic(sfx.maze,-1);
		}
	}
	else
	{
		Mix_PlayMusic(sfx.music, -1 );	
	}
	 Mix_VolumeMusic((MIX_MAX_VOLUME*sfx.mVolume)/(96));//change music volume
}