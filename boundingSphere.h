#ifndef INC_BOUNDINGSPHERE_H
#define INC_BOUNDINGSPHERE_H

#include <d3d9.h>
#include <d3dx9.h>

//
// Constants
//

class BoundingSphere
{
public:
	BoundingSphere();
	~BoundingSphere();
	bool isPointInside(D3DXVECTOR3& p);
	void setPosition(D3DXVECTOR3 newPos);
	
	float radius;
	D3DXVECTOR3 pos;
};
#endif // INC_BOUNDINGSPHERE_H