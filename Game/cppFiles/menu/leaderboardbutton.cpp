#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void LeaderboardMenu(void)
{
    leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 0 ] );
	if(game.leaderBoard!=1) {leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 5 ] );}
	if(game.leaderBoard!=3){leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ game.leaderBoard+1 ] );}
	else 
	{
		leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 7 ] );
		leaderBoardSpriteSheetTexture.render( 0, CHANGE_HEIGHT(760), &leaderBoardSpriteClips[ 1 ] );
	}

	loadLeaderboardScores();

	SDL_Color textColor = {255, 255, 255, 255};
	
	if(app.mouse.x>NEW_WIDTH(16) && app.mouse.x<NEW_WIDTH(61) && app.mouse.y>NEW_HEIGHT(31) && app.mouse.y<NEW_HEIGHT(112))
	{
        if (app.mouse.button[SDL_BUTTON_LEFT])
        {
            if(sfx.sCount)
            {
                playSound(sfx.click);
            }
            if(game.leaderBoard==1) {game.mainMenu = 1 ;}
			else { game.leaderBoard--;}
        }
        else
        {
			if(game.leaderBoard==1){leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 1 ] );}
            else {leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 6 ] );}
        }		
    }
	if(game.leaderBoard<3)
	{
		if(app.mouse.x>NEW_WIDTH(21) && app.mouse.x<NEW_WIDTH(65) && app.mouse.y>NEW_HEIGHT(620) && app.mouse.y<NEW_HEIGHT(700))
		{
			if (app.mouse.button[SDL_BUTTON_LEFT])
			{
				if(sfx.sCount)
				{
						playSound(sfx.click);
				}
				game.leaderBoard++ ;
			}
			else
			{
				leaderBoardSpriteSheetTexture.render( 0, 0, &leaderBoardSpriteClips[ 4 ] );
			}
			app.mouse.button[SDL_BUTTON_LEFT] = 0;		
		}
	}
	if(game.leaderBoard==3)
	{
		if(app.mouse.x>NEW_WIDTH(21) && app.mouse.x<NEW_WIDTH(65) && app.mouse.y>NEW_HEIGHT(620) && app.mouse.y<NEW_HEIGHT(700))
		{
			if (app.mouse.button[SDL_BUTTON_LEFT])
			{
				if(sfx.sCount)
				{
						playSound(sfx.click);
				}
				game.mainMenu = 1 ;
			}
			else
			{
				leaderBoardSpriteSheetTexture.render( 0, CHANGE_HEIGHT(760), &leaderBoardSpriteClips[ 1 ] );
			}
			app.mouse.button[SDL_BUTTON_LEFT] = 0;		
		}
	}
}

void loadLeaderboardScores()
{
	FILE *fPtr,*fPtr1;
	long long int a[8];
	char p[100000];
	char x;
	int i = 0;
	int heightGoes = 130;
	SDL_Color textColor = {255, 255, 255, 255};

	if(game.leaderBoard==1){fPtr = fopen("files/highscores/scores/scores1.txt", "r");}
	else if(game.leaderBoard==2){fPtr = fopen("files/highscores/scores/scores2.txt", "r");}
	else if(game.leaderBoard==3){fPtr = fopen("files/highscores/scores/scores3.txt", "r");}	

	while (fscanf(fPtr, "%lld",&a[i]) == 1)
	{
		i++;
		if (i == 8)
			break;
	}
	fclose(fPtr);

	i = 0;
	if(game.leaderBoard==1){fPtr1 = fopen("files/highscores/names/name1.txt", "r");}
	else if(game.leaderBoard==2){fPtr1 = fopen("files/highscores/names/name2.txt", "r");}
	else if(game.leaderBoard==3){fPtr1 = fopen("files/highscores/names/name3.txt", "r");}	

	while (fscanf(fPtr1, "%s",highscore[i].name) == 1)
	{
		i++;
		if (i == 8)
			break;
	}
	fclose(fPtr1);

	heightGoes = 130 ;

	for(int u = 0 ; u < 8 ; u++)
	{
		sprintf(p, "%s", highscore[u].name);

		int ll=strlen(p);
		p[ll]='\0';

		gfont.timeText.str(" ");

		gfont.timeText << "" << p;
		if (!gTimeTextTexture.loadFromRenderedText(gfont.timeText.str().c_str(), textColor,gfont.f3))
		{
			printf("Unable to render time texture!\n");
		}
		heightGoes += 60 ;
		gTimeTextTexture.render(NEW_WIDTH(160) ,NEW_HEIGHT(heightGoes));
	}
	
	heightGoes = 130 ;

	for(int u = 0 ; u < 8 ; u++)
	{
		sprintf(p, "%d.", u+1);
		
		gfont.timeText.str(" ");

		gfont.timeText << "" << p;
		if (!gTimeTextTexture.loadFromRenderedText(gfont.timeText.str().c_str(), textColor,gfont.f3))
		{
			printf("Unable to render time texture!\n");
		}
		heightGoes += 60 ;
		gTimeTextTexture.render(NEW_WIDTH(100) ,NEW_HEIGHT(heightGoes));
	}	

	heightGoes = 130 ;

	for(int u = 0 ; u < 8 ; u++)
	{
		sprintf(p, "%lld", a[u]);

		int ll=strlen(p);
		p[ll]='\0';

		gfont.timeText.str(" ");

		gfont.timeText << "" << p;
		if (!gTimeTextTexture.loadFromRenderedText(gfont.timeText.str().c_str(), textColor,gfont.f3))
		{
			printf("Unable to render time texture!\n");
		}
		heightGoes += 60 ;
		gTimeTextTexture.render(NEW_WIDTH(350) ,NEW_HEIGHT(heightGoes));
	}
}

void loadscore()
{	
	/* File pointer to hold reference to our file */
	FILE *fPtr, *fPtr1;
	FILE *fPtw, *fPtw1;
	long long int a[8], temp;
	char p[10000];
	int i = 0;
	if(game.levelNow==1){fPtr = fopen("files/highscores/scores/scores1.txt", "r");}
	else if(game.levelNow==2){fPtr = fopen("files/highscores/scores/scores2.txt", "r");}
	else{fPtr = fopen("files/highscores/scores/scores3.txt", "r");}
	
	for(i = 0 ; i < 8 ; i++)
	{
		fscanf(fPtr,"%lld",&a[i]);
	}
	fclose(fPtr);

	if(game.levelNow==1){fPtr1 = fopen("files/highscores/names/name1.txt", "r");}
	else if(game.levelNow==2){fPtr1 = fopen("files/highscores/names/name2.txt", "r");}
	else{fPtr1 = fopen("files/highscores/names/name3.txt", "r");}

	for(i = 0 ; i < 8 ; i++)
	{
		fscanf(fPtr1,"%s",highscore[i].name);
	}
	fclose(fPtr1);

	cout << score.recent << endl;

	for(int j = 0 ; j < 8 ; j ++)
	{
		if (score.recent > a[j])
		{
			for(int k = 7 ; k > j ; k--)
			{
				a[k] = a[k-1];
				strcpy(highscore[k].name,highscore[k-1].name);
			}
			a[j] = score.recent ;
			strcpy(highscore[j].name,app.typeText.c_str());	
			cout << score.recent << endl ;
			score.leader = j+1;
			break;
		}
	}

	if(game.levelNow==1){fPtw = fopen("files/highscores/scores/scores1.txt", "w");}
	else if(game.levelNow==2){fPtw = fopen("files/highscores/scores/scores2.txt", "w");}
	else{fPtw = fopen("files/highscores/scores/scores3.txt", "w");}

	for(int j = 0 ; j < 8 ; j ++)
	{
		fprintf(fPtw, "%lld\n", a[j]);
	}
	fclose(fPtw);

	if(game.levelNow==1){fPtw1 = fopen("files/highscores/names/name1.txt", "w");}
	else if(game.levelNow==2){fPtw1 = fopen("files/highscores/names/name2.txt", "w");}
	else{fPtw1 = fopen("files/highscores/names/name3.txt", "w");}	

	for(int j = 0 ; j < 8 ; j ++)
	{
		fprintf(fPtw1, "%s\n", highscore[j].name);
	}
	
	fclose(fPtw1);
	game.enterName = 0;
}