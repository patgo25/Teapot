#include "StdAfx.h"
#include "Intro.h"
#include "GameStateManager.h"
#include "GameState.h"
#include <iostream>


video::ITexture* image;
u32 timeStamp;
core::rect<s32> size;

Intro::Intro(void)
{
}

Intro::Intro(core::stringc newName) : GameState(newName)
{
}

Intro::~Intro(void)
{
}

void Intro::OnEnter()
{
	//device->getFileSystem()->addFileArchive("../irrlicht-1.8.1/media/map-20kdm2.pk3");

	//scene::IAnimatedMesh* q3levelmesh = device->getSceneManager()->getMesh("20kdm2.bsp");
	//scene::ISceneNode* q3node = 0;

	////Optimierung des Chunks mit Octree oder ohne
	//if(q3levelmesh)
	//{
	//	q3node = device->getSceneManager()->addOctreeSceneNode(q3levelmesh->getMesh(0), 0);
	//	//node = device->getSceneManager()->addMeshSceneNode(q3levelmesh->getMesh(0));
	//}

	////Triangledetektor erstellen
	//scene::ITriangleSelector *selector = 0;

	////Position der Map anpassen
	//if(q3node)
	//{
	//	q3node->setPosition(core::vector3df(-1350, -130, -1400));

	//	selector = device->getSceneManager()->createOctreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
	//	q3node->setTriangleSelector(selector);
	//}

	//scene::ICameraSceneNode *cam = device->getSceneManager()->addCameraSceneNodeFPS();
	//device->getCursorControl()->setVisible(false); //Mauszeiger unsichtbar machen
	//cam->setPosition(core::vector3df(50,50,-60));
	//cam->setTarget(core::vector3df(-70,30,-60));

	
	image = device->getVideoDriver()->getTexture("../Media/introsprit2.png");
	size = core::rect<s32>(0,224,475,574);
	timeStamp = device->getTimer()->getTime();
}

void Intro::OnEvent()
{
	//Benutzereingaben verwalten
}

void Intro::OnLeave()
{
	//Am Ende des Intros
	image->drop();
	device->getVideoDriver()->drop();
}

void Intro::render()
{
	u32 time = (device->getTimer()->getTime());
	std::cout<<time-timeStamp<<std::endl;

	if((time - timeStamp) >= 5000 && (time - timeStamp) <= 10000)
		size = core::rect<s32>(0,0,512,222);

	else if((time - timeStamp) >= 10000)
		size = core::rect<s32>(514, 0, 642, 128);

	if((time - timeStamp) >= 15000)
		finished(true);

	device->getVideoDriver()->draw2DImage(image, core::position2d<s32>(200,200), size, 0, video::SColor(255,255,255,255), true);
}
