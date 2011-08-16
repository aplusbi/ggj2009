#include "EventHandler.h"

EventHandler* EventHandler::m_pInstance = 0; //define the event handler instance

//returns the instance of the game main class
EventHandler* EventHandler::getInstance()
{
	//lazy intialization
	if (m_pInstance == 0)
		m_pInstance = new EventHandler;

	return m_pInstance;
}

//Update will watch for any SDL input events and 
//send them to gamemain where they will be handled by the current state's
//handleinput function. 
void EventHandler::update()
{
	SDL_PollEvent(&m_Event);

	//Quit program
	if(m_Event.type == SDL_QUIT || (m_Event.key.type == SDL_KEYDOWN && m_Event.key.keysym.sym == SDLK_ESCAPE))
		exit(1);

	//Send the keypress off to be handled by the current state
	GameMain::getInstance()->HandleInput(m_Event.key);
}
