#include "GameMain.h"
#include "SoundManager.h"
#include "CollisionSystem.h"
#include "SDL_ttf.h"
#include "FontRender.h"

GameMain* GameMain::m_pInstance = 0; //init the game instance


GameMain::GameMain()
{
	m_pCurState = NULL;
	//set the messages to be handled by messageProc.h
}

//This will be called to initialize SDL perhaps?
void GameMain::InitGame()
{

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	CollisionSystem::getInstance()->InitCollisionObjects();
	TTF_Init();
	SoundManager::getInstance()->Init();
	atexit(SDL_Quit);
	atexit(TTF_Quit);
	
	m_surface = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

GameMain* GameMain::getInstance()
{
	//lazy intialization
	if (m_pInstance == 0)
		m_pInstance = new GameMain;

	return m_pInstance;
}
void GameMain::Render()
{
		//Render the current state we are in. 
		SDL_Rect dest = {0,0,1024,600};
		SDL_FillRect(m_surface, &dest, 0);
		if(m_pCurState != NULL)
			m_pCurState->Render();
		FontRender::getInstance()->Render();
		//SDL_UpdateRect(m_surface, 0,0,0,0);
		SDL_Flip(m_surface);

}

void GameMain::GameUpdate(float fTime, LARGE_INTEGER liTime)
{
	static float ElapsedTime = 0;
	ElapsedTime += fTime; 
	if(ElapsedTime> 300)
		exit(1);//force close, game over

		//Update our current State
		if(m_pCurState != NULL)
		{
			m_pCurState->Update(fTime, liTime);
			FontRender::getInstance()->Update(fTime);
		}

}

//Exit Current state, Enter New State
void GameMain::ChangeState(BaseState* newState)
{
	if(m_pCurState != NULL)
		m_pCurState->Exit();
	m_pCurState = newState;
	newState->Enter();
}

void GameMain::HandleInput(SDL_KeyboardEvent keyPress)
{
	if(m_pCurState != NULL)
		m_pCurState->HandleInput(keyPress);
}

//Ignore Enter and Exit Calls and Swap
void GameMain::SwapState(BaseState* newState)
{
	m_pCurState = newState;
}

