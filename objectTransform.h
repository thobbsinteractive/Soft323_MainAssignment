//////////////////////////////////////////////////////////////////////////////////////////////////
// objectTransform.h
// Author: Tim Hobbs
// Description: A basic super class for all objects in the world, holding their positions and sound
// and now also a pointer to their mesh data.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INC_OBJECTTRANSFORM_H
#define INC_OBJECTTRANSFORM_H

#include "dsutil.h" 
#include "d3dutil.h"
#include "boundary.h"
#include "viewObject.h"
#include "frustumPlane.h"
#include "vertex.h"
#include "3DSound.h"

class objectTransform
{
public:
	objectTransform();
	objectTransform(D3DXVECTOR3 _pos, ViewObject* _pMesh);
	objectTransform(D3DXVECTOR3 _pos, D3DXVECTOR3 _rotation, D3DXVECTOR3 _look, ViewObject* _pMesh);
	objectTransform(Boundary _objectBoundaries, ViewObject* _pMesh);
	virtual ~objectTransform();

	D3DXVECTOR3 getCurrentDirectionalVector();
	bool checkIfVisibleToThisObject(objectTransform* objectToCheck);
	void getPosition(D3DXVECTOR3* _pos);
	void setPosition(D3DXVECTOR3* _pos);
	void getCameraPosition(D3DXVECTOR3* _pos);

	void getRotation(D3DXVECTOR3* _rotation);
	void setRotation(D3DXVECTOR3* _rotation);
	void getLook(D3DXVECTOR3* _look); //
	void setLook(D3DXVECTOR3* _look);
	void setScale(D3DXVECTOR3* _pScale);
	void setMesh(ViewObject* _pMesh);
	void getMesh(ViewObject** _pMesh);
	void setDevice(IDirect3DDevice9* localDevice);
	void setCamera(float _distanceZ, float _distanceY,float width, float height); // only needs to run once to setup camera
	bool highlevelCollisionDetection(objectTransform* objectToCheckAgainst);
	bool lowlevelCollisionDetection(objectTransform* objectToCheckAgainst);
	bool lowlevelMeshCollisionDetection(objectTransform* objectToCheckAgainst);
	bool highlevelCollisionDetection(D3DXVECTOR3 objectsPosition);
	void drawWithoutMatrix(int index);
	float addAngle(float angleToAdd,float existingAngle);

	void updatePositionInRelationTo(D3DXVECTOR3 offsetPostion,D3DXVECTOR3 rotationOfObject,D3DXVECTOR3* newPostion);

	void walk(float units); // forward/backward
	void pitch(float angle); // rotate on left vector
	void yaw(float angle); // rotate on up vector
	void roll(float angle); // rotate on look vector
	void getMatrix(D3DXMATRIX* V);
	void addObjectSound(LPSTR wavFileName, HWND handle,CSoundManager* sound3Dmanager);
	void playSound(int soundNumber,D3DXVECTOR3 listenerPosition);
	void drawMesh();
	void drawMesh(int index);
	void drawMeshBounding();
	float getPosX();
	float getPosY();
	float getPosZ();
	void setChaseCameraMatrix();

	// Based on http://www.c-unit.com/tutorials/mdirectx/?t=45
	// and 
	// http://www.toymaker.info/Games/html/direct3d_faq.html#D3D5

	void buildViewFrustum(D3DXMATRIX matView);
	bool SphereInFrustum(D3DXVECTOR3 pos,float radius);
	float getBoundingRadius();

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

protected:

	void updateCamera();

	bool chaseCamera;
	float distanceZ;
	float distanceY;


	D3DXMATRIX matProj; // Projection matrix for chase camera
	D3DXMATRIX matWorld;
	frustumPlane m_frustumPlanes[6]; // frustum from camera, help to cull objects

	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 look;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 currentVector; // Current directional vector. Used in object culling

	D3DXVECTOR3 cameraPosition; // camera Position
	D3DXVECTOR3 cameraLookAt; // camera lookAt;
	D3DXVECTOR3 up; // camera up
	D3DXVECTOR3 angularVelocity;


	Boundary objectBoundaries;
	std::vector<_3DSound> sound;  //can have a number of associated sounds
	std::vector<ViewObject*> pMeshObjects; //can have a number of meshes
	IDirect3DDevice9* localDevice;
	float fOrientation;
	int vertexCount;

};
#endif // INC_OBJECTTRANSFORM_H