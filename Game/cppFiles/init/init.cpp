#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

void initSDL(void)
{
	memset(&app, 0, sizeof(App));

    SDL_ShowCursor(0);
    
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)//initializing video
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)//initializing image
	{
		printf("Couldn't initialize image: %s\n", SDL_GetError());
		exit(1);
	}
	 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )//initializing mixer
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(1) ;
    }
	if( TTF_Init() < 0)//initializing ttf
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		exit(1) ;
	}
    
	app.window = SDL_CreateWindow("AVENTURAS DE COTTONTAIL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);//create window

	if (!app.window)//window not created
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);//render

	if (!app.renderer)//not rendered
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	initStage();//stage.cpp
}

void initSounds(void)//loading sounds and musics
{
	loadSounds();//load sounds
	loadmusic();//load musics
	//playMusic();
}

void initFont()
{
	gfont.f1 = TTF_OpenFont( "res/fonts/ArialCEBold.ttf", 40 );
	gfont.f2 = TTF_OpenFont( "res/fonts/ERASBD.TTF", 70 );
    gfont.f3 = TTF_OpenFont( "res/fonts/ArialCEBold.ttf", 50 );
    gfont.f4 = TTF_OpenFont( "res/fonts/Eras Medium ITC.ttf", 50 );

	gfont.textColor = { 0, 0, 0, 255 };
}