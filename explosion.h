#ifndef INC_EXPLOSION_H
#define INC_EXPLOSION_H

#include "billboardSprite.h"
#include "animatedTexture.h"
#include "light.h"

class Explosion
{
public:
	Explosion();
	~Explosion();
	void setupUpExplosion(IDirect3DDevice9* _device,float _timeToLive,float _size,float z,D3DXVECTOR3 _position,animatedTexture* _texture);
	void setSize(int _sizeX,int _sizeY);
	void getPosition(D3DXVECTOR3* _position);
	void drawExplosion(float timeDelta,D3DXVECTOR3 rotation);
	float getTimeToLive();
	float getCurrentTime();
	bool isAlive();
	void cleanUp();
	void setLight(D3DXCOLOR col);
	void setAsWarp(bool value);
	bool getAsWarp();

private:

	billboardSprite sprite;
	animatedTexture* texture;
	IDirect3DDevice9* device;
	float timeToLive;
	float currentTime;
	float zRotation;
	bool alive;
	bool lightOn;
	bool lightOff;
	bool isWarp; // helps determine light colour

	D3DXVECTOR3 position;
	D3DXVECTOR3 ownRotation;

	Light explosionLight; // closes explosion is lite
};




#endif //INC_EXPLOSION_H