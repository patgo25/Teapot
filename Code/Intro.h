#ifndef INTRO_H
#define INTRO_H

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
private:
	core::position2d<s32> pos;
	video::ITexture* image;
	u32 timeStamp;
	core::rect<s32> size;
};
#endif //INTRO_H DEFINED