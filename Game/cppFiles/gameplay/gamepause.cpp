#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

void GamePaused()
{
    gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 0 ] );
	
	doInput();

	if(app.mouse.y>NEW_HEIGHT(370) && app.mouse.y<NEW_HEIGHT(475))//buttons
	{
		if(app.mouse.x> NEW_WIDTH(87) && app.mouse.x<NEW_WIDTH(143))//menu
		{
			if(app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
			{
				if(sfx.sCount){playSound(sfx.click);}

				game.playing = 0;//game not playing
				game.save = 1;//save menu show
			}	
			gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 1 ] );	
        }
		else if(app.mouse.x> NEW_WIDTH(186) && app.mouse.x<NEW_WIDTH(242))//play
		{
			if(app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
			{
				if(sfx.sCount){playSound(sfx.click);}
				game.level[game.levelNow].paused = 0 ;//unpause
				allTimes.startTime += SDL_GetTicks() - allTimes.pausedOn ;//timer start again
			}
			gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 2 ] );
        }
		if(app.mouse.x>NEW_WIDTH(281)&& app.mouse.x<NEW_WIDTH(338))//music&sound
		{
			if(app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
			{
				if(sfx.sCount){playSound(sfx.click);}
				if(sfx.mCount)//playing music
				{
					Mix_PauseMusic();//pause music
					sfx.mCount = 0;//music paused
				}
				else//not playing music
				{
					playMusic();//play music
					sfx.mCount = 1;//music play
				}
			}
			gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 3 ] );
        }
		if(app.mouse.x>NEW_WIDTH(377) && app.mouse.x<NEW_WIDTH(433))//sound
		{
			if(app.mouse.button[SDL_BUTTON_LEFT])
			{
				if(sfx.sCount)//sound on
				{
					playSound(sfx.click);
					sfx.sCount = 0;//sound off
				}
				else//sound off
				{
					sfx.sCount = 1;//sound on
				}
			}
			gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 4 ] );
        }
    }
	app.mouse.button[SDL_BUTTON_LEFT] = 0 ;
	drawCursor();//draw cursor
}

void saveOrNot()//save the game or not?
{
	gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 5 ] );
	doInput();
	if(app.keyboard[SDL_SCANCODE_ESCAPE])//esc pressed
	{
		game.level[game.levelNow].paused = 1;//go back to pause menu
		app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
		game.save = 0;//not in the save option
		game.playing = 1;//game still playing
	}
	else
	{
		if(app.mouse.y>NEW_HEIGHT(400) && app.mouse.y<NEW_HEIGHT(435))//save
		{
			if(app.mouse.x>NEW_WIDTH(140) && app.mouse.x<NEW_WIDTH(210))//buttons
			{
				if(app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
				{
					if(sfx.sCount){playSound(sfx.click);}
					saveTheGame();//save the game
					game.playing = 0 ;//game not playing
					game.mainMenu = 1;//go to mainmenu
					game.save = 0 ;//not in the save option
					Mix_PauseMusic();
					if(sfx.mCount) {playMusic();}//menu music
				}	
				gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 6 ] );	
			}
			else if(app.mouse.x>NEW_WIDTH(300) && app.mouse.x<NEW_WIDTH(350))//do not save
			{
				if(app.mouse.button[SDL_BUTTON_LEFT])//mouse clicked
				{
					if(sfx.sCount){playSound(sfx.click);}
					game.playing = 0 ;//game not playing
					game.mainMenu = 1;//go to mainmenu
					game.save = 0 ;//not in the save option
					Mix_PauseMusic();
					if(sfx.mCount) {playMusic();}//play menu music
				}
				gamePauseSpriteSheetTexture.render( 0, 0, &gamePauseSpriteClips[ 7 ] );
			}
		}
		app.mouse.button[SDL_BUTTON_LEFT] = 0 ;
	}
}

void saveTheGame()
{
	long long int a[5], temp;
	int A[30];
	int i = 0;

	FILE *fPtw = fopen("files/save/saved.txt", "w");//open file
	fprintf(fPtw, "%d\n", game.levelNow);//save the level
	fclose(fPtw);//close file

	if(game.levelNow==1)//saving level 1
	{
		FILE *fPtw1 = fopen("files/save/savedLevel1.txt", "w");//open level1 file
		fprintf(fPtw1, "%.0lf %.0lf\n", player->x,player->y);//player coordinates saved

		for(int j = 0 ; j < 5 ; j ++)//car directions saved
        {
            fprintf(fPtw1, "%d ", car[j].a);
        }
		fprintf(fPtw1, "\n");

        for(int j = 0 ; j < 5 ; j ++)//car coordinates saved
        {
            fprintf(fPtw1, "%d ", car[j].x);
        }
		fprintf(fPtw1, "\n");
		
		fprintf(fPtw1, "%d %d\n", allTimes.t,allTimes.t2);//level 1 item timer time saved
		fprintf(fPtw1, "%d\n",score.recent);//current score saved
		fprintf(fPtw1, "%d %d\n",game.level[1].collision.check[0],game.level[1].collision.check[1]);//collided with map and hourglass or not, saved
		
		fclose(fPtw1);//close the file
	}	
	else if(game.levelNow==2)
	{
		FILE *fPtw2 = fopen("files/save/savedLevel2.txt", "w");//open level2 saving file

		fprintf(fPtw2, "%.0lf %.0lf\n", scope->x,scope->y);//save scope coordinates

		for(int j = 0 ; j < 5 ; j ++)//save junglee directions
        {
            fprintf(fPtw2, "%d ", junglee[j].dir);
        }
		fprintf(fPtw2, "\n");

        for(int j = 0 ; j < 5 ; j ++)//save junglee coordinates
        {
            fprintf(fPtw2, "%d ", junglee[j].x);
        }
		fprintf(fPtw2, "\n");

		for(int j = 0 ; j < 5 ; j ++)//save junglee dead or not
        {
            fprintf(fPtw2, "%d ", game.level[2].collision.dead[j]);
        }
		fprintf(fPtw2, "\n");
		
		fprintf(fPtw2, "%d\n",game.level[2].collision.bullet);//save bullets fired
		fprintf(fPtw2, "%d\n",score.recent);//save current score
		
		fclose(fPtw2);//close the file
	}	
	else if(game.levelNow==3)
	{
		FILE *fPtw3 = fopen("files/save/savedLevel3.txt", "w");//open level 3 saving file

		fprintf(fPtw3, "%.0lf %.0lf\n", player->x,player->y);//player coordinates

		for(int j = 0 ; j < 5 ; j ++)//demon directions
        {
            fprintf(fPtw3, "%d\n", demon[j].dir);
        }
		fprintf(fPtw3, "\n");
		for(int j = 0 ; j < 5 ; j ++)//demon x coordinate
        {
            fprintf(fPtw3, "%d\n", demon[j].x);
        }
		fprintf(fPtw3, "\n");
		for(int j = 0 ; j < 5 ; j ++)//dmeon y coordinate
        {
            fprintf(fPtw3, "%d\n", demon[j].y);
        }
		fprintf(fPtw3, "\n");
		for(int j = 0 ; j < 3 ; j ++)//dmeon y coordinate
        {
            fprintf(fPtw3, "%d\n", game.level[3].collision.check[j]);
        }
		fprintf(fPtw3, "\n");
		fprintf(fPtw3, "%d\n",score.recent);//current score
	cout << score.recent<<endl;
		fclose(fPtw3);//close file
	}	
}