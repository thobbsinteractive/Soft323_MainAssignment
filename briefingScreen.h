#ifndef INC_BRIEFINGSCREEN_H
#define INC_BRIEFINGSCREEN_H

#include "billboardSprite.h"
#include "mp3Player.h"

class BriefingScreen
{
public:
	BriefingScreen();
	~BriefingScreen();

	void initialise(int _width,int _height,IDirect3DDevice9* device);
	void setText(std::string newText);
	void displayScreen();

private:
	ID3DXFont* font;
	LOGFONT lf;
	std::string text;
	int width;
	int height;
	mp3Player briefingMusic;
	billboardSprite backGround;

	D3DXMATRIX matProj; // Projection matrix for chase camera
	D3DXMATRIX matWorld;

	IDirect3DDevice9* localDevice;

};
#endif //INC_BRIEFINGSCREEN_H