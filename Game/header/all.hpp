#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>

#include "struct.hpp"
#include "defs.hpp"
#include "texture.hpp"

using namespace std ;

//init
void initSDL(void) ;
void initSounds(void);
void initFont(void);

//sfx
void loadSounds(void);
void loadMusic(void);
void playSound(Mix_Chunk *x);
void playMusic(void);

//input
void doInput(void) ;
void doKeyDown(SDL_KeyboardEvent *event) ;
void doKeyUp(SDL_KeyboardEvent *event) ;
void doMouseButtonDown(SDL_MouseButtonEvent *event);
void doMouseButtonUp(SDL_MouseButtonEvent *event);
void doTextInput(SDL_TextInputEvent event);

//draw
void prepareScene(void) ;
void presentScene(void) ;
static void drawDemon(void);
void loadEverythingYouHaveGot();
static void draw(void) ;
static void drawItems(void) ;
void drawCursor() ;
void drawScope();
void drawJunglee();
void drawCar();
static void drawPlayer();
void drawMazeThings();

//stage
static void logic(void) ; 
void doMap();
void doHourglass();
void initStage(void) ;
static void initPlayer() ;
static void initScope() ;

//time
void countdown(void);
void timer();
void bullets();
static void capFrameRate(long *then, float *remainder);

//player
void doPlayer() ;
void doPlayer2(void) ;
void doScope();
void doMazePlayer();

//levelcompleted
void levelCompleted(void);
void Naming();

//gamepaused
void GamePaused();
void saveOrNot();
void saveTheGame();

//gameover
void Gameover(void);

//enemies
void doCar() ;
void doJunglee();
void doDemon();

//menu
void menu(void);

//buttons
void button_functions(int y);

//leaderboard button
void LeaderboardMenu(void);
void loadscore();
void loadLeaderboardScores();

//instructions
void instructions(void);

//music&sound
void soundMusic();

//close
void close();

void enterText(std::string inputText);

//play
void playButton();
void loadSavedGame();