//COMMON.h
//This will be used for globals that need to be shared across apps ( defines, enums, const globals etc. )
#ifndef _COMMON_H 
#define _COMMON_H

//Sounds enum types
enum eSound{ SFX_WALK, SFX_CLOCK, SFX_DRINK, SFX_LAMP, SFX_PILLS, SFX_SINK, SFX_TV, SFX_UNPLUG, SFX_TOASTER, SFX_COUNT };
//Collision object types
enum eColObjs { OBJ_DOOR, OBJ_OUTLET1, OBJ_OUTLET2, OBJ_OUTLET3, OBJ_OUTLET4, OBJ_TOMATO,
			    OBJ_SINK, OBJ_TOASTER, OBJ_DRINK, OBJ_CLOCK, OBJ_LAMP, OBJ_PILLS,
				OBJ_LIGHTSWITCH1, OBJ_LIGHTSWITCH2, OBJ_HALLWAY1, OBJ_HALLWAY2};

const float START_X = 822.0f;
const float START_Y = 320.0f;
const float ROOM_A_X = 0.0f;
const float ROOM_B_X = 900.0f;

struct tColObj
{
	//the left and right bounds of this area 
	float m_Left, m_Right;
};

#endif
