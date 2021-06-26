#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#include "header/texture.hpp"

void initSprites()//load all sprites
{
	loadMenu();
	loadGameover();
	loadinstructions();
	loadleaderBoard();
	loadGamePause();
	loadJungle();
	loadMaze();
	loadStory();
	loadSoundMenu();
	loadRoad();
}

void loadMenu()//load menu images
{
	//Load sprite sheet texture
	if( !menuSpriteSheetTexture.loadFromFile( "res/sprites/MENU.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0 ;
		for(int i = 0 ; i < 10 ; i ++)
		{
			menuSpriteClips[ i ].x = j;
			menuSpriteClips[ i ].y = k;
			menuSpriteClips[ i ].w = 1280;
			menuSpriteClips[ i ].h = 960;
			j += 1280;
			if(j==1280*5)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}

void loadRoad()
{
	//Load sprite sheet texture
	if( !roadSpriteSheetTexture.loadFromFile( "res/sprites/road1.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0;
		for(int i = 0 ; i < 10 ; i ++)
		{
			roadSpriteClips[ i ].x = j;
			roadSpriteClips[ i ].y = k;
			roadSpriteClips[ i ].w = 1280;
			roadSpriteClips[ i ].h = 960;

			j += 1280;
			if(j==6400)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}

void loadGameover()
{
	//Load sprite sheet texture
	if( !gameoverSpriteSheetTexture.loadFromFile( "res/sprites/GAMEOVER.PNG" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 ;
		for(int i = 0 ; i < 2 ; i ++)
		{
			gameoverSpriteClips[ i ].x = j;
			gameoverSpriteClips[ i ].y = 0;
			gameoverSpriteClips[ i ].w = 1280;
			gameoverSpriteClips[ i ].h = 960;

			j += 1280;
		}
	}
}

void loadinstructions()
{
	//Load sprite sheet texture
	if( !instructionsSpriteSheetTexture.loadFromFile( "res/sprites/INSTRUCTIONS1.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 ;
		for(int i = 0 ; i < 5 ; i ++)
		{
			instructionsSpriteClips[ i ].x = j;
			instructionsSpriteClips[ i ].y = 0;
			instructionsSpriteClips[ i ].w = 1280;
			instructionsSpriteClips[ i ].h = 960;

			j += 1280;
		}
	}
}

void loadleaderBoard()
{
	//Load sprite sheet texture
	if( !leaderBoardSpriteSheetTexture.loadFromFile( "res/sprites/highscore.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0 ;
		for(int i = 0 ; i < 8 ; i ++)
		{
			leaderBoardSpriteClips[ i ].x = j;
			leaderBoardSpriteClips[ i ].y = k;
			leaderBoardSpriteClips[ i ].w = 1280;
			leaderBoardSpriteClips[ i ].h = 960;

			j += 1280;
			if(j==1280*4)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}

void loadGamePause()
{
	//Load sprite sheet texture
	if( !gamePauseSpriteSheetTexture.loadFromFile( "res/sprites/GAMEPAUSE.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 ;
		for(int i = 0 ; i < 9 ; i ++)
		{
			gamePauseSpriteClips[ i ].x = j;
			gamePauseSpriteClips[ i ].y = 0;
			gamePauseSpriteClips[ i ].w = 1280;
			gamePauseSpriteClips[ i ].h = 960;

			j += 1280;
		}
	}
}

void loadJungle()
{
	//Load sprite sheet texture
	if( !jungleSpriteSheetTexture.loadFromFile( "res/sprites/jungle.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0;
		for(int i = 0 ; i < 7 ; i ++)
		{
			jungleSpriteClips[ i ].x = j;
			jungleSpriteClips[ i ].y = k;
			jungleSpriteClips[ i ].w = 1280;
			jungleSpriteClips[ i ].h = 960;

			j += 1280;
			if(j==1280*4)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}

void loadMaze()
{
	//Load sprite sheet texture
	if( !mazeSpriteSheetTexture.loadFromFile( "res/sprites/maze.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0 ;
		for(int i = 0 ; i < 8 ; i ++)
		{
			mazeSpriteClips[ i ].x = j;
			mazeSpriteClips[ i ].y = k;
			mazeSpriteClips[ i ].w = 1280;
			mazeSpriteClips[ i ].h = 960;

			j += 1280;
			if(j==1280*4)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}

void loadStory()
{
	//Load sprite sheet texture
	if( !storySpriteSheetTexture.loadFromFile( "res/sprites/stories1.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 ;
		for(int i = 0 ; i < 8 ; i ++)
		{
			storySpriteClips[ i ].x = j;
			storySpriteClips[ i ].y = 0;
			storySpriteClips[ i ].w = 1280;
			storySpriteClips[ i ].h = 960;

			j += 1280;
		}
	}
}

void loadSoundMenu()
{
	//Load sprite sheet texture
	if( !SoundSpriteSheetTexture.loadFromFile( "res/sprites/MUSIC.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	else
	{
		int j = 0 , k = 0;
		for(int i = 0 ; i < 16 ; i ++)
		{
			SoundSpriteClips[ i ].x = j;
			SoundSpriteClips[ i ].y = k;
			SoundSpriteClips[ i ].w = 1280;
			SoundSpriteClips[ i ].h = 960;

			j += 1280;
			if(j==1280*8)
			{
				k += 960;
				j = 0 ; 
			}
		}
	}
}