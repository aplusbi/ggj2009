#include "TextObject.h"

TextObject::TextObject(const char * const file, int size): m_Surface(NULL), m_IsDirty(false), m_x(0.0f), m_y(0.0f)
{
	m_Font = TTF_OpenFont(file, size);
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;
}

TextObject::~TextObject()
{
	TTF_CloseFont(m_Font);
	if(m_Surface)
		SDL_FreeSurface(m_Surface);
}

void TextObject::SetText(const std::string &text)
{
	m_Text = text;
	m_IsDirty = true;
}

void TextObject::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_Color.r = r;
	m_Color.b = b;
	m_Color.g = g;
	m_IsDirty = true;
}

void TextObject::SetPos(float x, float y)
{
	m_x = x;
	m_y = y;
}

bool TextObject::Render(SDL_Surface *target)
{
	if(m_IsDirty)
	{
		if(m_Surface)
			SDL_FreeSurface(m_Surface);
		m_Surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
		m_IsDirty = false;
	}
	SDL_Rect destRect = {int(m_x), int(m_y), m_Surface->w, m_Surface->h};
	SDL_Rect srcRect = {0, 0, m_Surface->w, m_Surface->h};
	if(m_Surface)
		SDL_BlitSurface(m_Surface, &srcRect, target, &destRect);
	return true;
}

