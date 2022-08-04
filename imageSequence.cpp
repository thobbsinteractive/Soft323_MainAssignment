#include "imageSequence.h"

imageSequence::imageSequence()
{
}

imageSequence::~imageSequence()
{
	for(int i = 0; i < (int)Textures.size(); i++)
	{
		Release<IDirect3DTexture9*>(Textures[i]);
	}
}

void imageSequence::setupTexture(IDirect3DDevice9* device)
{
	localDevice = device;
}

void imageSequence::addTexture(char* textureName)
{
	IDirect3DTexture9* temp = 0;
	D3DXCreateTextureFromFileA(localDevice, textureName,&temp);
	Textures.push_back(temp);
}

int imageSequence::getNumberOfImages()
{
	return (int)Textures.size();
}

void imageSequence::setTexture(int index)
{
	if(((int)Textures.size() > 0)&&(index < (int)Textures.size()))
	{
		localDevice->SetTexture(0,Textures[index]);
	}
}