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

#define	 _THRUSTFORCE				20.0f/2
#define	 _MAXTHRUST					80.0f/2
#define	 _MINTHRUST					0.0f
#define	 _DTHRUST					0.01f
#define  _STEERINGFORCE				6.0f
#define  _LINEARDRAGCOEFFICIENT		0.3f
#define  _ANGULARDRAGCOEFFICIENT	5000.0f

#define	_TOL 1e-10

class objectTransform
{
public:
	objectTransform();
	objectTransform(D3DXVECTOR3 _pos, ViewObject* _pMesh);
	objectTransform(D3DXVECTOR3 _pos, D3DXVECTOR3 _rotation, D3DXVECTOR3 _look, ViewObject* _pMesh);
	objectTransform(Boundary _objectBoundaries, ViewObject* _pMesh);
	~objectTransform();

	D3DXVECTOR3 getCurrentDirectionalVector();
	bool checkIfVisibleToThisObject(objectTransform* objectToCheck,float cullingAngleInDegrees);
	void getPosition(D3DXVECTOR3* _pos);
	void setPosition(D3DXVECTOR3* _pos);
	void getCameraPosition(D3DXVECTOR3* _pos);

	void calcLoads();
	void updateBodyEuler(double dt);
	void setThrusters(bool p, bool s);
	void modulateThrust(bool up);

	void getRotation(D3DXVECTOR3* _rotation);
	void setRotation(D3DXVECTOR3* _rotation);
	void getLook(D3DXVECTOR3* _look); //
	void setLook(D3DXVECTOR3* _look);
	void setScale(D3DXVECTOR3* _pScale);
	void setMesh(ViewObject* _pMesh);
	void getMesh(ViewObject** _pMesh);
	void setDevice(IDirect3DDevice9* localDevice);
	void setCamera(float _distanceZ, float _distanceY);
	bool highlevelCollisionDetection(objectTransform* objectToCheckAgainst);
	bool highlevelCollisionDetection(D3DXVECTOR3 objectsPosition);
	D3DXVECTOR3 rotate3D(float angle, D3DXVECTOR3 u);

	virtual void walk(float units); // forward/backward
	void updateCamera();
	void pitch(float angle); // rotate on left vector
	void yaw(float angle); // rotate on up vector
	void roll(float angle); // rotate on look vector
	virtual void getMatrix(D3DXMATRIX* V);
	void addObjectSound(CSound* _sound);
	void playSound(int soundNumber);
	void drawMesh();
	void drawMesh(int index);
	void drawMeshBounding();
	float getPosX();
	float getPosY();
	float getPosZ();

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
	bool chaseCamera;
	float distanceZ;
	float distanceY;

	D3DXVECTOR3 scale;
	D3DXVECTOR3 look;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 currentVector; // Current directional vector. Used in object culling

	D3DXVECTOR3 cameraPosition; // camera Position
	D3DXVECTOR3 cameraLookAt; // camera lookAt;


	Boundary    objectBoundaries;
	std::vector<CSound*> sound;  //can have a number of associated sounds
	std::vector<ViewObject*> pMeshObjects; //can have a number of meshes
	IDirect3DDevice9* localDevice;

	float	fMass;				// total mass (constant)
	float	fInertia;			// mass moment of inertia in body coordinates (constant)
	float	fInertiaInverse;	// inverse of mass moment of inertia (constant)
	
	D3DXVECTOR3	pos;			// position in earth coordinates
	D3DXVECTOR3	velocity;			// velocity in earth coordinates
	D3DXVECTOR3	velocityBody;		// velocity in body coordinates
	D3DXVECTOR3	angularVelocity;	// angular velocity in body coordinates
		
	float	fSpeed;				// speed (magnitude of the velocity)
	float	fOrientation;		// orientation 	

	D3DXVECTOR3	forces;			// total force on body
	D3DXVECTOR3	moment;			// total moment (torque) on body (2D: about z-axis only)

	float	thrustForce;		// Magnitude of the thrust force
	D3DXVECTOR3	pThrust, sThrust;	// bow thruster forces

	D3DXVECTOR3	CD;
	D3DXVECTOR3	CT;
	D3DXVECTOR3	CPT;
	D3DXVECTOR3	CST;

	D3DXVECTOR3	Fa;// other applied force
	D3DXVECTOR3  Pa;// location of other applied force

	float tol;

	float	ProjectedArea;
};
#endif // INC_OBJECTTRANSFORM_H