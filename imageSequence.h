//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: animatedTexture.h
// Author: Tim Hobbs
// Description: creates an sequence of images for using in an animated texture,
// I decided to make them separate after discovering that I needed to share the large 
// sequence of images between to multiple animated textures to avoid loading times, 
// To avoid the problems with "animatedTexture" controling only one texture for 
// multiple explosions causing only one explosion to be played.
// 
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INC_IMAGESEQUENCE_H
#define INC_IMAGESEQUENCE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <tchar.h>

using std::vector;

class imageSequence
{
public:
	imageSequence();
	~imageSequence();
	void setupTexture(IDirect3DDevice9* device);
	void addTexture(char* textureName);
	void setTexture(int index);
	int getNumberOfImages();

private:

	template<class T> void Release(T t)
	{
		if(t)
		{
			t->Release();
			t = 0;
		}
	};

	template<class T> void Delete(T t)
	{
		if(t)
		{
			delete t;
			t = 0;
		}
	};

	IDirect3DDevice9* localDevice;
	std::vector<IDirect3DTexture9*> Textures;
};
#endif //INC_IMAGESEQUENCE_H