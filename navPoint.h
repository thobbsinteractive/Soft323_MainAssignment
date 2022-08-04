// My input structure that stores my games nav point data
#ifndef INC_NAVPOINT_H
#define INC_NAVPOINT_H

struct NavPoint
{
	int index;
	D3DXVECTOR3 location;
	bool visited;

};

#endif // INC_NAVPOINT_H