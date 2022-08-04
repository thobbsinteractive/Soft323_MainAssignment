#ifndef INC_D3DAPPLICATION_H
#define INC_D3DAPPLICATION_H

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <strsafe.h>
//#include <dinput.h>

#include "viewObject.h"
#include "gameObjects.h"
#include "missionSystem.h"
#include "playerShip.h"
#include "capitalShip.h"
#include "dsutil.h" 
#include "d3dutil.h"
#include "capabilities.h"
#include "light.h"
#include "d3dfont.h"
#include "cubeEnviroment.h"
#include "briefingScreen.h"

// Direct Input
#include "userInputs.h"
#include "gameInput.h"


class d3dApplication
{
public:
	d3dApplication();
	~d3dApplication();
	bool run(GameSettings settings,HINSTANCE hInstance,HWND* hwnd,int width,int height);
	int getWindowWidth();
	int getWindowHeight();
	void setWindowWidth(bool _width);
	void setWindowHeight(bool _height);

private:
	bool initialiseCard();
	bool initialiseGeometery();
	bool initialiseShaders();
	void initialiseFonts();
	void setupLights();
	void setupCamera();
	void setInitialRenderStates();
	void setScreenRenderStates();
	void drawVolumeShadows();
	void drawSkyBox();
	void checkInputs(float timeDelta);
	void calcFPS(float timeDelta);
	void updateCamera();
	void updateObjects(float timeDelta);
	int  EnterMsgLoop( bool (d3dApplication::*ptr_displayFunction)(float timeDelta) ); // Takes a pointer to a function
	bool renderLowDetail(float timeDelta);
	void cleanUp();

	template<class T> void Release(T t)
	{
		if(t)
		{
			t->Release();
			t = 0;
		}
	}

	template<class T> void Delete(T t)
	{
		if(t)
		{
			delete t;
			t = 0;
		}
	}


	IDirect3DDevice9* d3dDevice; // Direct 3D Device
	MissionSystem gamesMission; // the missions event scripts
	BriefingScreen missionScreen;// briefing screen

	GameSettings userSettings;

	ViewObject cockpitShipMesh;
	ViewObject cockpit;
	ViewObject cockpitScreenLeft;
	ViewObject cockpitScreenRight;
	ViewObject cockpitScreenRadar;

	ViewObject cockpitArrow;

	ViewObject navPoint;

	PlayerShip playerShip;

	Light sun;

	 /* Allocate space for an enviromentCube */
	cubeEnviroment TheEnviroment;

	CD3DFont* Font;// Basic d3d fonts

	UserInputs keyPressesInput; // input structure
	GameInput input; // Game input class

	GameObjects gameObjects;
	char gameDetail;
	int meshDetail;

	DWORD FrameCnt;        // The number of frames that have occurred.
	float TimeElapsed; // The time that has elapsed so far
	float FPS;         // The frames rendered per second.
	char FPSString[50];     // String to display current frames per second
	char Values[300];       // String to display current positional information
	int maxTextureSize;
	float keyPressTime; // slows down key response for target keys

	int i;

	bool gameRunning;
	bool playerAlive;
	HWND* pMainWindowHandle;

	CSoundManager  *sound3Dmanager;
};
#endif // INC_D3DAPPLICATION_H