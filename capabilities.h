//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: capabilities.h
// Author: Tim Hobbs / Frank Luna (some initialisation code)
// Description: Starts up the 3d hardware, according to some capibilities
//          
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INC_CAPABILITIES_H
#define INC_CAPABILITIES_H

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <d3d9.h>
#include <fstream>

#include "Core\DXUT.h"

#include "gameSettings.h"

class Capabilities
{
public:
	Capabilities();
	~Capabilities();
	bool getCapabilities(int* width,					// [out] A pointer to the set screen width
						 int* height,					// [out] A pointer to the set screen height
						 int* textureSize,
						 GameSettings settings,
						 HINSTANCE hInstance,
						 HWND* hwnd,
						 IDirect3DDevice9** device);	// [out] A pointer to the created device)

	bool initDevice(IDirect3D9* d3d9,
					HWND* hwnd,
					bool windowed,
					D3DFORMAT depth,
					int width,
					int height,
					int vp,
					D3DDEVTYPE deviceType,
					IDirect3DDevice9** device);
private:
	GameSettings userSettings;
};

#endif //#ifndef INC_CAPABILITIES_H
