#include "FontRender.h"

FontRender FontRender::m_Instance;

void FontRender::AddText(TextObject *obj, float time, bool d)
{
	m_Stuff.push_back(Data(obj, time, d));
}

void FontRender::Update(float time)
{
	std::list<Data>::iterator beg, end;
	beg = m_Stuff.begin();
	end = m_Stuff.end();

	while(beg != end)
	{
 		beg->time -= time;
		if(beg->time < 0)
		{
			std::list<Data>::iterator temp;
			temp = beg;
			++beg;
			if(temp->d)
				delete temp->text;
			m_Stuff.erase(temp);
		}
		else
			++beg;
	}
}

void FontRender::Render()
{
	std::for_each(m_Stuff.begin(), m_Stuff.end(), RenderStuff());
}

