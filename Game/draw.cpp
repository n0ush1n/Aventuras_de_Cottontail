#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#include "texture.cpp"

void drawCursor()
{
	menuSpriteSheetTexture.render( app.mouse.x,app.mouse.y, &menuSpriteClips[ 1 ] );
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 62, 180, 137, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

void loadEverythingYouHaveGot() // load fonts, sounds & images
{
	initFont() ;//font initialize
	initSounds();//sound initialize
    initSprites();//sprite initialize
}

static void draw(void) //draw levels
{
	if(game.levelNow==1) // draw level 1 things
	{
		if(game.level[1].collision.Car == 0) //still playing
		{
			drawCar();
			drawItems();
			drawPlayer();
		}
		else // hit by a car & game over
		{
			Mix_PauseMusic();
			if(sfx.sCount){playSound(sfx.gameover);} // gameover sound
			game.level[1].completed = -1; //gameover
			score.leader = 0; // clearing the previous score for the next one
		}
	}
	else if(game.levelNow==2) // draw level 2 
	{
		drawJunglee();
		jungleSpriteSheetTexture.render( 0, 0, &jungleSpriteClips[ 0 ] );
		drawScope();
	}	
	else if(game.levelNow==3) // draw level 3
	{
		if(game.level[3].collision.demon == 0) //still playing
		{
			drawMazeThings();// draw the items the player have to collect
			drawPlayer();
			drawDemon();
		}
		else // bullet ended and game over
		{
			Mix_PauseMusic();
			if(sfx.sCount){playSound(sfx.gameover);} // gameover sound
			game.level[3].completed = -1; //gameover
			score.leader = 0; // clearing the previous score for the next one
		}
	}	
}

void drawCar()
{
	for(int i = 0 ; i < 5 ; i++) //  5 cars in different heights
	{
		roadSpriteSheetTexture.render( car[i].x, car[i].y, &roadSpriteClips[ i+1 ] );
	}	
}

static void drawItems(void) //  level 1 player
{	
	roadSpriteSheetTexture.render( player->x, player->y, &roadSpriteClips[ 6 ] );
	
	for(int i = 0 ; i < 2 ; i++)// map and hourglass
	{
		if(!game.level[1].collision.check[i])// if not collected, then draw
		{
			roadSpriteSheetTexture.render(enemy[i].x,enemy[i].y,&roadSpriteClips[i+7]);
		}
	}	
} 

void drawScope()// level 2 player scope
{
	jungleSpriteSheetTexture.render( scope->x, scope->y, &jungleSpriteClips[ 4 ] );
}

static void drawPlayer()// level 2 rabbit
{	
	if(player->up) {roadSpriteSheetTexture.render( player->x, player->y, &roadSpriteClips[ 6 ] );}
	else {mazeSpriteSheetTexture.render( player->x, player->y, &mazeSpriteClips[ 2 ] );}
} 

void drawJunglee()//level 2 enemies
{
	for(int i = 0 ; i < 5 ; i++)
	{
		if(game.level[2].collision.dead[i] == 0) //if the enemy is not dead
		{
			if(junglee[i].dir==-1){jungleSpriteSheetTexture.render( junglee[i].x, junglee[i].y, &jungleSpriteClips[ 2 ] );}
			else {jungleSpriteSheetTexture.render( junglee[i].x, junglee[i].y, &jungleSpriteClips[ 3 ] );}
		}
	}	
}

static void drawDemon(void)// level 3 enemies
{
	for(int i = 0 ; i <5 ; i++)// 5 demons
	{
		mazeSpriteSheetTexture.render( demon[i].x, demon[i].y, &mazeSpriteClips[ 1 ] );
	}
}
void drawMazeThings()// things in level 3 that need to be collected
{
	for(int i = 0 ; i < 3 ; i++)
	{
		if(!game.level[3].collision.check[i])// if the item is not collected, the draw
		{
			if(i==0 && game.level[3].collision.check[1]==1)// if the key is collected, open the treasure
			{
				mazeSpriteSheetTexture.render( mazeThings[i].x, mazeThings[i].y, &mazeSpriteClips[ 3 ] );
			}
			else// draw the closed treasure, map and key
			{
				mazeSpriteSheetTexture.render( mazeThings[i].x, mazeThings[i].y, &mazeSpriteClips[ 4+i ] );
			}		
		}		
		if(game.level[3].collision.check[2])//if the map is collected, draw the exit
		{
			mazeSpriteSheetTexture.render( 295, 5, &mazeSpriteClips[ 7] );	
		}		
	}
}