// Irrlicht1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <irrlicht.h>
#include <iostream>
#include "GameState.h"
#include "GameStateManager.h"
#include "Intro.h"
#include "StartMenu.h"
#include "SampleGame.h"
#include "Debuger.h"

using namespace irr;

#ifdef _IRR_WINDOWS_
#define _CRT_SECURE_NO_WARNINGS //Stopt MSVC sich �ber sprintf() zu beschweren
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

int main()
{

	if(manager.initalize(800,600,false))
	{
		Intro* intro = new Intro("intro");
		StartMenu* Menu = new StartMenu("menu");
		SampleGame* test = new SampleGame("test");
		manager.addGameState(intro);
		manager.addGameState(Menu);
		manager.addGameState(test);
		manager.changeGameState("intro");

		Debuger* dtest = new Debuger();
		//dtest->run();

		while(device->run())
		{
			device->getVideoDriver()->beginScene(true,true,video::SColor(255,255,255,255));

			if(((intro->isFinished()) == true && Menu->isActive() == false  && test->isActive() == false) || (test->isFinished() == true && Menu->isActive() == false))
			{
				manager.changeGameState("menu");
			}


			else if((Menu->isFinished()) == true && test->isActive() == false && Menu->newGame == true)
			{
				manager.changeGameState("test");
			}

			//dtest->draw();
 			manager.render();
 			device->getVideoDriver()->endScene();
		}

		manager.finalize();
	}



	
	return 0;
}

