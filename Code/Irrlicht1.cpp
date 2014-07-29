// Irrlicht1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <irrlicht.h>
#include <iostream>
#include "GameState.h"
#include "GameStateManager.h"
#include "Intro.h"

using namespace irr;

#ifdef _IRR_WINDOWS_
#define _CRT_SECURE_NO_WARNINGS //Stopt MSVC sich über sprintf() zu beschweren
#pragma comment (lib, "Irrlicht.lib")
#endif

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_OPTIONS_BUTTON,
    GUI_ID_SAVE_BUTTON,
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1,
	GAMESTATE_ID = 201
};

scene::ISceneManager* smgr;
video::IVideoDriver* driver;
int main()
{

	if(manager.initalize(800,640,false))
	{
		Intro* intro = new Intro("intro");
		manager.addGameState(intro);
		manager.changeGameState("intro");

		if(manager.getActiveGameState() == intro)
		{
			
		}

		while(device->run())
		{
			device->getVideoDriver()->beginScene(true,true,video::SColor(255,255,255,255));
 			manager.render();
 			device->getVideoDriver()->endScene();
		}

		manager.finalize();
	}



	
	return 0;
}

