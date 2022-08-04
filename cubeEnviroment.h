//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: cubeEnviroment.h
// Author: Tim Hobbs / Frank Luna
// Description: This creates a cubed enviroment for the skybox / Help by fanks code for creating
// Vertexes.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __cubeEnviromentH__
#define __cubeEnviromentH__

#include <d3dx9.h>
#include <vector>
#include "vertex.h"

using std::vector;

class cubeEnviroment
{
public:
	cubeEnviroment();
	~cubeEnviroment();
	void loadTextures(IDirect3DDevice9* device);
	void draw();

	template<class T> void Release(T t)
	{
		if(t)
		{
			t->Release();
			t = 0;
		}
	};

	template<class T> void Delete(T t)
	{
		if(t)
		{
			delete t;
			t = 0;
		}
	};

private:
	IDirect3DDevice9* localDevice;
	std::vector<IDirect3DTexture9*> Textures;
	D3DMATERIAL9 material;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
	Vertex* v;
};
#endif //__cubeEnviromentH__