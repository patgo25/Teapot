#include "StdAfx.h"
#include "Intro.h"
#include "GameStateManager.h"
#include "GameState.h"
#include <iostream>

Intro::Intro(void) :image(nullptr), size(), pos()
{
}

Intro::Intro(core::stringc newName) : GameState(newName)
{
}

Intro::~Intro(void)
{
}

void Intro::OnEnter()
{
	image = device->getVideoDriver()->getTexture("../Media/test.png");
	pos = core::position2d<s32>(150, 200);
	size = core::rect<s32>(75, 350, 604, 775);
	timeStamp = device->getTimer()->getTime();
}

void Intro::OnEvent()
{
	//Benutzereingaben verwalten
}

void Intro::OnLeave()
{
	//Am Ende des Intros
}

void Intro::render()
{
	u32 time = (device->getTimer()->getTime());
	std::cout << time - timeStamp << std::endl;
	if ((time - timeStamp) >= 3000 && (time - timeStamp) <= 8000)
	{
		//OpenGL Logo
		pos = core::position2d<s32>(100, 200);
		size = core::rect<s32>(60, 60, 640, 350);
	}

	else if ((time - timeStamp) >= 8000)
	{
		//Irrlichtlogo
		pos = core::position2d<s32>(250, 250);
		size = core::rect<s32>(680, 340, 960, 470);
	}

	if ((time - timeStamp) >= 12000)
	{
		//Switch to the next GameState
		finished(true);
	}

	device->getVideoDriver()->draw2DImage(image, pos, size, 0, video::SColor(255, 255, 255, 255), true);
}
