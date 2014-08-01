#pragma once
#define manager		GameStateManager::getInstance()
#define device		GameStateManager::getInstance().getDevice()

#include<irrlicht.h>
#include"GameState.h"
#include<vector>

using namespace irr;

class GameStateManager
{
private:
	IrrlichtDevice*				irrlichtDevice;
	std::vector<GameState*>		gameStates;

	GameStateManager(void);
	GameStateManager(const GameStateManager&);
	~GameStateManager(void);
	GameStateManager operator = (const GameStateManager&);

	

public:


	static GameStateManager& getInstance()
	{
		static GameStateManager instance;
		return(instance);
	}

	//Irrlicht Device erstellen
	bool initalize(int width, int height, bool fullscreen);

	//Irrlicht Device verwerfen
	bool finalize();

	//Irrlicht Device zur�ck geben
	IrrlichtDevice* getDevice();

	//L�uft es?
	bool isRunning();

	//GameState hinzuf�gen
	void addGameState(GameState* gamestate, bool active = false);

	//aktiven GameState wechseln
	void changeGameState(const char* name);

	//aktiven GameState zur�ckgeben
	GameState* getActiveGameState();

	//speziefischen GameState zur�ck geben
	GameState* getGameState(const char* name);

	void beginRender();
	void endRender();

	void render();
};

