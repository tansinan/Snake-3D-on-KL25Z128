/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "Timer.h"
#include "OLED.H"
#include "OLEDFB.h"
#include "OLEDFONT.h"
#include "OLEDFB3D.h"
#include "SnakeLogic.h"
#include "Button.h"
#include "AppFramework.h"
#include "Buzzer.h"
#include "AppReactionTime.h"
#include "AppMusicGame.h"
#include "Music.h"
#include "MusicLibrary.h"

int counter = 0;
int counter2 = 0;

void updateCounter()
{
	counter++;
	counter %= 60;
}

void updateCounter2()
{
	counter2++;
}

int main(void)
{
	Timer_init(10);
	OLED_Init();
	OLEDFB_init();
	Button_init();
	Buzzer_init();
	MusicLibrary_init();
	//Buzzer_set(880,50);
	//Music_play(&MusicLibrary_rainbow, -1);
	
	//用于调试的代码
	Timer_set(16, updateCounter);
	Timer_set(250, updateCounter2);
	
	int frame = 0;
	
    //Vec3D cameraPosition = {0, -3, 0};
    //Vec3D angle = {60, 0, 46.7};
	Vec3D cameraPosition = {0, 2.0, 2.8};
	Vec3D angle = {-25, 0, 0};
    //OLEDFB3D_projectPoint(vec1,vec2);
	
    Snake_init();
    AppReactionTime_init();
    AppMusicGame_init();
    
    App snakeApp;
    App_create(&snakeApp, Snake_onDrawHandler, Snake_eventHandler);
    
    App_switchTo(&snakeApp);
    
    
	for(;;)
	{
		//angle[1] = counter - 30;
	    OLEDFB3D_setCamera(cameraPosition, angle);
	    int fps = frame*4/counter2;
	    char str[4] = "   ";
	    str[0] = fps/100 + '0';
	    str[1] = (fps/10)%10 + '0';
	    str[2] = fps%10 + '0';
		OLEDFB_clear();
		OLEDFB_drawText(0,0,str);
		App_repaint();
	    frame ++;
	    OLEDFB_flush();
	}
}
