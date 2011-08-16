#include "MenuState.h"
#include "GameState.h"
#include "GameMain.h"

MenuState MenuState::m_Instance;

MenuState* MenuState::getInstance()
{
	return &m_Instance;
}

void MenuState::Enter()
{
	//init menu graphics and other stuff here
}

bool MenuState::Update( float fElapsedTime )
{
	return true;
}

bool MenuState::Render()
{
	return true;
}

void MenuState::Exit()
{
	//unload menu assets 
}

void MenuState::HandleInput(SDL_KeyboardEvent keyPressed)
{
	//Handle input relative to
	switch(keyPressed.keysym.sym)
	{
	case SDLK_SPACE:
		//Switch to the game state if we hit the spacebar
		GameMain::getInstance()->ChangeState(GameState::getInstance());
		break;
	};
}
