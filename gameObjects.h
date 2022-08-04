#ifndef INC_GAMEOBJECTS_H
#define INC_GAMEOBJECTS_H

#include <cstdlib>

#include "aiShip.h"
#include "basicColours.h"
#include "billboardSprite.h"
#include "spaceDust.h"
#include "playerShip.h"
#include "explosion.h"
#include "capitalShip.h"
#include "fire.h"
#include "mp3Player.h"

class GameObjects
{
public:
	GameObjects();
	~GameObjects();
	void setDevice(IDirect3DDevice9* _pDevice,CSoundManager* _soundManager);
	void initialiseSounds(HWND handle);
	void drawObjects();
	void drawObjectsWithVolumeShadow();
	void drawCockpitWithVolumeShadow();
	void BuildFromMesh( ID3DXMesh* pMesh, D3DXVECTOR3 vLight );
	void RenderShadowGeometry();
	void AddEdge(WORD* pEdges, DWORD& dwNumEdges, WORD v0, WORD v1);
	void drawRadarObjects();
	void drawObjects(int index);
	void drawSprites(float timeDelta);
	void drawSprite(int index);
	void getShip(int index,CapitalShip** selectedShip);
	void playSounds();
	void setDefaultRenderStates();
	void targetNextFriendly();
	void targetNextEnemy();
	void targetNearestEnemy();
	void getShipList(std::vector<CapitalShip*> *_pShipList);

	void addPlayerShip(PlayerShip* _playerShip);

	bool addObject(ViewObject* _pMesh, // Add an object to the vector of objects
			          CSound* _pSound,
					  D3DXVECTOR3 _pPos,
					  D3DXVECTOR3 _pRotation,
					  D3DXVECTOR3 _pScale);

	bool addAIShip(ViewObject* _pMeshL,
					ViewObject* _pMeshM,
					ViewObject* _pMeshH, // Add an object to the vector of objects
			          CSound* _pSound,
					  D3DXVECTOR3 _pPos,
					  D3DXVECTOR3 _pRotation,
					  D3DXVECTOR3 _pScale,
					  bool _friendly,std::vector<NavPoint*> navPointsList,
					  bool critical,
					  bool jumping,
					  std::string comments);

	bool addAICapShip(ViewObject* _pMeshL,
							ViewObject* _pMeshM,
							ViewObject* _pMeshH,
							ViewObject* _pFighterMeshL,
							ViewObject* _pFighterMeshM,
							ViewObject* _pFighterMeshH,
							CSound* _fighterSound,
							CSound* _pSound,
							D3DXVECTOR3 _pPos,
							D3DXVECTOR3 _pRotation,
							D3DXVECTOR3 _pScale,
							bool _friendly,std::vector<NavPoint*> navPointsList,
							bool critical,
							bool jumping,
							std::string comments,
							bool isPlayerCarrier);

	bool setObjectMesh(int index,ViewObject* _pMesh);
	bool setObjectSound(int index,CSound* _pSound);
	bool setObjectLocation(int index,D3DXVECTOR3* _pPos);
	bool setObjectRotation(int index,D3DXVECTOR3* _pRotation);
	bool setObjectScale(int index,D3DXVECTOR3* _pScale);
	void orientateSprites();
	void checkFire();
	void initialiseSpaceDust();
	void drawSpaceDust();

	void updateAIShips(float timeDelta);
	void drawCockpit();
	void setMeshDetail(int detail);

	void sporneFriendly();
	void sporneEnemy();

	void cleanUP();



private:

	template<class T> void Release(T t)
	{
		if(t)
		{
			t->Release();
			t = 0;
		}
	}

	template<class T> void Delete(T t)
	{
		if(t)
		{
			delete t;
			t = 0;
		}
	}

	float cullingAngle;
	D3DXVECTOR3 spriteOrientation;

	IDirect3DDevice9* pLocalDevice;

	std::vector<objectTransform*> pObjectsList;
	std::vector<Explosion*> pExplosionsList;

	std::vector<CapitalShip*> pShipList; // all ships are now capships

	PlayerShip* playerShip; // Pointer to player ship for drawing
	SpaceDust* dustSprites;

	billboardSprite plasmaSprite;
	billboardSprite targetReticuleFriendly;
	billboardSprite targetReticuleEnemy;

	billboardSprite reticuleNeutural;
	billboardSprite reticuleEnemy;

	imageSequence texture;
	imageSequence warpTexture;

	ID3DXMesh* sphereMesh;
	ID3DXMesh* radarMesh;
	ID3DXMesh* barMesh;
	ID3DXMesh* targetMesh;

	ViewObject navPointMesh;

	D3DMATERIAL9* greenMaterial;
	D3DMATERIAL9* redMaterial;
	D3DMATERIAL9* whiteMaterial;
	D3DMATERIAL9* grayMaterial;

	int meshDetail;

	D3DXVECTOR3 m_pVertices[32000]; // Vertex data for rendering shadow volume
    DWORD       m_dwNumVertices;

	// Sounds
	_3DSound engineSound;
	_3DSound plasmaFireSound;
	_3DSound warpSound;
	_3DSound explosion;

	CSoundManager *sound3Dmanager;

	HWND localHandle;

};
#endif // INC_GAMEOBJECTS_H
