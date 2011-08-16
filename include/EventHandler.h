#ifndef _H_EVENTHANDLER
#define _H_EVENTHANDLER

#include "GameMain.h"

class EventHandler
{

private:
	static EventHandler* m_pInstance;
	SDL_Event m_Event;

	EventHandler(){}
	EventHandler& operator=(const EventHandler& ref){}
	EventHandler(const EventHandler& ref){}

public:
	static EventHandler* getInstance();
	//Update will watch for any SDL input events and 
	//send them to gamemain where they will be handled by the current state's
	//handleinput function. 
	void update();

	const SDL_Event &GetEvent() { return m_Event; }

};

#endif
