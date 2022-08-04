#ifndef INC_MISSIONSYSTEM_H
#define INC_MISSIONSYSTEM_H

//#include <d3dx9.h>
//#include "d3dutil.h"
#include "viewObject.h"
#include "event.h"
#include "gameObjects.h"
#include "playerShip.h"
#include "gameSettings.h"

class MissionSystem
{
public:
	MissionSystem();
	~MissionSystem();
	bool initialiseMission(IDirect3DDevice9* _pDevice,int _meshDetail,PlayerShip* _playerShipRef,GameSettings _userSettings);
	void getBriefingText(std::string *text,float timeDelta);
	void getLoseText(std::string *text,float timeDelta);
	void getWinText(std::string *text,float timeDelta);
	void checkEvents(float timeDelta,GameObjects* pGameObjects);
	void loadEventsScript();
	void checkMusic(GameObjects* pGameObjects);
	void checkCriticalList(GameObjects* pGameObjects);
	bool showBriefingScreen();
	void startMission();

	bool missionFailed();
	bool missionComplete();
	bool missionBegun();

private:

	float missionTime;

	float winLoseTime; // how long to wait after losing/winning a mission

	int textTime;
	float timePast;

	float timeFractions;
	IDirect3DDevice9* plocalDevice;
	int meshDetail;

	std::vector<Event*> eventsList;
	std::vector<CapitalShip*> pShipList; // a copy of the ships list

	PlayerShip* playerShipRef; // a copy of the players ship, usefull for setting objectives

	ViewObject fighterHigh;
	ViewObject fighterMed;
	ViewObject fighterLow;

	ViewObject capShipHigh;
	ViewObject capShipMed;
	ViewObject capShipLow;


		// Music
	mp3Player briefingMusic;
	mp3Player failMusic;
	mp3Player friendLostMusic;
	mp3Player winMusic;
	mp3Player enemyArriveMusic;
	mp3Player dogfightMusic;
	mp3Player surspence;

	bool firstEnemyShipHasArrived; // helps to know when to play enemy arrived theme
	bool missionStarted;
	bool missionLost;
	bool missionWon;
	bool missionCompleted;  // When the mission is won we need to know if we have returned to carrier
	bool battleStarted;

	bool missionCriticalFriendlyAdded; // can lose mission if this is true and all critcal ships are destroyed
	bool missionCriticalEnemyAdded; // can win mission if this is true and all critcal ships are destroyed

	bool musicOn;
	std::string stringObjectivesList;
};

#endif //INC_MISSIONSYSTEM_H