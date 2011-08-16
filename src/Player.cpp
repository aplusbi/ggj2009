#include <math.h>
#include "SDL.h"
#include "Sprite.h"
#include "Recorder.h"
#include "GameMain.h"
#include "EventHandler.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "SoundManager.h"
#include "StateTest.h"

Player::Player(): m_Sprite(NULL), m_IsGhost(false), m_IsVisible(true), m_x(START_X), m_y(START_Y), m_Vel(80.0f), m_DeleteSprite(false), m_Sound(-1), m_IsPressing(false)
{
	memset(m_Keys, 0, sizeof(Uint8)*KEY_COUNT);
	//m_Recorder = new Recorder;
}

Player::Player(const Player &p): m_Sprite(NULL), m_IsGhost(false), m_IsVisible(true), m_x(START_X), m_y(START_Y), m_Vel(80.0f), m_DeleteSprite(false)
{
	m_Sprite = new Sprite(*p.m_Sprite);
	m_DeleteSprite = true;
	memset(m_Keys, 0, sizeof(Uint8)*KEY_COUNT);
	//m_Recorder = new Recorder;
}

Player::~Player()
{
	if(m_Recorder)
		delete m_Recorder;
	if(m_Sprite && m_DeleteSprite)
		delete m_Sprite;
	//if(m_Text)
		//delete m_Text;
}

bool Player::Update(float time, LARGE_INTEGER liTime)
{
	if(m_IsVisible == false)
		return true;

	//if(!m_IsGhost)
	//{
		const SDL_KeyboardEvent *event = &EventHandler::getInstance()->GetEvent().key;
		HandleInput(*event);
		//m_Recorder->RecordInput(*event, liTime);
	//}
	//else
	//{
		//const SDL_KeyboardEvent *event = m_Recorder->PlayBack(liTime);
		//if(event != NULL)
			//HandleInput(*event);
		//else
		//{
			//m_IsVisible = false;
			//memset(m_Keys, 0, sizeof(Uint8)*KEY_COUNT);
		//}
	//}

	bool dirty = false;
	if(m_Keys[KEY_LEFT])
	{
		dirty = true;
		if((StateTest::getInstance()->GetRoom() != 'b') || (m_x >= -5.0f))
			m_x -= m_Vel * time;
	}
	if(m_Keys[KEY_RIGHT])
	{
		dirty = true;
		if((StateTest::getInstance()->GetRoom() != 'a') || (m_x <= 900.0f))
			m_x += m_Vel * time;
	}

	if(dirty && m_Sound == -1)
	{
		m_Sound = SoundManager::getInstance()->PlaySnd(SFX_WALK, -1);
	}
	if(!dirty && m_Sound != -1)
	{
		SoundManager::getInstance()->HaltSound(m_Sound);
		m_Sound = -1;
	}

	m_Sprite->SetPos(m_x, m_y);
	m_ColObj.m_Left = m_x + 50;
	m_ColObj.m_Right = m_x + 76;
	m_CurObj = CollisionSystem::getInstance()->CheckCollision(this);

	m_Sprite->Update(time);
	return true;
}

bool Player::Render()
{
	SDL_Surface *dest = GameMain::getInstance()->getSurface();

	if(m_CurObj != NULL && m_CurObj->m_Sprite != NULL)
	{
		m_CurObj->m_Sprite->SetPos(450, 192);
		m_CurObj->m_Sprite->Render(dest);
	}

	if(m_IsVisible)
		m_Sprite->Render(dest);


	return true;
}
void Player::ResetPlayback()
{
	m_Recorder->ResetPlayback();
}

void Player::HandleInput(const SDL_KeyboardEvent &event)
{
	Uint8 mask = event.type == SDL_KEYDOWN?1:0;
	switch(event.keysym.sym)
	{
		case SDLK_LEFT:
			if(!mask)
				m_Sprite->SetCurrAnim(0);
			else
				m_Sprite->SetCurrAnim(1);
			m_Keys[KEY_LEFT] = mask;
			break;
		case SDLK_RIGHT:
			if(!mask)
				m_Sprite->SetCurrAnim(0);
			else
				m_Sprite->SetCurrAnim(2);
			m_Keys[KEY_RIGHT] = mask;
			break;
		case SDLK_SPACE:
			if(m_CurObj != NULL && !mask && m_IsPressing)
				m_CurObj->HandleCollision();//activate whatever this object does
			break;
		default:
			break;
	}
	if(mask)
		m_IsPressing = true;
	else
		m_IsPressing = false;
}

