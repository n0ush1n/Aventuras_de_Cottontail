#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

#include "defs.hpp"

typedef struct Mouse1
{
	int x;//mouse x coordinate
	int y;//mouse y coorinate
    int button[MAX_MOUSE_BUTTONS]; //mouse button pressed or not
} Mouse;

typedef struct {
	void (*draw)(void);
	void (*logic)(void);
	void (*level[4])();
} Delegate;

typedef struct 
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	Mouse mouse;
	std::string inputText;
	std::string typeText;
	int text;
} App;

typedef struct SFX1
{
	Mix_Chunk *click;
	Mix_Chunk *scream;
	Mix_Chunk *levelComplete;
	Mix_Chunk *gunshot;
	Mix_Chunk *gameover;
    Mix_Music *music;
	Mix_Music *roadmusic;
	Mix_Music *jungle;
	Mix_Music *maze;
	Mix_Chunk *collect;
	int sCount = 1;//sound on
	int mCount = 1;//music on
	int sVolume = 48;//sound on 3rd volume level
	int mVolume = 48;//music on 3rd volume level
	int mVolCnt = 3;//3rd image for music
	int sVolCnt = 3;//3rd image for sound
} SFX;

typedef struct TIME1
{
	int Check;
	int timerStart;//game start condition
	int pausedOn;//game pause time
	int timeReduced;//hourglass collected score factor
	int t = 500;//hourglass movement timer
	int t2 = 1250;//map for level 1 movement timer
	Uint32 startTime = 0;//game starting time
} TIME;

typedef struct Collision1
{
	int Car;//collision with car
	int check[4];//game level item collision
	int dead[5];//junglee collision
	int bullet;//number of bullet used
	int demon;//demon collision
} Collision;

typedef struct LEVELON
{
	int completed;//level completed = 1 or playing = 0 else game over
	int paused;//gaem paused = 1, play = 0
	int story;//story = 2, objetive = 1 else game play
	Collision collision;
} LEVEL;

typedef struct GAME1
{
	LEVEL level[MAX_LEVELS]; 
	int playing;//playing = 1 or menu/saving = 0 
	int mainMenu = 1;//mainmenu = 1 , instruction = 2 , highscore = 3 , settings = 4
	int instructions = 1 ;//instructions = 1, game controls = 0
	int levelNow;//now in which level
	int save;//save option = 1, not in save option = 0
	int enterName;//1 = enter name, 2 = loadscore, else = level completed page
	int finished;
	int leaderBoard;//1 = level1 leaders, 2= level2 scores, 3 = level3 scores
} GAME;

typedef struct Gfont1
{
	TTF_Font *f1;
	TTF_Font *f2;
	TTF_Font *f3;
	TTF_Font *f4;	
	SDL_Color textColor;	
	std::stringstream timeText;
} Gfont;

struct Entity {//player & scope
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	SDL_Texture *texture;
	struct Entity *next ;
	int up = 1;
};

typedef struct {//car & level 1 items
	int a;//direction (car)
	int x;
	int y;
	int speed;
} Enemy;

typedef struct {//level2 junglee
	int dir;//direction
	int x;
	int y;
	int speed;
	int x1;//leftmost x
	int x2;//rightmost x
} Junglee;

typedef struct {//demon of level 3
	int x;
	int y;
	int x1;//leftmost x
	int y1;//topmost y
	int speed;
	int dir;//direction
	int x2;//rightmost x
	int y2;//bottom y
} Demon;

typedef struct {//maze of level 3
	int x;//leftmost
	int y;//topmost
	int x1;//rightmost
	int y1;//bottom
}Maze;

typedef struct {//level3 items
	int weapon;
	int potion;
	int treasure;
	int mazemap;
}Found;

typedef struct {
	int recent;//current score while playing a level
	int score;
	int leader;//player rank in leaderboard
	int level[MAX_LEVELS];//score for different levels
	int ex;//score of previous level
	int reduce[MAX_LEVELS];//score factor
	int bullet;
} Score;

typedef struct {
	char name[12];//laderboard player name
	int score;//leaderboard player score
} Highscore;

App app ;
struct Entity *player = NULL ;
struct Entity *scope = NULL ;
SFX sfx ;
Enemy enemy[2];
Gfont gfont;
GAME game;
TIME allTimes;
Score score;
Highscore highscore[8];
Found found;
Maze mazeThings[4] = {{726,611,3,4},{935,877,5,6},{298,372,6,4},{NEW_WIDTH(10),NEW_HEIGHT(130),5,6}};//maze items position

void level1Start()//initializing level1
{
	//player position initialize
	player->x = DEFAULT_x;
	player->y = DEFAULT_y;
	player->up = 1;
	
	//car position initialize
	Enemy car[5] = {{1,NEW_WIDTH(-100),NEW_HEIGHT(560),CAR0_SPEED},{-1,NEW_WIDTH(600),NEW_HEIGHT(440),CAR1_SPEED},{1,NEW_WIDTH(-100),NEW_HEIGHT(320),CAR2_SPEED},{-1,NEW_WIDTH(600),NEW_HEIGHT(200),CAR3_SPEED},{1,NEW_WIDTH(-100),NEW_HEIGHT(80),CAR4_SPEED}} ;
	game.levelNow = 1;//current level
	memset(game.level , 0, sizeof(game.level)); 
	game.playing = 1;//playing
	game.mainMenu = 0;//not in menu
	
	allTimes.timerStart = 0;//countdown start
	allTimes.pausedOn=0;//not paused
	allTimes.timeReduced=0;//hourglass not collected
	allTimes.t = 500;//hourglass timer
	allTimes.t2 = 1250;//map timer
	allTimes.startTime = SDL_GetTicks();//game start time

	score.level[1] = 300;//level1 score initialize
	score.reduce[1] = 10;//level 1 scoring factor
	score.ex = 0 ;//previous level score
}

void level2Start()//initializing level2
{
	//scope position initialize
	scope->x = SCREEN_WIDTH/2 - 105;
	scope->y = SCREEN_HEIGHT/2 -30;
	player->up = 1;

	//junglee position
	Junglee junglee[5] = {{1,NEW_WIDTH(230),NEW_HEIGHT(200),JUNGLEE1_SPEED,NEW_WIDTH(0),NEW_WIDTH(227)},{-1,NEW_WIDTH(230),NEW_HEIGHT(240),JUNGLEE2_SPEED,NEW_WIDTH(175),NEW_WIDTH(375)},{1,NEW_WIDTH(100),NEW_HEIGHT(370),JUNGLEE3_SPEED,NEW_WIDTH(0),NEW_WIDTH(275)},{-1,NEW_WIDTH(340),NEW_HEIGHT(376),JUNGLEE4_SPEED,NEW_WIDTH(265),NEW_WIDTH(480)},{1,NEW_WIDTH(400),NEW_HEIGHT(290),JUNGLEE5_SPEED,NEW_WIDTH(385),NEW_WIDTH(540)}} ;
	//wall hole positions
	Maze window[5] = {{NEW_WIDTH(80),NEW_HEIGHT(197), NEW_WIDTH(167),NEW_HEIGHT(285)}, {NEW_WIDTH(281),NEW_HEIGHT(231),NEW_WIDTH(363),NEW_HEIGHT(321)}, {NEW_WIDTH(81),NEW_HEIGHT(360), NEW_WIDTH(232),NEW_HEIGHT(450)} , {NEW_WIDTH(333),NEW_HEIGHT(394), NEW_WIDTH(400),NEW_HEIGHT(463)}, {NEW_WIDTH(422),NEW_HEIGHT(285), NEW_WIDTH(512),NEW_HEIGHT(375)}};
	game.levelNow = 2;//current levels
	memset(game.level , 0, sizeof(game.level)); 
	game.playing = 1;//playing
	game.mainMenu = 0;//not in menu
	
	allTimes.timerStart = 0;//countdown start
	allTimes.pausedOn=0;//not paused
	allTimes.timeReduced=0;//hourglass not collected
	allTimes.startTime = SDL_GetTicks();//game start time

	score.level[2] = 600;//level 2 score initialize
	score.reduce[2] = 2;//level 2 scoring factor
}

void level3Start()//initializing level3
{
	//level 3 player initialize
	player->x = MAZE_x;
	player->y = MAZE_y;
	player->up = 1;

	//maze positions
	Maze maze[12] = {{NEW_WIDTH(160),NEW_HEIGHT(67), NEW_WIDTH(298),NEW_HEIGHT(117)},{NEW_WIDTH(346),NEW_HEIGHT(64), NEW_WIDTH(377),NEW_HEIGHT(233)}, {NEW_WIDTH(350),NEW_HEIGHT(233), NEW_WIDTH(440),NEW_HEIGHT(287)}, {630,NEW_HEIGHT(189), 695,NEW_HEIGHT(260)}, {NEW_WIDTH(0),NEW_HEIGHT(197), 490,NEW_HEIGHT(250)}, {390,445, 687,519}, {NEW_WIDTH(273),NEW_HEIGHT(381), 910,582}, {NEW_WIDTH(350),NEW_HEIGHT(383), 910,NEW_HEIGHT(640)}, {NEW_WIDTH(236),NEW_HEIGHT(335), NEW_WIDTH(258),NEW_HEIGHT(507)}, {NEW_WIDTH(172),NEW_HEIGHT(455),698,NEW_HEIGHT(507)}, {NEW_WIDTH(172),NEW_HEIGHT(580), NEW_WIDTH(200),NEW_HEIGHT(646)}, {NEW_WIDTH(240),NEW_HEIGHT(585), NEW_WIDTH(315),NEW_HEIGHT(640)}} ;
	//demons position
	Demon demon[5] = {{NEW_WIDTH(200),NEW_HEIGHT(134),NEW_WIDTH(170),NEW_HEIGHT(134),10,2,NEW_WIDTH(225),NEW_HEIGHT(258)},{NEW_WIDTH(335),NEW_HEIGHT(12),NEW_WIDTH(310),NEW_HEIGHT(12),10,2,NEW_WIDTH(390),NEW_HEIGHT(308)},{NEW_WIDTH(190),NEW_HEIGHT(403),NEW_WIDTH(125),NEW_HEIGHT(400),8,1,NEW_WIDTH(220),NEW_HEIGHT(515)},{925,NEW_HEIGHT(389),925,NEW_HEIGHT(389),15,-1,925,NEW_HEIGHT(590)},{NEW_WIDTH(203),NEW_HEIGHT(533),NEW_WIDTH(203),NEW_HEIGHT(533),7,1,NEW_WIDTH(315),NEW_HEIGHT(649)}};
	game.levelNow = 3;//current level
	memset(game.level , 0, sizeof(game.level)); 
	game.playing = 1;//playing
	game.mainMenu = 0;//not in menu
	
	allTimes.timerStart = 0;//countdown start
	allTimes.pausedOn=0;//not paused
	allTimes.timeReduced=0;//hourglass not collected
	allTimes.startTime = SDL_GetTicks();//game start time

	score.level[3] = 900;//level 3 score initialize
	score.reduce[3] = 3;//level 3 scoring factor
}

Enemy car[5] = {{1,NEW_WIDTH(-100),NEW_HEIGHT(560),CAR0_SPEED},{-1,NEW_WIDTH(600),NEW_HEIGHT(440),CAR1_SPEED},{1,NEW_WIDTH(-100),NEW_HEIGHT(320),CAR2_SPEED},{-1,NEW_WIDTH(600),NEW_HEIGHT(200),CAR3_SPEED},{1,NEW_WIDTH(-100),NEW_HEIGHT(80),CAR4_SPEED}} ;
Maze maze[12] = {{NEW_WIDTH(160),NEW_HEIGHT(67), NEW_WIDTH(298),NEW_HEIGHT(117)},{NEW_WIDTH(346),NEW_HEIGHT(64), NEW_WIDTH(377),NEW_HEIGHT(233)}, {NEW_WIDTH(350),NEW_HEIGHT(233), NEW_WIDTH(440),NEW_HEIGHT(287)}, {630,NEW_HEIGHT(189), 695,NEW_HEIGHT(260)}, {NEW_WIDTH(0),NEW_HEIGHT(197), 490,NEW_HEIGHT(250)}, {390,445, 687,519}, {NEW_WIDTH(273),NEW_HEIGHT(381), 910,582}, {NEW_WIDTH(350),NEW_HEIGHT(383), 910,NEW_HEIGHT(640)}, {NEW_WIDTH(236),NEW_HEIGHT(335), NEW_WIDTH(258),NEW_HEIGHT(507)}, {NEW_WIDTH(172),NEW_HEIGHT(455),698,NEW_HEIGHT(507)}, {NEW_WIDTH(172),NEW_HEIGHT(580), NEW_WIDTH(200),NEW_HEIGHT(646)}, {NEW_WIDTH(240),NEW_HEIGHT(585), NEW_WIDTH(315),NEW_HEIGHT(640)}} ;
Demon demon[5] = {{NEW_WIDTH(200),NEW_HEIGHT(134),NEW_WIDTH(170),NEW_HEIGHT(134),10,2,NEW_WIDTH(225),NEW_HEIGHT(258)},{NEW_WIDTH(335),NEW_HEIGHT(12),NEW_WIDTH(310),NEW_HEIGHT(12),10,2,NEW_WIDTH(390),NEW_HEIGHT(308)},{NEW_WIDTH(190),NEW_HEIGHT(403),NEW_WIDTH(125),NEW_HEIGHT(400),8,1,NEW_WIDTH(220),NEW_HEIGHT(515)},{925,NEW_HEIGHT(389),925,NEW_HEIGHT(389),15,-1,925,NEW_HEIGHT(590)},{NEW_WIDTH(203),NEW_HEIGHT(533),NEW_WIDTH(203),NEW_HEIGHT(533),7,1,NEW_WIDTH(315),NEW_HEIGHT(649)}};
Junglee junglee[5] = {{1,NEW_WIDTH(230),NEW_HEIGHT(200),JUNGLEE1_SPEED,NEW_WIDTH(0),NEW_WIDTH(220)},{-1,NEW_WIDTH(230),NEW_HEIGHT(240),JUNGLEE2_SPEED,NEW_WIDTH(175),NEW_WIDTH(375)},{1,NEW_WIDTH(100),NEW_HEIGHT(370),JUNGLEE3_SPEED,NEW_WIDTH(0),NEW_WIDTH(265)},{-1,NEW_WIDTH(340),NEW_HEIGHT(376),JUNGLEE4_SPEED,NEW_WIDTH(265),NEW_WIDTH(480)},{1,NEW_WIDTH(400),NEW_HEIGHT(290),JUNGLEE5_SPEED,NEW_WIDTH(385),NEW_WIDTH(540)}} ;
Maze window[5] = {{NEW_WIDTH(80),NEW_HEIGHT(197), NEW_WIDTH(167),NEW_HEIGHT(285)}, {NEW_WIDTH(281),NEW_HEIGHT(231),NEW_WIDTH(363),NEW_HEIGHT(321)}, {NEW_WIDTH(81),NEW_HEIGHT(360), NEW_WIDTH(232),NEW_HEIGHT(450)} , {NEW_WIDTH(333),NEW_HEIGHT(394), NEW_WIDTH(400),NEW_HEIGHT(463)}, {NEW_WIDTH(422),NEW_HEIGHT(285), NEW_WIDTH(512),NEW_HEIGHT(375)}};
	