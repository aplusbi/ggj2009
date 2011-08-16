#include "CollisionSystem.h"
#include "ObjectList.h"
#include "StateTest.h"
CollisionSystem CollisionSystem::m_Instance;

CollisionSystem *CollisionSystem::getInstance()
{
	return &m_Instance;
}

void CollisionSystem::InitCollisionObjects()
{
	ifstream fin;
	fin.open("assets/Objects.txt");
	//successfully loaded the file
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			float left, right;
			string sName;
			string sRoom;
			fin >> left;
			fin >> right;
			fin >> sName;
			fin >> sRoom;
			//register this loaded object into the handler
			FakeFactory(left, right, sName, sRoom);
			//Check if we were the last object to read or not
			fin>> sName;
			if(sName == "#eof")
				break;
		}
	}
	fin.close();
}

BaseObject *CollisionSystem::FindObj(int type)
{
	for(unsigned int i = 0; i < m_CollisionList.size(); i++)
	{
		if(m_CollisionList[i]->m_nType == type)
			return m_CollisionList[i];
	}
	return NULL;
}


//Registers an object to be handled by the collision system
void CollisionSystem::RegisterColObj(BaseObject* obj)
{
	m_CollisionList.push_back(obj);
}

BaseObject* CollisionSystem::CheckCollision(Player* testObj)
{
	for(unsigned int i = 0; i < m_CollisionList.size(); i++)
	{
		//cover all bases
		if( ( testObj->m_ColObj.m_Left >= m_CollisionList[i]->m_ColObj.m_Left &&
			testObj->m_ColObj.m_Left <= m_CollisionList[i]->m_ColObj.m_Right) ||
			( testObj->m_ColObj.m_Right >= m_CollisionList[i]->m_ColObj.m_Left &&
			testObj->m_ColObj.m_Right <= m_CollisionList[i]->m_ColObj.m_Right) ||
			( testObj->m_ColObj.m_Left <=  m_CollisionList[i]->m_ColObj.m_Left &&
			testObj->m_ColObj.m_Right >= m_CollisionList[i]->m_ColObj.m_Right) )
		{
			//if we fall in here there was collision
			//Handle collision on the object we hit
			//m_CollisionList[i]->HandleCollision();
			m_CollisionList[i]->Contact();

			//damnit 
			char hack;
			if(m_CollisionList[i]->m_nRoom == 0)
				hack = 'a';
			else
				hack = 'b';

			char test = StateTest::getInstance()->GetRoom();
			if(test == hack)
				return m_CollisionList[i];//return the object we hit for additional use
		}
	}

	return 0; //found nothing 
}

//our totally bogus factory function but hey, it works right? ( maybe :(  )
void CollisionSystem::FakeFactory(float fLeft, float fRight, string sName, string sRoom)
{

	if(sName == "Door")
	{
	/*	DoorObj* newObj = new DoorObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);*/

	}
	else if(sName == "Outlet1")
	{
		OutletObj1* newObj = new OutletObj1();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_power01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/lamp_unplug_light.png");
		newObj->m_OnSprite->LoadAnimation("assets/overlay.txt");
		newObj->m_OnSprite->SetPos(460.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}
	else if(sName == "Outlet2")
	{		
		OutletObj2* newObj = new OutletObj2();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_power01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/tv_on_light.png");
		newObj->m_OnSprite->LoadAnimation("assets/overlay.txt");
		newObj->m_OnSprite->SetPos(732.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(256, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}
	else if(sName == "Outlet3")
	{		
		OutletObj3* newObj = new OutletObj3();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_power01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/phonographplug_on_light.png");
		newObj->m_OnSprite->LoadAnimation("assets/overlay.txt");
		newObj->m_OnSprite->SetPos(526.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}
	else if(sName == "Outlet4")
	{		
		OutletObj4* newObj = new OutletObj4();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_power01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/toasterplug_on.png");
		newObj->m_OnSprite->SetPos(128.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}
	else if(sName == "Tomato")
	{		
		TomatoObj* newObj = new TomatoObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_tomato01.png");
	}
	else if(sName == "Sink")
	{		
		SinkObj* newObj = new SinkObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_sink01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/sink_on.png");
		newObj->m_OnSprite->SetPos(0.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}
	else if(sName == "Toaster")
	{		
		ToasterObj* newObj = new ToasterObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_toaster01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/toaster_on.png");
		newObj->m_OnSprite->SetPos(128.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}		
	else if(sName == "Drink")
	{		
		DrinkObj* newObj = new DrinkObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_drink01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/drink_on_light.png");
		newObj->m_OnSprite->LoadAnimation("assets/overlay.txt");
		newObj->m_OnSprite->SetPos(310.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}		
	else if(sName == "Clock")
	{		
		ClockObj* newObj = new ClockObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_clock01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/clock_on.png");
		newObj->m_OnSprite->SetPos(86.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}		
	else if(sName == "Lamp")
	{		
		LampObj* newObj = new LampObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_lamp01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/lamp_on.png");
		newObj->m_OnSprite->SetPos(460.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}		
	else if(sName == "Pills")
	{		
		PillsObj* newObj = new PillsObj();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_pills01.png");
		newObj->m_OnSprite = new Sprite();
		newObj->m_OnSprite->LoadImg("assets/pills_on_light.png");
		newObj->m_OnSprite->LoadAnimation("assets/overlay.txt");
		newObj->m_OnSprite->SetPos(676.0f, START_Y);
		newObj->m_OnSprite->Hide();
		newObj->m_OnSprite->SetDimensions(128, 128);
		newObj->m_OnSprite->m_Room = sRoom[0];
		StateTest::getInstance()->AddSprite(newObj->m_OnSprite);
	}		
	else if(sName == "LightSwitch1")
	{		
		LightSwitchObj1* newObj = new LightSwitchObj1();

		if(sRoom == "a")
			newObj->m_nRoom = 0;
		else
			newObj->m_nRoom = 1;
		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = new Sprite();
		newObj->m_Sprite->LoadImg("assets/icon_light01.png");
	}
	else if(sName == "Hallway1")
	{
		HallwayObj1* newObj = new HallwayObj1();

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = NULL;
	}
	else if(sName == "Hallway2")
	{
		HallwayObj2* newObj = new HallwayObj2();

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = NULL;
	}
	else if(sName == "Hallway2")
	{
		HallwayObj2* newObj = new HallwayObj2();

		newObj->setColArea(fLeft, fRight);
		RegisterColObj((BaseObject*)newObj);

		newObj->m_Sprite = NULL;
	}
	
}

//CALL ONLY AT PROGRAM SHUTDOWN
void CollisionSystem::CleanUp()
{
	while(m_CollisionList.size() > 0)
		delete m_CollisionList[m_CollisionList.size()];
}
