#ifndef OBJECT_H
#define OBJECT_H

struct SDL_Surface;

class Object
{
public:
	Object(): m_x(0.0f), m_y(0.0f), m_z(0.0) {}
	virtual bool Update(float fElapsedTime) = 0;
	virtual bool Render(SDL_Surface *target) = 0;
protected:
	double m_x, m_y, m_z;
};

#endif

