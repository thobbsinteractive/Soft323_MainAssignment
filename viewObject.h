//////////////////////////////////////////////////////////////////////////////////////////////////
// viewObject.h
// Author: Tim Hobbs /some Frank Luna code
// Description: Holds all mesh data, for drawing the mesh and drawing its shadows.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INC_VIEWOBJECT_H
#define INC_VIEWOBJECT_H

#include <d3dx9.h>
#include <vector>
#include "boundingBox.h"
using std::vector;

class ViewObject
{
public:
	ViewObject();
	~ViewObject();

	bool loadMeshIntoBuffer(char sysPath[], IDirect3DDevice9* localDevice);
	bool computeBoundingBox();
	void drawObject();
	void drawBoundingBox();
	void optmizeMesh();
	bool isPointInsideBoundingBox(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition);
	void cleanUP();

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
	
private:
	BoundingBox box;
	IDirect3DDevice9* localDevice;
	ID3DXMesh* pMesh;
	ID3DXMesh* boxMesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	ID3DXBuffer* adjBuffer;

};

#endif // INC_VIEWOBJECT_H