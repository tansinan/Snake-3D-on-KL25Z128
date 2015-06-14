/*
 * AppFramework.c
 *
 *  Created on: May 23, 2015
 *      Author: tansinan
 */

#include "Includes.h"
#include "AppFramework.h"

App* currentApp = NULL;

void App_create(App* app, void (*drawHandler)(), void (*keyEventHandler)(char key))
{
	app->onDraw = drawHandler;
	app->onKeyEvent = keyEventHandler;
}

void App_switchTo(App* app)
{
	currentApp = app;
}

App* App_getCurrentApp()
{
	return currentApp;
}
