#pragma once
#include "GameState.h"
class Intro : public GameState
{
public:
	Intro(void);
	Intro(core::stringc newName);
	~Intro(void);

	virtual void OnEvent();
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void render();


};

