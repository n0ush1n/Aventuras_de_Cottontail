#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

            case SDL_KEYDOWN://pressing key
				doKeyDown(&event.key);
				break;
			case SDL_KEYUP://not pressing key
				doKeyUp(&event.key);
				break;

			case SDL_MOUSEBUTTONDOWN://pressing mouse button
		        doMouseButtonDown(&event.button);
		        break;

	        case SDL_MOUSEBUTTONUP://not pressing mouse button
		        doMouseButtonUp(&event.button);
		        break;

			case SDL_TEXTINPUT://taking text input
		        doTextInput(event.text);
		        break;

			default:
				break;
		}
		SDL_GetMouseState(&app.mouse.x,&app.mouse.y);//get mouse coordinates
		//cout << app.mouse.x << " " << app.mouse.y << endl;
	}
}

void doKeyUp(SDL_KeyboardEvent *event)//key not pressed
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

void doKeyDown(SDL_KeyboardEvent *event)//key pressed
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

void doMouseButtonUp(SDL_MouseButtonEvent *event)//mouse not clicked
{
	app.mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent *event)//mouse clicked
{
	app.mouse.button[event->button] = 1;
}

void doTextInput(SDL_TextInputEvent event)//text input
{
	app.text = 1;
	app.inputText = event.text;
}