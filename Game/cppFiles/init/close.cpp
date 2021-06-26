#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

void close()
{
	gTimeTextTexture.free();
	//Free global font
	TTF_CloseFont( gfont.f1 );
	gfont.f1 = NULL;
	TTF_CloseFont( gfont.f2 );
	gfont.f2 = NULL;
	TTF_CloseFont( gfont.f3 );
	gfont.f3 = NULL;
	TTF_CloseFont( gfont.f4 );
	gfont.f4 = NULL;

	//Destroy window	
	SDL_DestroyRenderer( app.renderer );
	SDL_DestroyWindow( app.window );
	app.window = NULL;
	app.renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}