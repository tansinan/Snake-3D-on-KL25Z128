/*
 * AppFramework.h
 *
 *  Created on: May 23, 2015
 *      Author: tansinan
 */

#ifndef APPFRAMEWORK_H_
#define APPFRAMEWORK_H_

typedef struct App
{
	void (*onDraw)();
	void (*onKeyEvent)(char key);
	//TODO: more callback functions(e.g. Timer, UART I/O may need to be added.)
} App;

void App_create(App* app, void (*drawHandler)(), void (*keyEventHandler)(char key));
void App_switchTo(App* app);
App* App_getCurrentApp();
void App_defaultDrawHandler();
void App_defaultKeyHandler();

#endif /* APPFRAMEWORK_H_ */
