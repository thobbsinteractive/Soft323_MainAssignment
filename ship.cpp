#include "Ship.h"

Ship::Ship()
{
	health = 100.0f;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	speed = 0.0f;
	speedMax = 5.0f;
	currentSpeedSetting = 0.0f;
	fireRate = 0.25f;
	timeTillFire = 0.0f;
	beingTargeted = false;

	angleOfCurrentObjective = 0.0f;
}

Ship::Ship(float _health,D3DXVECTOR3 _pos, 
				D3DXVECTOR3 _rotation, 
				D3DXVECTOR3 _look)
{
	pos = _pos;
	health = _health;
	rotation = _rotation;
	look = _look;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	speed = 0.0f;
	speedMax = 5.0f;
	currentSpeedSetting = 0.0f;
	accelerationRate = 10.0f; // The Lower the faster
	fireRate = 0.25f;
	timeTillFire = 0.0f;
	beingTargeted = false;

	angleOfCurrentObjective = 0.0f;
};

Ship::~Ship()
{
	for(int i = 0; i < (int)fireBalls.size(); i++)
		fireBalls.erase(fireBalls.begin() + i);
};

void Ship::setSpeed(float _speed)
{
	speed = _speed;
}

void Ship::setTargetPosition(D3DXVECTOR3 _targetpos)
{
	targetpos = _targetpos;
}

float Ship::getAngleToRotate(float* x,float* y,float* z,Ship* object)
{
	/* 
	Example:

	A (1,2,3)         |A| = sqrt( 1^2 + 2^2 + 3^2) = sqrt(14) = 3.7417
	B (4,5,6)         |b| = sqrt( 4^2 + 5^2 + 6^2) = sqrt(77) = 8.7750
	
	^2 = squared

	  Cos(angle) =  Xa * Xb + Ya * Yb + Za * Zb   =  4 + 10 + 18    = 32    =  0.9746
                        ---------------------     ---------------    -----
                           (3.7417)*(8.7750)           32.8334       32.8334
	
	ArcCos (.9746) = 12.9ø
	*/

	D3DXVECTOR3 vecToThing;
	D3DXVECTOR3 objectsCurrentVecDir;
	float dotProduct;

	vecToThing.x = object->getPosX() - pos.x;
	vecToThing.y = object->getPosY() - pos.y;
	vecToThing.z = object->getPosZ() - pos.z;
		
		
		D3DXVec3Normalize(&vecToThing, &vecToThing);

		objectsCurrentVecDir = object->getCurrentDirectionalVector();

		dotProduct = D3DXVec3Dot(&vecToThing, &objectsCurrentVecDir);

		return cos(dotProduct);
		//if (dotProduct > cos(cullingAngle)) return TRUE; else return FALSE;
		//}
}

float Ship::getAngleOfCurrentObjective()
{
	return angleOfCurrentObjective;
}

void Ship::setHealth(float _health)
{
	health = _health;
};

void Ship::decreaseHealth(float amountToDecrease)
{
	health = health - amountToDecrease;	
};

void Ship::shoot()
{
	if (timeTillFire <= 0.0f)
	{
		if (fireBalls.size() < 200)
		{
			fire temp(500.0f,&pos,&rotation,&look);
			fireBalls.push_back(temp);
			playSound(0);
		}
		timeTillFire = fireRate;
	}
}

void Ship::updateFire(float timeDelta)
{

	for(int i = 0; i < (int)fireBalls.size(); i++)
	{
		fireBalls[i].walk(timeDelta);
		fireBalls[i].updateHealth(timeDelta);

		if (fireBalls[i].getHealth() < 0.0f)
		{
			//Delete fire ball if its dead
			fireBalls.erase(fireBalls.begin() + i);
		}
	}
	timeTillFire = timeTillFire - timeDelta;
}

void Ship::setFireHealth(int index, float _health)
{
	fireBalls[index].setHealth(_health);
}

void Ship::getFirePosition(int index, D3DXVECTOR3* firePos)
{
	fireBalls[index].getPosition(&*firePos);
}

void Ship::update(float timeDelta)
{
	// Maintain objects speed
	updateBodyEuler(timeDelta);

	//walk(speed * timeDelta,false);
	updateFire(timeDelta);
}

float Ship::getHealth()
{
	return health;
}

void Ship::getFireMatrix(int i,D3DXMATRIX* V)
{
	fireBalls[i].getMatrix(&*V,rotation);
};

int Ship::getNumberofFireBalls()
{
	return (int)fireBalls.size();
}

float Ship::getCurrentSpeedSetting()
{
	return currentSpeedSetting;
}
float Ship::getCurrentSpeed()
{
	return speed;
}

bool Ship::getTargeted()
{
	return beingTargeted;
}

void Ship::setTargeted()
{
	if(beingTargeted == false)
	{
		beingTargeted = true;
	}else
	{
		beingTargeted = false;
	}

}

void Ship::walk(float units,bool keypress)
{
    // Addition of speed controls means overloading the inherted function.
	D3DXVECTOR3 newLook;
	D3DXVECTOR3 posTemp;
	D3DXMATRIX RotationMatrix;
	D3DXVECTOR3 normedVector;
	
	// If a key is press increase or reduce the currentSpeedSetting setting accordingly
	if (keypress == true)
	{
		if((units > 0.0f) && (currentSpeedSetting < speedMax))
		{
			// Ensure that the setting does not go above speedMax
			if(currentSpeedSetting + units < speedMax)
			{
				currentSpeedSetting = currentSpeedSetting + units/2;
			}else
			{
				currentSpeedSetting = speedMax;
			}
		}
		
		if((units <= 0.0f) && (currentSpeedSetting > 0.0f))
		{
			// Ensure that the setting does not go below 0.0f
			if(currentSpeedSetting + units > 0.0f)
			{
				currentSpeedSetting = currentSpeedSetting + units/2;
			}else
			{
				currentSpeedSetting = 0.0f;
			}
		}
	}
	

	if(speed != currentSpeedSetting)
	{
		// Speed up to current speed setting if a positive value is used
		if(speed < currentSpeedSetting)
		{
			// Ensure that the setting does not go above currentSpeedSetting
			if(units > 0.0f)
			{
				if(speed + units/5 < currentSpeedSetting)
				{
					speed = speed + units/5;
				}else
				{
					speed = currentSpeedSetting;
				}
			}else
			{
				if(speed - units/5 < currentSpeedSetting)
				{
					speed = speed - units/5;
				}else
				{
					speed = currentSpeedSetting;
				}
			}
		}
		
		// Slow down to current speed setting if a negative value is used
		if(speed > currentSpeedSetting)
		{
			// Ensure that the setting does not go below 0.0f
			if(units < 0.0f)
			{
				if(speed + units/5 > 0.0f)
				{
					speed = speed + units/5;
				}else
				{
					speed = 0.0f;
				}
			}else
			{
				if(speed - units/5 > 0.0f)
				{
					speed = speed - units/5;
				}else
				{
					speed = 0.0f;
				}
			}
		}
	}


	// The "look" vector isn't even updated, if I assign the value of "normedVector" to "look"
	// The objects trajectory is messed up? normedVector seems to hold the amount of change to
	// make, not the actual vector.

	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&currentVector, &newLook );

	posTemp.x = pos.x;
	posTemp.y = pos.y;
	posTemp.z = pos.z;

	posTemp += currentVector * speed;

	//Test the new position first, if its okay update
	if((posTemp.x < objectBoundaries.Max.x) && (posTemp.x > objectBoundaries.Min.x))
	{
		pos.x = posTemp.x;
	}
		
	if((posTemp.y < objectBoundaries.Max.y) && (posTemp.y > objectBoundaries.Min.y))
	{
		pos.y = posTemp.y;
	}
		
	if((posTemp.z < objectBoundaries.Max.z) && (posTemp.z > objectBoundaries.Min.z))
	{
		pos.z = posTemp.z;
	}
}

void Ship::yaw(float angle)
{
	//angle = angle * (speed/10.0f);

	float twoPi = D3DX_PI*2;

	if (angle > twoPi)
		angle -= twoPi;         //Just to stop the rotation angle

	if (angle < 0) 
		angle += twoPi;

	rotation.x = rotation.x  + angle;
}

void Ship::getMatrix(D3DXMATRIX* V)
{
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,1.0f,1.0f,1.0f);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);

	*V = RotationMatrix * Translation * Scaling;
};