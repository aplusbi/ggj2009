//Program entry point
//main.cpp
#include <windows.h>
#include <stdlib.h>

#include "GameMain.h"
#include "EventHandler.h"
#include "StateTest.h"
#include "MenuState.h"

int main(int argc, char *argv[])
{
	GameMain* pGame = GameMain::getInstance();

	//TIMER INFORMATION////////////////////////////
	LARGE_INTEGER m_CounterFrequency;
	LARGE_INTEGER m_LastCount;

	static float PrevTime = 0.0f;
	static float CurTime = 0.0f;
	///////////////////////////////////////////////

	//One time initialization
	pGame->InitGame();
	pGame->ChangeState(StateTest::getInstance());

	QueryPerformanceFrequency(&m_CounterFrequency);
	QueryPerformanceCounter(&m_LastCount);
	while(true)
	{
		PrevTime = CurTime;
		LARGE_INTEGER lCurrent;
		QueryPerformanceCounter(&lCurrent);

		CurTime = float((lCurrent.QuadPart - m_LastCount.QuadPart) / double(m_CounterFrequency.QuadPart));
		
		//Update the event handler.
		EventHandler::getInstance()->update();
		//update the main game loop using elapsed time
		pGame->GameUpdate(CurTime - PrevTime, lCurrent);

		pGame->Render();
	}

	return 0;
}
