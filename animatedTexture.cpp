// Creates an animated texture


#include "animatedTexture.h"
#include "imageSequence.h"

animatedTexture::animatedTexture()
{
	currentFrame = 0;
	frameTime = 0.0f;
	frameSpeed = 0.0f;
}

animatedTexture::~animatedTexture()
{
	
}

void animatedTexture::setupTexture(float _frameSpeed,imageSequence* _textures)
{
	frameSpeed = _frameSpeed;
	textures = _textures;
}

int animatedTexture::getNumberOfFrames()
{
	return textures->getNumberOfImages();
}

int animatedTexture::getCurrentFrameNumber()
{
	return currentFrame;
}

void animatedTexture::setTexture(float timeDelta)
{
	if(textures->getNumberOfImages() > 0)
	{
		frameTime = frameTime + timeDelta;

		if(frameTime > frameSpeed)
		{
			frameTime = 0.0f;

			if(currentFrame < (textures->getNumberOfImages()-1))
			{
				currentFrame = currentFrame++;
			}//else                             //Modified to play once
			//{
			//	currentFrame = 0;
			//}
		}
		textures->setTexture(currentFrame);
	}
}