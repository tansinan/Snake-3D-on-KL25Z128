/*
 * AppFramework.h
 *
 *  Created on: May 23, 2015
 *      Author: tansinan
 */

#ifndef APPFRAMEWORK_H_
#define APPFRAMEWORK_H_

#include "Types.h"

#define EVENT_APP_INIT 1
#define EVENT_APP_QUIT 2

typedef struct App
{
	void (*paintHandler)();
	void (*eventHandler)(int event, int data);
} App;

void App_create(App* app, void (*drawHandler)(), void (*eventHandler)(int event, int data));

void App_switchTo(App* app);

App* App_getCurrentApp();

void App_sendMessage(int event, int data);

void App_repaint();

#endif /* APPFRAMEWORK_H_ */
