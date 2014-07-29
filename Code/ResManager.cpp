#include "StdAfx.h"
#include "ResManager.h"
#include <vector>
#include <irrlicht.h>


ResManager::ResManager()
{
	meshID = 0;
	textureID = 0;
	
}

void ResManager::loadMesh(irr::scene::IAnimatedMesh* file)
{
	mesh[meshID] = file;
	meshID ++;
}

void ResManager::loadTexture(irr::video::ITexture* file)
{
	texture[textureID] = file;
	textureID ++;
}

void ResManager::unload(bool meshUnload, bool textureUnload)
{
	if(meshUnload)
	{
		while(meshID >= 0)
		{
			mesh[meshID] = nullptr;
			meshID --;
		}

		meshID = 0;
	}

	if(textureUnload)
	{
		while(textureID >= 0)
		{
			texture[textureID] = nullptr;
			textureID --;
		}

		textureID = 0;
	}
}

irr::scene::IAnimatedMesh* ResManager::getMesh(int ID)
{
	if(ID <= meshID)
		return mesh[ID];

	else
		return nullptr;
}

irr::video::ITexture* ResManager::getTexture(int ID)
{
	if(ID <= textureID)
		return texture[ID];
	else
		return nullptr;
}

ResManager::~ResManager(void)
{
}


