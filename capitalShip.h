#ifndef INC_CAPITALSHIP_H
#define INC_CAPITALSHIP_H

#include "aiShip.h"
#include <cstdlib>

class CapitalShip : public AIShip
{
public:
	CapitalShip(ViewObject* fighterMeshL,
	ViewObject* fighterMeshM,
	ViewObject* fighterMeshH,
	CSound* fighterSound);
	void setAsPlayerCarrier(bool value);
	bool getIsPlayerCarrier();
	D3DXVECTOR3 getBayLocation();

	CapitalShip();
	~CapitalShip();

	bool highlevelCollisionDetection(objectTransform* objectToCheckAgainst);
	bool highlevelCollisionDetection(D3DXVECTOR3 objectsPosition);
	void launchFighter(IDirect3DDevice9* _pDevice,std::vector<CapitalShip*>* _pShipList,HWND localHandle,CSoundManager* sound3Dmanager);

private:
	ViewObject* _pMeshL;
	ViewObject* _pMeshM;
	ViewObject* _pMeshH;
	CSound* _pSound;
	D3DXVECTOR3 bayLocation;
	bool isPlayerCarrier;
};

#endif //INC_CAPITALSHIP_H








