#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

void Gameover()
{
	doInput();//input.cpp

	if(allTimes.Check<10)//blinking spacebar text show
	{
		gameoverSpriteSheetTexture.render( 0, 0, &gameoverSpriteClips[ 1 ] );
		allTimes.Check++ ;
	}
	else if(allTimes.Check==20)//blinking spacebar text timer
	{
		allTimes.Check = 0 ;
	}
	else//blinking spacebar text timer increament
	{
		allTimes.Check++ ;
	}

	if ((app.keyboard[SDL_SCANCODE_SPACE]))//play again
	{
		allTimes.startTime = SDL_GetTicks();//timer start
		
        level1Start();//memsetting level 1 &starting from level1
		game.level[game.levelNow].story = 1;//don't show story
		score.ex = 0 ;//score of previous level
		if(sfx.mCount)
		{
			playMusic();	
		}
		allTimes.Check = 0 ;//blinking spacebar timer memset	
	}
}