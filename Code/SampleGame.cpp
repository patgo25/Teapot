#include "StdAfx.h"
#include "SampleGame.h"
#include "GameStateManager.h"
#include <iostream>

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1,

	GUI_ID_BACK_BUTTON = 101,
	GUI_ID_YES_BUTTON,
	GUI_ID_NO_BUTTON
};


SampleGame::SampleGame(void)
{
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = irr::KEY_KEY_W;
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = irr::KEY_KEY_S;
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = irr::KEY_KEY_A;
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = irr::KEY_KEY_D;
	keyMap[4].Action = irr::EKA_JUMP_UP;
	keyMap[4].KeyCode = irr::KEY_SPACE;
	keyMap[5].Action = irr::EKA_CROUCH;
	keyMap[5].KeyCode = irr::KEY_KEY_C;



	smgr = device->getSceneManager();
	env = smgr->getGUIEnvironment();
	device->getFileSystem()->addFileArchive("../Media/map-20kdm2.pk3");
}

SampleGame::SampleGame(core::stringc newName) : GameState(newName)
{
	
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = irr::KEY_KEY_W;
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = irr::KEY_KEY_S;
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = irr::KEY_KEY_A;
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = irr::KEY_KEY_D;
	keyMap[4].Action = irr::EKA_JUMP_UP;
	keyMap[4].KeyCode = irr::KEY_SPACE;
	keyMap[5].Action = irr::EKA_CROUCH;
	keyMap[5].KeyCode = irr::KEY_KEY_C;



	smgr = device->getSceneManager();
	env = smgr->getGUIEnvironment();
	device->getFileSystem()->addFileArchive("../Media/map-20kdm2.pk3");
	
}

void SampleGame::OnEnter()
{
	lastFPS = -1;
	map = smgr->getMesh("../Media/20kdm2.bsp");
	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.3f, ID_IsNotPickable, keyMap, 6, true, 1.5f);
	camera->setPosition(core::vector3df(50,50,-60));
    camera->setTarget(core::vector3df(-70,30,-60));
	node = 0;

	exitWindow = env->addWindow(core::rect<s32>(300,260,520,360),true,0,0);
	exitWindow->getCloseButton()->setVisible(false);
	exitWindow->setDrawTitlebar(false);

	text = env->addStaticText(L"Wirklich zurück?", core::rect<s32>(10,10,210,50), false, false, exitWindow, false);
	env->addButton(core::rect<s32>(10,60,100,90), exitWindow, GUI_ID_YES_BUTTON, L"ja",0);
	env->addButton(core::rect<s32>(110,60,210,90), exitWindow, GUI_ID_NO_BUTTON, L"Nein",0);
	exitWindow->setVisible(false);

	std::cout<<"test-Game State gestartet:"<<std::endl;
	if(map)
	{
		node = smgr->addOctreeSceneNode(map->getMesh(0), 0, IDFlag_IsPickable, 12024, false);
	}

	
	if(node)
	{
        node->setPosition(core::vector3df(-1350,-130,-1400));
		selector = smgr->createOctreeTriangleSelector(map->getMesh(0), node, 128);
		node->setTriangleSelector(selector);
	}

	if(selector)
	{
		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, camera, core::vector3df(30,50,30), 
			core::vector3df(0,-10,0), core::vector3df(0,30,0));
		selector->drop();
		camera->addAnimator(anim);
		anim->drop();
	}

	device->getCursorControl()->setVisible(false);

	
}

bool SampleGame::OnEvent(const SEvent &myevent)
{
	//Events durch das GUI ausgelöst
	if(myevent.EventType == irr::EET_GUI_EVENT)
	{
		s32 id = myevent.GUIEvent.Caller->getID();

		switch(myevent.GUIEvent.EventType)
		{
		case gui::EGET_BUTTON_CLICKED:
			switch(id)
			{
			case GUI_ID_YES_BUTTON:
				
				finished(true);
				exitWindow->setVisible(false);
				std::cout<<"Knopf wurde gedrueckt"<<std::endl;
				return true;

			case GUI_ID_NO_BUTTON:
				device->getCursorControl()->setVisible(false);
				exitWindow->setVisible(false);
				text->setText(L"Wirklich zurück?");
				return true;
			}
			break;
		default:
			break;
		}
	}

		//Events durch die Tastatur ausgelöst
	if(myevent.EventType == EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[myevent.KeyInput.Key] = myevent.KeyInput.PressedDown;

		if(KeyIsDown[irr::KEY_ESCAPE])
		{
			device->getCursorControl()->setVisible(true);
			exitWindow->setVisible(true);
			return true;
		}

		else
			return false;

	}
	return false;
}

void SampleGame::OnLeave()
{
	camera->remove();
	camera = 0;
	node->remove();
	node = 0;
	map = 0;
	std::cout<<"test-Game State beendet"<<std::endl;
}

void SampleGame::render()
{
	smgr->drawAll();
	env->drawAll();

	int fps = smgr->getVideoDriver()->getFPS();

    if (lastFPS != fps)
    {
        core::stringw str = L"Game-Test [";
        str += smgr->getVideoDriver()->getName();
        str += "] FPS:";
        str += fps;

        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    }
}



SampleGame::~SampleGame(void)
{
}
