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
	userSettings.windowed = true;
	userSettings.meshDetail = 2;


	switch(SendMessage(m_hCbResolution,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.width = 1024; userSettings.height = 768; break;
		case 1: userSettings.width = 1280; userSettings.height = 1024; break;
		case 2: userSettings.width = 1600; userSettings.height = 1200; break;
		case 3: userSettings.width = 1920; userSettings.height = 1080; break;
	}

	switch(SendMessage(m_hCbMusic,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.music = true; break;
		case 1: userSettings.music = false; break;
	}

	switch(SendMessage(m_hCbFullScreen,CB_GETCURSEL,0,0))
	{
		case 0: userSettings.windowed = false; break;
		case 1: userSettings.windowed = true; break;
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
						UnregisterClass(_T("Direct3dConfig"),GetModuleHandle(NULL));
						::PostQuitMessage(0);
					break;
					}
					//cancel button pressed
					case ID_CANCEL:
					{
						quit = true;
						UnregisterClass(_T("Direct3dConfig"),GetModuleHandle(NULL));
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
	wc.lpszClassName = L"Direct3dConfig";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, L"RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	*ptrMainWindowHandle = ::CreateWindow(L"Direct3dConfig",
		L"Direct3dConfig",
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
		::MessageBox(0, L"CreateWindow() - FAILED", 0, 0);
		return false;
	}

	//create window elements
	m_hLblResolution = CreateWindowA("static", "Resolution:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,24,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbResolution = CreateWindowA("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,20,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	
	m_hLblMusic = CreateWindowA("static", "Music:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,54,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbMusic = CreateWindowA("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,50,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hLblFullScreen = CreateWindowA("static", "Full Screen:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,84,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbFullScreen = CreateWindowA("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,80,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hLblMeshDetail = CreateWindowA("static", "Mesh Detail:",WS_CHILD | WS_VISIBLE | SS_LEFT,20,144,200,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hCbMeshDetail = CreateWindowA("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,160,140,160,100,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	
	m_hBtnStart = CreateWindowA("button", "Start",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,65,250,80,24,*ptrMainWindowHandle,(HMENU)ID_START,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);
	m_hBtnCancel = CreateWindowA("button", "Cancel",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,175,250,80,24,*ptrMainWindowHandle,(HMENU)ID_CANCEL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);

	m_hLblGameSettings = CreateWindowA("static", "Default settings are: 1024, music on, fullscreen on, Mesh detail high",WS_CHILD | WS_VISIBLE | SS_LEFT,20,280,500,18,*ptrMainWindowHandle,NULL,(HINSTANCE)GetWindowLong(*ptrMainWindowHandle,GWL_HINSTANCE),NULL);

	//fill combo boxes
	SendMessageA(m_hCbResolution,CB_ADDSTRING,0,(long)"1024 x 768");
	SendMessageA(m_hCbResolution,CB_ADDSTRING,0,(long)"1280 x 1024");
	SendMessageA(m_hCbResolution,CB_ADDSTRING,0,(long)"1600 x 1200");
	SendMessageA(m_hCbResolution,CB_ADDSTRING,0,(long)"1920 x 1080");

	SendMessageA(m_hCbMusic,CB_ADDSTRING,0,(long)"ON");
	SendMessageA(m_hCbMusic,CB_ADDSTRING,0,(long)"OFF");

	SendMessageA(m_hCbFullScreen,CB_ADDSTRING,0,(long)"Yes");
	SendMessageA(m_hCbFullScreen,CB_ADDSTRING,0,(long)"No");
	
	SendMessageA(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"Low");
	SendMessageA(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"Medium");
	SendMessageA(m_hCbMeshDetail,CB_ADDSTRING,0,(long)"High");

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
	wc.lpszClassName = L"Direct3D9App";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, L"RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	*ptrMainWindowHandle = ::CreateWindow(L"Direct3D9App",
		L"Direct3D9App",
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
		::MessageBox(0, L"CreateWindow() - FAILED", 0, 0);
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
		MessageBox(NULL, L"Could Not initialise setup Window", L"FinalAssignment.exe", MB_OK);
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
			MessageBox(NULL, L"Could Not initialise application Window", L"FinalAssignment.exe", MB_OK);
		}

		if (!myGame->run(userSettings, hInstance,&mainWindowHandle,userSettings.width,userSettings.height))
		{
			::MessageBox(0, L"InitD3D() - FAILED",0,0);
		}

		// Clean Up
		delete myGame;
	}

	return 0;
}