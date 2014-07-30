#include "StdAfx.h"
#include "StartMenu.h"
#include "GameStateManager.h"



enum
{
    GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_GAME_BUTTON,
	GUI_ID_LOAD_GAME_BUTTON,
    GUI_ID_OPTIONS_BUTTON,
	GUI_ID_CREDITS_BUTTON
};
gui::IGUIEnvironment* env;
video::IVideoDriver* driver;
scene::ISceneManager* smgr;


StartMenu::StartMenu(void)
{
	env = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

}

StartMenu::StartMenu(core::stringc newName) : GameState(newName)
{
	env = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
}


StartMenu::~StartMenu(void)
{
}

void StartMenu::OnEnter()
{

	scene::IAnimatedMesh* mesh = smgr->getMesh("../Media/room.3ds");
	smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

	scene::ISceneNode* node = 0;

	node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialTexture(0, driver->getTexture("../Media/wall.jpg"));
    node->getMaterial(0).SpecularColor.set(0,0,0,0);

	mesh = smgr->addHillPlaneMesh("aHill", 
		core::dimension2d<f32>(20,20),
		core::dimension2d<u32>(40,40), 0, 0,
		core::dimension2d<f32>(0,0),
		core::dimension2d<f32>(10,10));

	node= smgr->addWaterSurfaceSceneNode(mesh->getMesh(0),3.0f,300.0f,30.0f);
	node->setPosition(core::vector3df(0,7,0));

	node->setMaterialTexture(0, driver->getTexture("../Media/stones.jpg"));
	node->setMaterialTexture(0, driver->getTexture("../Media/water.jpg"));

	node->setMaterialType(video::EMT_REFLECTION_2_LAYER);

	scene::ICameraSceneNode* camera = smgr->addCameraSceneNode();
	camera->setPosition(core::vector3df(-10,100,-150));
    camera->setFarValue(1000.0f);

	scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator(core::vector3df(0,150,0),250.0f);
	camera->addAnimator(anim);
	anim->drop();

	node = smgr->addLightSceneNode(0, camera->getAbsolutePosition(),video::SColorf(0.0f,0.5f,1.0f,1.0f), 8000.0f);

	scene::IVolumeLightSceneNode * n = smgr->addVolumeLightSceneNode(0, -1,
                32,                              
                32,                              
                video::SColor(255, 255, 255, 255), 
                 video::SColor(0, 0, 0, 0));

    if (n)
    {
        n->setScale(core::vector3df(100.0f, 100.0f, 100.0f));
        n->setPosition(core::vector3df(-90,50,50));

        
        core::array<video::ITexture*> textures;
        for (s32 g=7; g > 0; --g)
        {
            core::stringc tmp;
            tmp = "../Media/portal";
            tmp += g;
            tmp += ".bmp";
            video::ITexture* t = driver->getTexture( tmp.c_str() );
            textures.push_back(t);
        }

       
        scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures,150);
       
        n->addAnimator(glow);

        
        glow->drop();
    }

	node = smgr->addLightSceneNode(0, core::vector3df(-80,100,40),video::SColorf(1.0f,1.0f,1.0f,1.0f), 100.0f);

	env->addButton(core::rect<s32>(10,30,200,80),0, GUI_ID_NEW_GAME_BUTTON, L"Neues Spiel", L"Startet ein neues Spiel");
	env->addButton(core::rect<s32>(10,90,200,140),0, GUI_ID_OPTIONS_BUTTON, L"Optionen", L"zeigt die Spieloptionen");
	env->addButton(core::rect<s32>(10,150,200,200),0, GUI_ID_CREDITS_BUTTON, L"Credits", L"zeigt die Credits");
	env->addButton(core::rect<s32>(10,210,200,260),0, GUI_ID_QUIT_BUTTON, L"Beenden", L"Beendet das Programm");


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

			case GUI_ID_NEW_GAME_BUTTON:
				//wechsel auf MainGameState einfügen
				return true;

			case GUI_ID_LOAD_GAME_BUTTON:
				//Wechsel auf MainGameState mit Checkpoint einfügen
				return true;

			case GUI_ID_OPTIONS_BUTTON:
				//Wechsel auf OptionState einfügen
				return true;

			case GUI_ID_CREDITS_BUTTON:
				//Wechsel auf OutroState einfügen
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
	smgr->drawAll();
	env->drawAll();
}


