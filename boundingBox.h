#ifndef INC_BOUNDINGBOX_H
#define INC_BOUNDINGBOX_H

#include <d3d9.h>
#include <d3dx9.h>

//
// Constants
//

const float EPSILON  = 0.001f;

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();
	bool isPointInside(D3DXVECTOR3& p);
	void setPosition(D3DXVECTOR3 newPos);
	//bool isPointInside(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
	D3DXVECTOR3 pos;
};
#endif // INC_BOUNDINGBOX_H
