#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void playButton(void)//new game or continue
{
	menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 3 ] );
    doInput();
    
    if(app.keyboard[SDL_SCANCODE_ESCAPE])//esc pressed
	{
		game.playing = 0 ;//game pause condition
		app.keyboard[SDL_SCANCODE_ESCAPE] = 0 ;
		game.mainMenu = 1 ;
	}

    if(app.mouse.x>NEW_WIDTH(141) && app.mouse.x<NEW_WIDTH(400))
		{
            if(app.mouse.y>NEW_HEIGHT(250) && app.mouse.y<NEW_HEIGHT(350))//new game
            {
                if(app.mouse.button[SDL_BUTTON_LEFT])
                {
                    if(sfx.sCount)
                    {
                        playSound(sfx.click);
                    }
                    
                    level1Start();//start from level 1

                    if(sfx.mCount)
                    {
                       playMusic();//level 1 music
                    }
                }
                else
                {
                    menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 4 ] );
                }	
            }   
            if(app.mouse.y>NEW_HEIGHT(410) && app.mouse.y<NEW_HEIGHT(520))//continue saved game
            {
                if(app.mouse.button[SDL_BUTTON_LEFT])
                {
                    if(sfx.sCount)
                    {
                        playSound(sfx.click);
                    }
                    loadSavedGame();//load saved game
                    allTimes.timerStart = 1;//countdown end
                    game.level[game.levelNow].paused = 0;//game not paused
                    allTimes.startTime = SDL_GetTicks();//timer initialize
                    game.playing = 1;//game playing
	                game.mainMenu = 0;//not in main menu
                    if(sfx.mCount)
                    {
                        playMusic();
                    }
                }
                else
                {
                    menuSpriteSheetTexture.render( 0, 0, &menuSpriteClips[ 9 ] );
                }	
            }
        }
        drawCursor();//draw cursor
}

void loadSavedGame()
{
	//File pointer to hold reference to our file 
	FILE *fPtr;
    FILE *fPtr1;
    FILE *fPtr2;
    FILE *fPtr3;

	int A[30], temp;
	char p[10000];
	int i = 0;
    
	fPtr = fopen("files/save/saved.txt", "r");//level file open

    fscanf(fPtr, "%d", &game.levelNow);//load saved game level
    fclose(fPtr);

	if(game.levelNow==1)//level 1 saved
    {
        fPtr1 = fopen("files/save/savedLevel1.txt", "r");//open level1 file
		while(fscanf(fPtr1, "%d",&A[i])==1)//get all the data
        {
            i++;
            if(i==17)
            {
                break;
            }
        }
        fclose(fPtr1);//close file
        
        //player coordinates
        player->x = A[0];
        player->y = A[1];

        for(int j = 0 ; j < 5 ; j ++)//car directions
        {
            car[j].a = A[j+2];
        }

        for(int j = 0 ; j < 5 ; j ++)//car coordinates
        {
            car[j].x = A[j+7];
        }
        allTimes.t = A[12];//hourgalss timer
        allTimes.t2 = A[13];//map timer

        score.level[game.levelNow] = A[14];//player score now

        game.level[1].collision.check[0] = A[15];//hourglass collected or not
        game.level[1].collision.check[1] = A[16];//map collected or not

        score.reduce[1] = 10;//level 1 score factor
        score.ex = 0;//previous level score is 0
        game.level[1].story = 1;
    }   
    else if(game.levelNow==2)//saved level 2
    {
        fPtr1 = fopen("files/save/savedLevel2.txt", "r");//open level 2 file
		while(fscanf(fPtr1, "%d",&A[i])==1)//get all data
        {
            i++;
            if(i==20)
            {
                break;
            }
        }
        fclose(fPtr1);//close file
        scope->x = A[0];
        scope->y = A[1];

        for(int j = 0 ; j < 5 ; j ++)//junglee directions
        {
            junglee[j].dir = A[j+2];
        }

        for(int j = 0 ; j < 5 ; j ++)//junglee coordinates
        {
            junglee[j].x = A[j+7];
        }
        
        for(int j = 0 ; j < 5 ; j ++)//junglee dead or not
        {
            game.level[2].collision.dead[j] = A[j+12];
        }
        game.level[2].collision.bullet = A[17];//bullet used

        score.level[game.levelNow] = A[18];//current score
        score.ex = 0;//previous level score
        score.reduce[2] = 2;//level 2 scoring factor
	     score.bulletReduce = 0;
        //scope coordinates
        player->x = 10;
		player->y = 350;
    }   
    else if(game.levelNow==3)//level 3
    {
        i = 0 ;
        fPtr1 = fopen("files/save/savedLevel3.txt", "r");//level 3 saving file open
		while(fscanf(fPtr1, "%d",&A[i])==1)//get all data
        {
            i++;
            if(i==21)
            {
                break;
            }
        }
        fclose(fPtr1);//close file

        //player coordinates
        player->x = A[0];
        player->y = A[1];

        for(int j = 0 ; j < 5 ; j ++)//demon directions
        {
           demon[j].dir = A[j+2];
        }
		
		for(int j = 0 ; j < 5 ; j ++)//demon x coordinates
        {
            demon[j].x = A[j+7];
        }
		
		for(int j = 0 ; j < 5 ; j ++)//demon y coordinates
        {
            demon[j].y = A[j+12];
        }

        for(int j = 0 ; j < 3 ; j ++)//demon y coordinates
        {
            game.level[3].collision.check[j] = A[j+17];
        }
        score.level[game.levelNow] = A[20];//current score
        cout<<score.recent<<endl;
        score.ex = 0;//previous level score
        score.reduce[3] = 3;//level 3 score factor
    }   
}
