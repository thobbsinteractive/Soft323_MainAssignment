#include "aiShip.h"

AIShip::AIShip()
{
	health = 100.0f;
	friendly = true;
	turning = false;
	avoiding  = false;
	manover  = false;
	targetShipIndex = 0;
	awaitingNewObjective = true;
	currentNavPoint = 0;
	totalNumberOfNavPoints = 0;

	objectivePos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

AIShip::~AIShip()
{


}

bool AIShip::getIFF()
{
	return friendly;
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
	tempNav->index = newNavPoint.index;
	tempNav->location = newNavPoint.location;
	tempNav->visited = newNavPoint.visited;

	navPointsList.push_back(tempNav);

	totalNumberOfNavPoints++;
}

bool AIShip::getObjectiveStatus()
{
	return awaitingNewObjective;
}

void AIShip::getNextNavPoint()
{
	bool navPointSet = false;
	int unvisited = 0;

	for(int i = 0; i < (int)navPointsList.size();i++)
	{
		if(navPointSet == false)
		{
			if(navPointsList[i]->visited == false)
			{
				objectivePos = navPointsList[i]->location; // Get navpoints location
				navPointsList[i]->visited = true; // so we don't visit it again
				awaitingNewObjective = false;

				navPointSet	= true; // breaks out of the loop when new point is set
				currentNavPoint++;
			}
		}
	}

	if(totalNumberOfNavPoints == currentNavPoint) // If this is the last point in the list
	{
		// reset the visited status to start navpoint again
		for(int i = 0; i < (int)navPointsList.size();i++)
		{
			navPointsList[i]->visited = false; 
			currentNavPoint = 0;
		}
	}


}

void AIShip::manovering()
{
	/*
	if(targetShipIndex == 0) // if there are no ememy fighters
	{	
		// check ship is at nav point
		if((pos.x > (objectivePos.x-100)) && (pos.x < (objectivePos.x+100)))
		{
			if((pos.y > (objectivePos.y-100)) && (pos.y < (objectivePos.y+100)))
			{
				if((pos.z > (objectivePos.z-100)) && (pos.z < (objectivePos.z+100)))
				{
					getNextNavPoint();
					awaitingNewObjective = true;
					//currentSpeedSetting = 0.0f;
				}
			}
		}

		// If the ship has not yet reached the nav point
		if(awaitingNewObjective == false)
		{
			// Keep heading for it
			currentSpeedSetting = speedMax;
		}
	}*/

}

void AIShip::behavior(float units)
{
	manovering();
	walk(units,false);
}

void AIShip::turn(float timeDelta)
{
	bool	p = false;
	bool	s = false;

	//currentSpeedSetting = speedMax/3;
	// Turn
	D3DXVECTOR3 u,v;

	u = (targetpos - pos);

	///////
	//Vector	VRotate2D( float angle, Vector u)

	float x,y;
	//fOrientation = 0;
	x = u.x * cos(-fOrientation * 3.14 / 180) + u.y * sin(-fOrientation* 3.14 / 180);
	y = -u.x * sin(-fOrientation * 3.14 / 180) + u.y * cos(-fOrientation * 3.14 / 180);

	u = D3DXVECTOR3(x,y,0);
	D3DXVec3Normalize(&u, &u);

	if(u.x < -_TOL)
		p = true;
	else if(u.x > _TOL)
		s = true;
		
	setThrusters(p,s);
}
