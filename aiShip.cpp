#include "aiShip.h"

AIShip::AIShip()
{
	health = 100.0f;
	friendly = true;
	turning = false;
	avoiding  = false;
	manover  = false;
	awaitingNewObjective = true;
	currentNavPoint = 0;

	objectivePos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	fOrientation = 0;
	launching = false;
	time = 0.0f;
	capital = false;
	turnSpeed = 2.0f;
	timeToLaunchfor = 0.0f;
	hasEnemyTarget = false;

	timeToAvoidFor = 0.0f;
}

AIShip::~AIShip()
{
	for(int i = 0; i < (int)navPointsList.size(); i++)
	{
		navPointsList.erase(navPointsList.begin() + i);
	}
}

void AIShip::setCapital(bool value)
{
	capital=value;
	// we want captial ships to be slower
	if(value == true)
	{
		speedMax = 10.0f;
		health = 200.0f;
		//health = 20.0f;
	}
}

void AIShip::getAIFireMatrix(int i,D3DXMATRIX* V,D3DXVECTOR3 playerRotation)
{
	fireBalls[i].getMatrix(&*V,playerRotation);
}

void AIShip::setTargetShip(Ship* _targetedShip)
{
	targetedShip = _targetedShip;
	hasEnemyTarget = true;
}

bool AIShip::getHasTarget()
{
	return hasEnemyTarget;
}

void AIShip::isLaunching(float _time)
{
	timeToLaunchfor = time;
	launching = true;
}

bool AIShip::getIFF()
{
	return friendly;
}

bool AIShip::isCapital()
{
	return capital;
}

void AIShip::setIFF(bool _friendly)
{
	friendly = _friendly;
}

void AIShip::setCurrentSpeedSetting(float _speed)
{
	if(_speed < speedMax)
	{
		currentSpeedSetting = _speed;
	}else
	{
		currentSpeedSetting = speedMax;
	}
}

float AIShip::getObjectiveXPos()
{
	return objectivePos.x;
}

float AIShip::getObjectiveYPos()
{
	return objectivePos.y;
}

float AIShip::getObjectiveZPos()
{
	return objectivePos.z;
}

void AIShip::addNavPoint(NavPoint newNavPoint)
{
	NavPoint* tempNav = new NavPoint();
	tempNav->location = newNavPoint.location;
	navPointsList.push_back(tempNav);
}

bool AIShip::getObjectiveStatus()
{
	return awaitingNewObjective;
}

void AIShip::getNextNavPoint()
{
	if((int)navPointsList.size() > 0)
	{
		if((int)navPointsList.size() == currentNavPoint)
		{
			currentNavPoint =0;	
		}

		targetPos = navPointsList[currentNavPoint]->location; // Get navpoints location

		currentNavPoint++;
	}
}

void AIShip::setAvoiding(bool isAvoiding,float _time,Ship* _targetedShip)
{
	avoiding = isAvoiding;
	avoidanceShip = _targetedShip;
	timeToAvoidFor = _time;
}

void AIShip::setAvoiding(bool isAvoiding)
{
	avoiding = isAvoiding;
}

// turn away from target
void AIShip::avoidTurn(float timeDelta)
{
	float x = 0.0f;
	float y = 0.0f;
	float yawAmount = 0.0f;
	float pitchAmount = 0.0f;
	float difference = 0.0f;
	D3DXVECTOR3 posToAvoid;
	avoidanceShip->getPosition(&posToAvoid);

	getAngleToAvoid(&x,&y,posToAvoid);

	if(x > rotation.x)
	{
		difference = x - rotation.x;

		if(difference > (1*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				yawAmount = turnSpeed * timeDelta;
			}else
			{
				yawAmount = -turnSpeed * timeDelta;
			}
		}
	}

	if(x < rotation.x)
	{
		difference = rotation.x - x;
		
		if(difference > (1*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				yawAmount = -turnSpeed * timeDelta;
			}else
			{
				yawAmount = turnSpeed * timeDelta;
			}
		}
	}


	if(y > rotation.y)
	{
		difference = y - rotation.y;

		if(difference > (1*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				pitchAmount = turnSpeed * timeDelta;
			}else
			{
				pitchAmount = -turnSpeed * timeDelta;
			}
		}
	}

	if(y < rotation.y)
	{
		difference = rotation.y - y;
		
		if(difference > (1*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				pitchAmount = -turnSpeed * timeDelta;
			}else
			{
				pitchAmount = turnSpeed * timeDelta;
			}
		}
	}

	yaw(yawAmount);
	pitch(pitchAmount);
}

void AIShip::manovering(float timeDelta)
{

	// First Priority is to avoid
	if((avoiding == true)||(timeToAvoidFor > 0))
	{
			time += timeDelta;

			if(avoiding == true)
			{
				currentSpeedSetting = speedMax/2; // half speed
			}

			if((timeToAvoidFor >0)&&(avoiding == false))
			{
				currentSpeedSetting = speedMax;
			}

			if(avoiding == false)
			{
				currentSpeedSetting = speedMax;
			}
			
			avoidTurn(timeDelta);

			if(speed < currentSpeedSetting)
			{
				walk(timeDelta*40,true);
			}else
			{
				update(timeDelta);
			}

			// If we are out of the ships collision field keep head for set time
			if(timeToAvoidFor > 0)
			{
				timeToAvoidFor -= timeDelta;
			}
	}


	// update Position each time
	if(hasEnemyTarget == true)
	{
		targetedShip->getPosition(&targetPos);

		if(targetedShip->getHealth() <= 0)
		{
			hasEnemyTarget = false;
			currentSpeedSetting = 0.0f;
		}
	}

	float distance = distanceToTarget();

	if((hasEnemyTarget == true)&&(avoiding == false)&&(timeToAvoidFor <= 0))
	{
		// fire when in range
		if((distance < 100000)&&(capital == false))
		{
			shoot();
		}

		currentSpeedSetting = speedMax;
		turn(timeDelta);
		
		if(speed < currentSpeedSetting)
		{
			walk(timeDelta*40,true);
		}else
		{
			update(timeDelta);
		}
	}
	
	// If the ship is not launching from a carrier
	if((launching == false)&&(avoiding == false)&&(hasEnemyTarget == false)&&(timeToAvoidFor <= 0))
	{			
			if(distance < 1000)
			{
					getNextNavPoint();
			}else
			{
				// If the ship has no nav points just sit.
				if((int)navPointsList.size() == 0)
				{
					currentSpeedSetting = 0.0f;

				}else  // If the ship has not yet reached the target point
				{		// Keep heading for it
					currentSpeedSetting = speedMax;
					turn(timeDelta);
					
					if(speed < currentSpeedSetting)
					{
						walk(timeDelta*40,true);
					}else
					{
						update(timeDelta);
					}
				}
			}
	}

	if(launching == true)
	{
		if(time < timeToLaunchfor)
		{
			time += timeDelta;
			currentSpeedSetting = speedMax;
				//currentSpeedSetting = 0.0f;
				turn(timeDelta);
				if(speed < currentSpeedSetting)
				{
					walk(timeDelta*40,true);
				}else
				{
					update(timeDelta);
				}
		}
	}
}

void AIShip::turn(float timeDelta)
{
	float x = 0.0f;
	float y = 0.0f;
	float yawAmount = 0.0f;
	float pitchAmount = 0.0f;
	float difference = 0.0f;

	getAngleToRotate(&x,&y);

	if(x > rotation.x)
	{
		difference = x - rotation.x;

		if(difference > (0.2*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				yawAmount = -turnSpeed * timeDelta;
			}else
			{
				yawAmount = turnSpeed * timeDelta;
			}
		}
	}

	if(x < rotation.x)
	{
		difference = rotation.x - x;
		
		if(difference > (0.2*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				yawAmount = turnSpeed * timeDelta;
			}else
			{
				yawAmount = -turnSpeed * timeDelta;
			}
		}
	}


	if(y > rotation.y)
	{
		difference = y - rotation.y;

		if(difference > (0.2*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				pitchAmount = -turnSpeed * timeDelta;
			}else
			{
				pitchAmount = turnSpeed * timeDelta;
			}
		}
	}

	if(y < rotation.y)
	{
		difference = rotation.y - y;
		
		if(difference > (0.2*(D3DX_PI/180)))
		{
			if(difference > (180*(D3DX_PI/180)))
			{
				pitchAmount = turnSpeed * timeDelta;
			}else
			{
				pitchAmount = -turnSpeed * timeDelta;
			}
		}
	}

	yaw(yawAmount);
	pitch(pitchAmount);
}
