#pragma once
//include to player structs
#include "Player.h"
//include to team structs
#include "Team.h"

typedef struct headType
{
	struct teamType* teamlist;
	struct PlayerNode* playerlist;
}headder,*headderPtr;

