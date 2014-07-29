#include "StdAfx.h"
#include "StartMenu.h"
#include "GameStateManager.h"



enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_OPTIONS_BUTTON,
    GUI_ID_SAVE_BUTTON
};
gui::IGUIEnvironment* env;


StartMenu::StartMenu(void)
{
	env = device->getGUIEnvironment();

}

StartMenu::StartMenu(core::stringc newName) : GameState(newName)
{
	env = device->getGUIEnvironment();

}


StartMenu::~StartMenu(void)
{
}

void StartMenu::OnEnter()
{
	env->addButton(core::rect<s32>(10,300,150,350),0, GUI_ID_QUIT_BUTTON, L"Beenden", L"Beendet das Programm");

}

bool StartMenu::OnEvent(const SEvent &myevent)
{
	if(myevent.EventType == irr::EET_GUI_EVENT)
	{
		s32 id = myevent.GUIEvent.Caller->getID();

		switch(myevent.GUIEvent.EventType)
		{
		case gui::EGET_BUTTON_CLICKED:
			switch(id)
			{
			case GUI_ID_QUIT_BUTTON:
				device->closeDevice();
				return true;
			}
			break;
		default:
			break;
		}
	}

	return false;

}

void StartMenu::OnLeave()
{
}

void StartMenu::render()
{
	env->drawAll();
}


