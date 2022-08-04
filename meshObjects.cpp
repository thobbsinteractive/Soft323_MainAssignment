#include "meshObjects.h"
#include "navPoint.h"

MeshObjects::MeshObjects()
{
	loadNavPoints();
	cullingAngle = D3DXToRadian(30); //30 degrees
	
}
MeshObjects::~MeshObjects()
{

}

void MeshObjects::addPlayerShip(Ship* _playerShip)
{
	playerShip = _playerShip;	
}

void MeshObjects::setDevice(IDirect3DDevice9* _pDevice)
{
	pLocalDevice = _pDevice;
	plasmaSprite.setupSprite(pLocalDevice,100,100,"sprites/fireBall.dds"); // setup sprites
}

void MeshObjects::updateAIShips(float timeDelta)
{
	int numberOfEnemies = 0;

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getIFF() == false)
		{
			numberOfEnemies++;
		}
	}

	// if number of enemies is is greater than 0, assign enimies
	if(numberOfEnemies > 0)
	{
		for(int i = 0; i < (int)pShipList.size();i++)
		{
			
		}
	}

	// Update all AI ship positions
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		pShipList[i]->behavior(8.0f * timeDelta);
	}


}

bool MeshObjects::loadNavPoints()
{
	NavPoint* tempNav = new NavPoint();
	tempNav->index = 0;
	tempNav->location = D3DXVECTOR3(0.0f, 0.0f,10000.0f);
	tempNav->visited = false;

	navPointsList.push_back(tempNav);

	NavPoint* tempNav2 = new NavPoint();
	tempNav2->index = 1;
	tempNav2->location = D3DXVECTOR3(0.0f, 10.0f,20000.0f);
	tempNav2->visited = false;

	navPointsList.push_back(tempNav2);

	NavPoint* tempNav3 = new NavPoint();
	tempNav3->index = 2;
	tempNav3->location = D3DXVECTOR3(0.0f, 5.0f,30000.0f);
	tempNav3->visited = false;

	navPointsList.push_back(tempNav3);

	return true;

}

void MeshObjects::orientateSprites()
{
	playerShip->getRotation(&spriteOrientation);
}

void MeshObjects::checkFire()
{
	D3DXVECTOR3 plasmaPosition;
	for(int i =0; i < playerShip->getNumberofFireBalls(); i++)
	{
		playerShip->getFirePosition(i,&plasmaPosition);

		for(int j = 0; j < (int)pShipList.size();j++)
		{
			if(pShipList[j]->highlevelCollisionDetection(plasmaPosition) == true)
			{
				// Decrease the ships health
				pShipList[j]->decreaseHealth(20);

				// Kill this fire ball
				playerShip->setFireHealth(i,0);
			}
		}
	}
}

void MeshObjects::drawSprites()
{
	orientateSprites();

	D3DXMATRIX World;
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);

	for(int i =0; i < playerShip->getNumberofFireBalls(); i++)
	{
		playerShip->getFireMatrix(i,&World);
		pLocalDevice->SetTransform(D3DTS_WORLD, &World);
		plasmaSprite.draw();
	}
}

void MeshObjects::drawObjects(float timeDelta)
{

	D3DXVECTOR3 shipPosition;

	// use alpha from texture

	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pLocalDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pLocalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		// Check the ship can be seen by player
		//if(playerShip->checkIfVisibleToThisObject(pShipList[i],30) == true)
		//{
			pShipList[i]->drawMesh();

			if(pShipList[i]->getTargeted() == true)
			{
				//
				// Draw bounding volume in blue and at 10% opacity
				D3DMATERIAL9 blue;
				blue.Ambient  = BLUE;
				blue.Diffuse  = BLUE;
				blue.Specular = BLUE;
				blue.Emissive = BLACK;
				blue.Power    = 0.2f;

				blue.Diffuse.a = 0.10f; // 10% opacity

				pLocalDevice->SetMaterial(&blue);
				pLocalDevice->SetTexture(0, 0); // disable texture

				pShipList[i]->drawMeshBounding();

				//TEMP
				playerShip->getPosition(&shipPosition);
				pShipList[i]->setTargetPosition(shipPosition);
				pShipList[i]->turn(timeDelta);
			}

			// Check for collisions with player (TEMP)

			if(playerShip->highlevelCollisionDetection(pShipList[i]))
			{
				playerShip->setSpeed(-20);
			}
		//}
	}
	drawSprites();
	checkFire();
	
	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}


// Draws a selected object
void MeshObjects::drawObjects(int index)
{
	// use alpha from texture
	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pLocalDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pLocalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pShipList[index]->drawMesh();

	if(pShipList[index]->getTargeted() == true)
	{
		//
		// Draw bounding volume in blue and at 10% opacity
		D3DMATERIAL9 blue;
		blue.Ambient  = BLUE;
		blue.Diffuse  = BLUE;
		blue.Specular = BLUE;
		blue.Emissive = BLACK;
		blue.Power    = 0.2f;

		blue.Diffuse.a = 0.10f; // 10% opacity

		pLocalDevice->SetMaterial(&blue);
		pLocalDevice->SetTexture(0, 0); // disable texture

		pShipList[index]->drawMeshBounding();
	}
}

// Add an object to the vector of objects
bool MeshObjects::addObject(ViewObject* _pMesh,
			          CSound* _pSound,
					  D3DXVECTOR3* _pPos,
					  D3DXVECTOR3* _pRotation,
					  D3DXVECTOR3* _pScale)
{
	Ship* temp = new Ship();
		
	if(_pMesh)
	{
		temp->setMesh(_pMesh);
	}

	
	if(_pSound)
	{
		temp->addObjectSound(_pSound);
	}

	if(_pPos)
	{
		temp->setPosition(_pPos);
	}

	if(_pRotation)
	{
		temp->setRotation(_pRotation);
	}

	if(_pScale)
	{
		temp->setScale(_pScale);
	}

	temp->setTargeted();

	temp->setDevice(pLocalDevice);

	pObjectsList.push_back(temp);
	return true;

}

bool MeshObjects::addAIShip(ViewObject* _pMesh,
			          CSound* _pSound,
					  D3DXVECTOR3* _pPos,
					  D3DXVECTOR3* _pRotation,
					  D3DXVECTOR3* _pScale,
					  bool _friendly)
{
	AIShip* temp = new AIShip();
		
	if(_pMesh)
	{
		temp->setMesh(_pMesh);
	}

	
	if(_pSound)
	{
		temp->addObjectSound(_pSound);
	}

	if(_pPos)
	{
		temp->setPosition(_pPos);
	}

	if(_pRotation)
	{
		temp->setRotation(_pRotation);
	}

	if(_pScale)
	{
		temp->setScale(_pScale);
	}

	temp->setIFF(_friendly);

	temp->setTargeted();

	temp->setDevice(pLocalDevice);

	for(int i =0;i < (int)navPointsList.size();i++)
	{
		temp->addNavPoint(*navPointsList.at(i));
	}
	temp->getNextNavPoint();

	pShipList.push_back(temp);
	return true;

}

void MeshObjects::getShip(int index,AIShip** selectedShip)
{
	*selectedShip = pShipList[index];
}

bool MeshObjects::setObjectMesh(int index,ViewObject* _pMesh)
{
	pObjectsList[index]->setMesh(_pMesh);
	return true;
}

bool MeshObjects::setObjectSound(int index,CSound* _pSound)
{
	return true;
}

bool MeshObjects::setObjectLocation(int index,D3DXVECTOR3* _pPos)
{
	return true;
}

bool MeshObjects::setObjectRotation(int index,D3DXVECTOR3* _pRotation)
{
	return true;
}

bool MeshObjects::setObjectScale(int index,D3DXVECTOR3* _pScale)
{
	return true;
}

void MeshObjects::cleanUP()
{
}