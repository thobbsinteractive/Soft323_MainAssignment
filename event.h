// My input structure that stores my games event data
#ifndef INC_EVENT_H
#define INC_EVENT_H

#include <string>
#include "navPoint.h"

struct Event
{
	bool friendly;
	char type;
	D3DXVECTOR3 location;
	D3DXVECTOR3 rotation;
	std::string objectiveText; // shows for mission critical craft
	bool isPlayersCarrier; 
	bool jumpingIn; // if the ship is jumping in or out of the mission
	bool missionCritical; // depends on IFF, will end the mission good/bad if it dies
	float time;
	std::vector<NavPoint*> navPointsList;
};

#endif // INC_EVENT_H