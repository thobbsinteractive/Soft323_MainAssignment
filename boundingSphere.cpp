#include "BoundingSphere.h"

BoundingSphere::BoundingSphere()
{
	// infinite small 

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	radius = 0.0f;
}

BoundingSphere::~BoundingSphere()
{

}

void BoundingSphere::setPosition(D3DXVECTOR3 newCentre)
{
	pos = newCentre;
}

bool BoundingSphere::isPointInside(D3DXVECTOR3& p)
{
	// modified by me to allow for movement through the snow
	if( (p.x >= (pos.x - radius)) && (p.y >= (pos.y - radius)) && (p.z >= (pos.z - radius))&&
		(p.x <= (pos.x + radius)) && (p.y <= (pos.y + radius)) && (p.z <= (pos.z + radius)))
	{
		return true;
	}
	else
	{
		return false;
	}
}