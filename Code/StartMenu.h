#pragma once
#include "gamestate.h"
class StartMenu : public GameState
{
public:
	StartMenu(void);
	StartMenu(core::stringc newName);
	~StartMenu(void);

	virtual bool OnEvent(const SEvent &myevent);
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void render();
};

