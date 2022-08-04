#include "boundingBox.h"

BoundingBox::BoundingBox()
{
	// infinite small 
	min.x = INFINITY;
	min.y = INFINITY;
	min.z = INFINITY;

	max.x = -INFINITY;
	max.y = -INFINITY;
	max.z = -INFINITY;
}

BoundingBox::~BoundingBox()
{

}

bool BoundingBox::isPointInside(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition)
{
	// Adjust coordinates
	if( p->x >= (min.x+currentPosition->x) && p->y >= (min.y+currentPosition->y) && 
		p->z >= (min.z+currentPosition->z) &&
		p->x <= (max.x+currentPosition->x) && p->y <= (max.y+currentPosition->y) && 
		p->z <= (max.z+currentPosition->x) )
	{
		return true;
	}
	else
	{
		return false;
	}
}