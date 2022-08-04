//////////////////////////////////////////////////////////////////////////////////////////////////
// viewObject.h
// Author: Tim Hobbs /some Frank Luna code
// Description: Holds all mesh data, for drawing the mesh and drawing its shadows.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INC_VIEWOBJECT_H
#define INC_VIEWOBJECT_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <tchar.h>
#include "boundingSphere.h"
using std::vector;

class ViewObject
{
public:
	ViewObject();
	~ViewObject();

	bool loadMeshIntoBuffer(char sysPath[], IDirect3DDevice9* localDevice);
	bool computeBoundingSphere();
	void drawObject();
	void drawObjectBump();
	void drawObjectForRadar();
	void drawBoundingSphere();
	void optmizeMesh();
	bool isPointInsideBoundingBox(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition);
	bool isPointIntersectingWithMesh(D3DXVECTOR3 rayObjOrigin,D3DXVECTOR3 rayObjDirection);
	ID3DXMesh* getMesh();
	float getBoundingRadius();
	void cleanUP();
	DWORD VectorToRGB(D3DXVECTOR3* NormalVector);

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
	DWORD  F2DW( FLOAT f );

	BoundingSphere sphere;
	IDirect3DDevice9* localDevice;
	ID3DXMesh* pMesh;
	ID3DXMesh* sphereMesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	ID3DXBuffer* adjBuffer;

	D3DXVECTOR3 Light;							//light vector
	DWORD dwTFactor;	
	LPDIRECT3DTEXTURE9 pNormalMap;

};

#endif // INC_VIEWOBJECT_H