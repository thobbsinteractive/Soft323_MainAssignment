#include "d3dApplication.h"

d3dApplication::d3dApplication()
{
	TimeElapsed = 0; 
	FPS = 0;
	d3dDevice = 0;
	playerShip;
	sun;
	gameDetail = 'l';
	width = 1024;
	height = 768;
};

d3dApplication::~d3dApplication()
{
	cleanUp();
};

bool d3dApplication::initialiseGeometery()
{
	bool loadOkay = false;

	D3DXVECTOR3 Pos = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	TheEnviroment.loadTextures(d3dDevice); // skybox

	gameObjects.setDevice(d3dDevice);

	//Load select mesh from path and Get a pointer to an ID3DXMesh in video memory containing the model data
	//And pointers to Vectors containing Material and Texture Data.
	loadOkay = cockpit.loadMeshIntoBuffer("models/high/cockpit.x",d3dDevice);
	loadOkay = fighter.loadMeshIntoBuffer("models/high/goodfighter.x",d3dDevice);

	playerShip.setDevice(d3dDevice);
	playerShip.setMesh(&cockpit);
	playerShip.setPosition(&Pos);
	playerShip.setRotation(&Rotation);
	playerShip.setScale(&Scale);

	Pos = D3DXVECTOR3(0,30,2000);
	Rotation = D3DXVECTOR3(0,0,0);

	gameObjects.addAIShip(&fighter,NULL,&Pos,&Rotation,&Scale,true);
	gameObjects.addPlayerShip(&playerShip);

	return loadOkay;
}

bool d3dApplication::initialiseCard()
{
	return true;
}

bool d3dApplication::initialiseShaders()
{
	return true;
}

void d3dApplication::initialiseFonts()
{
	//
	// Create a font object and initialize it.
	//

	Font = new CD3DFont("Times New Roman", 16, 0);
	Font->InitDeviceObjects(d3dDevice );
	Font->RestoreDeviceObjects();
}

void d3dApplication::setupCamera()
{
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH(
		& proj,
		D3DX_PI * 0.25f,
		(float)width / (float)height,
		1.0f,
		100000.0f);

	d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

	playerShip.setCamera(470,150);
}

void d3dApplication::setInitialRenderStates()
{
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);     //Default fillmode
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); //Default shademode
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);        //Turn culling on

	// Texture Filters

	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

void d3dApplication::drawVolumeShadows()
{

}

void d3dApplication::drawCockpit()
{
	playerShip.drawMesh();
}

void d3dApplication::drawSkyBox()
{	
	D3DXMATRIX sceneryScale,sceneryLocation;
	D3DXVECTOR3 pos;
	playerShip.getPosition(&pos);
	
	// Draw skybox
	D3DXMatrixScaling(&sceneryScale,10000.0f,10000.0f,10000.0f);
	D3DXMatrixTranslation(&sceneryLocation, pos.x,pos.y,pos.z);
	D3DXMATRIX World = sceneryScale * sceneryLocation;
	
	d3dDevice->SetTransform(D3DTS_WORLD, &World);
	TheEnviroment.draw();

}

void d3dApplication::setupLights()
{
		D3DXVECTOR3 pos(-1000,1000,-1000);
		D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);

	if(gameDetail == 'l')
	{
		D3DLIGHT9 light = sun.InitPointLight(&pos, &col);

		d3dDevice->SetLight(0, &light);
		d3dDevice->LightEnable(0, true);
		d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	}
}

////////////// TEMP /////////////////
void d3dApplication::Update_Camera()
{
	AIShip *temp;
	//playerShip.updateCamera();
	///
	
	setupCamera();

	D3DXMATRIX V;

	D3DXVECTOR3 up;
	D3DXVECTOR3 look;
	D3DXVECTOR3 pos;

	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	playerShip.getPosition(&look);
	pos = D3DXVECTOR3(0.0f, 100.0f,-100.0f);

	D3DXMatrixLookAtLH(&V, &pos,&look,&up);
	d3dDevice->SetTransform(D3DTS_VIEW, &V);

	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR3 cameraRotation;
	D3DXVECTOR3 AIShipPosition;

	playerShip.getPosition(&cameraPosition);
	playerShip.getRotation(&cameraRotation);

	for(int i = 0;i < 300;i++)
	{
		Values[i] = 0;
	}

	gameObjects.getShip(0,&temp);
	temp->getPosition(&AIShipPosition);
	float nothing = 0.0f;
	float angleOfCurrentObjective = playerShip.getAngleToRotate(&nothing,&nothing,&nothing,temp);

	// Display the position  and speed of the Dragon
	sprintf(Values, "Angle to rotate:%f\nPos:%f,%f,%f,\nRotation:%f,%f,%f,\nSpeedSet:%f\nCurrentSpeed:%f,\nAI_ShipStatus:%f,\nAI_ShipPos:%f,%f,%f,\nAI_ShipSetSpeed:%f\nAI_ShipSpeed:%f\nAI_ShipObjPos:%f,%f,%f",
		angleOfCurrentObjective,
		cameraPosition.x,cameraPosition.y,cameraPosition.z,
		cameraRotation.x,cameraRotation.y,cameraRotation.z,
		playerShip.getCurrentSpeedSetting(),
		playerShip.getCurrentSpeed(),
		temp->getHealth(),
		AIShipPosition.x,AIShipPosition.y,AIShipPosition.z,
		temp->getCurrentSpeedSetting(),
		temp->getCurrentSpeed(),
		temp->getObjectiveXPos(),temp->getObjectiveYPos(),temp->getObjectiveZPos());
	Values[299] = '\0'; // mark end of string
}

void d3dApplication::checkInputs(float timeDelta)
{
	//
	// Update the inputs to check for changes
	//
	input.checkInputs();
	
	if(keyPressesInput.fireKey == true)
	{
		playerShip.shoot();
	}

	if(keyPressesInput.forwardKey == true)
	{
		playerShip.modulateThrust(true);
		//playerShip.walk(8.0f * timeDelta,true);
	}

	if(keyPressesInput.backKey == true)
	{
		playerShip.modulateThrust(false);
		//playerShip.walk(-8.0f * timeDelta,true);
	}

	if(keyPressesInput.upKey == true)
	{
		//playerShip.pitch(2.0f * timeDelta);

	}

	if(keyPressesInput.downKey == true)
	{
		//playerShip.pitch(-2.0f * timeDelta);
	}

	if(keyPressesInput.leftKey == true)
	{

		playerShip.setThrusters(false, true);
		//playerShip.yaw(-2.0f * timeDelta);
	}
			
	if(keyPressesInput.rightKey == true)
	{
		playerShip.setThrusters(true, false);
		//playerShip.yaw(2.0f * timeDelta);
	}
}

void d3dApplication::updateObjects(float timeDelta)
{
	playerShip.update(timeDelta);
	gameObjects.updateAIShips(timeDelta);
}
void d3dApplication::calcFPS(float timeDelta)
{
	//
	// Update: Compute the frames per second.
	//
	FrameCnt++;
	TimeElapsed += timeDelta;

	if(TimeElapsed >= 1.0f)
	{
		FPS = (float)FrameCnt / TimeElapsed;

		sprintf(FPSString, "%f", FPS);
		FPSString[99] = '\0'; // mark end of string

		TimeElapsed = 0.0f;
		FrameCnt = 0;
	}
}

bool d3dApplication::run(HINSTANCE hInstance,HWND* mainWindowHandle,int width,int height)
{
	Capabilities configWindow;

	bool errors = false;
	float timeDelta = 0.0f;
	bool (d3dApplication::*ptr_displayFunction)(float timeDelta); // Pointer to a display function
	
	// Get card config and start device
	if (configWindow.getCapabilities(&width, &height,mainWindowHandle,&d3dDevice) == false)
	{
		MessageBox(NULL, "Card configuration failed", "FinalAssignment.exe", MB_OK);
		errors = true;
	}

	if (initialiseGeometery() == false)
	{
		MessageBox(NULL, "Loading geometry failed", "FinalAssignment.exe", MB_OK);
		errors = true;
	}

	if(input.setup_Input(&hInstance,mainWindowHandle,&keyPressesInput) == false)
	{
		MessageBox(NULL, "Direct Input config failed", "FinalAssignment.exe", MB_OK);
		errors = true;
	}

	if(errors == false)
	{
		switch(gameDetail)
		{
			case 'l': 
				ptr_displayFunction = &d3dApplication::renderLowDetail;
				setInitialRenderStates();
				break;
			case 'm': 
				ptr_displayFunction = &d3dApplication::renderMediumDetail;
				break;
			case 'h': 
				ptr_displayFunction = &d3dApplication::renderHighDetail;
				break;
			default:
				ptr_displayFunction = &d3dApplication::renderLowDetail;
				setInitialRenderStates();
		}

		// Setup game
		initialiseFonts();
		setupLights();
		setupCamera();

		// Enter message loop with selected detail
		EnterMsgLoop(ptr_displayFunction);
	}
	return true;
}

int d3dApplication::EnterMsgLoop( bool (d3dApplication::*ptr_displayFunction)(float timeDelta) )
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static float lastTime = (float)timeGetTime(); 

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
        {	
			float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;

			// Run the selected render detail function
			(this->*ptr_displayFunction)(timeDelta);

			lastTime = currTime;	
        }
    }
    return (int)msg.wParam;
}

bool d3dApplication::renderLowDetail(float timeDelta)
{
/* The Display method calls the IDirect3Ddevice9::Clear method
   ,which clears the backbuffer and depth/stencil buffer to the
   colour black. We also implement here any and all drawing code.
*/
	if(d3dDevice)
	{
		//
		// Render
		//
		calcFPS(timeDelta);
		Update_Camera();
		checkInputs(timeDelta);
		updateObjects(timeDelta);

		d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
		d3dDevice->BeginScene();

		drawSkyBox();
		gameObjects.drawObjects(timeDelta);
		drawCockpit();

		//Draw FPS
		if( Font )
		{
			Font->DrawText(20, 20, 0xffffffff, FPSString);
			Font->DrawText(20, 50, 0xffffffff, Values);
		};

		d3dDevice->EndScene();
		d3dDevice->Present(0, 0, 0, 0);
	}
	return true;
}

bool d3dApplication::renderMediumDetail(float timeDelta)
{
/* The Display method calls the IDirect3Ddevice9::Clear method
   ,which clears the backbuffer and depth/stencil buffer to the
   colour black. We also implement here any and all drawing code.
*/

	if(d3dDevice)
	{
	
		//
		// Render
		//

		d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
		d3dDevice->BeginScene();
		d3dDevice->EndScene();
		d3dDevice->Present(0, 0, 0, 0);
	}
	return true;
}

bool d3dApplication::renderHighDetail(float timeDelta)
{
/* The Display method calls the IDirect3Ddevice9::Clear method
   ,which clears the backbuffer and depth/stencil buffer to the
   colour black. We also implement here any and all drawing code.
*/

	if(d3dDevice)
	{
	
		//
		// Render
		//

		d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
		d3dDevice->BeginScene();
		d3dDevice->EndScene();
		d3dDevice->Present(0, 0, 0, 0);
	}
	return true;
}

void d3dApplication::cleanUp()
{

	if( Font )
	{
		Font->InvalidateDeviceObjects();
		Font->DeleteDeviceObjects();
		d3dApplication::Delete<CD3DFont*>(Font);
	}

	d3dDevice->Release();
}