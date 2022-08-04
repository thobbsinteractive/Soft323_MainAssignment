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

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::setPosition(D3DXVECTOR3 newPos)
{
	pos = newPos;
}
/*
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
}*/

bool BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	// modified by me to allow for movement through the snow
	if( (p.x >= (pos.x + min.x)) && (p.y >= (pos.y + min.y)) && (p.z >= (pos.z + min.z)) &&
		(p.x <= (pos.x + max.x)) && (p.y <= (pos.y + max.y)) && (p.z <= (pos.z + max.z)))
	{
		return true;
	}
	else
	{
		return false;
	}
}