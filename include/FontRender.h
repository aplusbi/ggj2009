#ifndef FONTRENDER_H
#define FONTRENDER_H

#include "TextObject.h"
#include "GameMain.h"
#include <list>
#include <algorithm>

class FontRender
{
	static FontRender m_Instance;
	FontRender(){}
	FontRender(const FontRender &){}
	void operator=(const FontRender &){}

	struct Data
	{
		Data(TextObject *o, float t, bool b): text(o), time(t), d(b) {}
		TextObject *text;
		float time;
		bool d;
	};
	std::list<Data> m_Stuff;
public:
	static FontRender *getInstance() { return &m_Instance; }

	void AddText(TextObject *obj, float time, bool delete_it);
	void Update(float t);
	void Render();
private:
	struct RenderStuff
	{
		void operator()(Data stuff)
		{
 			stuff.text->Render(GameMain::getInstance()->getSurface());
		}
	};
	struct DeleteStuff
	{
		void operator()(Data stuff)
		{
			if(stuff.d)
				delete stuff.text;
		}
	};
};

#endif

