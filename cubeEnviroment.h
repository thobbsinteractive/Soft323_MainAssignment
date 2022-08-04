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

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "vertex.h"

using std::vector;

class cubeEnviroment
{
public:
	cubeEnviroment();
	~cubeEnviroment();
	bool loadMeshIntoBuffer(char sysPath[],
							char backPath[],
							char frontPath[],
							char leftPath[],
							char rightPath[],
							char topPath[],
							char bottomPath[],
							IDirect3DDevice9* Device);
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
	ID3DXMesh* pMesh;
	ID3DXBuffer* adjBuffer;
	int maxTextureSize;
};
#endif //__cubeEnviromentH__