#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

void doCar()// level 1 car movement
{
	for(int i = 0 ;i < 5 ; i++)
	{
		if(car[i].a==1)//left to right
		{
			if(car[i].x<SCREEN_WIDTH)// not reached the border
			{
				car[i].x += car[i].speed ;// go right
			}
			else
			{
				car[i].x = 0 ;//start again from the left border
			}	
		}
		else if(car[i].a ==-1)
		{
			if(car[i].x>0)//not reached left border
			{
				car[i].x -= car[i].speed ;//go left
			}
			else
			{
				car[i].x = SCREEN_WIDTH;//start again from the right border
			}
		}
	}
}

void doJunglee()// level 2 enemies movement
{
    for(int i=0;i<5;i++)
    {
    	if(junglee[i].dir==1)//go right
        {
            if(junglee[i].x<junglee[i].x2)//if not reached right 
            {
                junglee[i].x += junglee[i].speed ; //go right
            }
            else
            {
                junglee[i].dir = -1 ;// start going left
            }
        }
        else if(junglee[i].dir==-1)//go left
        {
            if(junglee[i].x>junglee[i].x1)//not reached left
            {
                junglee[i].x -= junglee[i].speed ; //go left
            }
            else
            {
              junglee[i].dir = 1 ;//start going right
            }
        }
	}
}

void doDemon()//level 3 enemies
{
    for(int i=0;i<5;i++)
    {
        if(i==2)//enemy at the bottom left corner
        {
            if(demon[i].dir==1)//go up
            {
                 if(demon[i].y>demon[i].y1)//not reached top
                 {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                     demon[i].dir = 2 ;//go right
                }
            }
            else if(demon[i].dir==2)//go right
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
            else
                {
                    demon[i].dir = -2 ;//go left
                }
            }
            else if(demon[i].dir==-2)//go left
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -1 ;//go down
                }
            }
            else if(demon[i].dir==-1)//go down
            {
                if(demon[i].y<demon[i].y2)//not reached bottom
                {
                    demon[i].y += demon[i].speed ; //kep going
                }
                else
                {
                    demon[i].dir = 3 ;//go right again
                }
            }
            else if(demon[i].dir==3)//go right again
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -3 ;//go left
                }
            }
            else if(demon[i].dir==-3)//go left
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 1 ;//go up
                }
            }
        }
        else if(i==0 )//enemy at the top left corner
        {
            if(demon[i].dir==1)//go up
            {
                if(demon[i].y>demon[i].y1)//not reached top
                {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -2 ; //go left
                }
            }
            else if(demon[i].dir==-1)//go down
            {
                if(demon[i].y<demon[i].y2)//not reached bottom
                {
                    demon[i].y += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -3 ;//go left again
                }
            }
            else if(demon[i].dir==-2)//go left
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 3 ;//go right again
                }
            }
            else if(demon[i].dir==2)//go right
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 1 ;//go down
                }
            }
            else if(demon[i].dir==3)//go right again
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -1 ;//go down
                }
            }
            else if(demon[i].dir==-3)//go left again
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; // keep going
                }
                else
                {
                    demon[i].dir = 2 ;// go right
                }
            }
        }
        else if(i==3 )//enemy at the bottom right 
        {
            if(demon[i].dir==1)//go down
            {
                if(demon[i].y>demon[i].y1)//not reached bottom
                {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -1 ;//go up
                }
            }
            else if(demon[i].dir==-1)//go up
            {
                if(demon[i].y<demon[i].y2)//not reached top
                {
                    demon[i].y += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 1 ;//go down
                }
            }
        }
         else if(i==4 )
        {
            if(demon[i].dir==1)//go down
            {
                if(demon[i].y>demon[i].y1)//not reached bottom
                {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -1 ;//go up
                }
            }
            else if(demon[i].dir==-1)//go up
            {
                if(demon[i].y<demon[i].y2)//not reached top
                {
                    demon[i].y += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 2 ;//go right
                }
            }
            else if(demon[i].dir==-2)//go left
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; // keep going
                }
                else
                {
                    demon[i].dir = 1 ;//go up
                }
            }
            else if(demon[i].dir==2)//go right
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 3 ;//go up again
                }
            }
            else if(demon[i].dir==3)//go up again
            {
                if(demon[i].y>demon[i].y1)//not reached top
                {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -3 ;//go down again
                }
            }
            else if(demon[i].dir==-3)//go down again
            {
                if(demon[i].y<demon[i].y2)//not reached bottom
                {
                    demon[i].y += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -2 ;//go left
                }
            }
        }
        else 
        {
            if(demon[i].dir==1) //go up
            {
                if(demon[i].y>demon[i].y1)//not reached top
                {
                    demon[i].y -= demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -1 ;//go down
                }
            }
            else if(demon[i].dir==-1)//go down
            {
                if(demon[i].y<demon[i].y2)//not reached bottom
                {
                    demon[i].y += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = 2 ;//go right
                }
            }
            else if(demon[i].dir==2)//go right
            {
                if(demon[i].x<demon[i].x2)//not reached right
                {
                    demon[i].x += demon[i].speed ; //keep going
                }
                else
                {
                    demon[i].dir = -2 ;//go left
                }
            }
            else if(demon[i].dir==-2)//go left
            {
                if(demon[i].x>demon[i].x1)//not reached left
                {
                    demon[i].x -= demon[i].speed ; //keep going
                }
                else
                {
                     demon[i].dir = 1 ;//go up
                }
            }
        }
	}	
}