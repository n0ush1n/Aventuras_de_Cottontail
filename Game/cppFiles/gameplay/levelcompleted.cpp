#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void levelCompleted(void)
{
	gfont.timeText.str( "" );
	gfont.timeText << "LEVEL COMPLETED" ; 
	SDL_Color textColor = { 255, 255, 255, 0xFF };
	
	//Render text
    if( !gLVLCompTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), textColor,gfont.f2) )//show level completed text
	{
		printf( "Unable to render time texture!\n" );
	}
	gLVLCompTextTexture.render((SCREEN_WIDTH/2)-(gLVLCompTextTexture.getWidth()/2), (SCREEN_HEIGHT/2)-(3*gLVLCompTextTexture.getHeight())) ;

	gfont.timeText.str( "" );
	gfont.timeText << "YOUR SCORE: " << score.recent ; 

	//Render text
    if( !gLVLCompTextTexture.loadFromRenderedText( gfont.timeText.str().c_str(), textColor,gfont.f1) )//show current score
	{
		printf( "Unable to render time texture!\n" );
	}
	gLVLCompTextTexture.render((SCREEN_WIDTH/2)-(gLVLCompTextTexture.getWidth()/2), (SCREEN_HEIGHT/2)+(gLVLCompTextTexture.getHeight()));

	if(score.leader>0)//player got position in leaderboard
	{
		gfont.timeText.str(" ");
		
		gfont.timeText << "!!!NEW POSITION IN LEADERBOARD!!!" ;
		if (!gTimeTextTexture.loadFromRenderedText(gfont.timeText.str().c_str(), textColor,gfont.f3))
		{
				printf("Unable to render time texture!\n");
		}
		gTimeTextTexture.render(140, 380);//show new position in leaderboard text

		gfont.timeText.str(" ");

		gfont.timeText << "YOUR POSITION: " << score.leader ;
		if (!gTimeTextTexture.loadFromRenderedText(gfont.timeText.str().c_str(), textColor,gfont.f1))//render text
		{
				printf("Unable to render time texture!\n");
		}
		gTimeTextTexture.render((SCREEN_WIDTH/2)-(gTimeTextTexture.getWidth()/2), 650 );//show current position  in leaderboard
	}

	if(allTimes.Check<10)//blinking enter text
	{
		storySpriteSheetTexture.render( 0, 0, &storySpriteClips[ 7 ] );
		allTimes.Check++ ;
	}
	else if(allTimes.Check==30)//blinking enter text timer
	{
		allTimes.Check = 0 ;
	}
	else//blinking enter text timer increament
	{
		allTimes.Check++ ;
	}
	
	if(app.keyboard[SDL_SCANCODE_RETURN])//PRESSED ENTER KEY
	{
		game.levelNow++ ;//next level
		if(game.levelNow==2)//level 2
		{
			level2Start();//start level 2
			//player position for level 2
			player->x = 10;
			player->y = 350;
		}
		else if(game.levelNow == 3)//level 3
		{
			level3Start();//start level 3
		}
		else if(game.levelNow == 4)//game completed
		{
			game.playing = 0 ;//game not playing
			game.mainMenu = 1;//show menu 
			game.save = 0 ;//not saving game
			Mix_PauseMusic();
			if(sfx.mCount) {playMusic();}//menu music
		}

		game.level[game.levelNow].story = 2;//game story for new game
		if(sfx.mCount) {playMusic();}//level music
		
		app.keyboard[SDL_SCANCODE_RETURN] = 0 ;

		score.leader = 0;//not ranked in leaderboard currently
		score.ex = score.recent;//score from previous level
		allTimes.Check = 0 ;//blinking enter text timer
	}
}

void Naming()//player name input
{
	bool renderText = false;
	SDL_Color textColor = { 255, 255, 255, 0xFF };

	if( !gPromptTextTexture.loadFromRenderedText( "ENTER YOUR NAME:", textColor,gfont.f3 ) )//show enter you name text
	{
		printf( "Failed to render prompt text!\n" );
	}

   	if((app.typeText.length() > 0) && (app.keyboard[SDL_SCANCODE_RETURN]))//pressed enter
	{
		SDL_StopTextInput();//stop taking text input
		game.enterName = 2;//leaderboard show condition
		loadscore();//load score and name in highscore files
		app.keyboard[SDL_SCANCODE_RETURN] = 0;
	}
    else if( (app.keyboard[SDL_SCANCODE_BACKSPACE]==1) && (app.typeText.length() > 0) )//delete previous letter
	{
		//lop off character
		app.typeText.pop_back();//delete from text
		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
		renderText = true;
	}
	else if(app.text==1 && app.keyboard[SDL_SCANCODE_SPACE]==0 && app.typeText.length()<10)//add letter
	{
		app.typeText += app.inputText;//add text
		renderText = true;
		app.text = 0;
	}

	if( renderText )//show text 
	{
		//Text is not empty
		if( app.inputText != "" )
		{
			//Render new text
			gInputTextTexture.loadFromRenderedText( app.typeText.c_str(), textColor,gfont.f1 );
		}
		//Text is empty
		else
		{
			//Render space texture
			gInputTextTexture.loadFromRenderedText( " ", textColor ,gfont.f1);
		}
	}
	gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 250 );
	gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, 350);
}