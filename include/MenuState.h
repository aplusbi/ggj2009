///////////////////////////////////////////////////////////////////
//  File    :   "CMenuState.h"
//
//  Author  :   Stefan Woskowiak
//
//  Purpose :   Contains base class for game states to inherit from.
///////////////////////////////////////////////////////////////////
#ifndef _H_MENUSTATE
#define _H_MENUSTATE

#include "includes.h"
#include "BaseState.h"
class MenuState : public BaseState
{
	static MenuState m_Instance;

	MenuState(){}
	MenuState(const MenuState& r){}
	MenuState& operator=(const MenuState& r){}
public:

	static MenuState* getInstance();

	void Enter();

	bool Update( float fElapsedTime );

	bool Render();

	void Exit();

	//Handle any input sent in from the event manager 
	void HandleInput(SDL_KeyboardEvent keyPressed);

};

#endif
