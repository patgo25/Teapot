#include "StdAfx.h"
#include "GameStateManager.h"


GameStateManager::GameStateManager(void)
{
}

GameStateManager::GameStateManager(const GameStateManager&)
{
}

GameStateManager::~GameStateManager(void)
{
}

bool GameStateManager::initalize(int windowWidth, int windowHeight, bool fullscreen)
{
	
	irrlichtDevice = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(windowWidth, windowHeight), 32, fullscreen);

	if(irrlichtDevice)
	{
		return(true);
	}

	return false;
}

bool GameStateManager::finalize()
{
	irrlichtDevice->closeDevice();
	irrlichtDevice->drop();

	return true;
}

IrrlichtDevice* GameStateManager::getDevice()
{
	return irrlichtDevice;
}

bool GameStateManager::isRunning()
{
	return irrlichtDevice->run();
}

void GameStateManager::addGameState(GameState* gamestate, bool active)
{
	gameStates.push_back(gamestate);

	if(active)
	{
		gamestate->setActive(true);
		irrlichtDevice->setEventReceiver(gamestate);
		gamestate->initalize();
	}
}

void GameStateManager::changeGameState(const char* name)
{
	for(unsigned int i = 0; i < gameStates.size(); i++)
	{
		if(core::stringc(name) == core::stringc(gameStates[i]->getName()))
		{
			if(getActiveGameState() != NULL)
			{
				getActiveGameState()->flush();
			}

			irrlichtDevice->setEventReceiver(gameStates[i]);
			gameStates[i]->initalize();
		}
	}
}

GameState* GameStateManager::getActiveGameState()
{
	for(unsigned int i = 0; i < gameStates.size(); i ++)
	{
		if(gameStates[i]->isActive())
		{
			return gameStates[i];
		}
	}
	return NULL;
}

GameState* GameStateManager::getGameState(const char* name)
{
	for(unsigned int i = 0; i> gameStates.size(); i++)
	{
		if(gameStates[i]->isActive())
			return (gameStates[i]);
	}

	return NULL;

}

void GameStateManager::beginRender()
{
	irrlichtDevice->getVideoDriver()->beginScene(true, true, video::SColor(255,255,255,255));
}

void GameStateManager::endRender()
{
	irrlichtDevice->getVideoDriver()->endScene();
}

void GameStateManager::render()
{
	getActiveGameState()->render();
}





