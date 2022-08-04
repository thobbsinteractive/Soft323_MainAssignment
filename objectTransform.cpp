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

	objectBoundaries = Boundary(D3DXVECTOR3(FLT_MAX, FLT_MAX,FLT_MAX),D3DXVECTOR3(-FLT_MAX,-FLT_MAX, -FLT_MAX));

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;
	vertexCount = 0;
};

objectTransform::objectTransform(D3DXVECTOR3 _pos, ViewObject* _pMesh)
{
	pos   = _pos;
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	objectBoundaries = Boundary(D3DXVECTOR3(FLT_MAX, FLT_MAX,FLT_MAX),D3DXVECTOR3(-FLT_MAX,-FLT_MAX, -FLT_MAX));
	
	pMeshObjects.push_back(_pMesh);

	chaseCamera = false;
	distanceZ=0;
	distanceY=0;
	vertexCount = 0;
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
	vertexCount = 0;
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
	vertexCount = 0;
};

objectTransform::~objectTransform()
{
	for(int i =0;i < (int)sound.size();i++)
	{
		//erase all sounds
		sound.erase(sound.begin() + i);
	}

	for(int i =0;i < (int)pMeshObjects.size();i++)
	{
		//erase all sounds
		pMeshObjects.erase(pMeshObjects.begin() + i);
	}
	printf("objectTransform deconstructor run");
	
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

void objectTransform::addObjectSound(LPTSTR wavFileName, HWND handle,CSoundManager* sound3Dmanager)
{
	//if(_sound)
	//{
		_3DSound temp;
		temp.initialiseSound(localDevice, wavFileName, handle, sound3Dmanager);
		sound.push_back(temp);
	//}
};

void objectTransform::playSound(int soundNumber,D3DXVECTOR3 listenerPosition)
{
	if((int)sound.size() > 0)
	{
		sound[soundNumber].setSoundPos(pos,0.0f);
		sound[soundNumber].playSound3D();
	}
}

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

bool objectTransform::checkIfVisibleToThisObject(objectTransform* objectToCheck)
{
	D3DXVECTOR3 objectsPosition;
	ViewObject* objectsMesh;

	objectToCheck->getPosition(&objectsPosition);
	objectToCheck->getMesh(&objectsMesh);

	return SphereInFrustum(objectsPosition,objectsMesh->getBoundingRadius());
}

float objectTransform::getBoundingRadius()
{
	return pMeshObjects[0]->getBoundingRadius();
}

void objectTransform::setCamera(float _distanceZ, float _distanceY,float width,float height)
{

	D3DXMatrixPerspectiveFovLH(
		& matProj,
		D3DX_PI * 0.25f,
		(float)width / (float)height,
		1.0f,
		1000000000.0f);

	localDevice->SetTransform(D3DTS_PROJECTION, &matProj);

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

	if(chaseCamera == true)
	{
		updateCamera();
	}
	// update the sound position every time the object moves
	for(int i = 0; i < sound.size(); i++)
	{
		sound[i].setSoundPos(pos,0);
	}

}

float objectTransform::addAngle(float angleToAdd,float existingAngle)
{
	float angleInDegrees = angleToAdd*(180/D3DX_PI);
	float rotationInDegrees = existingAngle*(180/D3DX_PI);
	float answer = 0.0f;
	bool finished = false;

	// Ensures all angles stay with limits

	// 0 to 360
	if(((rotationInDegrees + angleInDegrees) <= 360)&&
		((rotationInDegrees + angleInDegrees) >= 0)&&
		(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees;
		finished = true;
	}

	// 360 to 420
	if(((rotationInDegrees + angleInDegrees) > 360)&&(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees -360;
		finished = true;
	}

	// 0 to -360
	if(((rotationInDegrees + angleInDegrees) < 0)&&
		((rotationInDegrees + angleInDegrees) >= -360)&&
		(finished == false))
	{
		answer = 360 + (rotationInDegrees + angleInDegrees);
		finished = true;
	}

	return answer * (D3DX_PI/180); // In radians
}

void objectTransform::pitch(float angle)
{
	float angleInDegrees = angle*(180/D3DX_PI);
	float rotationInDegrees = rotation.y*(180/D3DX_PI);
	float answer = 0.0f;
	bool finished = false;

	// Ensures all angles stay with limits

	// 0 to 360
	if(((rotationInDegrees + angleInDegrees) <= 360)&&
		((rotationInDegrees + angleInDegrees) >= 0)&&
		(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees;
		finished = true;
	}

	// 360 to 420
	if(((rotationInDegrees + angleInDegrees) > 360)&&(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees -360;
		finished = true;
	}

	// 0 to -360
	if(((rotationInDegrees + angleInDegrees) < 0)&&
		((rotationInDegrees + angleInDegrees) >= -360)&&
		(finished == false))
	{
		answer = 360 + (rotationInDegrees + angleInDegrees);
		finished = true;
	}
	
	rotation.y = answer * (D3DX_PI/180); // In radians

	if(chaseCamera == true)
	{
		updateCamera();
	}
}

void objectTransform::yaw(float angle)
{
	float angleInDegrees = angle*(180/D3DX_PI);
	float rotationInDegrees = rotation.x*(180/D3DX_PI);
	float answer = 0.0f;
	bool finished = false;

	// Ensures all angles stay with limits

	// 0 to 360
	if(((rotationInDegrees + angleInDegrees) <= 360)&&
		((rotationInDegrees + angleInDegrees) >= 0)&&
		(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees;
		finished = true;
	}

	// 360 to 420
	if(((rotationInDegrees + angleInDegrees) > 360)&&(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees -360;
		finished = true;
	}

	// 0 to -360
	if(((rotationInDegrees + angleInDegrees) < 0)&&
		((rotationInDegrees + angleInDegrees) >= -360)&&
		(finished == false))
	{
		answer = 360 + (rotationInDegrees + angleInDegrees);
		finished = true;
	}
	
	rotation.x = answer * (D3DX_PI/180); // In radians

	if(chaseCamera == true)
	{
		updateCamera();
	}
}

void objectTransform::roll(float angle)
{
	float angleInDegrees = angle*(180/D3DX_PI);
	float rotationInDegrees = rotation.z*(180/D3DX_PI);
	float answer = 0.0f;
	bool finished = false;

	// Ensures all angles stay with limits

	// 0 to 360
	if(((rotationInDegrees + angleInDegrees) <= 360)&&
		((rotationInDegrees + angleInDegrees) >= 0)&&
		(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees;
		finished = true;
	}

	// 360 to 420
	if(((rotationInDegrees + angleInDegrees) > 360)&&(finished == false))
	{
		answer = rotationInDegrees + angleInDegrees -360;
		finished = true;
	}

	// 0 to -360
	if(((rotationInDegrees + angleInDegrees) < 0)&&
		((rotationInDegrees + angleInDegrees) >= -360)&&
		(finished == false))
	{
		answer = 360 + (rotationInDegrees + angleInDegrees);
		finished = true;
	}
	
	rotation.z = answer * (D3DX_PI/180); // In radians

	if(chaseCamera == true)
	{
		updateCamera();
	}
}

void objectTransform::updateCamera()
{
	cameraPosition = pos;
	cameraLookAt = pos;

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

	
	// Stops the camera being flipped upside down when rotating up
	if(((rotation.y*(180/D3DX_PI)) > 90)&&((rotation.y*(180/D3DX_PI)) < 270))
	{
		up = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	}else
	{
		up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

}

void objectTransform::updatePositionInRelationTo(D3DXVECTOR3 offsetPostion,D3DXVECTOR3 rotationOfObject,D3DXVECTOR3* newPostion)
{

	D3DXVECTOR3 look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 newLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX RotationMatrix;
	D3DXVECTOR3 normedVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	*newPostion = pos; // equals the postion of this object

	float radins = 270 * (D3DX_PI/180);

	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// Calculate new coordinates 
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotationOfObject.x+radins,rotationOfObject.y,rotationOfObject.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&normedVector, &newLook );

	*newPostion += normedVector * offsetPostion.x;

	look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	newLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normedVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotationOfObject.x,rotationOfObject.y+radins,rotationOfObject.z);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&normedVector, &newLook );

	*newPostion += normedVector * offsetPostion.y;

	look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	newLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normedVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotationOfObject.x,rotationOfObject.y,rotationOfObject.z+radins);
    D3DXVec3TransformCoord(&newLook, &look, &RotationMatrix);
    D3DXVec3Normalize(&normedVector, &newLook );

	*newPostion += normedVector * offsetPostion.z;
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
	matWorld = *V;
}


void objectTransform::drawMesh()
{	
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
	matWorld = RotationMatrix * Translation * Scaling;

	localDevice->SetTransform(D3DTS_WORLD, &matWorld);

	pMeshObjects[0]->drawObject();
}

void objectTransform::drawWithoutMatrix(int index)
{
	pMeshObjects[index]->drawObjectForRadar();
}

void objectTransform::drawMesh(int index)
{
	if((int)pMeshObjects.size() > 0)
	{
		D3DXMATRIX RotationMatrix;
		D3DXMATRIX Translation;
		D3DXMATRIX Scaling;

		D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
		D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
		D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
		matWorld = RotationMatrix * Translation * Scaling;

		localDevice->SetTransform(D3DTS_WORLD, &matWorld);
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

	return objectsMesh->isPointInsideBoundingBox(&objectsPosition,&pos);
}

bool objectTransform::highlevelCollisionDetection(D3DXVECTOR3 objectsPosition)
{
	return pMeshObjects[0]->isPointInsideBoundingBox(&objectsPosition,&pos);
}

// really need a detail level vairable in here
bool objectTransform::lowlevelCollisionDetection(objectTransform* objectToCheckAgainst)
{
	D3DXVECTOR3 objectsPosition;

	objectToCheckAgainst->getPosition(&objectsPosition);

	// Use inverse of matrix
	D3DXMATRIX matInverse;
	D3DXMatrixInverse(&matInverse,NULL,&matWorld);

	// Transform ray origin and direction by inv matrix
	D3DXVECTOR3 rayObjOrigin,rayObjDirection;
	D3DXVECTOR3 rayOrigin,rayDirection;
	objectToCheckAgainst->getPosition(&rayOrigin);
	objectToCheckAgainst->getRotation(&rayDirection);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	return pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection);
}

bool objectTransform::lowlevelMeshCollisionDetection(objectTransform* objectToCheckAgainst)
{
	IDirect3DVertexBuffer9* _vb;

	D3DXVECTOR3 objectsPosition;
	ViewObject* objectsMesh;
	ID3DXMesh* Mesh;
	bool hasHit = false;

	objectToCheckAgainst->getPosition(&objectsPosition);

	// Use inverse of matrix
	D3DXMATRIX matInverse;
	D3DXMatrixInverse(&matInverse,NULL,&matWorld);

	// Transform ray origin and direction by inv matrix
	D3DXVECTOR3 rayObjOrigin,rayObjDirection;
	D3DXVECTOR3 rayOrigin,rayDirection;
	objectToCheckAgainst->getRotation(&rayDirection);
	
	objectToCheckAgainst->getMesh(&objectsMesh);
	Mesh = objectsMesh->getMesh();

	
	// Vertex format
	//struct MESHVERTEX { D3DXVECTOR3 p, n; FLOAT tu, tv; };
	struct MESHVERTEX { D3DXVECTOR3 p;};
	MESHVERTEX* pVertices;

	Mesh->GetVertexBuffer(&_vb);
	_vb->Lock(0, 0, (void**)&pVertices, 0);
	int numberOfVertexs = Mesh->GetNumVertices();

	// Test 10 random vertexs each frame
	// make sure vertex 385 and 20 (the nose of the fighter are tested)
	/*
	for(int i = 0; i < 10; i++)
	{

		rayOrigin = pVertices[rand() % numberOfVertexs].p;
		objectToCheckAgainst->getPosition(&rayOrigin);

		D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
		D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
		D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

			//We can now call the intersect function on our untransformed graphic mesh data:

		if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
		{
			hasHit = true;
		}
	}*/

	// Test key vertexs across the model

	// Nose
	// Test vetrex 14
	rayOrigin = pVertices[14].p;
	objectToCheckAgainst->getPosition(&rayOrigin);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
	{
		hasHit = true;
	}

	// Engines

	// Test vetrex 233
	rayOrigin = pVertices[233].p;
	objectToCheckAgainst->getPosition(&rayOrigin);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
	{
		hasHit = true;
	}

	// test vetrex 1365
	rayOrigin = pVertices[1365].p;
	objectToCheckAgainst->getPosition(&rayOrigin);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
	{
		hasHit = true;
	}

	// underside

	// Test vetrex 432
	rayOrigin = pVertices[432].p;
	objectToCheckAgainst->getPosition(&rayOrigin);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
	{
		hasHit = true;
	}

	// test vetrex 143
	rayOrigin = pVertices[143].p;
	objectToCheckAgainst->getPosition(&rayOrigin);

	D3DXVec3TransformCoord(&rayObjOrigin,&rayOrigin,&matInverse);
	D3DXVec3TransformNormal(&rayObjDirection,&rayDirection,&matInverse);
	D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

	//We can now call the intersect function on our untransformed graphic mesh data:
	if (pMeshObjects[0]->isPointIntersectingWithMesh(rayObjOrigin,rayObjDirection))
	{
		hasHit = true;
	}

	Mesh->UnlockVertexBuffer();

	return hasHit;
}

void objectTransform::drawMeshBounding()
{	
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	D3DXMatrixScaling(&Scaling,scale.x,scale.y,scale.z);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
	D3DXMatrixTranslation(&Translation, pos.x,pos.y,pos.z);
	
	matWorld = RotationMatrix * Translation * Scaling;

	localDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pMeshObjects[(int)pMeshObjects.size()-1]->drawBoundingSphere();
}

void objectTransform::setChaseCameraMatrix()
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &cameraPosition,&cameraLookAt,&up);
	localDevice->SetTransform(D3DTS_VIEW, &matView);
	buildViewFrustum(matView);
}

// Based on http://www.c-unit.com/tutorials/mdirectx/?t=45
void objectTransform::buildViewFrustum(D3DXMATRIX matView)
{
	// Get combined matrix
	D3DXMATRIXA16 matComb;
	//D3DXMATRIXA16 matComb;
	D3DXMatrixMultiply(&matComb, &matView, &matProj);

	// Left clipping plane
	m_frustumPlanes[0].m_normal.x = matComb._14 + matComb._11; 
	m_frustumPlanes[0].m_normal.y = matComb._24 + matComb._21; 
	m_frustumPlanes[0].m_normal.z = matComb._34 + matComb._31; 
	m_frustumPlanes[0].m_distance = matComb._44 + matComb._41;

	// Right clipping plane 
	m_frustumPlanes[1].m_normal.x = matComb._14 - matComb._11; 
	m_frustumPlanes[1].m_normal.y = matComb._24 - matComb._21; 
	m_frustumPlanes[1].m_normal.z = matComb._34 - matComb._31; 
	m_frustumPlanes[1].m_distance = matComb._44 - matComb._41;

	// Top clipping plane 
	m_frustumPlanes[2].m_normal.x = matComb._14 - matComb._12; 
	m_frustumPlanes[2].m_normal.y = matComb._24 - matComb._22; 
	m_frustumPlanes[2].m_normal.z = matComb._34 - matComb._32; 
	m_frustumPlanes[2].m_distance = matComb._44 - matComb._42;

	// Bottom clipping plane 
	m_frustumPlanes[3].m_normal.x = matComb._14 + matComb._12; 
	m_frustumPlanes[3].m_normal.y = matComb._24 + matComb._22; 
	m_frustumPlanes[3].m_normal.z = matComb._34 + matComb._32; 
	m_frustumPlanes[3].m_distance = matComb._44 + matComb._42;

	// Near clipping plane 
	m_frustumPlanes[4].m_normal.x = matComb._13; 
	m_frustumPlanes[4].m_normal.y = matComb._23; 
	m_frustumPlanes[4].m_normal.z = matComb._33; 
	m_frustumPlanes[4].m_distance = matComb._43;

	// Far clipping plane 
	m_frustumPlanes[5].m_normal.x = matComb._14 - matComb._13; 
	m_frustumPlanes[5].m_normal.y = matComb._24 - matComb._23; 
	m_frustumPlanes[5].m_normal.z = matComb._34 - matComb._33; 
	m_frustumPlanes[5].m_distance = matComb._44 - matComb._43; 
}

bool objectTransform::SphereInFrustum(D3DXVECTOR3 position,float radius)
{
	D3DXVECTOR4 position4 = D3DXVECTOR4( position.x, position.y, position.z, 1.0f );


	for ( int i = 0; i < 6; i++ ) 
	{ 
		D3DXVECTOR4 frustumPlanes = D3DXVECTOR4(m_frustumPlanes[i].m_normal.x, 
											m_frustumPlanes[i].m_normal.y, 
											m_frustumPlanes[i].m_normal.z, 
											m_frustumPlanes[i].m_distance);

		// *1.5 on the radius ensures objects do not just dissapear from the edge of the screen
		// change it back to just "radius" to see object culling in effect
		if ( D3DXVec4Dot(&frustumPlanes,&position4 ) + radius*1.5 < 0 ) 
		{ 
			// Outside the frustum, reject it! 
			return false; 
		} 
	} 
	return true; 
}