#include "Sprite.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"
#include "StateTest.h"
#include <stdlib.h>
#include <fstream>

Sprite::Sprite(): m_Surface(NULL), m_CurrAnimation(0), m_IsClone(false), m_Time(0.0f), m_IsHidden(false), m_Room('\0')
{
	memset(&m_Rect, 0, sizeof(m_Rect));
}

Sprite::Sprite(const Sprite &sprite)
{
	m_Surface = sprite.m_Surface;
	m_Animations = sprite.m_Animations;
	m_CurrAnimation = sprite.m_CurrAnimation;
	m_Rect = sprite.m_Rect;
	m_IsClone = true;
}

Sprite::~Sprite()
{
	if(m_Surface && !m_IsClone)
		SDL_FreeSurface(m_Surface);

	m_Animations.clear();
}

bool Sprite::Update(float fElapsedTime)
{
	m_Time += fElapsedTime;
	while(m_CurrAnimation < m_Animations.size() && m_Time > m_Animations[m_CurrAnimation].rate)
	{
		m_Time -= m_Animations[m_CurrAnimation].rate;
		m_Animations[m_CurrAnimation].frame++;
	}
	return true;
}

bool Sprite::Render(SDL_Surface *target)
{
	if(m_IsHidden || (m_Room != '\0' && m_Room != StateTest::getInstance()->GetRoom()))
		return true;

	SDL_Rect frameRect, destRect;
	int frameNum;
	frameNum = m_CurrAnimation>=m_Animations.size()?0:m_Animations[m_CurrAnimation].GetFrame();
	//frameNum = 0;

	// set up the source rectangle to include only the current frame
	frameRect.x = m_Rect.w * frameNum;
	frameRect.y = 0;
	frameRect.w = m_Rect.w;
	frameRect.h = m_Rect.h;

	// set up the destination rectangle
	destRect.x = int(m_x);
	destRect.y = int(m_y);
	destRect.w = m_Rect.w;
	destRect.h = m_Rect.h;

	if(SDL_BlitSurface(m_Surface, &frameRect, target, &destRect)!=0)
		return false;
	return true;
}

bool Sprite::LoadImg(const char * const file)
{
	if(m_Surface != NULL)
		SDL_FreeSurface(m_Surface);

	SDL_Surface *temp = IMG_Load(file);	
	m_Surface = rotozoomSurface(temp, 0.0f, 2.0f, 0);
	SDL_FreeSurface(temp);
	SDL_SetColorKey(m_Surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(m_Surface->format, 255, 0, 255));

	// this should probably not stay this way
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = m_Surface->w;
	m_Rect.h = m_Surface->h;

	m_IsClone = false;

	return true;
}

bool Sprite::LoadAnimation(const char * const file)
{
	m_Animations.clear();
	std::ifstream in(file, std::ifstream::in);
	while(!in.eof())
	{
		int amount;
		in >> amount;
		if(in.eof())
			break;
		Anim newAnim;
		newAnim.frame = 0;
		newAnim.animation.resize(amount);
		for(int i=0; i<amount; ++i)
		{
			int element;
			in >> element;
			newAnim.animation[i] = element;
		}
		m_Animations.push_back(newAnim);
	}
	in.close();

	return true;
}

void Sprite::SetPos(double x, double y)
{
	m_x = x;
	m_y = y;
}

