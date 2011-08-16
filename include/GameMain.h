// GameMain.h
// Author: Stefan Woskowiak
// Contains information partaining to running the game prototype over the hex engine
// Through the use of the MainGame class object. 
#ifndef _H_GAMEMAIN_
#define _H_GAMEMAIN_

#include "INCLUDES.h"
#include "COMMON.h"
#include "BaseState.h"

class GameMain
{
private:
	//Instance of the MainGame
	static GameMain* m_pInstance;
	//Keep track of the SDL surface
	SDL_Surface* m_surface;
	//The current game state we are in
	BaseState*		 m_pCurState;
	//MainGame is a singleton
	GameMain();
	GameMain& operator=(const GameMain& ref){}
	GameMain(const GameMain& ref){}
public:
	//returns the instance of the MainGame class
	static GameMain* getInstance();
	//init certain game vars. 
	void InitGame();
	//Update the gameplay code. Takes a time in for time based calculations. 
	void GameUpdate(float fTime, LARGE_INTEGER liTime);
	//Render calls to associated objects.
	void Render();
	//Exit Current state, Enter New State
	void ChangeState(BaseState* newState);
	//Ignore Enter and Exit Calls and Swap
	void SwapState(BaseState* newState);

	void HandleInput(SDL_KeyboardEvent keyPress);

	//Return the SDL surface
	SDL_Surface* getSurface(){ return m_surface; }
};


#endif
