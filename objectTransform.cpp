/* Name: objectTransform.cpp
   Description: The methods for the objectTransform class
   
   This class holds an objects current positional coordinates and can be used to
   rotate an object on its own axis according to its own positiontion information.
   This is very useful for User and AI controlled objects.
*/
#include "objectTransform.h"

objectTransform::objectTransform()
{
	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // In radians
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	objectBoundaries = Boundary(D3DXVECTOR3(100000.0f, 100000.0f,100000.0f),D3DXVECTOR3(-100000.0f,-100000.0f, -100000.0f));

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;
	
	const float	tol = 0.000000000000001f;		// float type tolerance 

	fMass = 10;
	fInertia = 10;
	fInertiaInverse = 1/10;
	
	fOrientation = 135;	
	thrustForce = _THRUSTFORCE*1;


};

objectTransform::objectTransform(D3DXVECTOR3 _pos, ViewObject* _pMesh)
{
	pos   = _pos;
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	objectBoundaries = Boundary(D3DXVECTOR3(100000.0f, 100000.0f,100000.0f),D3DXVECTOR3(-100000.0f,-100000.0f, -100000.0f));
	
	pMeshObjects.push_back(_pMesh);

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;

	const float	tol = 0.000000000000001f;		// float type tolerance 

	fMass = 10;
	fInertia = 10;
	fInertiaInverse = 1/10;
	
	fOrientation = 135;	
	thrustForce = _THRUSTFORCE*1;
};

objectTransform::objectTransform(Boundary _objectBoundaries, ViewObject* _pMesh)
{
	objectBoundaries = _objectBoundaries;

	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pMeshObjects.push_back(_pMesh);

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;

	const float	tol = 0.000000000000001f;		// float type tolerance 

	fMass = 10;
	fInertia = 10;
	fInertiaInverse = 1/10;
	
	fOrientation = 135;	
	thrustForce = _THRUSTFORCE*1;
}

objectTransform::objectTransform(D3DXVECTOR3 _pos, D3DXVECTOR3 _rotation, D3DXVECTOR3 _look, ViewObject* _pMesh)
{
	D3DXVECTOR3 pos = _pos;
	D3DXVECTOR3 rotation = _rotation;
	D3DXVECTOR3 look = _look;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	objectBoundaries = Boundary(D3DXVECTOR3(10000.0f, 1000.0f,10000.0f),D3DXVECTOR3(-10000.0f, 100.0f, -10000.0f));
	pMeshObjects.push_back(_pMesh);

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;

	const float	tol = 0.000000000000001f;		// float type tolerance 

	fMass = 10;
	fInertia = 10;
	fInertiaInverse = 1/10;
	
	fOrientation = 135;	
	thrustForce = _THRUSTFORCE*1;
};

objectTransform::~objectTransform()
{
	for(int i =0;i < (int)sound.size();i++)
	{
		//erase all sounds
		sound.erase(sound.begin() + i);
	}
	
};

void objectTransform::getPosition(D3DXVECTOR3* _pos)
{
	*_pos = pos;
};

void objectTransform::setPosition(D3DXVECTOR3* _pos)
{
	pos = *_pos;
};

void objectTransform::getRotation(D3DXVECTOR3* _rotation)
{
	*_rotation = rotation;
};

void objectTransform::setRotation(D3DXVECTOR3* _rotation)
{
	rotation = *_rotation;
};
void objectTransform::getLook(D3DXVECTOR3* _look)
{
	*_look = look;
};

void objectTransform::setLook(D3DXVECTOR3* _look)
{
	look = *_look;
};

void objectTransform::setScale(D3DXVECTOR3* _pScale)
{
	scale = *_pScale;
};

void objectTransform::setMesh(ViewObject* _pMesh)
{
	if(_pMesh)
	{
		pMeshObjects.push_back(_pMesh);
	}
}

void objectTransform::setDevice(IDirect3DDevice9* _plocalDevice)
{
	localDevice = _plocalDevice;
}

void objectTransform::addObjectSound(CSound* _sound)
{
	if(_sound)
	{
		CSound* temp = _sound;
		sound.push_back(temp);
	}
};

void objectTransform::playSound(int soundNumber)
{
	if((int)sound.size() > 0)
	{
		sound[soundNumber]->Stop();
		sound[soundNumber]->Reset();
		sound[soundNumber]->Play();
	}
};

float objectTransform::getPosX()
{
	return pos.x;
};

float objectTransform::getPosY()
{
	return pos.y;
};

float objectTransform::getPosZ()
{
	return pos.z;
};

bool objectTransform::checkIfVisibleToThisObject(objectTransform* objectToCheck,float cullingAngleInDegrees)
{
	D3DXVECTOR3 vecToThing;
	D3DXVECTOR3 objectsCurrentVecDir;
	float dotProduct;
	float cullingAngleInRadians = D3DXToRadian(cullingAngleInDegrees);

	vecToThing.x = objectToCheck->getPosX() - pos.x;
	vecToThing.y = objectToCheck->getPosY() - pos.y;
	vecToThing.z = objectToCheck->getPosZ() - pos.z;
		
		
	D3DXVec3Normalize(&vecToThing, &vecToThing);
	objectsCurrentVecDir = objectToCheck->getCurrentDirectionalVector();

	dotProduct = D3DXVec3Dot(&vecToThing, &objectsCurrentVecDir);

	if (dotProduct > cos(cullingAngleInRadians))
	{
		return true;
	}else
	{
		return false;
	}
}

void objectTransform::setCamera(float _distanceZ, float _distanceY)
{
	chaseCamera = true;
	distanceZ = _distanceZ;
	distanceY = _distanceY;
};

D3DXVECTOR3 objectTransform::getCurrentDirectionalVector()
{
	return currentVector;
}

void objectTransform::walk(float units)
{
	// Mainly nicked from "thing3d", Thanks Nigel.

	D3DXVECTOR3 newLook;
	D3DXVECTOR3 posTemp;
	D3DXMATRIX RotationMatrix;

	posTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// move only on xz plane for land object
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize( &currentVector, &newLook );
	
	posTemp.x = pos.x;
	posTemp.y = pos.y;
	posTemp.z = pos.z;

	posTemp += currentVector * units;

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

void objectTransform::pitch(float angle)
{
	float twoPi = D3DX_PI*2;

	if (angle > twoPi)
		angle -= twoPi;         //Just to stop the rotation angle

	if (angle < 0) 
		angle += twoPi;
   
	rotation.y = rotation.y  + angle;

}

void objectTransform::yaw(float angle)
{
	float twoPi = D3DX_PI*2;

	if (angle > twoPi)
		angle -= twoPi;         //Just to stop the rotation angle

	if (angle < 0) 
		angle += twoPi;

	rotation.x = rotation.x  + angle;
}

void objectTransform::roll(float angle)
{

	float twoPi = D3DX_PI*2;

	if (angle > twoPi)
		angle -= twoPi;         //Just to stop the rotation angle

	if (angle < 0) 
		angle += twoPi;

	rotation.z = rotation.z  + angle;
}

void objectTransform::updateCamera()
{
	D3DXMATRIX V;

	cameraPosition = pos;
	cameraLookAt = pos;

	D3DXVECTOR3 up;
	D3DXVECTOR3 look;
	D3DXVECTOR3 newLook;
	D3DXMATRIX RotationMatrix;
	D3DXVECTOR3 normedVector;

	float HalfPi = D3DX_PI/2;

	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// Calculate Camera look at coordinates 
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&normedVector, &newLook );

	cameraLookAt += normedVector * distanceZ;
	cameraPosition -= normedVector * distanceZ;

	
	// Calculates Vertical Camera Position
	
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y+HalfPi,rotation.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&normedVector, &newLook );

	cameraLookAt -= normedVector * distanceY;
	cameraPosition -= normedVector * distanceY;

	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	/*
	if(rotation.y > 2.0f)
	{
		up = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	}else
	{
		up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
*/

	D3DXMatrixLookAtLH(&V, &cameraPosition,&cameraLookAt,&up);
	localDevice->SetTransform(D3DTS_VIEW, &V);
}

void objectTransform::getMatrix(D3DXMATRIX* V)
{
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);

	*V = RotationMatrix * Scaling * Translation;
}

void objectTransform::drawMesh()
{
	D3DXMATRIX World;
	
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
	World = RotationMatrix * Translation * Scaling;

	localDevice->SetTransform(D3DTS_WORLD, &World);
	pMeshObjects[0]->drawObject();
}

void objectTransform::drawMesh(int index)
{
	if((int)pMeshObjects.size() > 0)
	{
		D3DXMATRIX World;
	
		D3DXMATRIX RotationMatrix;
		D3DXMATRIX Translation;
		D3DXMATRIX Scaling;

		D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
		D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
		D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
		World = RotationMatrix * Translation * Scaling;

		localDevice->SetTransform(D3DTS_WORLD, &World);
		pMeshObjects[index]->drawObject();
	}
}

void objectTransform::getMesh(ViewObject** _pMesh)
{
	*_pMesh = pMeshObjects[0];
}

bool objectTransform::highlevelCollisionDetection(objectTransform* objectToCheckAgainst){
	
	ViewObject* objectsMesh;
	D3DXVECTOR3 objectsPosition;

	objectToCheckAgainst->getPosition(&objectsPosition);

	objectToCheckAgainst->getMesh(&objectsMesh);
	return objectsMesh->isPointInsideBoundingBox(&pos,&objectsPosition);
}

bool objectTransform::highlevelCollisionDetection(D3DXVECTOR3 objectsPosition)
{
	return pMeshObjects[0]->isPointInsideBoundingBox(&objectsPosition,&pos);
}

void objectTransform::drawMeshBounding()
{
	D3DXMATRIX World;
	
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
	World = RotationMatrix * Translation * Scaling;

	localDevice->SetTransform(D3DTS_WORLD, &World);
	pMeshObjects[0]->drawBoundingBox();
}

void objectTransform::calcLoads()
{
	D3DXVECTOR3	Fb;				// stores the sum of forces
	D3DXVECTOR3	Mb;				// stores the sum of moments
	D3DXVECTOR3	Thrust;			// thrust vector
	
	// reset forces and moments:
	forces.x = 0.0f;
	forces.y = 0.0f;
	forces.z = 0.0f;	// always zero in 2D

	moment.x = 0.0f;	// always zero in 2D
	moment.y = 0.0f;	// always zero in 2D
	moment.z = 0.0f;

	Fb.x = 0.0f;	
	Fb.y = 0.0f;	
	Fb.z = 0.0f;	

	Mb.x = 0.0f;
	Mb.y = 0.0f;
	Mb.z = 0.0f;

	// Define the thrust vector, which acts through the craft's CG
	Thrust.x = 0.0f;
	Thrust.y = 1.0f;
	Thrust.z = 0.0f;  // zero in 2D
	Thrust *= thrustForce;
	
	// Calculate forces and moments in body space:
	D3DXVECTOR3	localVelocity;
	float	fLocalSpeed;
	D3DXVECTOR3	dragVector;	
	float	tmp;
	D3DXVECTOR3	resultant;	
	D3DXVECTOR3	vtmp;	

		// Calculate the aerodynamic drag force:
		// Calculate local velocity:
		// The local velocity includes the velocity due to linear motion of the craft, 
		// plus the velocity at each element due to the rotation of the craft.

	
		// rotational part
		vtmp = D3DXVECTOR3(angularVelocity.y*CD.z - angularVelocity.z*CD.y,
				  -angularVelocity.x*CD.z + angularVelocity.z*CD.x,
				  angularVelocity.x*CD.y - angularVelocity.y*CD.x);

		localVelocity = velocityBody + vtmp; 

		// Calculate local air speed
		fLocalSpeed = sqrt(localVelocity.x*localVelocity.x + localVelocity.y*localVelocity.y + localVelocity.z*localVelocity.z);

		// Find the direction in which drag will act.
		// Drag always acts inline with the relative velocity but in the opposing direction
		if(fLocalSpeed > tol) 
		{
			D3DXVec3Normalize(&localVelocity, &localVelocity);
			dragVector = -localVelocity;		

			// Determine the resultant force on the element.
			float trustMagnitude = sqrt(Thrust.x*Thrust.x + Thrust.y*Thrust.y + Thrust.z*Thrust.z);

			float vectorMultplyThrustLV = Thrust.x*localVelocity.x + Thrust.y*localVelocity.y + Thrust.z*localVelocity.z;

			double f;
			if((Thrust.x*localVelocity.x + Thrust.y*localVelocity.y + Thrust.z*localVelocity.z) /(trustMagnitude * fLocalSpeed) > 0)
				f = 2;	
			else
				f = 1;

			tmp = 0.5f * fLocalSpeed*fLocalSpeed * ProjectedArea * f;		
			resultant = dragVector * _LINEARDRAGCOEFFICIENT * tmp; // simulate fuselage drag

			// Keep a running total of these resultant forces (total force)
			Fb += resultant;
		
			// Calculate the moment about the CG of this element's force
			// and keep a running total of these moments (total moment)
			vtmp = D3DXVECTOR3(CD.y*resultant.z - CD.z*resultant.y,
				  -CD.x*resultant.z + CD.z*resultant.x,
				  CD.x*resultant.y - CD.y*resultant.x);

			Mb += vtmp;
		}

		// Calculate the Port & Starboard bow thruster forces:
		// Keep a running total of these resultant forces (total force)
		Fb += 3*pThrust;
		

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment) 
		vtmp = D3DXVECTOR3(CPT.y*pThrust.z - CPT.z*pThrust.y,
				  -CPT.x*pThrust.z + CPT.z*pThrust.x,
				  CPT.x*pThrust.y - CPT.y*pThrust.x);

		Mb += vtmp;

		// Keep a running total of these resultant forces (total force)
		Fb += 3*sThrust;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = D3DXVECTOR3(CST.y*sThrust.z - CST.z*sThrust.y,
				  -CST.x*sThrust.z + CST.z*sThrust.x,
				  CST.x*sThrust.y - CST.y*sThrust.x);
		Mb += vtmp;

		// do other applied forces here
		Fb += Fa;
		vtmp = D3DXVECTOR3(Pa.y*Fa.z - Pa.z*Fa.y,
				  -Pa.x*Fa.z + Pa.z*Fa.x,
				  Pa.x*Fa.y - Pa.y*Fa.x);
		Mb += vtmp;

		// Calculate rotational drag
		float angularVelocityMagnitude = sqrt(angularVelocity.x*angularVelocity.x + angularVelocity.y*angularVelocity.y + angularVelocity.z*angularVelocity.z);
		if(angularVelocityMagnitude > tol)
		{
			vtmp.x = 0;
			vtmp.y = 0;
			tmp = 0.5f * angularVelocity.z*angularVelocity.z * ProjectedArea;
			if(angularVelocity.z > 0.0)
				vtmp.z = -_ANGULARDRAGCOEFFICIENT * tmp;		
			else
				vtmp.z = _ANGULARDRAGCOEFFICIENT * tmp;		

			Mb += vtmp;
		}


	// Now add the propulsion thrust
	Fb += Thrust; // no moment since line of action is through CG

	// Convert forces from model space to earth space
	forces = rotate3D(fOrientation, Fb);

	moment += Mb;	
}

void objectTransform::updateBodyEuler(double dt)
{
		D3DXVECTOR3 a;
		D3DXVECTOR3 dv;
		D3DXVECTOR3 ds;
		float  aa;
		float  dav;
		float  dr;
	
		// Calculate forces and moments:
		calcLoads();
		
		// Integrate linear equation of motion:
		a = forces / fMass;
		
		dv = a * dt;
		velocity += dv;

		ds = velocity * dt;
		pos += ds;

		// Integrate angular equation of motion:
		aa = moment.z / fInertia;

		dav = aa * dt;
		
		angularVelocity.z += dav;
		
		dr = (angularVelocity.z * dt) * (180.0f / D3DX_PI);
		//dr = RadiansToDegrees(angularVelocity.z * dt);
		fOrientation += dr; 
		
		// Misc. calculations:
		fSpeed = sqrt(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z);		
		velocityBody = rotate3D(-fOrientation, velocity);	
}

void objectTransform::setThrusters(bool p, bool s)
{
	pThrust.x = 0;
	pThrust.y = 0;
	sThrust.x = 0;
	sThrust.y = 0;
	
	if(p)
		pThrust.x = -_STEERINGFORCE;
	if(s)
		sThrust.x = _STEERINGFORCE;
}


D3DXVECTOR3 objectTransform::rotate3D( float angle, D3DXVECTOR3 u)
{
	float	x,y;

	x = u.x * cos(-angle*(D3DX_PI/180)) + u.y * sin(-angle*(D3DX_PI/180));
	y = -u.x * sin(-angle*(D3DX_PI/180)) + u.y * cos(-angle*(D3DX_PI/180));

	return D3DXVECTOR3( x, y, 0);
}

void objectTransform::modulateThrust(bool up)
{
	double	dT = up ? _DTHRUST:-_DTHRUST;

	thrustForce += dT;

	if(thrustForce > _MAXTHRUST) thrustForce = _MAXTHRUST;
	if(thrustForce < _MINTHRUST) thrustForce = _MINTHRUST;
}