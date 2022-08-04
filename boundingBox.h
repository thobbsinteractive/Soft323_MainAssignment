#ifndef INC_BOUNDINGBOX_H
#define INC_BOUNDINGBOX_H

#include <d3dx9.h>

//
// Constants
//

const float INFINITY = FLT_MAX;
const float EPSILON  = 0.001f;

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();
	bool isPointInside(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
};
#endif // INC_BOUNDINGBOX_H
