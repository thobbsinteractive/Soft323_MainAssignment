#ifndef INC_AISHIP_H
#define INC_AISHIP_H

#include "ship.h"
#include "navPoint.h"

class AIShip : public Ship
{
public:
	AIShip();
	~AIShip();
	void behavior(float units); //units consists of timedelta * 8.0f
	bool getIFF();
	void setIFF(bool _friendly);
	void setCurrentSpeedSetting(float _speed);
	void setTargetShip(int _targetShipIndex);
	bool getObjectiveStatus();
	void addNavPoint(NavPoint newNavPoint);
	void getNextNavPoint();
	float getObjectiveXPos();
	float getObjectiveYPos();
	float getObjectiveZPos();
	void turn(float timeDelta);

private:
	void avoid();
	void manovering();

	bool awaitingNewObjective; // IS the ship awaitingNewObjective
	bool friendly; // Is this ship a friendly to the player
	bool turning;
	bool avoiding;
	bool manover;

	int targetShipIndex;
	int currentNavPoint;
	int totalNumberOfNavPoints;

	D3DXVECTOR3 objectivePos;
	std::vector<NavPoint*> navPointsList;

};

#endif // INC_AISHIP_H