///////////////////////////////////////////////////////////////////
//  File    :   "CGameState.h"
//
//  Author  :   Stefan Woskowiak
//
//  Purpose :   Contains base class for game states to inherit from.
///////////////////////////////////////////////////////////////////
#ifndef _H_GAMESTATE
#define _H_GAMESTATE

#include "includes.h"
#include "BaseState.h"
class GameState : public BaseState
{
	static GameState m_Instance;


	GameState(){}
	GameState(const GameState& r){}
	GameState& operator=(const GameState& r){}
public:

	static GameState* getInstance();

	void Enter();

	bool Update( float fElapsedTime );

	bool Render();

	void Exit();

	void HandleInput(SDL_KeyboardEvent keyPress);

};

#endif
