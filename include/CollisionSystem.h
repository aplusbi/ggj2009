#ifndef _H_COLLISIONSYSTEM_
#define _H_COLLISIONSYSTEM_

#include "common.h"
#include "includes.h"
#include "BaseObject.h"
#include "Player.h"

//stores all static objects to interact with and handles collision
//checksmade against them by the player. 
class CollisionSystem
{
	static CollisionSystem m_Instance;


	CollisionSystem(){}
	CollisionSystem(const CollisionSystem& r){}
	CollisionSystem& operator=(const CollisionSystem& r){}
public:
	
	//List of all current objects 
	vector<BaseObject*> m_CollisionList;
	
	//Loads all collision data specified by the Objects.txt file
	void InitCollisionObjects();
	//returns the instance of the class
	static CollisionSystem* getInstance();

	//Registers an object to be handled by the collision system
	void RegisterColObj(BaseObject* obj);

	//a function to act as a "factory", taking in a string 
	//to compare to the type of object we want to create 
	void FakeFactory(float fLeft, float fRight, string sName, string sRoom);

	//Tests to see if the passed in collision obj hit another
	//and return the object it collided with. We should only need to test
	//between the player and existing objects so shouldn't need more than this
	BaseObject* CheckCollision(Player* testObj);
	//this will clean up allocated memory for this system
	void CleanUp();
	BaseObject *FindObj(int type);

};
#endif
