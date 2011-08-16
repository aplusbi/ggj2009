#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "SDL_ttf.h"
#include <string>

class TextObject
{
public:
	TextObject(const char * const file, int size);
	~TextObject();

	void SetText(const std::string &text);
	void SetPos(float x, float y);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	bool Render(SDL_Surface *target);
private:
	std::string m_Text;
	TTF_Font *m_Font;
	SDL_Surface *m_Surface;
	SDL_Color m_Color;
	float m_x, m_y;
	bool m_IsDirty;
};

#endif

