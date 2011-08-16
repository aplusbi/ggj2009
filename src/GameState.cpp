#include "GameState.h"

GameState GameState::m_Instance;

GameState* GameState::getInstance()
{
	return &m_Instance;
}

void GameState::Enter()
{}

bool GameState::Update( float fElapsedTime )
{
	return true;

}

bool GameState::Render()
{
	return true;
}

void GameState::Exit()
{}

void GameState::HandleInput(SDL_KeyboardEvent keyPress)
{}
