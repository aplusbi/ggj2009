#include "COMMON.h"
#include "SDL.h"
#include "GameMain.h"
#include "StateTest.h"
#include "SoundManager.h"

StateTest StateTest::m_Instance;

StateTest::StateTest(): m_IsRecording(true)
{
}

StateTest *StateTest::getInstance()
{
	return &m_Instance;
}

void StateTest::Enter()
{
	m_State = NONE;
	m_Room = 'a';
	m_IsDark = false;
	Sprite *sprite = new Sprite;
	sprite->LoadImg("assets/environment_a.png");
	sprite->SetPos(0.0f, START_Y);
	m_RoomSprite = sprite;

	m_Character = new Player;
	sprite = new Sprite;
	sprite->LoadImg("assets/animations/character_all.png");
	sprite->LoadAnimation("assets/animations/character_anim.txt");
	sprite->SetPos(START_X, START_Y);
	sprite->SetDimensions(128, 128);
	m_Character->SetSprite(sprite, true);
	m_Clones.push_back(m_Character);
	SoundManager::getInstance()->PlayMusic();

	sprite = new Sprite;
	sprite->LoadImg("assets/animations/woman_all.png");
	sprite->LoadAnimation("assets/animations/woman_anim.txt");
	sprite->SetDimensions(128, 128);
	sprite->SetPos(416.0f, START_Y);
	sprite->m_Room = 'b';
	m_Sprites.push_back(sprite);
	m_Girl = sprite;
	m_GirlRight = true;
	m_GirlTalk = 0.0f;
}

bool StateTest::Update( float fElapsedTime, LARGE_INTEGER liTime )
{
	m_RoomSprite->Update(fElapsedTime);
	m_GirlTalk -=fElapsedTime;
	if(m_GirlTalk < 0.0f)
	{
		if(m_GirlRight)
			m_Girl->SetCurrAnim(0);
		else
			m_Girl->SetCurrAnim(2);
	}

	m_GirlRight = true;
	if(m_Character->GetX() < 416.0f)
		m_GirlRight = false;
	std::for_each(m_Sprites.begin(), m_Sprites.end(), UpdateSprites(fElapsedTime));
	std::for_each(m_Clones.begin(), m_Clones.end(), UpdateClones(fElapsedTime, liTime));
	return true;
}

bool StateTest::Render()
{
	SDL_Surface *surface = GameMain::getInstance()->getSurface(); 
	m_RoomSprite->Render(surface);
	std::for_each(m_Sprites.begin(), m_Sprites.end(), RenderSprites(surface));
	std::for_each(m_Clones.begin(), m_Clones.end(), RenderClones());
	return true;
}

void StateTest::Exit()
{
	delete m_RoomSprite;
	std::for_each(m_Sprites.begin(), m_Sprites.end(), DeleteSprites());
	std::for_each(m_Clones.begin(), m_Clones.end(), DeleteClones());
	m_Clones.clear();
}

void StateTest::HandleInput(SDL_KeyboardEvent keyPress)
{
	if(keyPress.type == SDL_KEYDOWN && keyPress.keysym.sym == SDLK_r)
	{
		TimeTravel();
	}
}

void StateTest::SetRoom(char room)
{
	if(m_Room != room)
	{
		m_Room = room;
		char room_name[256];
		if(m_IsDark)
			sprintf(room_name, "assets/environment_%c_dark.png", m_Room);
		else
			sprintf(room_name, "assets/environment_%c.png", m_Room);
		m_RoomSprite->LoadImg(room_name);
		if(m_Room == 'a')
			m_Character->SetPos(ROOM_A_X, START_Y);
		else
			m_Character->SetPos(ROOM_B_X, START_Y);
	}
}

void StateTest::SetRoomDark(bool dark)
{
	if(m_IsDark != dark)
	{
		m_IsDark = dark;
		char room_name[256];
		if(m_IsDark)
			sprintf(room_name, "assets/environment_%c_dark.png", m_Room);
		else
			sprintf(room_name, "assets/environment_%c.png", m_Room);
		m_RoomSprite->LoadImg(room_name);
		std::for_each(m_Sprites.begin(), m_Sprites.end(), SetDarkSprites(m_IsDark));
	}
}

void StateTest::TimeTravel()
{
	//m_Character = new Player(*m_Clones.back());
	//std::for_each(m_Clones.begin(), m_Clones.end(), ResetClones());
	//m_Clones.push_back(m_Character);
}

void StateTest::GirlTalk()
{
	if(m_GirlRight)
		m_Girl->SetCurrAnim(1);
	else
		m_Girl->SetCurrAnim(3);
	m_GirlTalk = 3.0f;
}

