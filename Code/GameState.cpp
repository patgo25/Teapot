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
	OnEnter();
	active = true;
	finish = false;
	
}

void GameState::flush()
{
	active = false;
	finish = true;
	OnLeave();
}

void GameState::finished(bool fine)
{
	finish = fine;
}

bool GameState::isFinished()
{
	return finish;
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


