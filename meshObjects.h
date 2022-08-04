#ifndef INC_MESHOBJECTS_H
#define INC_MESHOBJECTS_H

#include "aiShip.h"
#include "basicColours.h"
#include "billboardSprite.h"

class MeshObjects
{
public:
	MeshObjects();
	~MeshObjects();
	void setDevice(IDirect3DDevice9* _pDevice);
	void drawObjects(float timeDelta);
	void drawObjects(int index);
	void drawSprites();
	void drawSprite(int index);
	void getShip(int index,AIShip** selectedShip);

	void addPlayerShip(Ship* _playerShip);

	bool addObject(ViewObject* _pMesh, // Add an object to the vector of objects
			          CSound* _pSound,
					  D3DXVECTOR3* _pPos,
					  D3DXVECTOR3* _pRotation,
					  D3DXVECTOR3* _pScale);
	bool addAIShip(ViewObject* _pMesh, // Add an object to the vector of objects
			          CSound* _pSound,
					  D3DXVECTOR3* _pPos,
					  D3DXVECTOR3* _pRotation,
					  D3DXVECTOR3* _pScale,
					  bool _friendly);

	bool setObjectMesh(int index,ViewObject* _pMesh);
	bool setObjectSound(int index,CSound* _pSound);
	bool setObjectLocation(int index,D3DXVECTOR3* _pPos);
	bool setObjectRotation(int index,D3DXVECTOR3* _pRotation);
	bool setObjectScale(int index,D3DXVECTOR3* _pScale);
	void orientateSprites();
	void checkFire();

	void updateAIShips(float timeDelta);
	void drawCockpit();

	void cleanUP();

private:
	bool loadNavPoints();

	float cullingAngle;
	D3DXVECTOR3 spriteOrientation;

	std::vector<NavPoint*> navPointsList;
	IDirect3DDevice9* pLocalDevice;
	std::vector<objectTransform*> pObjectsList;
	std::vector<AIShip*> pShipList;
	Ship* playerShip; // Pointer to player ship for drawing

	billboardSprite plasmaSprite;
};
#endif // INC_MESHOBJECTS_H
