#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "COMMON.h"
#include "TextObject.h"
#include <windows.h>
#include "BaseObject.h"
class Sprite;
class Recorder;

class Player
{
public:
	Player();
	Player(const Player &p);
	~Player();

	bool Update(float time, LARGE_INTEGER liTime);
	bool Render();

	void ResetPlayback();

	void SetSprite(Sprite *sprite, bool delete_it = false) { m_Sprite = sprite; m_DeleteSprite = delete_it; }
	void SetGhost() { m_IsGhost = true; }
	void Show() { m_IsVisible = true; }
	void Hide() { m_IsVisible = false; }
	void SetPos(float x, float y) {m_x = x; m_y = y; }
	float GetX() { return m_x; }

	tColObj m_ColObj;
private:
	BaseObject* m_CurObj; //the object we are currently intersecting with
	enum { KEY_LEFT, KEY_RIGHT, KEY_COUNT };
	Sprite *m_Sprite;
	Recorder *m_Recorder;
	TextObject *m_Text;
	bool m_IsGhost, m_IsVisible, m_DeleteSprite;
	int m_Sound;
	float m_x, m_y, m_Vel;
	Uint8 m_Keys[KEY_COUNT];
	bool m_IsPressing;
	
	void HandleInput(const SDL_KeyboardEvent &event);
};

#endif

