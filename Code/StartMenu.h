#pragma once
#include "gamestate.h"
class StartMenu : public GameState
{
private:
bool KeyIsDown[KEY_KEY_CODES_COUNT];

public:
	StartMenu(void);
	StartMenu(core::stringc newName);
	~StartMenu(void);

	virtual bool OnEvent(const SEvent &myevent);
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void render();


	
};

