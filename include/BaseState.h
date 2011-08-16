///////////////////////////////////////////////////////////////////
//  File    :   "CGameState.h"
//
//  Author  :   Stefan Woskowiak
//
//  Purpose :   Contains base class for game states to inherit from.
///////////////////////////////////////////////////////////////////
#ifndef _H_BASESTATE
#define _H_BASESTATE

#include "includes.h"
#include <windows.h>
class BaseState
{
protected:
	//name of the class
	string m_sName;
	//enum type of the object 
	int m_nType;
public:
	BaseState(){}
	virtual ~BaseState(){}

	////////////////////////////////////////////////////
    //  Function    :   "Enter"
    //
    //  Purpose     :   What happens when we "enter" the current state?
    ////////////////////////////////////////////////////
	virtual void Enter() = 0;
	////////////////////////////////////////////////////
    //  Function    :   "Update"
    //
    //  Purpose     :   Update the current state
    ////////////////////////////////////////////////////
	virtual bool Update( float fElapsedTime ) = 0;
	virtual bool Update( float fElapsedTime, LARGE_INTEGER liTime ) { return Update(fElapsedTime); }
	////////////////////////////////////////////////////
    //  Function    :   "Render"
    //
    //  Purpose     :   Render objects
    ////////////////////////////////////////////////////
	virtual bool Render() = 0;
	////////////////////////////////////////////////////
    //  Function    :   "Exit"
    //
    //  Purpose     :   What happens when we "exit" the current state?
    ////////////////////////////////////////////////////
	virtual void Exit() = 0;

	////////////////////////////////////////////////////
    //  Function    :   "Exit"
    //
    //  Purpose     :   What happens when we "exit" the current state?
    ////////////////////////////////////////////////////
	virtual void HandleInput(SDL_KeyboardEvent keyPress) = 0;

};

#endif
