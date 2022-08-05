#include "d3dApplication.h"

d3dApplication::d3dApplication()
{
	TimeElapsed = 0; 
	FPS = 0;
	d3dDevice = 0;
	playerShip;
	sun;
	gameDetail = 'l';
	meshDetail = 2;
	maxTextureSize = 0;
	keyPressTime = 0;
	i =0;
	gameRunning = true;
	sound3Dmanager = new CSoundManager();
};

d3dApplication::~d3dApplication()
{
	cleanUp();
};

bool d3dApplication::initialiseGeometery()
{
	bool loadOkay = false;

	D3DXVECTOR3 Pos = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0*(D3DX_PI/180),0,0);
	D3DXVECTOR3 Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	// Select skybox texture according to size
	if((maxTextureSize/2) < 129)
	{
		TheEnviroment.loadMeshIntoBuffer("models/low/skyBox.x",
										  "sky/low/spaceBoxBack.jpg",
										  "sky/low/spaceBoxFront.jpg",
										  "sky/low/spaceBoxLeft.jpg",
										  "sky/low/spaceBoxRight.jpg",
										  "sky/low/spaceBoxTop.jpg",
										  "sky/low/spaceBoxBottom.jpg",
										d3dDevice); // skybox

	}
	
	if(((maxTextureSize/2) > 128)&&((maxTextureSize/2) < 513))
	{
		TheEnviroment.loadMeshIntoBuffer("models/low/skyBox.x",
										  "sky/med/spaceBoxBack.jpg",
										  "sky/med/spaceBoxFront.jpg",
										  "sky/med/spaceBoxLeft.jpg",
										  "sky/med/spaceBoxRight.jpg",
										  "sky/med/spaceBoxTop.jpg",
										  "sky/med/spaceBoxBottom.jpg",
										d3dDevice); // skybox

	}

	if((maxTextureSize/2) > 1023)
	{
		TheEnviroment.loadMeshIntoBuffer("models/low/skyBox.x",
										  "sky/high/spaceBoxBack.jpg",
										  "sky/high/spaceBoxFront.jpg",
										  "sky/high/spaceBoxLeft.jpg",
										  "sky/high/spaceBoxRight.jpg",
										  "sky/high/spaceBoxTop.jpg",
										  "sky/high/spaceBoxBottom.jpg",
										d3dDevice); // skybox
	}

	//Load select mesh from path and Get a pointer to an ID3DXMesh in video memory containing the model data
	//And pointers to Vectors containing Material and Texture Data.
	loadOkay = cockpit.loadMeshIntoBuffer("models/low/cockpit.x",d3dDevice);
	loadOkay = cockpitScreenLeft.loadMeshIntoBuffer("models/low/cockpitScreenLeft.x",d3dDevice);
	loadOkay = cockpitScreenRight.loadMeshIntoBuffer("models/low/cockpitScreenRight.x",d3dDevice);
	loadOkay = cockpitScreenRadar.loadMeshIntoBuffer("models/low/cockpitRadar.x",d3dDevice);
	loadOkay = cockpitShipMesh.loadMeshIntoBuffer("models/high/playership.x",d3dDevice);
	loadOkay = cockpitArrow.loadMeshIntoBuffer("models/low/arrow.x",d3dDevice);

	playerShip.setDevice(d3dDevice);
	playerShip.initialiseFonts(userSettings.width,userSettings.height);

	playerShip.setMesh(&cockpitShipMesh); // needs to be first we test collisions againts this mesh
	playerShip.setMesh(&cockpit);
	playerShip.setMesh(&cockpitScreenLeft);
	playerShip.setMesh(&cockpitScreenRight);
	playerShip.setMesh(&cockpitScreenRadar);
	playerShip.setMesh(&cockpitArrow);

	playerShip.setPosition(&Pos);
	playerShip.setRotation(&Rotation);
	playerShip.setScale(&Scale);

	playerShip.addObjectSound(L"sound/playerengine.wav",*pMainWindowHandle,sound3Dmanager);
	playerShip.addObjectSound(L"sound/fire.wav",*pMainWindowHandle,sound3Dmanager);
	playerShip.addObjectSound(L"sound/bleep.wav",*pMainWindowHandle,sound3Dmanager);
	playerShip.addObjectSound(L"sound/collision.wav",*pMainWindowHandle,sound3Dmanager);

	gameObjects.setDevice(d3dDevice,sound3Dmanager);
	gameObjects.initialiseSounds(*pMainWindowHandle);
	gameObjects.setMeshDetail(meshDetail);
	gameObjects.addPlayerShip(&playerShip);
	gameObjects.initialiseSpaceDust();

	gamesMission.initialiseMission(d3dDevice,meshDetail,&playerShip,userSettings);
	missionScreen.initialise(userSettings.width,userSettings.height,d3dDevice);

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

	Font = new CD3DFont(_T("Times New Roman"), 16, 0);
	Font->InitDeviceObjects(d3dDevice );
	Font->RestoreDeviceObjects();
}

void d3dApplication::setupCamera()
{
	playerShip.setCamera(510,165,(float)userSettings.width,(float)userSettings.height);
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

void d3dApplication::setScreenRenderStates()
{
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);     //Default fillmode
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); //Default shademode
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);        //Turn culling on

	// Texture Filters

	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}


void d3dApplication::drawSkyBox()
{	
	D3DXMATRIX sceneryScale,sceneryLocation;
	D3DXVECTOR3 pos;
	playerShip.getPosition(&pos);
	
	// Draw skybox
	D3DXMatrixScaling(&sceneryScale,1000000.0f,1000000.0f,1000000.0f);
	D3DXMatrixTranslation(&sceneryLocation, pos.x,pos.y,pos.z);
	D3DXMATRIX World = sceneryScale * sceneryLocation;
	
	d3dDevice->SetTransform(D3DTS_WORLD, &World);
	TheEnviroment.draw();

}

void d3dApplication::setupLights()
{
		D3DXVECTOR3 pos(-5000,5000,-100000);
		D3DXCOLOR col(1.0f, 1.0f, 1.0f, 0.0f);

		D3DLIGHT9 light = sun.InitDirectionalLight(&pos, &col);
		//D3DLIGHT9 light = sun.InitPointLight(&pos,&col);

		d3dDevice->SetLight(0, &light);
		d3dDevice->LightEnable(0, true);
		d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

////////////// TEMP /////////////////
void d3dApplication::updateCamera()
{
	playerShip.setChaseCameraMatrix();
}

void d3dApplication::checkInputs(float timeDelta)
{
	//
	// Update the inputs to check for changes
	//
	D3DXVECTOR3 playerPosition;
	playerShip.getPosition(&playerPosition);

	input.checkInputs();

	keyPressTime = keyPressTime + timeDelta;
	
	
	if(keyPressesInput.fireKey == true)
	{
		playerShip.shoot();
		//playerShip.playSound(1,playerPosition);
	}

	if(keyPressesInput.forwardKey == true)
	{
		playerShip.walk(40.0f * timeDelta,true);
	}

	if(keyPressesInput.backKey == true)
	{
		playerShip.walk(-40.0f * timeDelta,true);
	}

	if(keyPressesInput.upKey == true)
	{
		playerShip.pitch(2.0f * timeDelta);
	}

	if(keyPressesInput.downKey == true)
	{
		playerShip.pitch(-2.0f * timeDelta);
	}

	if(keyPressesInput.leftKey == true)
	{
		playerShip.yaw(-2.0f * timeDelta);
	}
			
	if(keyPressesInput.rightKey == true)
	{
		playerShip.yaw(2.0f * timeDelta);
	}

	if(keyPressesInput.targetEnemyKey == true)
	{
		if(keyPressTime > 0.3)
		{
			gameObjects.targetNextEnemy();
			keyPressTime = 0.0f;
			playerShip.playSound(2,playerPosition);
		}
	}

	if(keyPressesInput.targetFriendlyKey == true)
	{	
		if(keyPressTime > 0.1)
		{
			gameObjects.targetNextFriendly();
			keyPressTime = 0.0f;
			playerShip.playSound(2,playerPosition);
		}
	}

	if(keyPressesInput.targetNearestEnemy == true)
	{	
		if(keyPressTime > 0.1)
		{
			gameObjects.targetNearestEnemy();
			keyPressTime = 0.0f;
			playerShip.playSound(2,playerPosition);
		}
	}


	// Mouse Movement
	if(keyPressesInput.xMouseMove > 0.0f)
	{
		playerShip.yaw(keyPressesInput.xMouseMove * timeDelta);
	}
			
	if(keyPressesInput.xMouseMove < 0.0f)
	{
		playerShip.yaw(keyPressesInput.xMouseMove * timeDelta);
	}

	if(keyPressesInput.yMouseMove > 0.0f)
	{
		playerShip.pitch(keyPressesInput.yMouseMove * timeDelta);
	}
			
	if(keyPressesInput.yMouseMove < 0.0f)
	{
		playerShip.pitch(keyPressesInput.yMouseMove * timeDelta);
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

bool d3dApplication::run(GameSettings _userSettings, HINSTANCE hInstance,HWND* mainWindowHandle,int width,int height)
{
	pMainWindowHandle = mainWindowHandle;
	userSettings = _userSettings;
	Capabilities configWindow;
	meshDetail = userSettings.meshDetail;

	bool errors = false;
	float timeDelta = 0.0f;
	bool (d3dApplication::*ptr_displayFunction)(float timeDelta); // Pointer to a display function
	
	// Get card config and start device
	if (configWindow.getCapabilities(&width, &height,&maxTextureSize,userSettings,hInstance,mainWindowHandle,&d3dDevice) == false)
	{
		MessageBox(NULL, _T("Card configuration failed"), _T("FinalAssignment.exe"), MB_OK);
		errors = true;
	}

	if (initialiseGeometery() == false)
	{
		MessageBox(NULL, _T("Loading geometry failed"), _T("FinalAssignment.exe"), MB_OK);
		errors = true;
	}

	if(input.setup_Input(&hInstance,mainWindowHandle,&keyPressesInput) == false)
	{
		MessageBox(NULL, _T("Direct Input config failed"), _T("FinalAssignment.exe"), MB_OK);
		errors = true;
	}

	if(errors == false)
	{
		// Didnt have tom to implement volume shadows so this is pointless
		switch(gameDetail)
		{
			case 'l': 
				ptr_displayFunction = &d3dApplication::renderLowDetail;
				setInitialRenderStates();
				break;
			case 'm': 
				ptr_displayFunction = &d3dApplication::renderLowDetail;
				setInitialRenderStates();
				break;
			case 'h': 
				ptr_displayFunction = &d3dApplication::renderLowDetail;
				setInitialRenderStates();
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

	static std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();

	while((msg.message != WM_QUIT)&&(gameRunning == true))
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
        {	
			std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> timeDelta = (currTime - lastTime)*0.001f;

			// Run the selected render detail function
			(this->*ptr_displayFunction)(timeDelta.count());

			std::chrono::duration<double, std::milli> renderTimeMS = std::chrono::system_clock::now() - currTime;

			//lock to 60 fps
			if (renderTimeMS.count() > 0 && renderTimeMS.count() < 16.0f)
			{
				Sleep(16.0f - renderTimeMS.count());
			}

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
		D3DXVECTOR3 playerPosition;
		playerShip.getPosition(&playerPosition);
		//
		// Render
		//

		if(gamesMission.showBriefingScreen() == false)
		{
			playerShip.updateAllsounds();

			if(i == 0)
			{
				setInitialRenderStates();
				i++;
			}

			calcFPS(timeDelta);
			checkInputs(timeDelta);
			updateObjects(timeDelta);
			gameObjects.checkFire();
			gamesMission.checkEvents(timeDelta,&gameObjects);
			gamesMission.checkMusic(&gameObjects);
			gamesMission.checkCriticalList(&gameObjects);

			d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
			d3dDevice->BeginScene();


			gameObjects.setDefaultRenderStates();
			drawSkyBox();
			gameObjects.drawObjects();
			gameObjects.drawSprites(timeDelta);
			gameObjects.drawCockpit();

			// Soud stuff
			gameObjects.playSounds();
			playerShip.playSound(0,playerPosition);

			//Draw FPS
			if( Font )
			{
				Font->DrawText(20, 20, 0xffffffff, FPSString);
				Font->DrawText(20, 50, 0xffffffff, Values);
			};

			//playerShip.updateAllsounds();

			d3dDevice->EndScene();
			d3dDevice->Present(0, 0, 0, 0);
		}else
		{
			setScreenRenderStates();
			i = 0;

			d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
			d3dDevice->BeginScene();

			d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
			d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

			//
			// Update the inputs to check for changes
			//
			input.checkInputs();
			std::string briefingText = "";

			if(gamesMission.missionBegun() == false)
			{
				gamesMission.getBriefingText(&briefingText,timeDelta);

			}else if(gamesMission.missionComplete() == true)
			{
				gamesMission.getWinText(&briefingText,timeDelta);

			}else if(gamesMission.missionFailed() == true)
			{	
				gamesMission.getLoseText(&briefingText,timeDelta);
			}

			missionScreen.setText(briefingText);
			missionScreen.displayScreen();
			gamesMission.checkMusic(&gameObjects);

			if((keyPressesInput.fireKey == true)&&(gamesMission.missionBegun() == false))
			{
				gamesMission.startMission();

			}else if(keyPressesInput.fireKey == true)
			{
				if((gamesMission.missionComplete() == true)||(gamesMission.missionFailed() == true))
				{
					// Exit game
					gameRunning = false;
				}
			}

			d3dDevice->SetRenderState(D3DRS_LIGHTING, true);

			d3dDevice->EndScene();
			d3dDevice->Present(0, 0, 0, 0);
		}
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