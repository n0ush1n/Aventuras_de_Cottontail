#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

static void capFrameRate(long *then, float *remainder)//frame rate
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}

void bullets()//level 2: show bullets  remaining
{
    gfont.timeText.str( "" );
	gfont.timeText << "Remaining bullets : " << 12 - game.level[2].collision.bullet; 

	SDL_Color tColor = { 255, 255, 255, 255 };
	//Render text
    if( !gTimeTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), tColor,gfont.f1) )
	{
		printf( "Unable to render time texture!\n" );
	}
	gTimeTextTexture.render( 5, 0 );
}

void timer()//show current score
{
	score.recent = score.ex + score.level[game.levelNow] - (((((SDL_GetTicks() - allTimes.startTime)/1000)-(allTimes.timeReduced*5)))*score.reduce[game.levelNow]) ;
	
	if(game.levelNow==2)//level2: score changes with bullets shot
	{
		score.recent -= score.bulletReduce * 30;
	}

	if(score.recent<=0)//minimum score 0
	{
		score.recent = 0;
	}

	gfont.timeText.str( "" );
	gfont.timeText << "Score : " << score.recent; 

	SDL_Color tColor = { 255, 255, 255, 255 };

	if(game.levelNow==1)
	{
		tColor = { 0, 0, 0, 255 };
	}
	
	//Render text
    if( !gTimeTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), tColor,gfont.f1) )
	{
		printf( "Unable to render time texture!\n" );
	}
	if(game.levelNow==2) {gTimeTextTexture.render( SCREEN_WIDTH - gTimeTextTexture.getWidth()-10, 0 );}
	else {gTimeTextTexture.render( SCREEN_WIDTH/2, 0 );}
}

void countdown()//countdown before starting game
{
    gfont.timeText.str( "" );
	gfont.timeText << "GET READY!  " <<  3 - ((SDL_GetTicks() - allTimes.startTime)/1000); //show coutdown for 3 secs

	SDL_Color tColor = { 255, 255, 255, 255 };

	if(game.levelNow==2)
	{
		tColor = { 0, 0, 0, 255 };
	}
		
	//Render text
    if( !gTimeTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), tColor,gfont.f2) )
	{
		printf( "Unable to render time texture!\n" );
	}

	if((((SDL_GetTicks()-allTimes.startTime)/1000)>3) && (((SDL_GetTicks()-allTimes.startTime)/1000)<5))//show go! from 3 to 5 sec
	{
		gfont.timeText.str( "" );
		gfont.timeText << "GO!" ; 

		 if( !gTimeTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), tColor,gfont.f2) )
		{
			printf( "Unable to render time texture!\n" );
		}
		gTimeTextTexture.render( SCREEN_WIDTH/2-(gTimeTextTexture.getWidth()/2), (SCREEN_HEIGHT/2)-(gTimeTextTexture.getHeight()/2));
	}
	else if(((SDL_GetTicks()-allTimes.startTime)/1000)==5)//start game after 5 secs
	{
		allTimes.timerStart = 1;//game start condition
		gTimeTextTexture.free(); 
		allTimes.startTime = SDL_GetTicks() ;//game timer start
		allTimes.timeReduced = 0 ;//hourglass not collected yet
	}
	else
	{
		gTimeTextTexture.render( (SCREEN_WIDTH/2)-(gTimeTextTexture.getWidth()/2), (SCREEN_HEIGHT/2)-(gTimeTextTexture.getHeight()/2) );
	}
}
