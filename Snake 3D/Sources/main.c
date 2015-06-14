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
	//Buzzer_set(880,50);
	
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
    
    App snakeApp;
    App_create(&snakeApp, Snake_onDrawHandler, Snake_eventHandler);
    
    App_switchTo(&AppReactionTime_theApp);
    
    
	for(;;)
	{
		//angle[1] = counter - 30;
	    OLEDFB3D_setCamera(cameraPosition, angle);
	    int fps = frame*4/counter2;
	    char str[4] = "   ";
	    str[0] = fps/100 + '0';
	    str[1] = (fps/10)%10 + '0';
	    str[2] = fps%10 + '0';
	    /*OLEDFB_clear();
	    for(uint16 i=0;i<128;i++)
	    {
	    	uint16 j = (uint16)sqrt(64*64-(i-64)*(i-64));
	    	OLEDFB_setPixelWhite(i,j);
	    	OLEDFB_setPixelWhite(i,counter-j);
	    }
	    OLEDFB_drawTextEx(counter,counter, 14, 14,str);
	    //OLEDFB_drawBitmapEx(0,0,39,39,&OLEDFONT[('A'-0x20)*8],8,8);
	    OLEDFB_drawLine(0,0,20,60);
	    OLEDFB_drawRect(80, 10, 120, 40,OLEDFB_WHITE);
	    OLEDFB_drawRect(0, 0, 120, 40,OLEDFB_INVERTED);
	    OLEDFB_drawCircle(40,40,20,OLEDFB_INVERTED);
	    OLEDFB_drawRect(40, 40, 100, 60,OLEDFB_BLACK);*/
	    //OLEDFB3D_mat33Product(mat3, mat1, mat2);
	    //OLEDFB3D_mat33vec3Product(vec2, mat3, vec1);
		OLEDFB_clear();
		//OLEDFB3D_drawTriangle2D(triangle);
		OLEDFB_drawText(0,0,str);
		//Snake_onDrawHandler();
		App_repaint();
	    frame ++;
	    OLEDFB_flush();
	}
}
