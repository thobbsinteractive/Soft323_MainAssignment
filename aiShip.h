#ifndef INC_AISHIP_H
#define INC_AISHIP_H

#include <math.h>
#include "ship.h"
#include "navPoint.h"
#include "Core\DXUT.h"

class AIShip : public Ship
{
public:
	AIShip();
	~AIShip();
	bool getIFF();
	void setIFF(bool _friendly);
	void setCurrentSpeedSetting(float _speed);
	void setTargetShip(Ship* _targetedShip);
	bool getObjectiveStatus();
	void addNavPoint(NavPoint newNavPoint);
	void getNextNavPoint();
	float getObjectiveXPos();
	float getObjectiveYPos();
	float getObjectiveZPos();
	void manovering(float timeDelta);
	void isLaunching(float _time);
	void setAvoiding(bool isAvoiding,float _time,Ship* _targetedShip);
	void setAvoiding(bool isAvoiding);
	bool isCapital();
	void setCapital(bool value);
	bool getHasTarget();
	void getAIFireMatrix(int i,D3DXMATRIX* V,D3DXVECTOR3 playerRotation);

protected:
	void avoid();
	void turn(float timeDelta);
	void avoidTurn(float timeDelta);
	float turnSpeed;

	bool awaitingNewObjective; // IS the ship awaitingNewObjective
	bool friendly; // Is this ship a friendly to the player
	bool turning;
	bool avoiding;
	bool manover;
	bool capital;
	bool hasEnemyTarget;

	Ship* targetedShip;
	Ship* avoidanceShip;
	int currentNavPoint;

	D3DXVECTOR3 objectivePos;

	std::vector<NavPoint*> navPointsList;
	bool launching;
	float timeToLaunchfor;
	float time;

	float timeToAvoidFor;

	bool evading;

};

#endif // INC_AISHIP_H