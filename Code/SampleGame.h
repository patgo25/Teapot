#pragma once
#include "gamestate.h"
class SampleGame :public GameState
{
private:
	scene::IAnimatedMesh *map;
	scene::ISceneManager * smgr;
	gui::IGUIEnvironment* env;
	video::IVideoDriver* driver;
	scene::ICameraSceneNode* camera;
	scene::IMeshSceneNode *node;
	scene::IAnimatedMeshSceneNode *dwarf;
	scene::ITriangleSelector* selector;
	gui::IGUIWindow *exitWindow;
	gui::IGUIStaticText* text;
	scene::ILightSceneNode *light;
	scene::ISceneNode* highlightedSceneNode, *selectedSceneNode;
    scene::ISceneCollisionManager* collMan;
	video::SMaterial material;
	scene::IBillboardSceneNode *bill;
	
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

