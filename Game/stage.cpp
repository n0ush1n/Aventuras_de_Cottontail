#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#include "stage.hpp"

void initStage(void)//initialize things
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	app.delegate.level[0] = playButton;
	app.delegate.level[1] = level1;
	app.delegate.level[2] = level2;
	app.delegate.level[3] = level3;
	game.levelNow = 1;

	initPlayer();	
	initScope();
	loadEverythingYouHaveGot();
}

static void initPlayer()//initialize player
{
	player = (struct Entity*)malloc(sizeof(struct Entity));
	memset(player, 0, sizeof(Entity));

	//initialize player position
	player->x = DEFAULT_x;
	player->y = DEFAULT_y;
}

static void initScope()//initialize scope
{
	scope = (struct Entity*)malloc(sizeof(struct Entity));
	memset(scope, 0, sizeof(Entity));

	//initialize scope position
	scope->x = SCREEN_WIDTH/2 - 105;
	scope->y = SCREEN_HEIGHT/2 -30;
}

static void logic(void)//level item movements
{
	if(app.keyboard[SDL_SCANCODE_ESCAPE])//esc pressed
	{
		game.level[game.levelNow].paused = 1 ;//game pause condition
		app.keyboard[SDL_SCANCODE_ESCAPE] = 0 ;
		allTimes.pausedOn = SDL_GetTicks();//game paused when?
	}
	if(app.keyboard[SDL_SCANCODE_F1])//F1 pressed
	{
		game.level[game.levelNow].story = 2 ;//show story
		app.keyboard[SDL_SCANCODE_F1] = 0;
	}

	if(game.levelNow==1)//level 1
	{
		doCar();//car movement
		if(allTimes.t==500)//change hourglass position after every 8 seconds
		{
			doHourglass();
			allTimes.t = 0 ;//start hourglass position changer timer again
		}
		allTimes.t++;//increase hourglass position changer time

		if(allTimes.t2==1250)//change map position after every 20 seconds
		{
			doMap();
			allTimes.t2 = 0 ;//start map position changer timer again
		}
		allTimes.t2++;//increase map position changer time
		doPlayer();//player movement
	}
	else if(game.levelNow==2)//level 2
	{
		doScope();//scope movement

		if(app.keyboard[SDL_SCANCODE_LCTRL])//lctrl pressed
		{
            game.level[2].collision.bullet++;//number of used  bullet

			score.bullet = 1;//bullet shot now

			jungleSpriteSheetTexture.render( scope->x+90, scope->y+90, &jungleSpriteClips[ 6 ] );//show bullet 

			if(sfx.sCount) {playSound(sfx.gunshot);}//bullet shot sound

			app.keyboard[SDL_SCANCODE_LCTRL] = 0;

            int cnt = 0;
			//check if junglee dead or alive
            for(int i = 0; i < 5; i++)
            {
				if(!game.level[2].collision.dead[i])//junglee still alive
					{
               		if(((scope->x+105 > junglee[i].x) && (scope->x+105 < junglee[i].x + 90)) && ((scope->y+105 > junglee[i].y) && (scope->y+105 < junglee[i].y + 90)) && ((scope->x+105 > window[i].x) && (scope->x+105 < window[i].x1)) && ((scope->y+105 > window[i].y) && (scope->y+105 < window[i].y1)))
					{
						if(sfx.sCount) {playSound(sfx.scream);}//junglee scream
						cout << "ENEMY HIT\n" << "ENEMY no." << i+1 << "\n";
						game.level[2].collision.dead[i] = 1;//junglee dead
						break;
					}
                }
            }
		}
	}
	else if(game.levelNow==3)//level 3
	{
		doDemon();//demon movement
		doMazePlayer();//player movement
	}	
}

void doMap(void)//level 1 hourglass position change with time
{
	enemy[1].x = NEW_WIDTH(118) + (rand() % (NEW_WIDTH(422)-200 + (-4 + (rand() % 15))));
	enemy[1].y = NEW_HEIGHT(118) + (rand() % (SCREEN_HEIGHT-200 + (-2 + (rand() % 12))));
}

void doHourglass(void)//level 1 map position change with time
{
	enemy[0].x = NEW_WIDTH(118) + (rand() % (NEW_WIDTH(422)-NEW_WIDTH(118) + (-2 + (rand() % 10))));
	enemy[0].y = NEW_HEIGHT(118) + (rand() % (SCREEN_HEIGHT-NEW_HEIGHT(118) + (-3 + (rand() % 10))));
}

