#include "StdAfx.h"
#include "StartMenu.h"
#include "GameStateManager.h"
#include "SettingManager.h"
#include <iostream>



enum
{
    GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_GAME_BUTTON,
	GUI_ID_LOAD_GAME_BUTTON,
    GUI_ID_OPTIONS_BUTTON,
	GUI_ID_CREDITS_BUTTON,
	GUI_ID_SAVE_CHANGES_BUTTON,
	GUI_ID_BACK_BUTTON,
	GUI_ID_YES_BUTTON,
	GUI_ID_NO_BUTTON
};
gui::IGUIEnvironment* env;
video::IVideoDriver* driver;
scene::ISceneManager* smgr;

scene::IAnimatedMesh* mesh;
scene::ICameraSceneNode* camera;

gui::IGUIStaticText *titel, *debug;
gui::IGUIButton *saveButton, *backButton, *newGameButton, *loadGameButton, *optionsButton, *creditsButton, *exitButton;
gui::IGUIWindow *exitWindow;
gui::IGUIListBox *fpsList;
gui::IGUISkin *skin;
gui::IGUIFont *font;
scene::ISceneNode* node, *licht, *wasser;
scene::IVolumeLightSceneNode * n;
video::ITexture* t, *stone, *water, *wall;
core::array<video::ITexture*> textures;

int fps;

StartMenu::StartMenu(void)
{
	env = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	newGame = false;
}

StartMenu::StartMenu(core::stringc newName) : GameState(newName)
{
	env = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	newGame = false;
}


StartMenu::~StartMenu(void)
{
}

void StartMenu::OnEnter()
{
	std::cout<<"Menu-State gestartet:"<<std::endl;
	//Font personalisieren
	skin = env->getSkin();
	font = env->getFont("../Media/fonts/celtic/celtic.xml");
	mesh = 0;
	node = 0;

	if(font)
		skin->setFont(font);

	titel = env->addStaticText(L"The celestial teapot", core::rect<s32>(280, 10, 1000, 80),false,false,0,1,false);

	//Mesh laden
	mesh = smgr->getMesh("../Media/room.3ds");
	smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

	 

	//Mash mit Steinen Pflastern
	node = smgr->addAnimatedMeshSceneNode(mesh);
	wall = driver->getTexture("../Media/wall.jpg");
    node->setMaterialTexture(0, wall);
    node->getMaterial(0).SpecularColor.set(0,0,0,0);

	//Boden wässern
	mesh = smgr->addHillPlaneMesh("aHill", 
		core::dimension2d<f32>(20,20),
		core::dimension2d<u32>(40,40), 0, 0,
		core::dimension2d<f32>(0,0),
		core::dimension2d<f32>(10,10));

	wasser= smgr->addWaterSurfaceSceneNode(mesh->getMesh(0),3.0f,300.0f,30.0f);
	wasser->setPosition(core::vector3df(0,7,0));

	stone = driver->getTexture("../Media/stones.jpg");
	water = driver->getTexture("../Media/water.jpg");
	wasser->setMaterialTexture(0, stone);
	wasser->setMaterialTexture(0, water);

	wasser->setMaterialType(video::EMT_REFLECTION_2_LAYER);

	//Kamera einfügen
	camera = smgr->addCameraSceneNode(0,core::vector3df(0,0,0), core::vector3df(0,0,100), 2, true);
	camera->setPosition(core::vector3df(-10,100,-150));
    camera->setFarValue(1000.0f);

	scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator(core::vector3df(0,150,0),250.0f);
	camera->addAnimator(anim);
	anim->drop();

	//Und ich sprach es werde Licht ;)
	licht = smgr->addLightSceneNode(0, camera->getAbsolutePosition(),video::SColorf(0.0f,0.5f,1.0f,1.0f), 8000.0f);

	n = smgr->addVolumeLightSceneNode(0, -1,
                32,                              
                32,                              
                video::SColor(255, 255, 255, 255), 
                 video::SColor(0, 0, 0, 0));

    if (n)
    {
        n->setScale(core::vector3df(100.0f, 100.0f, 100.0f));
        n->setPosition(core::vector3df(-90,50,50));

        
        
        for (s32 g=7; g > 0; --g)
        {
            core::stringc tmp;
            tmp = "../Media/portal";
            tmp += g;
            tmp += ".bmp";
            t = driver->getTexture( tmp.c_str() );
            textures.push_back(t);
        }

       
        scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures,150);
       
        n->addAnimator(glow);

        
        glow->drop();
    }

	licht = smgr->addLightSceneNode(0, core::vector3df(-80,100,40),video::SColorf(1.0f,1.0f,1.0f,1.0f), 100.0f);

	//Knöpfe
	newGameButton = env->addButton(core::rect<s32>(10,50,200,100),0, GUI_ID_NEW_GAME_BUTTON, L"Neues Spiel", L"Startet ein neues Spiel");
	loadGameButton = env->addButton(core::rect<s32>(10,110,200,160),0, GUI_ID_LOAD_GAME_BUTTON, L"Spiel laden", L"Startet ein neues Spiel");
	optionsButton = env->addButton(core::rect<s32>(10,170,200,220),0, GUI_ID_OPTIONS_BUTTON, L"Optionen", L"zeigt die Spieloptionen");
	creditsButton = env->addButton(core::rect<s32>(10,230,200,280),0, GUI_ID_CREDITS_BUTTON, L"Credits", L"zeigt die Credits");
	exitButton = env->addButton(core::rect<s32>(10,290,200,340),0, GUI_ID_QUIT_BUTTON, L"Verlassen", L"Beendet das Programm");
	backButton = env->addButton(core::rect<s32>(10,110,200,160),0, GUI_ID_BACK_BUTTON, L"Zurück", L"Kehrt zum Hauptmenü zurück");
	saveButton = env->addButton(core::rect<s32>(10,50,200,100),0, GUI_ID_SAVE_CHANGES_BUTTON, L"Speichern", L"Speichert die Änderungen");
	saveButton->setVisible(false);
	backButton->setVisible(false);

	//Beenden Dialog
	exitWindow = env->addWindow(core::rect<s32>(300,260,520,360),true,0,0);
	exitWindow->getCloseButton()->setVisible(false);
	exitWindow->setDrawTitlebar(false);

	env->addStaticText(L"Wirklich beenden?", core::rect<s32>(10,10,210,50), false, false, exitWindow, false);
	env->addButton(core::rect<s32>(10,60,100,90), exitWindow, GUI_ID_YES_BUTTON, L"ja",0);
	env->addButton(core::rect<s32>(110,60,210,90), exitWindow, GUI_ID_NO_BUTTON, L"Nein",0);
	exitWindow->setVisible(false);

	//Optionen Dialog

	//Insert Code here


	//Debugbereich im Creditmenü
	fpsList = env->addListBox(core::rect<s32>(10,220,395,630),0,-1,true);
	fpsList->setVisible(false);
	core::stringw debugText = L"\n\nVideodriver: ";
	debugText += driver->getName();
	debugText += L"\n\nBetriebssystem: ";
	debugText += device->getOSOperator()->getOperatingSystemVersion();
	debugText += L"\n\nIrrlichtversion: ";
	debugText += device->getVersion();
	debugText += L"\n\nGrafikartenhersteller: ";
	debugText += driver->getVendorInfo();
	debugText += L"\n\nVersionsnummer: N/A";
	debugText += L"\n\ngeladene Meshs: 1";
	debugText += L"\n\ngeladene Bilder: 11";
	debugText += L"\n\ngeladene Fonts: 1(+1)";
	debugText += L"\n\ngeladene Sounds: 0";
	debugText += L"\n\nUm neue Framraten zu erhalten [f] drücken (Auch außerhalb dieses Bereichs im Hauptmenü möglich)";
	debug = env->addStaticText(debugText.c_str(),core::rect<s32>(405,220,790,630),false, true, 0, -1, true);
	debug->setVisible(false);
}
bool StartMenu::OnEvent(const SEvent &myevent)
{
	//Events durch das GUI ausgelöst
	if(myevent.EventType == irr::EET_GUI_EVENT)
	{
		s32 id = myevent.GUIEvent.Caller->getID();

		switch(myevent.GUIEvent.EventType)
		{
		case gui::EGET_BUTTON_CLICKED:
			switch(id)
			{
			case GUI_ID_QUIT_BUTTON:
				//Wenn der verlassen Knopp gedrückt wird
				exitWindow->setVisible(true);
				
				return true;

			case GUI_ID_NEW_GAME_BUTTON:
				//wechsel auf MainGameState einfügen
				newGame = true;
				finished(true);
				return true;

			case GUI_ID_LOAD_GAME_BUTTON:
				//Wechsel auf MainGameState mit Checkpoint einfügen
				return true;

			case GUI_ID_OPTIONS_BUTTON:
				//Spieloptionen
				titel->setText(L"The almighty options");
				saveButton->setVisible(true);
				backButton->setVisible(true);
				newGameButton->setVisible(false);
				loadGameButton->setVisible(false);
				optionsButton->setVisible(false);
				creditsButton->setVisible(false);
				exitButton->setVisible(false);

				return true;

			case GUI_ID_CREDITS_BUTTON:
				//Wechsel auf OutroState einfügen
				skin->setFont(env->getBuiltInFont());
				titel->setText(L"Debug-Informationen");
				backButton->setVisible(true);
				newGameButton->setVisible(false);
				loadGameButton->setVisible(false);
				optionsButton->setVisible(false);
				creditsButton->setVisible(false);
				exitButton->setVisible(false);
				debug->setVisible(true);
				fpsList->setVisible(true);


				return true;

			case GUI_ID_SAVE_CHANGES_BUTTON:
				//In den Optionen geändertes Zeug hier speichern
				return true;

			case GUI_ID_BACK_BUTTON:
				//Derzeitiges Untermenü verlassen und zum Hauptmenü zurück
				titel->setText(L"The celestial teapot");
				saveButton->setVisible(false);
				backButton->setVisible(false);
				newGameButton->setVisible(true);
				loadGameButton->setVisible(true);
				optionsButton->setVisible(true);
				creditsButton->setVisible(true);
				exitButton->setVisible(true);
				debug->setVisible(false);
				fpsList->setVisible(false);
				skin->setFont(font);

				return true;

			case GUI_ID_YES_BUTTON:
				//Wenn im Beenden-Dialog "ja" gedrückt wurde
				device->closeDevice();

				return true;

			case GUI_ID_NO_BUTTON:
				exitWindow->setVisible(false);

				return true;

			}
			break;
		default:
			break;
		}
	}

	//Events durch die Tastatur ausgelöst
	if(myevent.EventType == EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[myevent.KeyInput.Key] = myevent.KeyInput.PressedDown;

		if(KeyIsDown[irr::KEY_KEY_F])
		{
			u32 time = device->getTimer()->getTime();
			core::stringw tmp(L"aktuelle Framerate: ");
			fps = driver->getFPS();
			tmp += fps;
			titel->setText(tmp.c_str());
			tmp += L" | timestamp: ";
			tmp += time;
			fpsList->addItem(tmp.c_str());
		}
		if(!KeyIsDown[irr::KEY_KEY_F])
		{
			titel->setText(L"The celestial teapot");
		}
	}


	return false;

}


void StartMenu::OnLeave()
{
	node->remove();
	node = 0;
	wasser->remove();
	wasser = 0;
	n->remove();
	n = 0;

	newGameButton->setVisible(false);
	loadGameButton->setVisible(false);
	optionsButton->setVisible(false);
	creditsButton->setVisible(false);
	exitButton->setVisible(false);
	titel->setVisible(false);

	std::cout<<"Menu-State beendet"<<std::endl;
}

void StartMenu::render()
{
	smgr->drawAll();
	env->drawAll();
}


