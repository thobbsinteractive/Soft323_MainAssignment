#include "explosion.h"

Explosion::Explosion()
{
	timeToLive=0;
	currentTime=0;
	alive = true;
	lightOn = false;
	lightOff = false;
	isWarp = false;
}

Explosion::~Explosion()
{

}

void Explosion::setupUpExplosion(IDirect3DDevice9* _device,float _timeToLive,float _size,float z,D3DXVECTOR3 _position,animatedTexture* _texture)
{
	device = _device;
	texture = _texture;
	sprite.setupSprite(device,_size,_size,NULL);
	zRotation = z;
	timeToLive = _timeToLive;
	position = _position;
	
}

void Explosion::setAsWarp(bool value)
{
	isWarp = value;
}

bool Explosion::getAsWarp()
{
	return isWarp;
}

void Explosion::setLight(D3DXCOLOR col)
{
	// We only want to set this once
	if((lightOn == false)&&(lightOff == false))
	{
		lightOn = true;

		D3DLIGHT9 light = explosionLight.InitPointLight(&position,&col);

		device->SetLight(1, &light);
		device->LightEnable(1, true);
	}

	// turn off light;
	if((currentTime > (texture->getNumberOfFrames()*0.75f))&&(lightOff == false))
	{
		lightOff = true;
		device->LightEnable(1, false);
	}
}

void Explosion::setSize(int _sizeX,int _sizeY)
{
	sprite.setSize(_sizeX,_sizeY);
}

void Explosion::getPosition(D3DXVECTOR3* _position)
{
	*_position = position;
}

float Explosion::getTimeToLive()
{
	return timeToLive;
}

float Explosion::getCurrentTime()
{
	return currentTime;
}

bool Explosion::isAlive()
{
	return alive;
}

void Explosion::drawExplosion(float timeDelta,D3DXVECTOR3 rotation)
{
	D3DXMATRIX World;
	
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling;

	if((texture->getCurrentFrameNumber()) < (texture->getNumberOfFrames()-1))
	{

		D3DXMatrixScaling(&Scaling,1.0,1.0,1.0);
		D3DXMatrixRotationYawPitchRoll(&RotationMatrix,rotation.x,rotation.y,zRotation);
		D3DXMatrixTranslation(&Translation, position.x,position.y,position.z);
	
		World = RotationMatrix * Translation * Scaling;

		device->SetTransform(D3DTS_WORLD, &World);

		texture->setTexture(timeDelta);
		sprite.draw();
	}else
	{
		alive = false;
	}
	currentTime = currentTime++;
}

void Explosion::cleanUp()
{

}