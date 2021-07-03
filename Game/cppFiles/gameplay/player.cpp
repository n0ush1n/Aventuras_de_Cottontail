#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void doPlayer()//level 1 player movement
{
	player->dx = player->dy = 0;

	if (app.keyboard[SDL_SCANCODE_UP])//player goes up
	{
		if(player->y-player->dy>=0) 
		{
			player->dy = -PLAYER_SPEED;//player is in the frame ,so go up
			player->up = 1 ;
		}

	}
	if (app.keyboard[SDL_SCANCODE_DOWN])//player goes down
	{
		if(player->y+player->dy+45<=SCREEN_HEIGHT) 
		{
			player->dy = PLAYER_SPEED;//player is in the frame ,so go down
			player->up = 0 ;
		}
	}
	if (app.keyboard[SDL_SCANCODE_LEFT])//player goes left
	{
		if(player->x-player->dx>=NEW_WIDTH(118)) player->dx = -PLAYER_SPEED;//player is in the frame ,so go left
	}
	if (app.keyboard[SDL_SCANCODE_RIGHT])//player goes right
	{
		if(player->x+player->dx+45<=NEW_WIDTH(422)) player->dx = PLAYER_SPEED;//player is in the frame ,so go right
	}
	
	//car collision
	for(int i = 0; i < 5; i++)
	{
		if(((player->y+PLAYER_HEIGHT > car[i].y && player->y+PLAYER_HEIGHT < car[i].y+CAR_HEIGHT) || (player->y > car[i].y && player->y < car[i].y+CAR_HEIGHT)) && ((player->x+PLAYER_WIDTH > car[i].x && player->x+PLAYER_WIDTH < car[i].x+CAR_WIDTH) || (player->x > car[i].x && player->x < car[i].x+CAR_WIDTH)))
		{
			game.level[1].collision.Car = 1;//collision flag
		}
	}

	//entity collision
	for(int i = 0; i < 2; i++)
	{
		if(!game.level[1].collision.check[i])//not collided
		{
			if(((player->y+PLAYER_HEIGHT > enemy[i].y && player->y+PLAYER_HEIGHT < enemy[i].y+40) || (player->y > enemy[i].y && player->y < enemy[i].y+40)) && ((player->x+PLAYER_WIDTH > enemy[i].x && player->x+PLAYER_WIDTH < enemy[i].x+40) || (player->x > enemy[i].x && player->x < enemy[i].x+40)))
			{
				if(app.keyboard[SDL_SCANCODE_LSHIFT])//pressed shift key
				{
					game.level[1].collision.check[i] = 1;//collsion flag
					if(i==0)allTimes.timeReduced = 1;//hourglass scoring factor
					if(sfx.sCount)playSound(sfx.collect);//item collect sound
				}
			}
		}
	}
	
	//change position
	player->x += player->dx;
	player->y += player->dy;
}

void doScope()//scope move
{
	scope->dx = scope->dy = 0;

	if (app.keyboard[SDL_SCANCODE_UP])//go up
	{
		if(scope->y-scope->dy>=0) scope->dy = -SCOPE_SPEED;
		app.keyboard[SDL_SCANCODE_UP] = 0;
	}
	if (app.keyboard[SDL_SCANCODE_DOWN])//go down
	{
		if(scope->y+scope->dy+105<=SCREEN_HEIGHT) scope->dy = SCOPE_SPEED;
		app.keyboard[SDL_SCANCODE_DOWN] = 0;
	}
	if (app.keyboard[SDL_SCANCODE_LEFT])//go left
	{
		if(scope->x-scope->dx>=0) scope->dx = -SCOPE_SPEED;
		app.keyboard[SDL_SCANCODE_LEFT] = 0;
	}
	if (app.keyboard[SDL_SCANCODE_RIGHT])//go right
	{
		if(scope->x+scope->dx+105<=SCREEN_WIDTH) scope->dx = SCOPE_SPEED;
		app.keyboard[SDL_SCANCODE_RIGHT] = 0 ;
	}

	//change position
	scope->x += scope->dx;
	scope->y += scope->dy;
}

void doPlayer2()//level 2 rabbit movement
{
	player->dx = player->dy = 0;//initialize player position change

	if (app.keyboard[SDL_SCANCODE_UP])//go up
	{
		if(player->y-player->dy>=100) 
		{
			player->dy = -PLAYER_SPEED;
			player->up = 1 ;
		}
	}
	if (app.keyboard[SDL_SCANCODE_DOWN])//go down
	{
		if(player->y+player->dy+45<=SCREEN_HEIGHT-100) 
		{
			player->dy = PLAYER_SPEED;
			player->up = 0 ;
		}
	}
	if (app.keyboard[SDL_SCANCODE_LEFT])//go left
	{
		if(player->x-player->dx>=0) player->dx = -PLAYER_SPEED;
	}
	if (app.keyboard[SDL_SCANCODE_RIGHT])//go right
	{
		if(player->x+player->dx+45<=SCREEN_WIDTH) player->dx = PLAYER_SPEED;
	}

	//entity collision
	if(!game.level[3].collision.check[0])
	{
		if(((player->y+PLAYER_HEIGHT > NEW_HEIGHT(335) && player->y+PLAYER_HEIGHT < NEW_HEIGHT(400)) || (player->y > NEW_HEIGHT(335) && player->y < NEW_HEIGHT(400))) && ((player->x+PLAYER_WIDTH > NEW_WIDTH(217) && player->x+PLAYER_WIDTH < NEW_WIDTH(315)) || (player->x > NEW_WIDTH(217) && player->x < NEW_WIDTH(315))))
		{
			if(app.keyboard[SDL_SCANCODE_LSHIFT])
			{
				game.level[2].collision.check[0] = 1;//collided condition
				if(sfx.sCount)playSound(sfx.collect);//item collect sound
				game.level[2].completed=1;//level 2 complete condition
				SDL_StartTextInput();//player name input start
				game.enterName = 1;//name input page condition
			}
		}
	}
	
	//player's new coordinates
	player->x += player->dx;
	player->y += player->dy;
}


void doMazePlayer()//level 3 player movement
{
	player->dx = player->dy = 0;//initialize player position change

	int cnt1;

	if (app.keyboard[SDL_SCANCODE_UP])//go up
	{
		cnt1 = 0;
		//check if colliding with maze
		for(int i = 0; i < 12; i++){
			if(((player->y - MAZE_SPEED < maze[i].y1) && (player->y + PLAYER_HEIGHT - MAZE_SPEED > maze[i].y)) && ((player->x < maze[i].x1) && (player->x+PLAYER_WIDTH > maze[i].x))){
				cnt1 = 1;//collided with maze condition
			}
		}
		if(cnt1 == 0) 
		{
			player->dy = -MAZE_SPEED;//not collided with maze, thus, can go upwards
			player->up = 1 ;
		}
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])//go down
	{
		cnt1 = 0;
		//check if colliding with maze
		for(int i = 0; i < 12; i++){
			if(((player->y + PLAYER_HEIGHT+ MAZE_SPEED  > maze[i].y) && (player->y + PLAYER_HEIGHT< maze[i].y1)) && ((player->x < maze[i].x1) && (player->x+PLAYER_WIDTH > maze[i].x))){
				cnt1 = 1;//collided with maze condition
			}
		}
		if(cnt1 == 0) 
		{
			player->dy = MAZE_SPEED;//not collided with maze, thus, can go downwards
			player->up = 0 ;
		}
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])//go left
	{
		cnt1 = 0;
		//check if colliding with maze
		for(int i = 0; i < 12; i++){
			if(((player->x - MAZE_SPEED < maze[i].x1) && (player->x+PLAYER_WIDTH - MAZE_SPEED > maze[i].x)) && ((player->y < maze[i].y1) && (player->y+PLAYER_HEIGHT > maze[i].y))){
				cnt1 = 1;//collided with maze condition
			}
		}
		if(cnt1 == 0) player->dx = -MAZE_SPEED;//not collided with maze, thus, can go left
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])//go right
	{
		cnt1 = 0;
		//check if colliding with maze
		for(int i = 0; i < 12; i++){
			if(((player->x+PLAYER_WIDTH + MAZE_SPEED  > maze[i].x) && (player->x+PLAYER_WIDTH < maze[i].x1)) && ((player->y < maze[i].y1) && (player->y+PLAYER_HEIGHT > maze[i].y))){
				cnt1 = 1;//collided with maze condition
			}
		}
		if(cnt1 == 0) player->dx = MAZE_SPEED;//not collided with maze, thus, can go right
	}

	if((player->x + player->dx+PLAYER_WIDTH <= CHANGE_WIDTH(1012)) && (player->x+ player->dx >= CHANGE_WIDTH(290))) player->x += player->dx;//player is in the frame, so move
	
	if((player->y + player->dy+PLAYER_HEIGHT <= SCREEN_HEIGHT) && (player->y+ player->dy >= 0)) player->y += player->dy;//player is in the frame, so move

	//check if collision with demon
	for(int i = 0; i < 5; i++){
		if(((player->y+PLAYER_HEIGHT > demon[i].y && player->y+PLAYER_HEIGHT < demon[i].y+60) || (player->y > demon[i].y && player->y < demon[i].y+60)) && ((player->x+PLAYER_WIDTH > demon[i].x && player->x+PLAYER_WIDTH < demon[i].x+60) || (player->x > demon[i].x && player->x < demon[i].x+60))){
			game.level[3].collision.demon = 1;//collided with demon
		}
	}

	//check if collided with items of level 3
	for(int i = 0; i < 4; i++){
		if(!game.level[3].collision.check[1])//not collided with key yet
		{
			if(((player->y+PLAYER_HEIGHT > mazeThings[1].y && player->y+PLAYER_HEIGHT < mazeThings[1].y+25) || (player->y > mazeThings[1].y && player->y < mazeThings[1].y+25)) && ((player->x+PLAYER_WIDTH > mazeThings[1].x && player->x+PLAYER_WIDTH < mazeThings[1].x+25) || (player->x > mazeThings[1].x && player->x < mazeThings[1].x+25))){
				if(app.keyboard[SDL_SCANCODE_LSHIFT])//shift key pressed
				{
					game.level[3].collision.check[1] = 1;//collided with key
				}
			}
		}
		else//collided with key
		{
			if(!game.level[3].collision.check[0])//not collided with treasure yet
			{
				if(((player->y+PLAYER_HEIGHT > mazeThings[0].y && player->y+PLAYER_HEIGHT < mazeThings[0].y+25) || (player->y > mazeThings[0].y && player->y < mazeThings[0].y+25)) && ((player->x+PLAYER_WIDTH > mazeThings[0].x && player->x+PLAYER_WIDTH < mazeThings[0].x+25) || (player->x > mazeThings[0].x && player->x < mazeThings[0].x+25))){
					if(app.keyboard[SDL_SCANCODE_LSHIFT])//shift key pressed
					{
						game.level[3].collision.check[0] = 1;//collided with treasure
					}
				}
			}
			else//collided with treasure
			{
				if(!game.level[3].collision.check[2])//not collided with map yet
				{
					if(((player->y+PLAYER_HEIGHT > mazeThings[2].y && player->y+PLAYER_HEIGHT < mazeThings[2].y+25) || (player->y > mazeThings[2].y && player->y < mazeThings[2].y+25)) && ((player->x+PLAYER_WIDTH > mazeThings[2].x && player->x+PLAYER_WIDTH < mazeThings[2].x+25) || (player->x > mazeThings[2].x && player->x < mazeThings[2].x+25))){
						if(app.keyboard[SDL_SCANCODE_LSHIFT])//shift key pressed
						{
							game.level[3].collision.check[2] = 1;//collided with map
						}
					}
				}
				else//collided with map
				{
					if(((player->y+PLAYER_HEIGHT > 5 && player->y+PLAYER_HEIGHT < 30) || (player->y > 5 && player->y < 30)) && ((player->x+PLAYER_WIDTH > 290 && player->x+PLAYER_WIDTH < 330) || (player->x > 290 && player->x < 330))){
						if(app.keyboard[SDL_SCANCODE_LSHIFT])//shift key pressed
						{
							game.level[3].collision.check[3] = 1;//collided with exit
							game.level[3].completed = 1;//level completed
							SDL_StartTextInput();//get name condition

							game.enterName = 1;//name page
						}
					}
				}
			}
		}
	}
}
