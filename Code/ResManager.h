#pragma once
#include <irrlicht.h>

class ResManager
{
private:
	int meshID, textureID;
	irr::scene::IAnimatedMesh* mesh[100];
	irr::video::ITexture* texture[100];
public:
	ResManager(); 

	void loadMesh(irr::scene::IAnimatedMesh* file);					//neues Mesh hinzufügen 
	void loadTexture(irr::video::ITexture* file);					//Neue Texturen ins Array

	void unload(bool meshUnload, bool textureUnload);				//bestimmte Arrays verwerfen

	irr::scene::IAnimatedMesh* getMesh(int ID);						//Mesh abrufen
	irr::video::ITexture* getTexture(int ID);						//Texture abrufen




	~ResManager(void);


};

