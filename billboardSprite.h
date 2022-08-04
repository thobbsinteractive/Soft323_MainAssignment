//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: billboardSprite.h
// Author: Tim Hobbs
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INC_BILLBOARDSPRITE_H
#define INC_BILLBOARDSPRITE_H

//#include "dsutil.h" 
#include "d3dutil.h"
#include "vertex.h"

class billboardSprite
{
public:
	billboardSprite();
	~billboardSprite();
	void setSize(int _sizeX,int _sizeY);
	void setupSprite(IDirect3DDevice9* device,float _sizeX, float _sizeY,char texturePath[]);
	void draw();
private:

	IDirect3DDevice9* localDevice;
	IDirect3DTexture9* texture;
	D3DMATERIAL9 material;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
	Vertex* v;
	float sizeX;
	float sizeY;
};
#endif //INC_BILLBOARDSPRITE_H