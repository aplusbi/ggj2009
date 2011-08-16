//ObjectList.h
//This will probably end up becoming sloppy looking but its 
//quick and dirty all the way today 
#ifndef _H_OBJECTLIST_H
#define _H_OBJECTLIST_H

#include "BaseObject.h"
#include "includes.h"
#include "StateTest.h"
#include "SoundManager.h"
#include "FontRender.h"

//test object representing what we can make 
class InteractiveObj : public BaseObject
{
	//name of the object ( possibly for text feedback later )
	string m_sName;
	//Possibly throw in the attached sprite object here?
public:
	//
	InteractiveObj(): m_sName("DefaultName")  {m_bActive =false;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//
	void setName(string sName){ m_sName = sName; }
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		//do stuff here 
		m_bActive = !m_bActive;
	}
};
/////////////////////////////////////////////////////////////////
// FIND : DOOR
/////////////////////////////////////////////////////////////////
class DoorObj : public BaseObject
{
	string m_sName;
public:
	DoorObj(): m_sName("Door")  {m_bActive =false; m_nType = OBJ_DOOR;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		//this will increment everytime we toggle this object 
		//how awesome is that? very!
		m_Count++;
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
			m_Sprite->LoadImg("assets/icon_door01_on.png");
		else
			m_Sprite->LoadImg("assets/icon_door01.png");
	}
};
/////////////////////////////////////////////////////////////////
// FIND : OUTLET1
/////////////////////////////////////////////////////////////////
class OutletObj1 : public BaseObject
{
	string m_sName;
public:
	OutletObj1(): m_sName("Outlet1")  {m_bActive =false; m_nType = OBJ_OUTLET1;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 3)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("What are you doing in there?");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			SM->PlaySnd(SFX_UNPLUG);
			m_OnSprite->Show();
			m_Sprite->LoadImg("assets/icon_power01_on.png");
			BaseObject *obj = CollisionSystem::getInstance()->FindObj(OBJ_LAMP);
			if(obj != NULL)
				obj->m_OnSprite->Show();
		}
		else
		{
			SM->PlaySnd(SFX_UNPLUG);
			m_OnSprite->Hide();
			m_Sprite->LoadImg("assets/icon_power01.png");
			BaseObject *obj = CollisionSystem::getInstance()->FindObj(OBJ_LAMP);
			if(obj != NULL)
				obj->m_OnSprite->Hide();
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : OUTLET2
/////////////////////////////////////////////////////////////////
class OutletObj2 : public BaseObject
{
	string m_sName;
public:
	OutletObj2(): m_sName("Outlet2")  {m_bActive =false; m_nType = OBJ_OUTLET2;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;

		if(m_Count == 1)
		{
			//"Hey I was watching Friends!"
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_power01_on.png");
			m_OnSprite->Show();
			SM->PlaySnd(SFX_TV);
		}
		else
		{
			m_Sprite->LoadImg("assets/icon_power01.png");
			m_OnSprite->Hide();
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : OUTLET3
/////////////////////////////////////////////////////////////////
class OutletObj3 : public BaseObject
{
	string m_sName;
public:
	OutletObj3(): m_sName("Outlet3")  {m_bActive =false; m_nType = OBJ_OUTLET3;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 1)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Hey! I was listening to that!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		if(m_Count == 2)
		{
			SM->PlaySnd(SFX_UNPLUG);
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("...Thanks");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 1, true);
		//	"Thank you"
		}
		if(m_Count == 3)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Jerk!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		if(m_Count == 10)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("What the heck has gotten into you?...");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_power01_on.png");
			SoundManager::getInstance()->PauseMusic();
			m_OnSprite->Show();
			SM->PlaySnd(SFX_UNPLUG);
		}
		else
		{
			m_Sprite->LoadImg("assets/icon_power01.png");
			SoundManager::getInstance()->ResumeMusic();
			m_OnSprite->Hide();
			SM->PlaySnd(SFX_UNPLUG);
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : OUTLET4
/////////////////////////////////////////////////////////////////
class OutletObj4 : public BaseObject
{
	string m_sName;
public:
	OutletObj4(): m_sName("Outlet4")  {m_bActive =false; m_nType = OBJ_OUTLET4;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;


		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_OnSprite->Show();
			m_Sprite->LoadImg("assets/icon_power01_on.png");
			SM->PlaySnd(SFX_UNPLUG);
		}
		else
		{
			m_OnSprite->Hide();
			m_Sprite->LoadImg("assets/icon_power01.png");
			SM->PlaySnd(SFX_UNPLUG);
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : TOMATO
/////////////////////////////////////////////////////////////////
class TomatoObj : public BaseObject
{
	string m_sName;
public:
	TomatoObj(): m_sName("Tomato")  {m_bActive =false; m_nType = OBJ_TOMATO;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count > 0)
		{
				TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("* A tomato, nothing more. *");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		//if(m_bActive)
			//m_Sprite->LoadImg("assets/icon_tomato01_on.png");
		//else
			//m_Sprite->LoadImg("assets/icon_tomato01.png");
	}
};
/////////////////////////////////////////////////////////////////
// FIND : SINK
/////////////////////////////////////////////////////////////////
class SinkObj : public BaseObject
{
	string m_sName;
public:
	SinkObj(): m_sName("Sink")  {m_bActive =false; m_nType = OBJ_SINK;}
	int Channel;
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 1)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("That thing does nothing but pour rust out.");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		if(m_Count == 10)
		{		
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("You're gonna flood the damn sink!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_OnSprite->Show();
			m_Sprite->LoadImg("assets/icon_sink01_on.png");
			Channel = SM->PlaySnd(SFX_SINK, -1);
		}
		else
		{
			m_OnSprite->Hide();
			m_Sprite->LoadImg("assets/icon_sink01.png");
			SM->HaltSound(Channel);
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : TOASTER
/////////////////////////////////////////////////////////////////
class ToasterObj : public BaseObject
{
	string m_sName;
public:
	ToasterObj(): m_sName("Toaster")  {m_bActive =false; m_nType = OBJ_TOASTER;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if( m_Count == 1)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Its already broken thanks to you");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		//	"Maybe if you didn't mess with that so much it wouldn't be broken"
		}
		else if(m_Count == 5)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("You really have no life do you?");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_OnSprite->Show();
			m_Sprite->LoadImg("assets/icon_toaster01_on.png");
			SM->PlaySnd(SFX_TOASTER);
		}
		else
		{
			m_OnSprite->Hide();
			m_Sprite->LoadImg("assets/icon_toaster01.png");
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : DRINK
/////////////////////////////////////////////////////////////////
class DrinkObj : public BaseObject
{
	string m_sName;
public:
	DrinkObj(): m_sName("Drink")  {m_bActive =false; m_nType = OBJ_DRINK;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 1)
		{	
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Gross! That juice had mold floating in it!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = true;
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_drink01_on.png");
			m_OnSprite->Show();
			SM->PlaySnd(SFX_DRINK);
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : CLOCK
/////////////////////////////////////////////////////////////////
class ClockObj : public BaseObject
{
	string m_sName;
public:
	ClockObj(): m_sName("Clock")  {m_bActive =false; m_nType = OBJ_CLOCK;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 3)
		{	
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("You're gonna break it!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		//	"You're gonna break my Dad's clock!"
		}
		else if(m_Count == 5)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Can you please just stop!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_clock01_on.png");
			m_OnSprite->Show();
			SM->PlaySnd(SFX_CLOCK);
		}
		else
		{
			m_Sprite->LoadImg("assets/icon_clock01.png");
			m_OnSprite->Hide();
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : LAMP
/////////////////////////////////////////////////////////////////
class LampObj : public BaseObject
{
	string m_sName;
public:
	LampObj(): m_sName("Lamp")  {m_bActive =false; m_nType = OBJ_LAMP;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 1)
		{	
			
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_lamp01_on.png");
			m_OnSprite->Show();
			SM->PlaySnd(SFX_LAMP);
		}
		else
		{
			m_Sprite->LoadImg("assets/icon_lamp01.png");
			m_OnSprite->Hide();
			SM->PlaySnd(SFX_LAMP);
		}


	}
};
/////////////////////////////////////////////////////////////////
// FIND : PILLS
/////////////////////////////////////////////////////////////////
class PillsObj : public BaseObject
{
	string m_sName;
public:
	PillsObj(): m_sName("Pills")  {m_bActive =false; m_nType = OBJ_PILLS;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;

		if(m_Count == 1)
		{	
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Thats my medication!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
			//FontRender::getInstance()->AddText(textObj,5 , true);
		}
		if(m_Count == 3)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Go ahead and kill yourself than!");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		if(m_bActive)
		{
			m_OnSprite->Show();
			m_Sprite->LoadImg("assets/icon_pills01_on.png");
			SM->PlaySnd(SFX_PILLS);
		}
		else
		{
			m_OnSprite->Hide();
			m_Sprite->LoadImg("assets/icon_pills01.png");
		}
	}
};
/////////////////////////////////////////////////////////////////
// FIND : LIGHTSWITCH1
/////////////////////////////////////////////////////////////////
class LightSwitchObj1 : public BaseObject
{
	string m_sName;
public:
	LightSwitchObj1(): m_sName("LightSwitch1")  {m_bActive =false; m_nType = OBJ_LIGHTSWITCH1;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		m_Count++;
		if(m_Count == 10)
		{	
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Thats getting annoying");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
			//FontRender::getInstance()->AddText(textObj,5 , true);
		}
		else if(m_Count == 20)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("Seriously... stop");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		else if(m_Count == 50)
		{
			TextObject* textObj = new TextObject("assets/fonts/arial.ttf", 24);
			textObj->SetText("You have no life at all do you?");
			textObj->SetPos(200, 500);
			textObj->SetColor(76, 48, 64);
			FontRender::getInstance()->AddText(textObj, 3, true);
		}
		//do stuff here 
		m_bActive = !m_bActive;
		StateTest::getInstance()->SetRoomDark(m_bActive);
		if(m_bActive)
		{
			m_Sprite->LoadImg("assets/icon_light01_on.png");
			SM->PlaySnd(SFX_TV);
		}
		else
		{
			m_Sprite->LoadImg("assets/icon_light01.png");
			SM->PlaySnd(SFX_TV);
		}
	}
};

/////////////////////////////////////////////////////////////////
// FIND : HALLWAY1
/////////////////////////////////////////////////////////////////
class HallwayObj1 : public BaseObject
{
	string m_sName;
public:
	HallwayObj1(): m_sName("Hallway1")  {m_bActive =false; m_nType = OBJ_HALLWAY1;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		//do stuff here 
		m_bActive = !m_bActive;
	}
	void Contact()
	{
		StateTest::getInstance()->SetRoom('b');
	}
};

/////////////////////////////////////////////////////////////////
// FIND : HALLWAY2
/////////////////////////////////////////////////////////////////
class HallwayObj2 : public BaseObject
{
	string m_sName;
public:
	HallwayObj2(): m_sName("Hallway2")  {m_bActive =false; m_nType = OBJ_HALLWAY2;}
	//Set the col area of this object 
	void setColArea(float left, float right){ 	
		m_ColObj.m_Left = left;
		m_ColObj.m_Right = right;}
	//return if we are active or not
	bool getActive(){ return m_bActive; }
	//what do we do if we were collided with?
	void HandleCollision()
	{
		//do stuff here 
		m_bActive = !m_bActive;
	}
	void Contact()
	{
		StateTest::getInstance()->SetRoom('a');
	}
};

//Declare new objects HERE


#endif

