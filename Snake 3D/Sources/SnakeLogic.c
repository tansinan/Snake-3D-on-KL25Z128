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

App Snake3D_theApp;

const uint8 MAP_NORMAL = 0;
const uint8 MAP_FOOD = 1;
const uint8 MAP_WALL_HARD = 3;
const uint8 MAP_WALL_SOFT = 4;

const uint8 SNAKE_DIRECTION_UP = 0;
const uint8 SNAKE_DIRECTION_DOWN = 1;
const uint8 SNAKE_DIRECTION_LEFT = 2;
const uint8 SNAKE_DIRECTION_RIGHT = 3;

static uint8 animationTimerId;

static uint16 animationCounter;

static void animationTimerHandler();

static void drawTerrain();
static void drawSnake();
void Snake3D_init();
static void Snake_init();
static void paintHandler();
static void eventHandler(int event, int data);

struct Snake_Game
{
	uint8 map[20][20];
	//[0] => head ||  [1] => body closest to head;
	uint8 snakePositions[20][2];
	uint8 snakeHead;
	uint8 snakeLength;
	uint8 viewPortCenterX;
	uint8 viewPortCenterY;
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
				if(rnd%10==0) snakeGame.map[i][j] = MAP_WALL_HARD;
				else if(rnd%10 == 1) snakeGame.map[i][j] = MAP_FOOD;
				else snakeGame.map[i][j] = MAP_NORMAL;
			}
		}
	}
	snakeGame.snakeHead = 0;
	for(int i=0;i<3;i++)
	{
		snakeGame.snakePositions[i][0] = 5;
		snakeGame.snakePositions[i][1] = 5 + i;
	}
	/*snakeGame.snakePositions[0][0] = 5;
	snakeGame.snakePositions[0][1] = 5;
	snakeGame.snakePositions[1][0] = 5;
	snakeGame.snakePositions[1][1] = 6;
	snakeGame.snakePositions[2][0] = 6;
	snakeGame.snakePositions[2][1] = 6;
	snakeGame.snakePositions[3][0] = 6;
	snakeGame.snakePositions[3][1] = 5;
	snakeGame.snakePositions[4][0] = 6;
	snakeGame.snakePositions[4][1] = 4;
	snakeGame.snakePositions[5][0] = 5;
	snakeGame.snakePositions[5][1] = 4;
	snakeGame.snakePositions[6][0] = 4;
	snakeGame.snakePositions[6][1] = 4;
	snakeGame.snakePositions[7][0] = 4;
	snakeGame.snakePositions[7][1] = 5;
	snakeGame.snakePositions[8][0] = 4;
	snakeGame.snakePositions[8][1] = 6;*/
	/*for(int i=0;i<9;i++)
	{
		snakeGame.snakePositions[i][0] = 10 - snakeGame.snakePositions[i][0];
	}*/
	/*snakeGame.snakePositions[4][0] = 6;
	snakeGame.snakePositions[4][1] = 4;*/
	snakeGame.snakeLength = 3;
	snakeGame.viewPortCenterX = 3;
	snakeGame.viewPortCenterY = 3;
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
		centerY -= animationCounter /100.0*0.5;
	}
	else if(snakeDirection == SNAKE_DIRECTION_DOWN)
	{
		centerY += animationCounter /100.0*0.5;
	}
	else if(snakeDirection == SNAKE_DIRECTION_LEFT)
	{
		centerX -= animationCounter /100.0*0.5;
	}
	else if(snakeDirection == SNAKE_DIRECTION_RIGHT)
	{
		centerX += animationCounter /100.0*0.5;
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
		}
	}
}

static void drawSnake()
{
	const float yLow = -0.5;
	const float yHigh = -0.25;
    Vec3D lastPoint[3];
    Vec3D currentPoint[3];
    
	int relativeX,relativeY;
    for(int i=0;i<= snakeGame.snakeLength;i++)
    {
    	if( i != snakeGame.snakeLength)
    	{
    		relativeX = snakeGame.snakePositions[i][0] - snakeGame.snakePositions[0][0];
    		relativeY = snakeGame.snakePositions[i][1] - snakeGame.snakePositions[0][1];
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
	drawTerrain();
	drawSnake();
}

static void animationTimerHandler()
{
	if(animationCounter < 100)
	{
		animationCounter++;
	}
	else
	{
		animationCounter = 0;
		int newX = snakeGame.snakePositions[0][0];
		int newY = snakeGame.snakePositions[0][1];
		if(snakeDirection == SNAKE_DIRECTION_UP) newY--;
		else if(snakeDirection == SNAKE_DIRECTION_DOWN) newY++;
		else if(snakeDirection == SNAKE_DIRECTION_LEFT) newX--;
		else if(snakeDirection == SNAKE_DIRECTION_RIGHT) newX++;
		for(int i=snakeGame.snakeLength-1;i>=1;i--)
		{
			for(int j=0;j<2;j++)
			{
				snakeGame.snakePositions[i][j] = snakeGame.snakePositions[i - 1][j];
			}
		}
		snakeGame.snakePositions[0][0] = newX;
		snakeGame.snakePositions[0][1] = newY;
		if(lastPressedKey == KEY_UP) snakeDirection = SNAKE_DIRECTION_UP;
		else if(lastPressedKey == KEY_DOWN) snakeDirection = SNAKE_DIRECTION_DOWN;
		else if(lastPressedKey == KEY_LEFT) snakeDirection = SNAKE_DIRECTION_LEFT;
		else if(lastPressedKey == KEY_RIGHT) snakeDirection = SNAKE_DIRECTION_RIGHT;
	}
}
static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		animationCounter = 0;
		snakeDirection = SNAKE_DIRECTION_UP;
		animationTimerId = Timer_set(10, animationTimerHandler);
		Snake_init();
		//setState(STATE_SPLASH);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	case EVENT_KEY_DOWN:
		/*if(data == KEY_DOWN && snakeGame.viewPortCenterY < 20-1)
		{
			snakeGame.viewPortCenterY++;
		}
		else if(data == KEY_UP && snakeGame.viewPortCenterY > 0)
		{
			snakeGame.viewPortCenterY--;
		}
		else if(data == KEY_RIGHT && snakeGame.viewPortCenterX < 20-1)
		{
			snakeGame.viewPortCenterX++;
		}
		else if(data == KEY_LEFT && snakeGame.viewPortCenterX > 0)
		{
			snakeGame.viewPortCenterX--;
		}*/
		lastPressedKey = data;
		break;
	}
}
