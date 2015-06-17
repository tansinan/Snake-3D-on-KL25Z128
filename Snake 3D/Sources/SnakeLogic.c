/*
 * Snake.c
 *
 *  Created on: Jun 4, 2015
 *      Author: tansinan
 */

#include "Types.h"
#include "OLEDFB3D.h"
#include "SnakeLogic.h"
#include "Timer.h"
#include "Button.h"

#define STATE_SPLASH 0
#define STATE_GAME 1
#define STATE_GAMEOVER 2

App Snake3D_theApp;

static int state = STATE_SPLASH;

const uint8 MAP_NORMAL = 0;
const uint8 MAP_FOOD = 1;
const uint8 MAP_WALL_HARD = 3;
const uint8 MAP_WALL_SOFT = 4;

const uint8 SNAKE_DIRECTION_UP = 0;
const uint8 SNAKE_DIRECTION_DOWN = 1;
const uint8 SNAKE_DIRECTION_LEFT = 2;
const uint8 SNAKE_DIRECTION_RIGHT = 3;

static uint8 animationTimerId;

static uint16 score = 0;

static uint16 animationCounter;

static void animationTimerHandler();

static void drawTerrain();
static void drawSnake();
void Snake3D_init();
static void Snake_init();
static void paintHandler();
static void eventHandler(int event, int data);
static void setState(int _state);

struct Snake_Game
{
	uint8 map[20][20];
	//[0] => head ||  [1] => body closest to head;
	uint8 snakePositions[25][2];
	uint8 snakeLength;
} snakeGame;

static int8 lastPressedKey = -1;

static uint8 snakeDirection;

//获取 (x2,y2) 相对于 (x1,y1)的相对位置关系
static int relativePosition(int x1, int y1, int x2, int y2)
{
	if(x1 == x2)
	{
		if(y2 > y1) return SNAKE_DIRECTION_DOWN;
		if(y2 < y1) return SNAKE_DIRECTION_UP;
	}
	else if(y1 ==y2)
	{
		if(x2 > x1) return SNAKE_DIRECTION_RIGHT;
		if(x2 < x1) return SNAKE_DIRECTION_LEFT;
	}
	return -1;
}

void Snake3D_init()
{
	App_create(&Snake3D_theApp, paintHandler, eventHandler);
}

static void Snake_init()
{
	//初始化地图
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(i==0||i==19||j==0||j==19)
			{
				snakeGame.map[i][j] = MAP_WALL_HARD;
			}
			else
			{
				int rnd = rand();
				if(rnd%10==0 && i!=7) snakeGame.map[i][j] = MAP_WALL_HARD;
				else if(rnd%10 == 1 && i!=7) snakeGame.map[i][j] = MAP_FOOD;
				else snakeGame.map[i][j] = MAP_NORMAL;
			}
		}
	}
	for(int i=0;i<3;i++)
	{
		snakeGame.snakePositions[i][0] = 7;
		snakeGame.snakePositions[i][1] = 7 + i;
	}
	snakeGame.snakeLength = 3;
}

static void drawTerrain()
{
	//绘制背景的地形图。需要注意的是x方向的中轴对应x=0
	//y 为常量，-0.5
	//z只能为负。
	//目前规划的绘制区域大小为7*7
	
	float centerX = snakeGame.snakePositions[0][0];
	float centerY = snakeGame.snakePositions[0][1];
	
	
	if(snakeDirection == SNAKE_DIRECTION_UP)
	{
		centerY +=1;
		centerY -= animationCounter /100.0;
	}
	else if(snakeDirection == SNAKE_DIRECTION_DOWN)
	{
		centerY -=1;
		centerY += animationCounter /100.0;
	}
	else if(snakeDirection == SNAKE_DIRECTION_LEFT)
	{
		centerX +=1;
		centerX -= animationCounter /100.0;
	}
	else if(snakeDirection == SNAKE_DIRECTION_RIGHT)
	{
		centerX -= 1;
		centerX += animationCounter /100.0;
	}
	
	int paintRegionX1 = centerX - 4;
	int paintRegionY1 = centerY - 4;
	int paintRegionX2 = centerX + 4;
	int paintRegionY2 = centerY + 4;
	if(paintRegionX1 < 0) paintRegionX1 = 0;
	if(paintRegionX2 > 19) paintRegionX2 = 19;
	if(paintRegionY1 < 0) paintRegionY1 = 0;
	if(paintRegionY2 > 19) paintRegionY2 = 19;
	
	for(int i=paintRegionX1;i<=paintRegionX2+1;i++)
	{
		Vec3D point1;
		Vec3D point2;
		point1[1] = point2[1] = -0.5;
		point1[0] = point2[0] = (i - centerX)/2.0 - 0.25;
		point1[2] = (paintRegionY1 - centerY)/2.0 - 1.5;
		point2[2] = (paintRegionY2 + 1 - centerY)/2.0 - 1.5;
		OLEDFB3D_drawLine3D(point1, point2);
	}
	
	for(int i=paintRegionY1;i<=paintRegionY2+1;i++)
	{
		Vec3D point1;
		Vec3D point2;
		point1[1] = point2[1] = -0.5;
		point1[2] = point2[2] = (i - centerY)/2.0 - 1.5;
		point1[0] = (paintRegionX1 - centerX)/2.0 - 0.25;
		point2[0] = (paintRegionX2 + 1 - centerX)/2.0 - 0.25;
		OLEDFB3D_drawLine3D(point1, point2);
	}
	
	for(int i=paintRegionX1;i<=paintRegionX2;i++)
	{
		for(int j=paintRegionY1;j<=paintRegionY2;j++)
		{
			if(snakeGame.map[i][j]==MAP_WALL_HARD)
			{
				Quad3D quad;
				Vec3D temp;
				for(int i=0;i<4;i++) quad[i][1] = 0;
				quad[0][0] = (i - centerX)/2.0 - 0.25;
				quad[2][0] = (i - centerX)/2.0 + 0.25;
				quad[0][2] = (j - centerY)/2.0 - 1.5;
				quad[2][2] = (j + 1 - centerY)/2.0 - 1.5;
				quad[1][0] = quad[0][0];
				quad[1][2] = quad[2][2];
				quad[3][0] = quad[2][0];
				quad[3][2] = quad[0][2];
				OLEDFB3D_drawQuad3D(quad);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<3;j++)
					{
						temp[j] = quad[i][j];
					}
					temp[1] = -0.5; 
					OLEDFB3D_drawLine3D(quad[i],temp);
				}
			}
			else if (snakeGame.map[i][j] == MAP_FOOD)
			{
				Quad3D quad;
				for(int i=0;i<4;i++) quad[i][1] = -0.5;
				quad[0][0] = (i - centerX)/2.0 - 0.25;
				quad[0][2] = (j - centerY + 0.5)/2.0 - 1.5;
				quad[1][0] = (i - centerX)/2.0;
				quad[1][2] = (j + 1 - centerY)/2.0 - 1.5;
				quad[2][0] = (i - centerX)/2.0 + 0.25;
				quad[2][2] = (j + 0.5 - centerY)/2.0 - 1.5;
				quad[3][0] = (i - centerX)/2.0;
				quad[3][2] = (j - centerY)/2.0 - 1.5;
				OLEDFB3D_drawQuad3D(quad);
			}
		}
	}
}

static void drawSnake()
{
	const float yLow = -0.5;
	const float yHigh = -0.25;
    Vec3D lastPoint[3];
    Vec3D currentPoint[3];
    
	float relativeX,relativeY;
    for(int i=0;i<= snakeGame.snakeLength;i++)
    {
    	if( i != snakeGame.snakeLength)
    	{
    		relativeX = snakeGame.snakePositions[i][0] - snakeGame.snakePositions[0][0];
    		relativeY = snakeGame.snakePositions[i][1] - snakeGame.snakePositions[0][1];
    	}
    	if(snakeDirection == SNAKE_DIRECTION_UP)
    	{
    		relativeY -= 1;
    		relativeY += animationCounter /100.0;
    	}
    	else if(snakeDirection == SNAKE_DIRECTION_DOWN)
    	{
    		relativeY +=1;
    		relativeY -= animationCounter /100.0;
    	}
    	else if(snakeDirection == SNAKE_DIRECTION_LEFT)
    	{
    		relativeX -= 1;
    		relativeX += animationCounter /100.0;
    	}
    	else if(snakeDirection == SNAKE_DIRECTION_RIGHT)
    	{
    		relativeX += 1;
    		relativeX -= animationCounter /100.0;
    	}
		int relPos = i > 0 ? relativePosition(snakeGame.snakePositions[i-1][0],
				snakeGame.snakePositions[i-1][1],
				snakeGame.snakePositions[i][0],
				snakeGame.snakePositions[i][1]) : -1;
    	if( i == 0 )
    	{
        	lastPoint[0][0] = 0.5 * relativeX;
        	lastPoint[0][1] = yLow;
        	lastPoint[0][2] = 0.5*relativeY - 1.25;
        	continue;
    	}
    	else if (i == snakeGame.snakeLength)
    	{
    		currentPoint[0][0] = relativeX*0.5;
    		currentPoint[0][1] = yLow;
    		currentPoint[0][2] = 0.5*relativeY - 1.25;
    		for(int i=0;i<3;i++)
    		{
    			OLEDFB3D_drawLine3D(currentPoint[0],lastPoint[i]);
    		}
    	}
    	else
    	{
			currentPoint[0][1] = yLow;
			currentPoint[1][1] = yLow;
			currentPoint[2][1] = yHigh;
    		if(relPos == SNAKE_DIRECTION_DOWN)
    		{
				currentPoint[0][0] = relativeX*0.5-0.2;
				currentPoint[0][2] = 0.5*relativeY - 1.5;
				currentPoint[1][0] = relativeX*0.5+0.2;
				currentPoint[1][2] = 0.5*relativeY - 1.5;
				currentPoint[2][0] = relativeX*0.5;
				currentPoint[2][2] = 0.5*relativeY - 1.5;
    		}
    		else if(relPos == SNAKE_DIRECTION_UP)
    		{
				currentPoint[1][0] = relativeX*0.5-0.2;
				currentPoint[1][2] = 0.5*(relativeY + 1) - 1.5;
				currentPoint[0][0] = relativeX*0.5+0.2;
				currentPoint[0][2] = 0.5*(relativeY + 1) - 1.5;
				currentPoint[2][0] = relativeX*0.5;
				currentPoint[2][2] = 0.5*(relativeY + 1) - 1.5;
    		}
    		else if(relPos == SNAKE_DIRECTION_LEFT)
    		{
				currentPoint[0][0] = relativeX*0.5 + 0.25;
				currentPoint[0][2] = 0.5*(relativeY + 1) - 1.75 - 0.2;
				currentPoint[1][0] = relativeX*0.5 + 0.25;
				currentPoint[1][2] = 0.5*(relativeY + 1) - 1.75 + 0.2;
				currentPoint[2][0] = relativeX*0.5 + 0.25;
				currentPoint[2][2] = 0.5*(relativeY + 1) - 1.75;
    		}
    		else if(relPos == SNAKE_DIRECTION_RIGHT)
    		{
				currentPoint[0][0] = relativeX*0.5 - 0.25;
				currentPoint[0][2] = 0.5*(relativeY + 1) - 1.75 + 0.2;
				currentPoint[1][0] = relativeX*0.5 - 0.25;
				currentPoint[1][2] = 0.5*(relativeY + 1) - 1.75 - 0.2;
				currentPoint[2][0] = relativeX*0.5 - 0.25;
				currentPoint[2][2] = 0.5*(relativeY + 1) - 1.75;
    		}
    		if(i==1)
    		{
        		for(int i=0;i<3;i++)
        		{
        			OLEDFB3D_drawLine3D(lastPoint[0],currentPoint[i]);
        		}
    		}
    		else
    		{
				for(int i=0;i<3;i++)
				{
					OLEDFB3D_drawLine3D(lastPoint[i],currentPoint[i]);
				}
    		}
    		for(int i=0;i<3;i++)
    		{
    			for(int k=0;k<i;k++)
    			{
    				OLEDFB3D_drawLine3D(currentPoint[i],currentPoint[k]);
    			}
    		}
    	}
		for(int i=0;i<3;i++)
			for(int k=0;k<3;k++)
				lastPoint[i][k] = currentPoint[i][k];
    }
}

static void paintHandler()
{	
	switch(state)
	{
	case STATE_SPLASH:
		OLEDFB_drawTextEx(5,5,24,24, "Snake");
		OLEDFB_drawTextEx(100,29,12,12, "3D");
		OLEDFB_drawTextEx(0,45,8,8, "ANYKEY->CONTINUE");
		break;
	case STATE_GAME:
		drawTerrain();
		drawSnake();
		break;
	case STATE_GAMEOVER:
		{
			char temp[20];
			sprintf(temp,"Score:%d",score);
			OLEDFB_drawTextEx(5,5,12,12, "GameOver");
			for(int i=0;i<8;i++)
			{
				if(i>=2)
				{
					OLEDFB_drawLine(16*i,20,16*i,28);
					OLEDFB_drawLine(16*(i-1),28,16*i,28);
					OLEDFB_drawLine(16*(i-1),20,16*i,20);
				}
				else if(i==1)
				{
					OLEDFB_drawLine(16*(i-1),24,16*i - 8,18);
					OLEDFB_drawLine(16*(i-1),24,16*i - 8,30);
					OLEDFB_drawLine(16*i - 8,18,16*i,20);
					OLEDFB_drawLine(16*i - 8,30,16*i,28);
				}
			}
			OLEDFB_drawTextEx(20,40,8,8,temp);
		}
		break;
	}
}

static void animationTimerHandler()
{
	if(state == STATE_SPLASH || state ==  STATE_GAMEOVER)
	{
		if(animationCounter < 100) animationCounter++;
	}
	else if(state == STATE_GAME)
	{
		if(animationCounter < 100)
		{
			animationCounter++;
		}
		else
		{
			if(lastPressedKey == KEY_UP) snakeDirection = SNAKE_DIRECTION_UP;
			else if(lastPressedKey == KEY_DOWN) snakeDirection = SNAKE_DIRECTION_DOWN;
			else if(lastPressedKey == KEY_LEFT) snakeDirection = SNAKE_DIRECTION_LEFT;
			else if(lastPressedKey == KEY_RIGHT) snakeDirection = SNAKE_DIRECTION_RIGHT;
			animationCounter = 0;
			int newX = snakeGame.snakePositions[0][0];
			int newY = snakeGame.snakePositions[0][1];
			if(snakeDirection == SNAKE_DIRECTION_UP) newY--;
			else if(snakeDirection == SNAKE_DIRECTION_DOWN) newY++;
			else if(snakeDirection == SNAKE_DIRECTION_LEFT) newX--;
			else if(snakeDirection == SNAKE_DIRECTION_RIGHT) newX++;
			for(int i=snakeGame.snakeLength;i>=1;i--)
			{
				for(int j=0;j<2;j++)
				{
					snakeGame.snakePositions[i][j] = snakeGame.snakePositions[i - 1][j];
				}
			}
			snakeGame.snakePositions[0][0] = newX;
			snakeGame.snakePositions[0][1] = newY;
			if(snakeGame.map[newX][newY] == MAP_FOOD)
			{
				snakeGame.map[newX][newY] == MAP_NORMAL;
				snakeGame.snakeLength++;
				score++;
				if(snakeGame.snakeLength > 20) snakeGame.snakeLength = 20;
			}
			else if(snakeGame.map[newX][newY] == MAP_WALL_HARD)
			{
				setState(STATE_GAMEOVER);
			}
			lastPressedKey = -1;
		}
	}
}

static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		animationTimerId = Timer_set(10, animationTimerHandler);
		setState(STATE_SPLASH);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	case EVENT_KEY_DOWN:
		if(state == STATE_SPLASH)
		{
			setState(STATE_GAME);
		}
		else if(state == STATE_GAME)
		{
			if(lastPressedKey == -1) lastPressedKey = data;
			if(lastPressedKey == KEY_UP && snakeDirection == SNAKE_DIRECTION_DOWN) lastPressedKey = -1;
			if(lastPressedKey == KEY_DOWN && snakeDirection == SNAKE_DIRECTION_UP) lastPressedKey = -1;
			if(lastPressedKey == KEY_LEFT && snakeDirection == SNAKE_DIRECTION_RIGHT) lastPressedKey = -1;
			if(lastPressedKey == KEY_RIGHT && snakeDirection == SNAKE_DIRECTION_LEFT) lastPressedKey = -1;
		}
		else  if(state == STATE_GAMEOVER)
		{
			setState(STATE_SPLASH);
		}
		break;
	}
}

static void setState(int _state)
{
	switch(_state)
	{
	case STATE_SPLASH:
		animationCounter = 0;
		break;
	case STATE_GAME:
		score = 0;
		animationCounter = 0;
		snakeDirection = SNAKE_DIRECTION_UP;
		Snake_init();
		break;
	case STATE_GAMEOVER:
		{
			animationCounter = 0;
			break;
		}
	}
	state = _state;
}
