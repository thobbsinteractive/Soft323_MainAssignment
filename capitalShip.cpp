#include "capitalShip.h"

CapitalShip::CapitalShip(ViewObject* fighterMeshL,
		ViewObject* fighterMeshM,
		ViewObject* fighterMeshH,
		CSound* fighterSound)
{
	_pMeshL = fighterMeshL;
	_pMeshM = fighterMeshM;
	_pMeshH = fighterMeshH;
	_pSound = fighterSound;

	bayLocation = D3DXVECTOR3(0.0f,-10000.0f,-18000.0f);
	turnSpeed = 0.1f;

	isPlayerCarrier = false;
	capital = false;
};

CapitalShip::CapitalShip()
{
	isPlayerCarrier = false;
};

CapitalShip::~CapitalShip()
{
	for(int i = 0; i < (int)navPointsList.size(); i++)
	{
		navPointsList.erase(navPointsList.begin() + i);
	}
}

void CapitalShip::setAsPlayerCarrier(bool value)
{
	isPlayerCarrier = value;
	capital = true;
}

bool CapitalShip::getIsPlayerCarrier()
{
	return isPlayerCarrier;
}

D3DXVECTOR3 CapitalShip::getBayLocation()
{
	D3DXVECTOR3 _pPos;
	updatePositionInRelationTo(bayLocation,rotation,&_pPos);

	return _pPos;
}

void CapitalShip::launchFighter(IDirect3DDevice9* _pDevice,std::vector<CapitalShip*>* _pShipList,HWND localHandle,CSoundManager* sound3Dmanager)
{
	CapitalShip* temp = new CapitalShip();
	D3DXVECTOR3 _pScale;
	D3DXVECTOR3 _pPos;
	D3DXVECTOR3 _pRotation;
	D3DXMATRIX translationTemp;
	D3DXMATRIX rotationTemp;

	updatePositionInRelationTo(bayLocation,rotation,&_pPos);
	
	_pRotation = rotation;
	_pScale = scale;

	if(_pMeshL)
	{
		temp->setMesh(_pMeshL);
	}

	if(_pMeshM)
	{
		temp->setMesh(_pMeshM);
	}

	if(_pMeshH)
	{
		temp->setMesh(_pMeshH);
	}

	
	temp->addObjectSound("sound/engine.wav",localHandle,sound3Dmanager);
	temp->addObjectSound("sound/fire.wav",localHandle,sound3Dmanager);

	if(_pPos)
	{
		temp->setPosition(&_pPos);
	}

	if(_pRotation)
	{
		temp->setRotation(&_pRotation);
	}

	if(_pScale)
	{
		temp->setScale(&_pScale);
	}

	temp->setIFF(getIFF());

	temp->setDevice(_pDevice);

	for(int i =0;i < (int)navPointsList.size();i++)
	{
		temp->addNavPoint(*navPointsList.at(i));
	}
	temp->isLaunching(1000000);

	_pShipList->push_back(temp);
}

bool CapitalShip::highlevelCollisionDetection(objectTransform* objectToCheckAgainst)
{
	
	ViewObject* objectsMesh;
	D3DXVECTOR3 objectsPosition;

	objectToCheckAgainst->getPosition(&objectsPosition);

	objectToCheckAgainst->getMesh(&objectsMesh);

	// For cap ships we need to check ahead due to their size
	if(capital == true)
	{
		D3DXVECTOR3 newPosition;
		updatePositionInRelationTo(D3DXVECTOR3(0.0f,0.0f,50000.0f),rotation,&newPosition);
		return objectsMesh->isPointInsideBoundingBox(&objectsPosition,&newPosition);
	}else
	{
		return objectsMesh->isPointInsideBoundingBox(&objectsPosition,&pos);
	}
}

bool CapitalShip::highlevelCollisionDetection(D3DXVECTOR3 objectsPosition)
{
	return pMeshObjects[0]->isPointInsideBoundingBox(&objectsPosition,&pos);
}
