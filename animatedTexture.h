//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: animatedTexture.h
// Author: Tim Hobbs
// Description: creates an animated texture
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __animatedTextureH__
#define __animatedTextureH__

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "imageSequence.h"

using std::vector;

class animatedTexture
{
public:
	animatedTexture();
	~animatedTexture();
	void setupTexture(float _frameSpeed,imageSequence* _textures);
	void setTexture(float timeDelta);
	int getNumberOfFrames();
	int getCurrentFrameNumber();

private:

	imageSequence* textures;
	float frameSpeed;
	float frameTime;
	int currentFrame;
};
#endif //__animatedTextureH__