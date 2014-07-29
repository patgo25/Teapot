// Irrlicht1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <irrlicht.h>
#include <iostream>
#include <driverChoice.h>
#include "EventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#define _CRT_SECURE_NO_WARNINGS //Stopt MSVC sich über sprintf() zu beschweren
#pragma comment (lib, "Irrlicht.lib")
#endif

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_OPTIONS_BUTTON,
    GUI_ID_SAVE_BUTTON,
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1,
	GAMESTATE_ID = 201
};

int main()
{

	video::E_DRIVER_TYPE driverType;
	driverType = driverChoiceConsole();
	bool esc = true;
	bool stop = false;

	//Device erstellen und beenden bei fehlschlag:
	IrrlichtDevice *device = createDevice(driverType, dimension2d<u32>(1280,1024),32,false,true,true);
	EventReceiver events = EventReceiver(device);
	device->setEventReceiver(&events);
	

	if(device == 0)
		return 1; //gewählter Treiber konnte nicht geladen werden


	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment *env = device->getGUIEnvironment();

	//Font anpassen
	IGUISkin *skin = env->getSkin();
	IGUIFont *font = env->getFont("../irrlicht-1.8.1/media/fonthaettenschweiler.bmp");
	if(font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
	
	//Optionsmenü erstellen
	IGUIWindow *menu = env->addWindow(rect<s32>(500, 500, 800, 800), true, L"MENÜ");
	menu->setVisible(false);
	menu->setDraggable(true);
	menu->getCloseButton()->setVisible(false);

	

	//Button implementieren
	env->addButton(rect<s32>(10,40,110,40 + 32),menu, GUI_ID_QUIT_BUTTON, L"Beenden", L"Beendet das Spiel");
	env->addButton(rect<s32>(10,80,110,80 + 32), menu, GUI_ID_OPTIONS_BUTTON, L"Optionen", L"Zeigt die Optionen an");
	env->addButton(rect<s32>(10,120,110,120 + 32), menu, GUI_ID_SAVE_BUTTON, L"Speichern", L"Speichert das Spiel");


	device->getFileSystem()->addFileArchive("../irrlicht-1.8.1/media/map-20kdm2.pk3");

	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* q3node = 0;

	//Optimierung des Chunks mit Octree oder ohne
	if(q3levelmesh)
	{
		q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
		//node = smgr->addMeshSceneNode(q3levelmesh->getMesh(0));
	}

	//Triangledetektor erstellen
	scene::ITriangleSelector *selector = 0;

	//Position der Map anpassen
	if(q3node)
	{
		q3node->setPosition(core::vector3df(-1350, -130, -1400));

		selector = smgr->createOctreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
		q3node->setTriangleSelector(selector);
	}

	//KeyMap für Kamera
	SKeyMap tasten[10];

	//Vorwärts W und key up
	tasten[0].Action = irr::EKA_MOVE_FORWARD;
	tasten[0].KeyCode = irr::KEY_UP;
	tasten[1].Action = irr::EKA_MOVE_FORWARD;
	tasten[1].KeyCode = irr::KEY_KEY_W;

	//Rückwärts S und key down
	tasten[2].Action = irr::EKA_MOVE_BACKWARD;
	tasten[2].KeyCode = irr::KEY_DOWN;
	tasten[3].Action = irr::EKA_MOVE_BACKWARD;
	tasten[3].KeyCode = irr::KEY_KEY_S;

	//Links A und key left
	tasten[4].Action = irr::EKA_STRAFE_LEFT;
	tasten[4].KeyCode = irr::KEY_LEFT;
	tasten[5].Action = irr::EKA_STRAFE_LEFT;
	tasten[5].KeyCode = irr::KEY_KEY_A;

	//Rechts D und key right
	tasten[6].Action = irr::EKA_STRAFE_RIGHT;
	tasten[6].KeyCode = irr::KEY_RIGHT;
	tasten[7].Action = irr::EKA_STRAFE_RIGHT;
	tasten[7].KeyCode = irr::KEY_KEY_D;

	//Springen j und leertaste
	tasten[8].Action = irr::EKA_JUMP_UP;
	tasten[8].KeyCode = irr::KEY_KEY_J;
	tasten[9].Action = irr::EKA_JUMP_UP;
	tasten[9].KeyCode = irr::KEY_SPACE;

	//Ducken c
	tasten[10].Action = irr::EKA_CROUCH;
	tasten[10].KeyCode = irr::KEY_KEY_C;


	//Kamera
	scene::ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS(0,100.0f,0.3f, ID_IsNotPickable, tasten, 11, true, 3.f);  //Erstellt eine FPS-Kamera
	device->getCursorControl()->setVisible(false); //Mauszeiger unsichtbar machen
	cam->setPosition(vector3df(50,50,-60));
	cam->setTarget(vector3df(-70,30,-60));

	if(selector)
	{
		ISceneNodeAnimator *anim = smgr->createCollisionResponseAnimator(selector, cam,vector3df(30,50,30),
																			vector3df(0,-9.81f,0), vector3df(0,30,0));
		selector->drop(); //Fertig damit also wegschmeißen
		cam->addAnimator(anim);
		anim->drop(); //Nicht mehr gebraucht -<entfernen
	}

	//Billboard
	IBillboardSceneNode *bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, driver->getTexture("../irrlicht-1.8.1/media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); //Sichert das es nicht ausversehen aufgepickt wird

	//MD2-Knoten, Vektorbasiert
	scene::IAnimatedMeshSceneNode *npc = 0;
	SMaterial material;

	npc = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../irrlicht-1.8.1/media/faerie.md2"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	npc->setPosition(vector3df(-90,-15,-140)); //Füße auf den Boden
	npc->setScale(vector3df(1.6f)); //Sieht realistischer aus
	npc->setMD2Animation(EMAT_POINT);
	npc->setAnimationSpeed(20.f);
	material.setTexture(0, driver->getTexture("../irrlicht-1.8.1/media/faerie2.bmp"));
	material.Lighting = true;
	material.NormalizeNormals = true;

	//Neuen Dreiecksselector für NPC erstellen (auto. update)
	selector = smgr->createTriangleSelector(npc);
	npc->setTriangleSelector(selector);
	selector->drop();

	//2 NPC erstellen B3D Typ
	npc = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../irrlicht-1.8.1/media/ninja.b3d"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	npc->setScale(vector3df(10));
	npc->setPosition(vector3df(-75,-66,-80));
	npc->setRotation(vector3df(0,90,0));
	npc->setAnimationSpeed(8.f);
	npc->getMaterial(0).NormalizeNormals = true;
	npc->getMaterial(0).Lighting = true;

	selector = smgr->createTriangleSelector(npc);
	npc->setTriangleSelector(selector);
	selector->drop();

	//3 NPC erstellen X Type Skelletanimation ohne skinning
	npc = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../irrlicht-1.8.1/media/dwarf.x"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	npc->setPosition(vector3df(-70,-66,-30));
	npc->setRotation(vector3df(0,-90,0));
	npc->setAnimationSpeed(20.f);
	npc->getMaterial(0).NormalizeNormals = true;
	npc->getMaterial(0).Lighting = true;

	selector = smgr->createTriangleSelector(npc);
	npc->setTriangleSelector(selector);
	selector->drop();

	//4 NPC aus MDL Datei Skelletanimation mit skinning
	npc = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../irrlicht-1.8.1/media/yodan.mdl"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	npc->setPosition(vector3df(-90,-25,20));
	npc->setScale(vector3df(0.8f));
	npc->setAnimationSpeed(20.f);
	npc->getMaterial(0).NormalizeNormals = true;
	npc->getMaterial(0).Lighting = true;

	selector = smgr->createTriangleSelector(npc);
	npc->setTriangleSelector(selector);
	selector->drop();

	material.setTexture(0,0);
	material.Lighting = false;

	//Licht hinzufügen damit die nichtausgewhählten NPCs nicht komplett dunkel sind
	ILightSceneNode *light = smgr->addLightSceneNode(0, vector3df(-60,100,400), SColorf(1.0f,1.0f,1.0f,1.0f),600.f);
	light->setID(ID_IsNotPickable); //Sicher stellen das das Licht nicht ausgewählt werden kann

	//Merken welcher NPC ausgewählt wurde
	ISceneNode *highlightedNPC = 0;
	ISceneCollisionManager *collMan = smgr->getSceneCollisionManager();

	//Auswahldreieck nur als Rahmenlinie zeichnen
	material.Wireframe = true;

	//Zeichne das Level!
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	//Geschwindigkeit in Einheiten/Sekunde setzen
	const f32 MOVEMENT_SPEED = 50.f;

	while(device->run())
	{
		//Errechne FDT
		const u32 now = device->getTimer()->getTime();
		const f32 fdt = (f32) ((now - then) / 1000.f); // Zeit in Sekunden
		then = now;

		//Tasten überprüfen

		if(events.IsKeyDown(irr::KEY_ESCAPE) && !stop)
		{
			if(esc)
			{
				menu->setVisible(true);
				device->getCursorControl()->setVisible(true);
			}
			
			else
			{
				menu->setVisible(false);
				device->getCursorControl()->setVisible(false);
			}
			
			stop = true;
		}
		if(!events.IsKeyDown(irr::KEY_ESCAPE) && stop)
		{
			if(esc)
				esc = false;
			else
				esc = true;

			stop = false;
		}
					
		


		if(device->isWindowActive()) //Nur wenn das Fenster aktiv ist
		{
			driver->beginScene(true, true, video::SColor(255,113,113,113));
			smgr->drawAll();
			env->drawAll();
			driver->endScene();

			if(highlightedNPC)
			{
				highlightedNPC->setMaterialFlag(video::EMF_LIGHTING, true);
				highlightedNPC = 0;
			}

			line3d<f32> ray;
			ray.start = cam->getPosition();
			ray.end = ray.start + (cam->getTarget() - ray.start).normalize() * 1000.0f;

			//Verfolgt aktulle Berührungspüunkte mit einem Mesh
			vector3df intersection;
			
			//Um das getroffene Dreieck anzuzeigen
			triangle3df hitTriangle;

			ISceneNode *selectionNPC = collMan->getSceneNodeAndCollisionPointFromRay(ray,					
																					 intersection,			//Position der Kollison
																					 hitTriangle,			//Getroffenes Dreieck	
																					 IDFlag_IsPickable,		//Nur NPC mit diesem Flag sind betroffen
																					 0);					//überprüft die gesamte Scene

			//Wenn Strahl was trifft, dann  Dreieck anzeigen
			if(selectionNPC)
			{
				bill->setPosition(intersection);

				//Transformation zurück setzen bevor wir selber handeln können
				driver->setTransform(video::ETS_WORLD, matrix4());
				driver->setMaterial(material);
				driver->draw3DTriangle(hitTriangle, SColor(0,255,0,0));

				if((selectionNPC->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
				{
					highlightedNPC = selectionNPC;
					highlightedNPC->setMaterialFlag(EMF_LIGHTING, false);
				}
			}
			
			
			
			int fps = driver->getFPS();

			if(lastFPS != fps) //Frame Rate in den Titel setzen und aktuallisieren
			{
				core::stringw str = L"Quake 3 Map Beispiel [";
				str += driver->getName();
				str += "] FPS: ";
				str += fps;

				device->setWindowCaption(str.c_str());
				
				lastFPS = fps;
			}
			
		}
		else
			device->yield(); //Wenn Fenster inaktiv CPU entlasten
	}

	device->drop(); //Endlich: Device löschen

	return 0;
}

