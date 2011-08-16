#ifndef _H_BASEOBJECT
#define _H_BASEOBJECT

//An abstract class that all objects will derive from 
#include "common.h"
#include "sprite.h"
#include "TextObject.h"

class BaseObject
{
public:
	int m_Count;
	//the enum value assigned to this object
	//Is this object activated or not?
	bool m_bActive;
	int m_nType;
	//the sprite image associated with this 
	Sprite *m_Sprite;
	Sprite *m_OnSprite;
	//the room this object is in
	int m_nRoom;
	//The active area this object resides in ( public for laziness )
	tColObj m_ColObj; 
	//Text that will be said upon triggering an action
	TextObject* m_Text;

	BaseObject(): m_Sprite(NULL), m_Count(0), m_OnSprite(NULL) {}
	virtual ~BaseObject(){}

	virtual void HandleCollision() = 0;
	virtual void Contact() {}
};

#endif
