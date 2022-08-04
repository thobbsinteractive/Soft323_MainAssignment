#include "gameInput.h"

GameInput::GameInput()
{
	directInput       = NULL; // The DirectInput object         
	keyboardDevice    = NULL; // The keyboard device
	mouseDevice		  = NULL; // The mouse device

	// Mouse sensivity
	mouseXSensivity = 0.001f;
	mouseYSensivity = 0.001f;
	mouseZSensivity = 0.001f;
};

GameInput::~GameInput()
{

	if(directInput != NULL)
	{
		if(keyboardDevice != NULL)
		{
			keyboardDevice->Unacquire();
			keyboardDevice->Release();
		}

		if(mouseDevice != NULL)
		{
			mouseDevice->Unacquire();
			mouseDevice->Release();
		}
	directInput->Release();
	}
};

bool GameInput::setup_Input(HINSTANCE* mainInstance,HWND* hwnd, UserInputs* _keysPressed)
{
	bool okay = true;

	keysPressed = _keysPressed;


	// Initialise all values to false

	keysPressed->backKey = false;
	keysPressed->upKey = false;
	keysPressed->forwardKey = false;
	keysPressed->downKey = false;
	keysPressed->leftKey = false;
	keysPressed->rightKey = false;
	keysPressed->fireKey = false;
	keysPressed->escapeKey = false;
	keysPressed->targetEnemyKey = false;
	keysPressed->targetFriendlyKey = false;
	keysPressed->roleLeft = false;
	keysPressed->roleRight = false;
	keysPressed->mouseRole = false;
	keysPressed->targetNearestEnemy = false;
	keysPressed->xMouseMove = 0;
	keysPressed->yMouseMove = 0;

	if (FAILED(DirectInput8Create(*mainInstance, DIRECTINPUT_VERSION, 
			   IID_IDirectInput8, (void**)&directInput, NULL)))
	{
		MessageBox(NULL, _T("Error creating input device"), _T("MakeSomethingFly.exe"), MB_OK);
		okay = false;
	}
  
	if (FAILED(directInput->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL)))
	{
		MessageBox(NULL, _T("Error creating keyboard device"), _T("MakeSomethingFly.exe"), MB_OK);
		okay = false;
	}
  
	if (FAILED(keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
    {
		MessageBox(NULL, _T("Error setting data format"), _T("MakeSomethingFly.exe"), MB_OK);
		okay = false;
	}
	
	if (FAILED(keyboardDevice->SetCooperativeLevel(*hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
    {
		MessageBox(NULL, _T("Error setting SetCooperativeLevel"), _T("MakeSomethingFly.exe"), MB_OK);
		okay = false;
	}	
  
	if (FAILED(keyboardDevice->Acquire()))
    { 
		MessageBox(NULL, _T("Error acquiring keyboard"), _T("MakeSomethingFly.exe"), MB_OK);
		okay = false;
	}


	// initialize the mouse
	if (FAILED(directInput->CreateDevice(GUID_SysMouse, &mouseDevice, NULL)))
	{

	}

	//if (FAILED(mouseDevice->SetCooperativeLevel(*hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	if (FAILED(mouseDevice->SetCooperativeLevel(*hwnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE)))
	{
		
	}

	if (FAILED(mouseDevice->SetDataFormat(&c_dfDIMouse)))
	{

	}
	if (FAILED(mouseDevice->Acquire()))
	{

	}

	return okay;
};

void GameInput::checkInputs()
{
	DIMOUSESTATE mouse_state; // mouse state structure

	keysPressed->backKey = false; // reset all keys (keeps them unsticky)
	keysPressed->upKey = false;
	keysPressed->forwardKey = false;
	keysPressed->downKey = false;
	keysPressed->leftKey = false;
	keysPressed->rightKey = false;
	keysPressed->fireKey = false;
	keysPressed->escapeKey = false;
	keysPressed->targetEnemyKey = false;
	keysPressed->targetFriendlyKey = false;
	keysPressed->roleLeft = false;
	keysPressed->roleRight = false;
	keysPressed->mouseRole = false;
	keysPressed->xMouseMove = 0.0f;
	keysPressed->yMouseMove = 0.0f;
	keysPressed->targetNearestEnemy = false;



	// Check the keyboard status
	if (FAILED(keyboardDevice->GetDeviceState(sizeof(unsigned char[256]), (LPVOID)keystate)))
    {	
		MessageBox(NULL, _T("Error getting key status"), _T("MakeSomethingFly.exe"), MB_OK);
	}

	// Check Mouse status
	if (FAILED(mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state)))
	{
		MessageBox(NULL, _T("Error getting mouse status"), _T("MakeSomethingFly.exe"), MB_OK);
	}
	
	
	// Check changes to keyboard and mouse states
	if (KeyDown(keystate, DIK_ESCAPE))
	{
		keysPressed->escapeKey = true;
	}

	if (KeyDown(keystate, DIK_LEFT))
	{
		keysPressed->leftKey = true;
	}

	if (KeyDown(keystate, DIK_RIGHT))
	{
		keysPressed->rightKey = true;
	}

	if (KeyDown(keystate, DIK_PGUP))
	{
		keysPressed->forwardKey = true;
	}

	if (KeyDown(keystate, DIK_PGDN))
	{
		keysPressed->backKey = true;
	}

	if (KeyDown(keystate, DIK_UP))
	{
		keysPressed->upKey = true;
	}

	if (KeyDown(keystate, DIK_DOWN))
	{
		keysPressed->downKey = true;
	}

	if (KeyDown(keystate, DIK_DOWN))
	{
		keysPressed->downKey = true;
	}

	if ((KeyDown(keystate, DIK_RCONTROL)) || (KeyDown(keystate, DIK_RETURN)))
	{
		keysPressed->fireKey = true;
	}

	if (KeyDown(keystate, DIK_ESCAPE))
	{
		keysPressed->escapeKey = true;
	}

	if (KeyDown(keystate, DIK_E))
	{
		keysPressed->targetEnemyKey = true;
	}

	if (KeyDown(keystate, DIK_N))
	{
		keysPressed->targetNearestEnemy = true;
	}

	if (KeyDown(keystate, DIK_T))
	{
		keysPressed->targetFriendlyKey = true;
	}

	//Mouse overides keys

	// If left mouse button is pressed
	if (mouse_state.rgbButtons[0] & 0x80)
	{
		keysPressed->fireKey = true;
	}

	// If right mouse button is pressed
	if (mouse_state.rgbButtons[1] & 0x80)
	{
		keysPressed->targetNearestEnemy = true;
	}

	// Check for mouse movement
	if (mouse_state.lX > mouseXSensivity)
	{
		if(mouse_state.lX < 2.0f)
		{
			keysPressed->xMouseMove = mouse_state.lX;
		}else
		{
			keysPressed->xMouseMove = 2.0f;
		}
	}

	if (mouse_state.lX < (-mouseXSensivity))
	{
		if(mouse_state.lX > -2.0f)
		{
			keysPressed->xMouseMove = mouse_state.lX;
		}else
		{
			keysPressed->xMouseMove = -2.0f;
		}
	}

	if (mouse_state.lY > mouseYSensivity)
	{
		if(mouse_state.lY < 2.0f)
		{
			keysPressed->yMouseMove = mouse_state.lY;
		}else
		{
			keysPressed->yMouseMove = 2.0f;
		}
	}

	if (mouse_state.lY < (-mouseYSensivity))
	{
		if(mouse_state.lY > -2.0f)
		{
			keysPressed->yMouseMove = mouse_state.lY;
		}else
		{
			keysPressed->yMouseMove = -2.0f;
		}
	}

	if (mouse_state.lZ > mouseZSensivity)
	{
		keysPressed->forwardKey = true;
	}

	if (mouse_state.lZ < (mouseZSensivity-mouseZSensivity-mouseZSensivity))
	{
		keysPressed->backKey = true;
	}
};

