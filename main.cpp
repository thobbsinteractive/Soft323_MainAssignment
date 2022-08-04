#include "d3dApplication.h"

//Globals

// The main Window Handle
HWND mainWindowHandle = 0;

// Window Width and Height
int	width = 1024;
int	height = 768;



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
		}
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
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
	myGame = new d3dApplication();

	if(setupApplicationWindow(hInstance,&mainWindowHandle,width,height) == false)
	{
		MessageBox(NULL, "Could Not initialise application Window", "FinalAssignment.exe", MB_OK);
	}

	if (!myGame->run(hInstance,&mainWindowHandle,width,height))
	{
		::MessageBox(0, "InitD3D() - FAILED",0,0);
	}

	// Clean Up
	delete myGame;

	return 0;
}