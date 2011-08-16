#ifndef SPRITE_H
#define SPRITE_H

#include "Object.h"
#include "SDL.h"
#include <vector>

class Sprite: public Object
{
public:
	Sprite();
	Sprite(const Sprite &sprite);
	virtual ~Sprite();

	virtual bool Update(float fElapsedTime);
	virtual bool Render(SDL_Surface *target);

	bool LoadImg(const char * const file);
	bool LoadAnimation(const char * const file);
	void SetPos(double x, double y);
	void SetCurrAnim(int anim) { m_CurrAnimation = anim; }
	void SetDimensions(int w, int h) { m_Rect.w = w; m_Rect.h = h; }
	double GetX() { return m_x; }
	double GetY() { return m_y; }
	void Hide() { m_IsHidden = true; }
	void Show() { m_IsHidden = false; }
	char m_Room;
protected:
	struct Anim
	{
		Anim(): rate(0.1f), frame(0) {}
		float rate;
		int frame;
		std::vector<int> animation;
		int &operator[](int index)
		{
			if(index > animation.size())
				index = 0;
			return animation[index];
		}
		int GetFrame()
		{
			if(frame >= animation.size())
				frame = 0;
			return animation[frame];
		}
	};

	SDL_Surface* m_Surface;
	std::vector<Anim> m_Animations;
	int m_CurrAnimation;
	SDL_Rect m_Rect;
	bool m_IsClone;
	bool m_IsHidden;
	float m_Time;
};

#endif

