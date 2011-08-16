#ifndef STATETEST_H
#define STATETEST_H

#include "BaseState.h"
#include "Sprite.h"
#include "Recorder.h"
#include "EventHandler.h"
#include "Player.h"
#include <list>
#include <windows.h>

class Sprite;
class Player;

class StateTest : public BaseState
{
public:
	enum State { NONE, MOVING_LEFT, MOVING_RIGHT};
protected:
	static StateTest m_Instance;
	StateTest();
	StateTest(const StateTest &r){}
	StateTest &operator=(const StateTest &r){}

	void TimeTravel();

	std::list<Player*> m_Clones;
	std::list<Sprite*> m_Sprites;
	Player *m_Character;
	State m_State;

	Recorder m_Record;
	bool m_IsRecording;
	bool m_IsDark;
	char m_Room;
	Sprite *m_RoomSprite;
	Sprite *m_Girl;
	bool m_GirlRight;
	float m_GirlTalk;

public:
	static StateTest *getInstance();

	void Enter();

	bool Update( float fElapsedTime ) {return true;}
	bool Update( float fElapsedTime, LARGE_INTEGER liTime );

	bool Render();

	void Exit();

	void HandleInput(SDL_KeyboardEvent keyPress);
	void SetRoom(char room);
	void SetRoomDark(bool dark);
	char GetRoom(){return m_Room;}
	void AddSprite(Sprite *sprite) { m_Sprites.push_back(sprite); }
	void GirlTalk();
private:
	struct UpdateSprites
	{
		float time;
		UpdateSprites(float t): time(t) {}
		void operator()(Sprite* sprite)
		{
			sprite->Update(time);
		}
	};
	struct RenderSprites
	{
		SDL_Surface *surface;
		RenderSprites(SDL_Surface *s): surface(s) {}
		void operator()(Sprite* sprite)
		{
			sprite->Render(surface);
		}
	};
	struct SetDarkSprites
	{
		bool dark;
		SetDarkSprites(bool d): dark(d) {}
		void operator()(Sprite* sprite)
		{
			if(dark)
				sprite->SetCurrAnim(1);
			else
				sprite->SetCurrAnim(0);
		}
	};
	struct DeleteSprites
	{
		void operator()(Sprite* sprite)
		{
			delete sprite;
		}
	};
	struct UpdateClones
	{
		LARGE_INTEGER liTime;
		float time;
		UpdateClones(float t, LARGE_INTEGER l): time(t), liTime(l) {}
		void operator()(Player *p)
		{
			p->Update(time, liTime);
		}
	};
	struct RenderClones
	{
		void operator()(Player *p)
		{
			p->Render();
		}
	};
	struct ResetClones
	{
		void operator()(Player *p)
		{
			p->ResetPlayback();
			p->SetGhost();
			p->Show();
			p->SetPos(START_X, START_Y);
		}
	};
	struct DeleteClones
	{
		void operator()(Player *p)
		{
			delete p;
		}
	};
};

#endif

