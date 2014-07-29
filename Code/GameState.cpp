#include "StdAfx.h"
#include "GameState.h"


GameState::GameState(void)
{
	name = core::stringc("unbekannt");
	active = false;
	firstEnter = true;
}

GameState::GameState(core::stringc newName) : name(newName)
{
	active = false;
	firstEnter = true;
}

GameState::~GameState(void)
{
}

core::stringc GameState::getName()
{
	return name;
}

bool GameState::isActive()
{
	return active;
}

void GameState::setActive(bool isactive)
{
	active = isactive;
}

void GameState::initalize()
{
	active = true;
	OnEnter();
}

void GameState::flush()
{
	active = false;
	OnLeave();
}

void GameState::OnEnter()
{
}

void GameState::OnLeave()
{
}

bool GameState::OnEvent(const SEvent &myevent)
{
	return false;
}

void GameState::render()
{
}


