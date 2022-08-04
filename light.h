//////////////////////////////////////////////////////////////////////////////////////////////////
// light.h
// Author: Tim Hobbs / Frank Luna
// Description: I really just put Franks code in a class for this one.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INC_LIGHT_H
#define INC_LIGHT_H

#include <d3dx9.h>

class Light
{
	public:
		Light();
		~Light();
		D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
		D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
		D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);
};
#endif //INC_LIGHT_H
