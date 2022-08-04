#include "d3dApplication.h"
#include "gameSettings.h"

//Button ID's
#define ID_START			3
#define ID_CANCEL			4

//Globals

// The main Window Handle
HWND mainWindowHandle = 0;

GameSettings userSettings;

// config window handle
HWND						m_hBtnStart,
							m_hBtnCancel,

							m_hLblResolution,
							m_hCbResolution,

							m_hLblMusic,
							m_hCbMusic,

							m_hLblFullScreen,
							m_hCbFullScreen,

							m_hLblMeshDetail,
							m_hCbMeshDetail,

							m_hLblGameSettings;
							
bool quit = false;

// adapted from vairous sources
void getConfigSettings()
{

	// default settings
	userSettings.width = 1024;
	userSettings.height = 768;
	userSettings.music = true;
	userSettings.fullScreen = false;
	userSettings.meshDetail = 2;


	switch(SendMessage(m_hCbResolution,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.width = 1024; userSettings.height = 768; break;
		case 1: userSettings.width = 1152; userSettings.height = 864; break;
		case 2: userSettings.width = 1280; userSettings.height = 960; break;
		case 3: userSettings.width = 1280; userSettings.height = 1024; break;
		case 4: userSettings.width = 1600; userSettings.height = 1200; break;
	}

	switch(SendMessage(m_hCbMusic,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.music = true; break;
		case 1: userSettings.music = false; break;
	}

	switch(SendMessage(m_hCbFullScreen,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.fullScreen = false; break;
		case 1: userSettings.fullScreen = true; break;
	}

	switch(SendMessage(m_hCbMeshDetail,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.meshDetail = 0; break;
		case 1: userSettings.meshDetail  = 1; break;
		case 2: userSettings.meshDetail  = 2; break;
	}
}

// adapted from vairous sources
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//
	// Receives certain events/messages from the application window and responds to them with
	// messages or exiting the application.
	//

		switch(msg)
		{
			case WM_DESTROY:
				::PostQuitMessage(0);
				break;

			case WM_KEYDOWN:
				if (wParam == VK_ESCAPE)
					::DestroyWindow(hwnd);
				break;

			//user command on window
			case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
					//start button pressed
					case ID_START:
					{
						//switch to D3D loop and init D3D with settings
						getConfigSettings();
						UnregisterClass("Direct3dConfig",GetModuleHandle(NULL));
						::PostQuitMessage(0);
					break;
					}
					//cancel button pressed
					case ID_CANCEL:
					{
						quit = true;
						UnregisterClass("Direct3dConfig",GetModuleHandle(NULL));
						::PostQuitMessage(0);
					break;
					}
				}
				return 0;
			}
		}
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

// adapted from vairous sources
bool setupConfigWindow(HINSTANCE hInstance,HWND* ptrMainWindowHandle,int width, int height)
{

	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3dConfig";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	*ptrMainWindowHandle = ::CreateWindow("Direct3dConfig", 
									   "Direct3dConfig", 
									   WS_EX_TOPMOST,
									   0, 
									   0, 
									   width, 
									   height,
									   0 /*parent hwnd*/, 
									   0 /* menu */, 
									   hInstance, 
									   0 /*extra*/); 

	if( !*ptrMainWindowHandle )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	//create window elements
	m_hLblResolution = CreateWindow("static","Resolution:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,24,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbResolution = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,20,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	
	m_hLblMusic = CreateWindow("static","Music:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,54,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbMusic = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,50,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hLblFullScreen = CreateWindow("static","Full Screen:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,84,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbFullScreen = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,80,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hLblMeshDetail = CreateWindow("static","Mesh Detail:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,144,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbMeshDetail = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,140,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	
	m_hBtnStart = CreateWindow("button","Start",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,65,250,80,24,*ptrMainWindowHandle,(HMENU)ID_START,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hBtnCancel = CreateWindow("button","Cancel",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,175,250,80,24,*ptrMainWindowHandle,(HMENU)ID_CANCEL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);

	m_hLblGameSettings = CreateWindow("static","Default settings are: 1042,music on, fullscreen on, Mesh detail high",WS_CHILD | WS_VISIBLE | SS_LEFT,20,280,500,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);

	//fill combo boxes
	SendMessage(m_hCbResolution,CB_ADDSTRING,0,(long)"1024 x 768");
	SendMessage(m_hCbResolution,CB_ADDSTRING,0,(long)"1152 x 864");
	SendMessage(m_hCbResolution,CB_ADDSTRING,0,(long)"1280 x 960");
	SendMessage(m_hCbResolution,CB_ADDSTRING,0,(long)"1280 x 1024");
	SendMessage(m_hCbResolution,CB_ADDSTRING,0,(long)"1600 x 1200");

	SendMessage(m_hCbMusic,CB_ADDSTRING,0,(long)"ON");
	SendMessage(m_hCbMusic,CB_ADDSTRING,0,(long)"OFF");

	SendMessage(m_hCbFullScreen,CB_ADDSTRING,0,(long)"Yes");
	SendMessage(m_hCbFullScreen,CB_ADDSTRING,0,(long)"No");
	
	SendMessage(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"Low");
	SendMessage(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"Medium");
	SendMessage(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"High");

	::ShowWindow(*ptrMainWindowHandle, SW_SHOW);
	::UpdateWindow(*ptrMainWindowHandle);

	return true;
}

bool setupApplicationWindow(HINSTANCE hInstance,HWND* ptrMainWindowHandle,int width, int height)
{
	//
	// Create the main application window.
	//
	
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	*ptrMainWindowHandle = ::CreateWindow("Direct3D9App", 
									   "Direct3D9App", 
									   WS_POPUP,//WS_EX_TOPMOST,
									   0, 
									   0, 
									   width, 
									   height,
									   0 /*parent hwnd*/, 
									   0 /* menu */, 
									   hInstance, 
									   0 /*extra*/); 

	if( !*ptrMainWindowHandle )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	::ShowWindow(*ptrMainWindowHandle, SW_SHOW);
	::UpdateWindow(*ptrMainWindowHandle);
	
	return true;
}

//------------------------------------- Main -------------------------------------//
int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE prevInstance, 
				   PSTR cmdLine, 
				   int showCmd)
{
	d3dApplication* myGame;

	if(setupConfigWindow(hInstance,&mainWindowHandle,640,480) == false)
	{
		MessageBox(NULL, "Could Not initialise setup Window", "FinalAssignment.exe", MB_OK);
	}

	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
    }

	if(quit != true)
	{
		myGame = new d3dApplication();

		if(setupApplicationWindow(hInstance,&mainWindowHandle,userSettings.width,userSettings.height) == false)
		{
			MessageBox(NULL, "Could Not initialise application Window", "FinalAssignment.exe", MB_OK);
		}

		if (!myGame->run(userSettings, hInstance,&mainWindowHandle,userSettings.width,userSettings.height))
		{
			::MessageBox(0, "InitD3D() - FAILED",0,0);
		}

		// Clean Up
		delete myGame;
	}

	return 0;
}