//////////////////////////////////////////////////////////////////////////////////////////////////
// ship.h
// Author: Tim Hobbs
// Description: Models the ships position and gunfire
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "objectTransform.h"
#include "fire.h"
#include <math.h>

class Ship : public objectTransform
{
public:
	Ship();
	Ship(float _health,D3DXVECTOR3 _pos, 
			D3DXVECTOR3 _rotation, 
			D3DXVECTOR3 _look);
	~Ship();

	void setHealth(float _health);
	float getHealth();
	void decreaseHealth(float amountToDecrease);
	void getFireMatrix(int i,D3DXMATRIX* V);
	void getFirePosition(int index,D3DXVECTOR3* firePos);
	void setFireHealth(int index, float _health);
	int getNumberofFireBalls();
	void getScale(D3DXVECTOR3* _scale);
	void walk(float units,bool keypress);
	void getMatrix(D3DXMATRIX* V);
	float getCurrentSpeedSetting();
	float getCurrentSpeed();
	void yaw(float angle); 
	void shoot();
	void update(float timeDelta);
	void setSpeed(float _speed);
	void setTargeted();
	bool getTargeted();
	float getAngleToRotate(float* x,float* y,float* z,Ship* object);
	float getAngleOfCurrentObjective();
	void setTargetPosition(D3DXVECTOR3 _targetpos);

protected:
	void updateFire(float timeDelta);

	float health;
	D3DXVECTOR3 targetpos;
	std::vector<fire> fireBalls;
	bool beingTargeted;
	float speed;
	float currentSpeedSetting;
	float speedMax;
	float accelerationRate;
	float fireRate;
	float timeTillFire;

	float angleOfCurrentObjective;
};

#endif //INC_SHIP_H