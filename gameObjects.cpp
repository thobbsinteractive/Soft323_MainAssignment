#include "GameObjects.h"
#include "navPoint.h"

GameObjects::GameObjects()
{
	greenMaterial = new D3DMATERIAL9;
	redMaterial   = new D3DMATERIAL9;
	whiteMaterial = new D3DMATERIAL9;
	grayMaterial  = new D3DMATERIAL9;

	D3DCOLORVALUE green;
	D3DCOLORVALUE red;
	D3DCOLORVALUE white;
	D3DCOLORVALUE gray;

	green.r = 0.2f;
	green.b = 0.2f;
	green.g = 1.0f;
	green.a = 0.0f;

	red.r = 1.0f;
	red.b = 0.0f;
	red.g = 0.0f;
	red.a = 1.0f;

	white.r = 1.0f;
	white.b = 1.0f;
	white.g = 1.0f;
	white.a = 1.0f;

	gray.r = 0.5f;
	gray.b = 0.5f;
	gray.g = 0.5f;
	gray.a = 1.0f;

	greenMaterial->Diffuse = green;
	greenMaterial->Ambient = green;
	greenMaterial->Emissive = green;
	greenMaterial->Power = 0.8f;
	greenMaterial->Specular = green;

	redMaterial->Diffuse = red;
	redMaterial->Ambient = red;
	redMaterial->Emissive = red;
	redMaterial->Power = 1.0f;
	redMaterial->Specular = red;

	whiteMaterial->Diffuse = white;
	whiteMaterial->Ambient = white;
	whiteMaterial->Emissive = white;
	whiteMaterial->Power = 1.0f;
	whiteMaterial->Specular = white;

	grayMaterial->Diffuse = gray;
	grayMaterial->Ambient = gray;
	grayMaterial->Emissive = gray;
	grayMaterial->Power = 1.0f;
	grayMaterial->Specular = gray;
}
GameObjects::~GameObjects()
{
	cleanUP();
}

void GameObjects::addPlayerShip(PlayerShip* _playerShip)
{
	playerShip = _playerShip;	
}

void GameObjects::setMeshDetail(int detail)
{
	meshDetail = detail;
}

void GameObjects::setDevice(IDirect3DDevice9* _pDevice,CSoundManager* _soundManager)
{
	pLocalDevice = _pDevice;
	sound3Dmanager = _soundManager;

	D3DXCreateSphere(
		pLocalDevice,
		800,
		2,
		2,
		&sphereMesh,
		0);

	D3DXCreateBox(
		pLocalDevice,
		900,
		900,
		900,
		&targetMesh,
		0);

	D3DXCreateSphere(
		pLocalDevice,
		100,
		20,
		20,
		&radarMesh,
		0);

	D3DXCreateBox(
		pLocalDevice,
		10,
		2,
		2,
		&barMesh,
		0);

	plasmaSprite.setupSprite(pLocalDevice,100,100,"sprites/fireBall.dds"); // setup sprites
	targetReticuleFriendly.setupSprite(pLocalDevice,100,100,"sprites/targetReticuleFriendly.dds"); 
	targetReticuleEnemy.setupSprite(pLocalDevice,100,100,"sprites/targetReticuleEnemy.dds");

	reticuleNeutural.setupSprite(pLocalDevice,25,25,"sprites/targetReticuleFriendly.dds");
	reticuleEnemy.setupSprite(pLocalDevice,25,25,"sprites/targetReticuleEnemy.dds");

	texture.setupTexture(pLocalDevice);
	texture.addTexture("sprites/high/explosion/explosion00.dds");
	texture.addTexture("sprites/high/explosion/explosion01.dds");
	texture.addTexture("sprites/high/explosion/explosion02.dds");
	texture.addTexture("sprites/high/explosion/explosion03.dds");
	texture.addTexture("sprites/high/explosion/explosion04.dds");
	texture.addTexture("sprites/high/explosion/explosion05.dds");
	texture.addTexture("sprites/high/explosion/explosion06.dds");
	texture.addTexture("sprites/high/explosion/explosion07.dds");
	texture.addTexture("sprites/high/explosion/explosion08.dds");
	texture.addTexture("sprites/high/explosion/explosion09.dds");
	texture.addTexture("sprites/high/explosion/explosion10.dds");
	texture.addTexture("sprites/high/explosion/explosion11.dds");
	texture.addTexture("sprites/high/explosion/explosion12.dds");
	texture.addTexture("sprites/high/explosion/explosion13.dds");
	texture.addTexture("sprites/high/explosion/explosion14.dds");
	texture.addTexture("sprites/high/explosion/explosion15.dds");
	texture.addTexture("sprites/high/explosion/explosion16.dds");
	texture.addTexture("sprites/high/explosion/explosion17.dds");
	texture.addTexture("sprites/high/explosion/explosion18.dds");
	texture.addTexture("sprites/high/explosion/explosion19.dds");
	texture.addTexture("sprites/high/explosion/explosion20.dds");
	texture.addTexture("sprites/high/explosion/explosion21.dds");
	texture.addTexture("sprites/high/explosion/explosion22.dds");
	texture.addTexture("sprites/high/explosion/explosion23.dds");
	texture.addTexture("sprites/high/explosion/explosion24.dds");
	texture.addTexture("sprites/high/explosion/explosion25.dds");
	texture.addTexture("sprites/high/explosion/explosion26.dds");
	texture.addTexture("sprites/high/explosion/explosion27.dds");
	texture.addTexture("sprites/high/explosion/explosion28.dds");
	texture.addTexture("sprites/high/explosion/explosion29.dds");
	texture.addTexture("sprites/high/explosion/explosion30.dds");
	texture.addTexture("sprites/high/explosion/explosion31.dds");
	texture.addTexture("sprites/high/explosion/explosion32.dds");
	texture.addTexture("sprites/high/explosion/explosion33.dds");
	texture.addTexture("sprites/high/explosion/explosion34.dds");
	texture.addTexture("sprites/high/explosion/explosion35.dds");
	texture.addTexture("sprites/high/explosion/explosion36.dds");
	texture.addTexture("sprites/high/explosion/explosion37.dds");
	texture.addTexture("sprites/high/explosion/explosion38.dds");
	texture.addTexture("sprites/high/explosion/explosion39.dds");
	texture.addTexture("sprites/high/explosion/explosion40.dds");
	texture.addTexture("sprites/high/explosion/explosion41.dds");
	texture.addTexture("sprites/high/explosion/explosion42.dds");
	texture.addTexture("sprites/high/explosion/explosion43.dds");
	texture.addTexture("sprites/high/explosion/explosion44.dds");
	texture.addTexture("sprites/high/explosion/explosion45.dds");
	texture.addTexture("sprites/high/explosion/explosion46.dds");
	texture.addTexture("sprites/high/explosion/explosion47.dds");
	texture.addTexture("sprites/high/explosion/explosion48.dds");
	texture.addTexture("sprites/high/explosion/explosion49.dds");
	texture.addTexture("sprites/high/explosion/explosion50.dds");

	warpTexture.setupTexture(pLocalDevice);
	warpTexture.addTexture("sprites/high/warp/worm00.dds");
	warpTexture.addTexture("sprites/high/warp/worm01.dds");
	warpTexture.addTexture("sprites/high/warp/worm02.dds");
	warpTexture.addTexture("sprites/high/warp/worm03.dds");
	warpTexture.addTexture("sprites/high/warp/worm04.dds");
	warpTexture.addTexture("sprites/high/warp/worm05.dds");
	warpTexture.addTexture("sprites/high/warp/worm06.dds");
	warpTexture.addTexture("sprites/high/warp/worm07.dds");
	warpTexture.addTexture("sprites/high/warp/worm08.dds");
	warpTexture.addTexture("sprites/high/warp/worm09.dds");
	warpTexture.addTexture("sprites/high/warp/worm20.dds");
	warpTexture.addTexture("sprites/high/warp/worm21.dds");
	warpTexture.addTexture("sprites/high/warp/worm22.dds");
	warpTexture.addTexture("sprites/high/warp/worm23.dds");
	warpTexture.addTexture("sprites/high/warp/worm24.dds");
	warpTexture.addTexture("sprites/high/warp/worm25.dds");
	warpTexture.addTexture("sprites/high/warp/worm26.dds");
	warpTexture.addTexture("sprites/high/warp/worm27.dds");
	warpTexture.addTexture("sprites/high/warp/worm28.dds");
	warpTexture.addTexture("sprites/high/warp/worm29.dds");
	warpTexture.addTexture("sprites/high/warp/worm30.dds");
	warpTexture.addTexture("sprites/high/warp/worm31.dds");
	warpTexture.addTexture("sprites/high/warp/worm32.dds");
	warpTexture.addTexture("sprites/high/warp/worm33.dds");
	warpTexture.addTexture("sprites/high/warp/worm34.dds");
	warpTexture.addTexture("sprites/high/warp/worm35.dds");
	warpTexture.addTexture("sprites/high/warp/worm36.dds");
	warpTexture.addTexture("sprites/high/warp/worm37.dds");
	warpTexture.addTexture("sprites/high/warp/worm38.dds");
	warpTexture.addTexture("sprites/high/warp/worm39.dds");
	warpTexture.addTexture("sprites/high/warp/worm40.dds");
	warpTexture.addTexture("sprites/high/warp/worm41.dds");
	warpTexture.addTexture("sprites/high/warp/worm42.dds");
	warpTexture.addTexture("sprites/high/warp/worm43.dds");
	warpTexture.addTexture("sprites/high/warp/worm44.dds");
	warpTexture.addTexture("sprites/high/warp/worm45.dds");
	warpTexture.addTexture("sprites/high/warp/worm46.dds");
	warpTexture.addTexture("sprites/high/warp/worm47.dds");
	warpTexture.addTexture("sprites/high/warp/worm48.dds");
	warpTexture.addTexture("sprites/high/warp/worm49.dds");
	warpTexture.addTexture("sprites/high/warp/worm50.dds");

	navPointMesh.loadMeshIntoBuffer("models/low/navPoint.x",pLocalDevice);
}

void GameObjects::initialiseSounds(HWND handle)
{
	localHandle = handle;
	explosion.initialiseSound(pLocalDevice, _T("sound/explode.wav"),handle,sound3Dmanager);
}

void GameObjects::drawCockpit()
{
	D3DXMATRIX shipMatrix;
	D3DXMATRIX radarMatrix;
	D3DXMATRIX scalingMatrix;
	D3DXMATRIX shipRotationMatrix;
	
	D3DXVECTOR3 rotation;

	// Update the camera, this matrix must be set before all other movement
	playerShip->setChaseCameraMatrix();

	playerShip->drawMesh(1);

	// use alpha from texture
	//pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// Draw targeting Reticule
	if(true)
	{
		D3DXMatrixRotationYawPitchRoll(&shipRotationMatrix,0.0f,0.0f,0.0f);
		playerShip->getMatrix(&shipMatrix);

		D3DXMatrixTranslation(&radarMatrix, 0,165,50);
		D3DXMatrixScaling(&scalingMatrix,1.0f,1.0f,1.0f);

		shipMatrix = shipRotationMatrix * radarMatrix * scalingMatrix * shipMatrix;

		pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);
		reticuleNeutural.draw();


		// Draw arrow to targeted ship
		pLocalDevice->SetMaterial(whiteMaterial);
		pLocalDevice->SetTexture(0,NULL);

		pLocalDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);     //Default fillmode

		float x,y;

		D3DXVECTOR3 arrowPosition;

		// display objective pointer
		playerShip->getAnglesToRotateForPlayer(&x,&y,&arrowPosition);

			playerShip->getRotation(&rotation);
			rotation = rotation + D3DXVECTOR3(x,y,0);

			D3DXMatrixRotationYawPitchRoll(&shipRotationMatrix,rotation.x,rotation.y,rotation.z);
			D3DXMatrixTranslation(&shipMatrix, arrowPosition.x,arrowPosition.y,arrowPosition.z);
			D3DXMatrixScaling(&scalingMatrix,1.0f,1.0f,1.0f);
			playerShip->getRotation(&rotation);

			shipMatrix = shipRotationMatrix * scalingMatrix * shipMatrix;
			pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);
			playerShip->drawWithoutMatrix(5);

		pLocalDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);     //Default fillmode
	}

	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// Turn off light on cockpit screens
	pLocalDevice->SetRenderState(D3DRS_LIGHTING, false);

    pLocalDevice->SetRenderState(D3DRS_STENCILENABLE,    true);
    pLocalDevice->SetRenderState(D3DRS_STENCILFUNC,      D3DCMP_ALWAYS);
    pLocalDevice->SetRenderState(D3DRS_STENCILREF,       0x1);
    pLocalDevice->SetRenderState(D3DRS_STENCILMASK,      0xffffffff);
    pLocalDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
    pLocalDevice->SetRenderState(D3DRS_STENCILZFAIL,     D3DSTENCILOP_KEEP);
    pLocalDevice->SetRenderState(D3DRS_STENCILFAIL,      D3DSTENCILOP_KEEP);
    pLocalDevice->SetRenderState(D3DRS_STENCILPASS,      D3DSTENCILOP_REPLACE);

	// disable writes to the depth and back buffers
    pLocalDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
    pLocalDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
    pLocalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    // draw the radar to the stencil buffer
	playerShip->drawMesh(2);
	playerShip->drawMesh(3);
	playerShip->drawMesh(4);

	// Re enable lighting
	pLocalDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	// re-enable depth writes
	pLocalDevice->SetRenderState( D3DRS_ZWRITEENABLE, true );

	// only draw radar objects to the pixels where the radar
	// was drawn to.
	pLocalDevice->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_EQUAL);
    pLocalDevice->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP);

	// clear depth buffer and blend the radar objects with the radar
	pLocalDevice->SetRenderState(D3DRS_ZENABLE, false);
	pLocalDevice->SetRenderState(D3DRS_ZWRITEENABLE, false );

	pLocalDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_DESTCOLOR);
    pLocalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);


	// Finally, draw the radar objects
	pLocalDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);     //Default fillmode

	drawRadarObjects();

	pLocalDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);     //Default fillmode

	// Restore render states.
	pLocalDevice->SetRenderState(D3DRS_ZENABLE, true);
	pLocalDevice->SetRenderState(D3DRS_ZWRITEENABLE, true );

	pLocalDevice->SetRenderState(D3DRS_STENCILENABLE, false);	

	// Draw the AI ships status
	playerShip->displayTargetStatus();
}

void GameObjects::getShipList(std::vector<CapitalShip*> *_pShipList)
{
	*_pShipList = pShipList;
}

void GameObjects::drawRadarObjects()
{
	pLocalDevice->SetMaterial(whiteMaterial);
	pLocalDevice->SetTexture(0,NULL);

	D3DXMATRIX shipMatrix;
	D3DXMATRIX shipPositionMatrix;
	D3DXMATRIX currentPositionMatrix;
	D3DXMATRIX aiPosMatrix;
	D3DXMATRIX radarMatrix;
	D3DXMATRIX radarOffSet;
	D3DXMATRIX shipRotationMatrix;
	D3DXMATRIX scalingMatrix;

	D3DXVECTOR3 shipRotation = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 shipPosition = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 aiShipPos = D3DXVECTOR3(0,0,0);

	// Draw Player Ship status

	pLocalDevice->SetMaterial(whiteMaterial);

	int currentSpeed = (int)playerShip->getCurrentSpeed();
	int speedSetting = (int)playerShip->getCurrentSpeedSetting();
	int maxSpeed = (int)playerShip->getMaxSpeed();

	speedSetting = (10 / maxSpeed)*speedSetting; // Speed setting in units of ten

	if(currentSpeed > 0)
	{
		currentSpeed = (10 / maxSpeed)*currentSpeed; // current speed as percentage
	}else
	{
		currentSpeed = 0.0f;
	}

	D3DXMatrixRotationYawPitchRoll(&shipRotationMatrix,0.0f,0.0f,0.0f);

	pLocalDevice->SetMaterial(grayMaterial);

	// Draw background to speed bar
	for(int i = 0; i < 10; i++)
	{
		playerShip->getMatrix(&shipMatrix);

		D3DXMatrixTranslation(&radarMatrix, 190,-30+(5*i),0);
		D3DXMatrixScaling(&scalingMatrix,1.0f,1.0f,1.0f);

		shipMatrix = shipRotationMatrix * radarMatrix * scalingMatrix * shipMatrix;

		pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);
		barMesh->DrawSubset(0);
	}

	pLocalDevice->SetMaterial(whiteMaterial);

	// Draw current speed
	for(int i = 0; i < 10; i++)
	{
		if(currentSpeed >i+1)
		{
			playerShip->getMatrix(&shipMatrix);

			D3DXMatrixTranslation(&radarMatrix, 190,-30+(5*i),0);
			D3DXMatrixScaling(&scalingMatrix,1.0f,1.0f,1.0f);

			shipMatrix = shipRotationMatrix * radarMatrix * scalingMatrix * shipMatrix;

			pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);
			barMesh->DrawSubset(0);
		}
	}

	pLocalDevice->SetMaterial(redMaterial);

	// Draw current speed setting
	bool drawn = false;

	for(int i = 0; i < 10; i++)
	{
		if((speedSetting == i+1)&&(drawn == false))
		{
			drawn = true;
			playerShip->getMatrix(&shipMatrix);

			D3DXMatrixTranslation(&radarMatrix, 190,-30+(5*i),-2);
			D3DXMatrixScaling(&scalingMatrix,1.0f,1.0f,1.0f);

			shipMatrix = shipRotationMatrix * radarMatrix * scalingMatrix * shipMatrix;

			pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);
			barMesh->DrawSubset(0);
		}
	}


	playerShip->getRotation(&shipRotation);
	playerShip->getPosition(&shipPosition);
	D3DXMatrixRotationYawPitchRoll(&shipRotationMatrix,shipRotation.x,shipRotation.y,shipRotation.z);

	D3DXVECTOR3 radarScreenPos = D3DXVECTOR3(-140,20,-50);
	playerShip->getMatrix(&shipMatrix);

	// Draw Target Ship / Object
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getTargeted() == true)
		{
			if(pShipList[i]->getIFF() == false)
			{
				pLocalDevice->SetMaterial(redMaterial);
			}else
			{
				pLocalDevice->SetMaterial(greenMaterial);
			}

			if(pShipList[i]->isCapital() == true)
			{
				pShipList[i]->getTargetMatrix(radarScreenPos,0.0005,&radarMatrix);
			}else
			{
				pShipList[i]->getTargetMatrix(radarScreenPos,0.008,&radarMatrix);
			}
			shipMatrix = radarMatrix * shipMatrix;
			pLocalDevice->SetTransform(D3DTS_WORLD, &shipMatrix);

			pShipList[i]->drawWithoutMatrix(0); // Draw in lowest detail possible

			playerShip->setTargetShip(pShipList[i]);
		}
	}

	// Draw Radar screen

	pLocalDevice->SetMaterial(whiteMaterial);

	D3DXMATRIX scaling;
	D3DXMATRIX scaling2;
	D3DXMatrixTranslation(&shipPositionMatrix, shipPosition.x,shipPosition.y,shipPosition.z);

	// Radar Position
	D3DXMatrixTranslation(&radarMatrix,0,45,0);

	D3DXMatrixRotationYawPitchRoll(&radarOffSet,0.0f,0.02f,0.0f);

	D3DXMatrixScaling(&scaling2,1.0,0.1,1.0);
	D3DXMatrixScaling(&scaling,0.00005,0.00005,0.00005);

	shipPositionMatrix = shipPositionMatrix * radarMatrix;
	shipPositionMatrix = scaling2 * shipPositionMatrix;

	pLocalDevice->SetTransform(D3DTS_WORLD,&shipPositionMatrix);
	radarMesh->DrawSubset(0);

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getIFF() == false)
		{
			pLocalDevice->SetMaterial(redMaterial);
		}else
		{
			pLocalDevice->SetMaterial(greenMaterial);
		}

		pShipList[i]->getPosition(&aiShipPos);

		D3DXMatrixTranslation(&shipPositionMatrix, shipPosition.x,shipPosition.y,shipPosition.z);
		currentPositionMatrix = shipPositionMatrix * radarMatrix;
/*
		if(shipPosition.x == aiShipPos.x)
		{
			aiShipPos.x = shipPosition.x;
		}

		if((shipPosition.x > aiShipPos.x)&&(aiShipPos.x >= 0.0f)&&(shipPosition.x >= 0.0f))
		{
			aiShipPos.x = shipPosition.x - aiShipPos.x;
		}

		if((shipPosition.x < aiShipPos.x)&&(aiShipPos.x >= 0.0f)&&(shipPosition.x >= 0.0f))
		{
			aiShipPos.x = aiShipPos.x - shipPosition.x;
		}

		if((shipPosition.x > aiShipPos.x)&&(aiShipPos.x < 0.0f)&&(shipPosition.x >= 0.0f))
		{
			aiShipPos.x = -shipPosition.x + aiShipPos.x;
		}

		if((shipPosition.x < aiShipPos.x)&&(aiShipPos.x < 0.0f)&&(shipPosition.x < 0.0f))
		{
			aiShipPos.x = shipPosition.x + -aiShipPos.x;
		}

		///// Y ////////
		if(shipPosition.y == aiShipPos.y)
		{
			aiShipPos.y = shipPosition.y;
		}

		if((shipPosition.y > aiShipPos.y)&&(aiShipPos.y >= 0.0f)&&(shipPosition.y >= 0.0f))
		{
			aiShipPos.y = shipPosition.y - aiShipPos.y;
		}

		if((shipPosition.y < aiShipPos.y)&&(aiShipPos.y >= 0.0f)&&(shipPosition.y >= 0.0f))
		{
			aiShipPos.y = aiShipPos.y - shipPosition.y;
		}

		if((shipPosition.y > aiShipPos.y)&&(aiShipPos.y < 0.0f)&&(shipPosition.y >= 0.0f))
		{
			aiShipPos.y = -shipPosition.y + aiShipPos.y;
		}

		if((shipPosition.y < aiShipPos.y)&&(aiShipPos.y < 0.0f)&&(shipPosition.y < 0.0f))
		{
			aiShipPos.y = shipPosition.y + -aiShipPos.y;
		}
*/
		///// z /////////
		/*
		if(shipPosition.z == aiShipPos.z)
		{
			aiShipPos.z = shipPosition.z;
		}

		///////2
		if((shipPosition.z > aiShipPos.z)&&(aiShipPos.z >= 0.0f)&&(shipPosition.z >= 0.0f))
		{
			//float difference = aiShipPos.z - shipPosition.z;
			aiShipPos.z =  aiShipPos.z+(shipPosition.z - aiShipPos.z);
		}

		//////////// works
		if((shipPosition.z < aiShipPos.z)&&(aiShipPos.z >= 0.0f)&&(shipPosition.z >= 0.0f))
		{
			aiShipPos.z = aiShipPos.z - shipPosition.z;
		}

		if((shipPosition.z > aiShipPos.z)&&(aiShipPos.z < 0.0f)&&(shipPosition.z >= 0.0f))
		{
			aiShipPos.z = -shipPosition.z + aiShipPos.z;
		}

		///// 3 // works
		if((shipPosition.z < aiShipPos.z)&&(aiShipPos.z > 0.0f)&&(shipPosition.z < 0.0f))
		{
			aiShipPos.z = shipPosition.z-(aiShipPos.z - shipPosition.z);
		}

		/// 4 ///
		if((shipPosition.z > aiShipPos.z)&&(aiShipPos.z < 0.0f)&&(shipPosition.z < 0.0f))
		{
			aiShipPos.z = -shipPosition.z + aiShipPos.z;
		}

		// Seems to work
		if((shipPosition.z < aiShipPos.z)&&(aiShipPos.z < 0.0f)&&(shipPosition.z < 0.0f))
		{
			aiShipPos.z = -shipPosition.z + aiShipPos.z;
		}*/



		D3DXMatrixTranslation(&aiPosMatrix, aiShipPos.x,0.0f,aiShipPos.z);
		aiPosMatrix = aiPosMatrix * scaling;

		//shipPositionMatrix = (aiPosMatrix + shipPositionMatrix) * currentPositionMatrix;
		
		//shipPositionMatrix = aiPosMatrix * currentPositionMatrix;
		shipPositionMatrix = aiPosMatrix * currentPositionMatrix;
		pLocalDevice->SetTransform(D3DTS_WORLD, &shipPositionMatrix);
		sphereMesh->DrawSubset(0); // Draw as sphere

		if(pShipList[i]->getTargeted() == true)
		{
			pLocalDevice->SetMaterial(whiteMaterial);
			targetMesh->DrawSubset(0);
		}
	}
}

void GameObjects::initialiseSpaceDust()
{
	BoundingBox boundingBox;
	boundingBox.min = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	boundingBox.max = D3DXVECTOR3( 10000.0f, 10000.0f,10000.0f);
	dustSprites = new SpaceDust(&boundingBox, 5000);
	dustSprites->init(pLocalDevice, "sprites/snowflake.dds");
}

void GameObjects::drawSpaceDust()
{
	D3DXMATRIX World;
	D3DXMATRIX I;

	D3DXVECTOR3 shipPosition;

	playerShip->getPosition(&shipPosition);
	
	D3DXMatrixTranslation(&World,shipPosition.x,shipPosition.y,shipPosition.z);
	dustSprites->updateBoundingBoxPosition(shipPosition.x,shipPosition.y,shipPosition.z);
	pLocalDevice->SetTransform(D3DTS_WORLD, &I);
	dustSprites->render();
}

void GameObjects::updateAIShips(float timeDelta)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rotation;

	// count number of friendly and number of enemy ships
	int numberOfEnemy = 0;
	int numberOfFriendly = 0;

	int numberOfEnemyCap = 0;
	int numberOfFriendlyCap = 0;

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getIFF() == false)
		{
			if(pShipList[i]->isCapital() == true)
			{
				numberOfEnemyCap++;
			}
			numberOfEnemy++;
		}

		if(pShipList[i]->getIFF() == true)
		{
			if(pShipList[i]->isCapital() == true)
			{
				numberOfFriendlyCap++;
			}
			numberOfFriendly++;
		}
	}


	int index = 0;

	// Set targets for AI ship
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		// Select targets for friendlies fighters
		if((pShipList[i]->getIFF() == true)&&(pShipList[i]->getHasTarget() == false)&&(pShipList[i]->isCapital() == false))
		{
			if(numberOfEnemy > 0)
			{
				index = 0;
				// pick any enemy
				int f;

				f = (rand()%numberOfEnemy);

				// find its index
				for(int j = 0; j < (int)pShipList.size();j++)
				{
					if(pShipList[j]->getIFF() == false)
					{
						if(index == f)
						{
							pShipList[i]->setTargetShip(pShipList[j]);
						}
						index++;
					}
				}
			}
		}

		// Select targets for friendlies capitals
		if((pShipList[i]->getIFF() == true)&&(pShipList[i]->getHasTarget() == false)&&(pShipList[i]->isCapital()==true))
		{
			if(numberOfEnemyCap > 0)
			{
				index = 0;
				// pick any enemy
				int f = (rand() % numberOfEnemyCap);

				// find its index
				for(int j = 0; j < (int)pShipList.size();j++)
				{
					if(pShipList[j]->getIFF() == false)
					{
						if(index == f)
						{
							pShipList[i]->setTargetShip(pShipList[j]);
						}
						index++;
					}
				}
			}
		}

		// Select targets for enemy fighters includeing player
		if((pShipList[i]->getIFF() == false)&&(pShipList[i]->getHasTarget() == false)&&(pShipList[i]->isCapital() == false))
		{
			if(numberOfFriendly > 0)
			{
				index = 0;
				// pick any enemy
				int f;

				f = (rand()%numberOfFriendly);

				// target player
				//if(f == numberOfFriendly+1)
				//{
					//pShipList[i]->setTargetShip(playerShip);
				//}else
				//{
					// find its index
					for(int j = 0; j < (int)pShipList.size();j++)
					{
						if(pShipList[j]->getIFF() == true)
						{
							if(index == f)
							{
								pShipList[i]->setTargetShip(pShipList[j]);
							}
							index++;
						}
					}
				//}
			}
		}

		// Select targets for enemy capitals
		if((pShipList[i]->getIFF() == false)&&(pShipList[i]->getHasTarget() == false)&&(pShipList[i]->isCapital()==true))
		{
			if(numberOfFriendlyCap > 0)
			{
				index = 0;
				// pick any enemy
				int f = (rand() % numberOfFriendlyCap);

				// find its index
				for(int j = 0; j < (int)pShipList.size();j++)
				{
					if(pShipList[j]->getIFF() == true)
					{
						if(index == f)
						{
							pShipList[i]->setTargetShip(pShipList[j]);
						}
						index++;
					}
				}
			}
		}
	}


	// Update all AI ship positions and remove dead ships
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		pShipList[i]->getPosition(&pos);
		// If ship is warping in, create warp field effect
		if(pShipList[i]->isJumping() == true)
		{	
			Explosion* temp = new Explosion();
			animatedTexture* temp_ani = new animatedTexture();
			temp_ani->setupTexture(0.05,&warpTexture);
			temp->setupUpExplosion(pLocalDevice,1000,pShipList[i]->getBoundingRadius()*4,(rand() % 100) * 0.02f,pos,temp_ani);
			temp->setAsWarp(true);
			pExplosionsList.push_back(temp);

			pShipList[i]->setJumping(false); // so we dont keep adding warping effects to the list
		}

		// Check if ship is dieing
		if(pShipList[i]->getHealth() <= 0)
		{	
			Explosion* temp = new Explosion();
			animatedTexture* temp_ani = new animatedTexture();
			temp_ani->setupTexture(0.05,&texture);
			temp->setupUpExplosion(pLocalDevice,1000,pShipList[i]->getBoundingRadius()*2,(rand() % 100) * 0.02f,pos,temp_ani);
			pExplosionsList.push_back(temp);

			pShipList.erase(pShipList.begin() + i); // remove ship if it is dead
		}
	}

	// Check for collisions for player
	playerShip->getPosition(&pos);

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->highlevelCollisionDetection(pos))
		{
			if(pShipList[i]->lowlevelMeshCollisionDetection(playerShip))
			{
				if(playerShip->getCurrentSpeed() >= 0)
				{
					playerShip->setSpeed(-(playerShip->getCurrentSpeed()/2));
				}else
				{
					playerShip->setSpeed(playerShip->getCurrentSpeed());	
				}
				playerShip->decreaseHealth(2);
				playerShip->playSound(3,D3DXVECTOR3(0.0f,0.0f,0.0f));
			}
		}
	}

	bool highLevelCollision = false;
	float closestShipDistance;

	D3DXVECTOR3 avoidPosition;

	// Check for collisions for AI
	for(int j = 0; j < (int)pShipList.size();j++)
	{
		highLevelCollision = false;
		closestShipDistance = 100000000.0f;

		for(int i = 0; i < (int)pShipList.size();i++)
		{
			// so the ai wont avoid itself
			if(j != i)
			{
				if((pShipList[j]->highlevelCollisionDetection(pShipList[i]) == true))
				{
					// we only want capital ships to avoid each other
					if((pShipList[j]->isCapital() == true)&&(pShipList[i]->isCapital() == true))
					{
						pShipList[i]->getPosition(&avoidPosition);

						// avoid this ship unless we find one closer
						if(pShipList[j]->distanceToTarget(avoidPosition) < closestShipDistance);
						{
							closestShipDistance = pShipList[j]->distanceToTarget(avoidPosition);
							pShipList[j]->setAvoiding(true,(rand() % 20),pShipList[i]); // avoid from a random time
							highLevelCollision = true; // have collided
						}
					}

					if(pShipList[j]->isCapital() == false)
					{
						//pShipList[i]->getPosition(&avoidPosition);
						avoidPosition = pShipList[i]->getWhereShipIsGoingToBe();

						// avoid this ship unless we find one closer
						if(pShipList[j]->distanceToTarget(avoidPosition) < closestShipDistance);
						{
							closestShipDistance = pShipList[j]->distanceToTarget(avoidPosition);
							pShipList[j]->setAvoiding(true,(rand() % 20),pShipList[i]); // avoid from a random time
							highLevelCollision = true; // have collided
						}
					}
				}
			}

			// Check againts player ship
			
			if((pShipList[j]->highlevelCollisionDetection(playerShip) == true))
			{
				if(pShipList[j]->isCapital() == false)
				{
						playerShip->getPosition(&avoidPosition);

					// avoid this ship unless we find one closer
					if(pShipList[j]->distanceToTarget(avoidPosition) < closestShipDistance);
					{
						closestShipDistance = pShipList[j]->distanceToTarget(avoidPosition);
						pShipList[j]->setAvoiding(true,(rand() % 20),playerShip); // avoid from a random time
						highLevelCollision = true; // have collided
					}
				}
			}

			if(highLevelCollision == false)
			{
				pShipList[j]->setAvoiding(false); // stop avoiding
			}
		}
	}

	// Move all ships
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		pShipList[i]->manovering(timeDelta);
	}
}

void GameObjects::orientateSprites()
{
	playerShip->getRotation(&spriteOrientation);
}

void GameObjects::checkFire()
{
	D3DXVECTOR3 plasmaPosition;
	objectTransform plasmaBallObject;

	for(int i =0; i < playerShip->getNumberofFireBalls(); i++)
	{
		playerShip->getFireObject(i,&plasmaBallObject);
		plasmaBallObject.getPosition(&plasmaPosition);

		for(int j = 0; j < (int)pShipList.size();j++)
		{
			if(pShipList[j]->highlevelCollisionDetection(plasmaPosition) == true)
			{
				if(pShipList[j]->lowlevelCollisionDetection(&plasmaBallObject))
				{
					// Decrease the ships health
					pShipList[j]->decreaseHealth(2);

					// if the ship has been hit too many times
					// Evade
					if((pShipList[j]->getHealth() < 50)&&(pShipList[j]->isCapital() == false))
					{
						pShipList[j]->setAvoiding(true,(rand() % 10),playerShip); // avoid from a random time

						// one in three chance of this ship targeting you
						if((rand() % 2) == 1)
						{
							pShipList[j]->setTargetShip(playerShip);
						}
					}

					// Kill this fire ball
					playerShip->setFireHealth(i,0);
				}
			}
		}
	}


	// Check AI's shots
	for(int k = 0; k < (int)pShipList.size(); k++)
	{
		for(int i =0; i < pShipList[k]->getNumberofFireBalls(); i++)
		{
			pShipList[k]->getFireObject(i,&plasmaBallObject);
			plasmaBallObject.getPosition(&plasmaPosition);

			for(int j = 0; j < (int)pShipList.size();j++)
			{
				// Disclude the ship that is firing
				if(j != k)
				{
					if(pShipList[j]->highlevelCollisionDetection(plasmaPosition) == true)
					{
						if(pShipList[j]->lowlevelCollisionDetection(&plasmaBallObject))
						{
							// Decrease the ships health
							pShipList[j]->decreaseHealth(2);

							// if the ship has been hit too many times
							// Evade
							if((pShipList[j]->getHealth() < 50)&&(pShipList[j]->isCapital() == false))
							{
								pShipList[j]->setAvoiding(true,(rand() % 10),pShipList[k]); // avoid from a random time

								// one in three chance of this ship targeting you
								if((rand() % 2) == 1)
								{
									pShipList[j]->setTargetShip(pShipList[k]);
								}
							}

							// Kill this fire ball
							pShipList[k]->setFireHealth(i,0);
						}
					}
				}
			}

			// check if player is hit
			if(playerShip->highlevelCollisionDetection(plasmaPosition)== true)
			{
				if(playerShip->lowlevelCollisionDetection(&plasmaBallObject)== true)
				{
					playerShip->decreaseHealth(2);
					playerShip->playSound(3,D3DXVECTOR3(0.0f,0.0f,0.0f));
				}
			}
		}
	}
}

void GameObjects::sporneFriendly()
{
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if((pShipList[i]->getIFF() == true)&&(pShipList[i]->isCapital() == true))
		{
			pShipList[i]->launchFighter(pLocalDevice,&pShipList,localHandle,sound3Dmanager);
		}
	}	
}

void GameObjects::sporneEnemy()
{
	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if((pShipList[i]->getIFF() == false)&&(pShipList[i]->isCapital() == true))
		{
			pShipList[i]->launchFighter(pLocalDevice,&pShipList,localHandle,sound3Dmanager);
		}
	}	
}

void GameObjects::playSounds()
{
	D3DXVECTOR3 position;
	float lowestDistance = 1000000;
	int indexOfNearest[5] = {-1,-1,-1,-1};
	int lowestIndex;
	int j = 0;
	int k =0;

	//std::vector<CapitalShip*> pTempShipList;
	//std::vector<Explosion*> pTempExplosionsList;

	// play sounds for nearest 4 ships
	/*
	int listSize = (int)pShipList.size();
	float distance;

	for(int j =0; j < listSize; j++)
	{
		lowestIndex = -1;

		lowestDistance = 1000000; // reset lowest distance, only want to hear noises 100000 away

		for(int i =0; i < (int)pShipList.size(); i++)
		{
			pShipList[i]->getPosition(&position);
			distance = playerShip->distanceToTarget(position);

			// If lowest Distance (and has not been found before)
			if((distance < lowestDistance)&&
				(indexOfNearest[0] != i)&&
				(indexOfNearest[1] != i)&&
				(indexOfNearest[2] != i)&&
				(indexOfNearest[3] != i))
			{
				lowestIndex = i;
				indexOfNearest[k] = i;
			}
		}

		if(k < 4)
		{
			k++;
		}

		if(lowestIndex > -1)
		{
			pTempShipList.push_back(pShipList[lowestIndex]);
		}
	}
	*/

	// PlaySounds
	for(int i =0; i < (int)pShipList.size(); i++)
	{
		pShipList[i]->playSound(0,position);
	}

	// PlaySounds xplosion
	
	for(int i =0; i < (int)pExplosionsList.size(); i++)
	{
		D3DXVECTOR3 expPosition;
		// if explosion has just started
		if(pExplosionsList[i]->getCurrentTime() < 1.0f)
		{
			// start sound playing

			pExplosionsList[i]->getPosition(&expPosition);
			explosion.setSoundPos(expPosition,0.0f);

			explosion.stop();
			explosion.playSound3D();
		}else
		{

			pExplosionsList[i]->getPosition(&expPosition);
			explosion.setSoundPos(expPosition,0.0f);
			explosion.playSound3D();
		}
	}
}

void GameObjects::drawSprites(float timeDelta)
{

	orientateSprites();

	D3DXVECTOR3 spritePosition;

	D3DXMATRIX World;
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;

	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	float distance = 0.0f;
	float highestDistance = 0;
	int highestIndex;

	std::vector<Explosion*> pTempExplosionsList;

	// use alpha from texture
	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pLocalDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	pLocalDevice->SetRenderState(D3DRS_LIGHTING, false);
	

	// Reorder explosions according to distance from player, furthest are to be drawn first
	int listSize = (int)pExplosionsList.size();

	for(int j =0; j < listSize; j++)
	{
		highestIndex = -1;
		highestDistance = 0.0f; // reset highest distance

		for(int i =0; i < (int)pExplosionsList.size(); i++)
		{
			pExplosionsList[i]->getPosition(&position);
			distance = playerShip->distanceToTarget(position);

			// If highest Distance
			if(distance >= highestDistance)
			{
				highestIndex = i;
			}
		}

		if(highestIndex > -1)
		{
			pTempExplosionsList.push_back(pExplosionsList[highestIndex]);
			pExplosionsList.erase(pExplosionsList.begin() + highestIndex);
		}
	}

	// Copy reorganised contents across
	pExplosionsList = pTempExplosionsList;

	// Draw explosions
	for(int i =0; i < (int)pExplosionsList.size(); i++)
	{
		pExplosionsList[i]->getPosition(&spritePosition);

		// Ensure sprites too close to the cockpit are culled
		if(playerShip->distanceToTarget(spritePosition) > 1500)
		{
			pExplosionsList[i]->drawExplosion(timeDelta,spriteOrientation);
		}
		// Light nearest
		if(i == 0)
		{
			if(pExplosionsList[i]->getAsWarp() == true)
			{
				pExplosionsList[i]->setLight(D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.0f));
			}else
			{
				pExplosionsList[i]->setLight(D3DXCOLOR(1.0f, 1.0f, 0.5f, 0.0f));
			}
		}

		if(pExplosionsList[i]->isAlive() == false)
		{
			pExplosionsList.erase(pExplosionsList.begin() + i);
		}
	}

	// Draw sprites
	for(int i =0; i < playerShip->getNumberofFireBalls(); i++)
	{
		playerShip->getFireMatrix(i,&World);
		pLocalDevice->SetTransform(D3DTS_WORLD, &World);
		plasmaSprite.draw();
	}

	// Draw AI Sprites
	for(int i =0; i < pShipList.size(); i++)
	{
		for(int j =0; j < pShipList[i]->getNumberofFireBalls(); j++)
		{
			pShipList[i]->getAIFireMatrix(j,&World,spriteOrientation);
			pLocalDevice->SetTransform(D3DTS_WORLD, &World);
			plasmaSprite.draw();
		}
	}

	// Draw Target Reticules
	for(int i =0; i < pShipList.size(); i++)
	{
		if(pShipList[i]->getTargeted() == true)
		{
			pShipList[i]->getPosition(&position);
			playerShip->getRotation(&rotation);
			
			D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,rotation.z);
			D3DXMatrixTranslation(&Translation, position.x,position.y,position.z);
	
			World = RotationMatrix * Translation;

			pLocalDevice->SetTransform(D3DTS_WORLD, &World);
			
			if(pShipList[i]->getIFF() == true)
			{
				targetReticuleFriendly.setSize(pShipList[i]->getBoundingRadius()*2,pShipList[i]->getBoundingRadius()*2);	

				pShipList[i]->getPosition(&spritePosition);

				// Ensure sprites too close to the cockpit are culled
				if(playerShip->distanceToTarget(spritePosition) > 2000)
				{
					targetReticuleFriendly.draw();
				}
			}
			if(pShipList[i]->getIFF() == false)
			{
				
				targetReticuleEnemy.setSize(pShipList[i]->getBoundingRadius()*2,pShipList[i]->getBoundingRadius()*2);	
				
				pShipList[i]->getPosition(&spritePosition);

				// Ensure sprites too close to the cockpit are culled
				if(playerShip->distanceToTarget(spritePosition) > 1000)
				{
					targetReticuleEnemy.draw();
				}
			}
		}
	}


	//drawSpaceDust();

	pLocalDevice->SetRenderState(D3DRS_LIGHTING, true);
	pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void GameObjects::setDefaultRenderStates()
{
	pLocalDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pLocalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


// Developed with help from
// http://www.gamedev.net/reference/articles/article2019.asp

void GameObjects::drawObjectsWithVolumeShadow()
{
	//colour buffer OFF
	pLocalDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pLocalDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
	pLocalDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );

	//lighting OFF
	pLocalDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//depth buffer ON (write+test)
	pLocalDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pLocalDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//stencil buffer OFF
	pLocalDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );

	//FIRST PASS: render scene to the depth buffer

	drawObjects();

	//colour buffer ON
	pLocalDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pLocalDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
	pLocalDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	//ambient lighting ON
	pLocalDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	pLocalDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0) );
	pLocalDevice->LightEnable( 0, FALSE );
	pLocalDevice->LightEnable( 1, FALSE );
	pLocalDevice->LightEnable( 2, FALSE );
	pLocalDevice->LightEnable( 3, FALSE );

	//SECOND PASS: render scene to the colour buffer
	drawObjects();

    //clear stencil buffer
    pLocalDevice->Clear( 0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

    //turn OFF colour buffer
    pLocalDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    pLocalDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
    pLocalDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

    //disable lighting (not needed for stencil writes!)
    pLocalDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    //turn ON stencil buffer
    pLocalDevice->SetRenderState( D3DRS_STENCILENABLE, TRUE );
    pLocalDevice->SetRenderState( D3DRS_STENCILFUNC,  D3DCMP_ALWAYS );

    //render shadow volume
  
      //USE THE TRADITIONAL 2-PASS METHOD

      //set stencil to increment
      pLocalDevice->SetRenderState(   D3DRS_STENCILPASS, D3DSTENCILOP_INCR );
      //render front faces
      pLocalDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
      
	  drawObjects();

      //set stencil to decrement
      pLocalDevice->SetRenderState(   D3DRS_STENCILPASS, D3DSTENCILOP_DECR );
      //render back faces
      pLocalDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
      
	  drawObjects();

      pLocalDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );


    //alter stencil buffer
    pLocalDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_GREATER );
    pLocalDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );

    // turn on CURRENT light, turn off all others, we only care about sun 
	// light the first light
    pLocalDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    pLocalDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0) );
    pLocalDevice->LightEnable( 0,TRUE);
    
    //turn ON colour buffer
    pLocalDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    pLocalDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
    pLocalDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
    
    //render scene
    drawObjects();

    //reset any necessary render states
    pLocalDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );
}

void GameObjects::drawObjects()
{

	D3DXVECTOR3 shipPosition;
	float distanceFromPlayerShip;
	// use alpha from texture

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		// Check the ship can be seen by player
		if(playerShip->checkIfVisibleToThisObject(pShipList[i]))
		{

			// Check the distance to playerShip
			pShipList[i]->getPosition(&shipPosition);
			distanceFromPlayerShip = playerShip->distanceToTarget(shipPosition);
			
			// Scale graphics according to distance
			if(distanceFromPlayerShip <= 20000.0f)
			{
				if(meshDetail == 2)
				{
					pShipList[i]->drawMesh(2);
				}

				if(meshDetail == 1)
				{
					pShipList[i]->drawMesh(1);
				}

				if(meshDetail == 0)
				{
					pShipList[i]->drawMesh(0);
				}
			}

			if((distanceFromPlayerShip > 20000.0f)&&(distanceFromPlayerShip < 50000.0f))
			{
				if(meshDetail == 2)
				{
					pShipList[i]->drawMesh(1);
				}

				if(meshDetail == 1)
				{
					pShipList[i]->drawMesh(0);
				}

				if(meshDetail == 0)
				{
					pShipList[i]->drawMesh(0);
				}
			}

			if(distanceFromPlayerShip >= 50000.0f)
			{
				pShipList[i]->drawMesh(0);
			}
		}
	}
	//pLocalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

// Draws a selected object
void GameObjects::drawObjects(int index)
{

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
bool GameObjects::addObject(ViewObject* _pMesh,
			          CSound* _pSound,
					  D3DXVECTOR3 _pPos,
					  D3DXVECTOR3 _pRotation,
					  D3DXVECTOR3 _pScale)
{
	Ship* temp = new Ship();
		
	if(_pMesh)
	{
		temp->setMesh(_pMesh);
	}

	
	//if(_pSound)
	//{
	//	temp->addObjectSound(engineSound);
	//}

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

	temp->setDevice(pLocalDevice);

	pObjectsList.push_back(temp);
	return true;

}

bool GameObjects::addAIShip(ViewObject* _pMeshL,
							ViewObject* _pMeshM,
							ViewObject* _pMeshH,
			          CSound* _pSound,
					  D3DXVECTOR3 _pPos,
					  D3DXVECTOR3 _pRotation,
					  D3DXVECTOR3 _pScale,
					  bool _friendly,
					  std::vector<NavPoint*> navPointsList,
					  bool critical,
					  bool jumping,
					  std::string comments)
{
	// All AI ships are created as capital, this works fine unless someone 
	// is stupid enought to call launch Fighters without the meshes setup
	CapitalShip* temp = new CapitalShip();
	
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

	/*
	if(_pSound)
	{
		temp->addObjectSound(_pSound);
	}*/

	temp->addObjectSound(_T("sound/engine.wav"),localHandle,sound3Dmanager);
	temp->addObjectSound(_T("sound/fire.wav"),localHandle,sound3Dmanager);

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

	temp->setComment(comments);

	temp->setMissionCritical(critical);

	temp->setIFF(_friendly);

	temp->setDevice(pLocalDevice);

	temp->setJumping(jumping);

	temp->setCapital(false);

	for(int i =0;i < (int)navPointsList.size();i++)
	{
		temp->addNavPoint(*navPointsList.at(i));
	}
	temp->getNextNavPoint();

	pShipList.push_back(temp);
	return true;

}

bool GameObjects::addAICapShip(ViewObject* _pMeshL,
							ViewObject* _pMeshM,
							ViewObject* _pMeshH,
							ViewObject* _pFighterMeshL,
							ViewObject* _pFighterMeshM,
							ViewObject* _pFighterMeshH,
							CSound* _fighterSound,
							CSound* _pSound,
							D3DXVECTOR3 _pPos,
							D3DXVECTOR3 _pRotation,
							D3DXVECTOR3 _pScale,
							bool _friendly,
							std::vector<NavPoint*> navPointsList,
							bool critical,
							bool jumping,
							std::string comments,
							bool isPlayerCarrier)
{
	CapitalShip* temp = new CapitalShip(_pFighterMeshL,_pFighterMeshM,_pFighterMeshH,_fighterSound);
	
	
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

	
	//if(_pSound)
	//{
	temp->addObjectSound(_T("sound/engine.wav"),localHandle,sound3Dmanager);
	temp->addObjectSound(_T("sound/fire.wav"),localHandle,sound3Dmanager);
	//}

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

	temp->setMissionCritical(critical);

	temp->setIFF(_friendly);

	temp->setDevice(pLocalDevice);

	temp->setComment(comments);

	temp->setJumping(jumping);

	temp->setAsPlayerCarrier(isPlayerCarrier);

	/*
	for(int i =0;i < (int)navPointsList.size();i++)
	{
		temp->addNavPoint(*navPointsList.at(i));
	}
	temp->getNextNavPoint();
	*/

	temp->setCapital(true);

	pShipList.push_back(temp);
	return true;

}

void GameObjects::getShip(int index,CapitalShip** selectedShip)
{
	*selectedShip = pShipList[index];
}

bool GameObjects::setObjectMesh(int index,ViewObject* _pMesh)
{
	pObjectsList[index]->setMesh(_pMesh);
	return true;
}

bool GameObjects::setObjectSound(int index,CSound* _pSound)
{
	return true;
}

bool GameObjects::setObjectLocation(int index,D3DXVECTOR3* _pPos)
{
	return true;
}

bool GameObjects::setObjectRotation(int index,D3DXVECTOR3* _pRotation)
{
	return true;
}

bool GameObjects::setObjectScale(int index,D3DXVECTOR3* _pScale)
{
	return true;
}

void GameObjects::targetNextFriendly()
{
	bool targetSelected =false;
	int targetIndex = -1;

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getTargeted() == true)
		{
			pShipList[i]->setTargeted();
			targetIndex = i;
			// Un set this ship as the target
		}
	}

	// If there was a previous target
	if(targetIndex > -1)
	{
		// Look through the rest of the list for another target
		for(int i = targetIndex+1; i < (int)pShipList.size();i++)
		{
			if((pShipList[i]->getIFF() == true)&&(targetSelected == false))
			{
				pShipList[i]->setTargeted();
				targetSelected = true;
			}
		}
	}

	// If none was found start at the beginning looking from any friendly target
	if(targetSelected == false)
	{
		for(int i = 0; i < (int)pShipList.size();i++)
		{
			if((pShipList[i]->getIFF() == true)&&(targetSelected == false))
			{
				pShipList[i]->setTargeted();
				targetSelected = true;
			}
		}
	}
}

void GameObjects::targetNextEnemy()
{
	bool targetSelected =false;
	int targetIndex = -1;

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getTargeted() == true)
		{
			pShipList[i]->setTargeted();
			targetIndex = i;
			// Un set this ship as the target
		}
	}

	// If there was a previous target
	if(targetIndex > -1)
	{
		// Look through the rest of the list for another target
		for(int i = targetIndex+1; i < (int)pShipList.size();i++)
		{
			if((pShipList[i]->getIFF() == false)&&(targetSelected == false))
			{
				pShipList[i]->setTargeted();
				targetSelected = true;
			}
		}
	}

	// If none was found, start at the beginning looking from any friendly target
	if(targetSelected == false)
	{
		for(int i = 0; i < (int)pShipList.size();i++)
		{
			if((pShipList[i]->getIFF() == false)&&(targetSelected == false))
			{
				pShipList[i]->setTargeted();
				targetSelected = true;
			}
		}
	}
}

void GameObjects::targetNearestEnemy()
{
	D3DXVECTOR3 position;

	for(int i = 0; i < (int)pShipList.size();i++)
	{
		if(pShipList[i]->getTargeted() == true)
		{
			pShipList[i]->setTargeted();
			// Un set this ship as the target
		}
	}

	float lowestDistance = FLT_MAX;
	int lowestIndex = -1;
	float distance;

	for(int i =0; i < (int)pShipList.size(); i++)
	{
		if(pShipList[i]->getIFF() == false)
		{
			pShipList[i]->getPosition(&position);
			distance = playerShip->distanceToTarget(position);

			// If lowest Distance (and has not been found before)
			if(distance < lowestDistance)
			{
				lowestIndex = i;
			}
		}
	}

	if(lowestIndex > -1)
	{	
		pShipList[lowestIndex]->setTargeted();	
	}

}

//-----------------------------------------------------------------------------
// Name: BuildFromMesh()
// Desc: Takes a mesh as input, and uses it to build a shadowvolume. The
//       technique used considers each triangle of the mesh, and adds it's
//       edges to a temporary list. The edge list is maintained, such that
//       only silohuette edges are kept. Finally, the silohuette edges are
//       extruded to make the shadow volume vertex list.
//-----------------------------------------------------------------------------
void GameObjects::BuildFromMesh( ID3DXMesh* pMesh, D3DXVECTOR3 vLight )
{

    // Note: the MESHVERTEX format depends on the FVF of the mesh
    struct MESHVERTEX { D3DXVECTOR3 p, n; FLOAT tu, tv; };
    MESHVERTEX* pVertices;
    WORD*       pIndices;

    // Lock the geometry buffers
    pMesh->LockVertexBuffer( 0L, (LPVOID*)&pVertices );
    pMesh->LockIndexBuffer( 0L, (LPVOID*)&pIndices );
    DWORD dwNumFaces    = pMesh->GetNumFaces();

    // Allocate a temporary edge list
    WORD* pEdges = new WORD[dwNumFaces*6];
    if( pEdges == NULL )
    {
        pMesh->UnlockVertexBuffer();
        pMesh->UnlockIndexBuffer();
    }
    DWORD dwNumEdges = 0;

    // For each face
    for( DWORD i=0; i<dwNumFaces; i++ )
    {
        WORD wFace0 = pIndices[ 3 * i + 0 ];
        WORD wFace1 = pIndices[ 3 * i + 1 ];
        WORD wFace2 = pIndices[ 3 * i + 2 ];

        D3DXVECTOR3 v0 = pVertices[ wFace0 ].p;
        D3DXVECTOR3 v1 = pVertices[ wFace1 ].p;
        D3DXVECTOR3 v2 = pVertices[ wFace2 ].p;

        // Transform vertices or transform light?
        D3DXVECTOR3 vCross1(v2-v1);
        D3DXVECTOR3 vCross2(v1-v0);
        D3DXVECTOR3 vNormal;
        D3DXVec3Cross( &vNormal, &vCross1, &vCross2 );

        if( D3DXVec3Dot( &vNormal, &vLight ) >= 0.0f )
        {
            AddEdge( pEdges, dwNumEdges, wFace0, wFace1 );
            AddEdge( pEdges, dwNumEdges, wFace1, wFace2 );
            AddEdge( pEdges, dwNumEdges, wFace2, wFace0 );
        }
    }

    for(int i = 0; i < dwNumEdges; i++)
    {
		
        D3DXVECTOR3 v1 = pVertices[pEdges[2*i+0]].p;
        D3DXVECTOR3 v2 = pVertices[pEdges[2*i+1]].p;
		D3DXVECTOR3 v3 = v1 - vLight*500;
		D3DXVECTOR3 v4 = v2 - vLight*500;

        // Add a quad (two triangles) to the vertex list
        m_pVertices[m_dwNumVertices++] = v1;
        m_pVertices[m_dwNumVertices++] = v2;
        m_pVertices[m_dwNumVertices++] = v3;

        m_pVertices[m_dwNumVertices++] = v2;
        m_pVertices[m_dwNumVertices++] = v4;
        m_pVertices[m_dwNumVertices++] = v3;
    }

    // Delete the temporary edge list
    delete[] pEdges;

    // Unlock the geometry buffers
    pMesh->UnlockVertexBuffer();
    pMesh->UnlockIndexBuffer();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the volume geometry, assumes that stencil buffer is already
//		 configured correctly.
//-----------------------------------------------------------------------------
void GameObjects::RenderShadowGeometry()
{
    pLocalDevice->SetFVF( D3DFVF_XYZ );
	//pLocalDevice->SetTransform( D3DTS_WORLD, &m_matWorld );

    pLocalDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, m_dwNumVertices/3,
                                        m_pVertices, sizeof(D3DXVECTOR3) );
}

void GameObjects::AddEdge( WORD* pEdges, DWORD& dwNumEdges, WORD v0, WORD v1 )
{
    // Remove interior edges (which appear in the list twice)
    for( DWORD i=0; i < dwNumEdges; i++ )
    {
        if( ( pEdges[2*i+0] == v0 && pEdges[2*i+1] == v1 ) ||
            ( pEdges[2*i+0] == v1 && pEdges[2*i+1] == v0 ) )
        {
            if( dwNumEdges > 1 )
            {
                pEdges[2*i+0] = pEdges[2*(dwNumEdges-1)+0];
                pEdges[2*i+1] = pEdges[2*(dwNumEdges-1)+1];
            }
            dwNumEdges--;
            return;
        }
    }

    pEdges[2*dwNumEdges+0] = v0;
    pEdges[2*dwNumEdges+1] = v1;
    dwNumEdges++;
}

void GameObjects::cleanUP()
{
	for(int i =0;i < (int)pShipList.size();i++)
	{
		pShipList.erase(pShipList.begin() + i);
	}
/*
	for(int i =0;i < (int)navPointsList.size();i++)
	{
		navPointsList.erase(navPointsList.begin() + i);
	}
*/
	for(int i =0;i < (int)pObjectsList.size();i++)
	{
		pObjectsList.erase(pObjectsList.begin() + i);
	}

	for(int i =0;i < (int)pExplosionsList.size();i++)
	{
		pExplosionsList.erase(pExplosionsList.begin() + i);
	}

	sphereMesh->Release();
	radarMesh->Release();
	barMesh->Release();
	targetMesh->Release();

	delete dustSprites;
	delete greenMaterial;
	delete redMaterial;
	delete whiteMaterial;
	delete grayMaterial;
}