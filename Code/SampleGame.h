#pragma once
#include "gamestate.h"
class SampleGame :public GameState
{
private:
	scene::IAnimatedMesh *map;
	scene::ISceneManager * smgr;
	gui::IGUIEnvironment* env;
	scene::ICameraSceneNode* camera;
	scene::IMeshSceneNode *node;
	scene::ITriangleSelector* selector;
	gui::IGUIWindow *exitWindow;
	gui::IGUIStaticText* text;
	int lastFPS;
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	irr::SKeyMap keyMap[6];

public:
	SampleGame(void);
	SampleGame(core::stringc newName);
	~SampleGame(void);

	virtual bool OnEvent(const SEvent &myevent);
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void render();
};

