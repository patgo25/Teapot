#pragma once
#include<irrlicht.h>

using namespace irr;

class GameState : public IEventReceiver
{
private:
	core::stringc	name;
	bool			active;
	bool			firstEnter;
	

public:
	GameState(void);
	GameState(core::stringc newName);
	virtual ~GameState(void);

	//Name des Gamestates erhalten
	core::stringc getName();

	//Läuft der Gamestates zurzeit?
	bool isActive();

	//Auf wahr setzen wenn es zurzeit läuft
	void setActive(bool);

	//Gamestate inizialisieren (GUI erstellen oder so)
	virtual void initalize();

	//Gamestate reinigen
	virtual void flush();

	//Aufgerufen wenn der Gamestate startet
	virtual void OnEnter();

	//Aufgerufen wenn Gamestate verlassen wird
	virtual void OnLeave();

	//Benutzereingaben (von IEventReceiver abgeleitet)
	virtual bool OnEvent(const SEvent &myevent);

	//Alles rendern (GUI, Scene...)
	virtual void render();
};

