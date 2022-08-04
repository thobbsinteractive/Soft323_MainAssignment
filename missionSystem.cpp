#include "missionSystem.h"

MissionSystem::MissionSystem()
{
	timeFractions=0.0f;
	missionTime=0.0f;
	winLoseTime = 20.0f;

	firstEnemyShipHasArrived = false;
	missionStarted = false;
	missionLost = false;
	missionWon = false;
	missionCompleted = false;
	battleStarted = false;

	missionCriticalFriendlyAdded = false;
	missionCriticalEnemyAdded = false;

	stringObjectivesList = "";
	textTime = 0.0f;
	timePast = 0.0f;
}

MissionSystem::~MissionSystem()
{
	// stop any other music and unload it
	if(musicOn == true)
	{
		surspence.unLoad();	
		enemyArriveMusic.unLoad();
		briefingMusic.unLoad();
		failMusic.unLoad();
		friendLostMusic.unLoad();
		winMusic.unLoad();
		dogfightMusic.unLoad();
	}

	for(int i =0;i < (int)eventsList.size();i++)
	{
		//erase all events when finished
		eventsList.erase(eventsList.begin() + i);
	}
}

void MissionSystem::startMission()
{
	missionStarted = true;
}

bool MissionSystem::missionFailed()
{
	return missionLost;
}

bool MissionSystem::missionComplete()
{
	return missionCompleted;
}

bool MissionSystem::missionBegun()
{
	return missionStarted;
}

bool MissionSystem::initialiseMission(IDirect3DDevice9* _pDevice,int _meshDetail,PlayerShip* _playerShipRef,GameSettings userSettings)
{
	bool loadOkay;
	plocalDevice = _pDevice;
	meshDetail = _meshDetail;
	playerShipRef = _playerShipRef;

	D3DXVECTOR3 Pos = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	musicOn = userSettings.music;

	if(musicOn == true)
	{
		briefingMusic.load("music/Briefing.mp3");
		failMusic.load("music/FriendlyDown.mp3");
		winMusic.load("music/Win.mp3");
		enemyArriveMusic.load("music/EnemyArrival.mp3");
		dogfightMusic.load("music/Battle.mp3");
		surspence.load("music/Suspense.mp3");
	}

	if(meshDetail == 2)
	{
		loadOkay = fighterLow.loadMeshIntoBuffer("models/low/goodfighter.x",plocalDevice);
		loadOkay = fighterMed.loadMeshIntoBuffer("models/med/goodfighter.x",plocalDevice);
		loadOkay = fighterHigh.loadMeshIntoBuffer("models/high/goodfighter.x",plocalDevice);

		loadOkay = capShipHigh.loadMeshIntoBuffer("models/high/capShip.x",plocalDevice);
		loadOkay = capShipMed.loadMeshIntoBuffer("models/med/capShip.x",plocalDevice);
		loadOkay = capShipLow.loadMeshIntoBuffer("models/low/capShip.x",plocalDevice);

	}

	if(meshDetail == 1)
	{
		loadOkay = fighterLow.loadMeshIntoBuffer("models/low/goodfighter.x",plocalDevice);
		loadOkay = fighterMed.loadMeshIntoBuffer("models/med/goodfighter.x",plocalDevice);

		loadOkay = capShipMed.loadMeshIntoBuffer("models/low/capShip.x",plocalDevice);
		loadOkay = capShipLow.loadMeshIntoBuffer("models/med/capShip.x",plocalDevice);
	}

	if(meshDetail == 0)
	{
		loadOkay = fighterLow.loadMeshIntoBuffer("models/low/goodfighter.x",plocalDevice);

		loadOkay = capShipLow.loadMeshIntoBuffer("models/low/capShip.x",plocalDevice);
	}

	loadEventsScript();

	return loadOkay;
}

bool MissionSystem::showBriefingScreen()
{
	if(missionStarted == false)
	{
		return true;

	}else if(winLoseTime < 0.0f)
	{
		return true;

	}else if(missionCompleted == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// This should all really be read from a file
void MissionSystem::loadEventsScript()
{

	// Nav points for this object, dimond formation around cap ship for friendlies
	std::vector<NavPoint*> navPointsList;
	NavPoint* tempNav = new NavPoint();
	tempNav->location = D3DXVECTOR3(0.0f,0.0f,150000.0f);
	navPointsList.push_back(tempNav);

	tempNav = new NavPoint();
	tempNav->location = D3DXVECTOR3(0.0f,150000.0f,0.0f);
	navPointsList.push_back(tempNav);

	tempNav = new NavPoint();
	tempNav->location = D3DXVECTOR3(150000.0f,0.0f,150000.0f);
	navPointsList.push_back(tempNav);

	tempNav = new NavPoint();
	tempNav->location = D3DXVECTOR3(-150000.0f,0.0f,0.0f);
	navPointsList.push_back(tempNav);

	tempNav = new NavPoint();
	tempNav->location = D3DXVECTOR3(0.0f, 150000.0f,0.0f);
	navPointsList.push_back(tempNav);

	// Player Carrier
	Event* tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(0,10.0,19.0);
	tempEvent->rotation = D3DXVECTOR3(0*(D3DX_PI/180),0,0);
	tempEvent->friendly = true;
	tempEvent->time = 0.0f;
	tempEvent->type = 'c';
	tempEvent->missionCritical = true; // if this ship dies you lose the mission
	tempEvent->isPlayersCarrier = true; // needed for landing
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "HMS Exeter\n(Must Survive):";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(-50,0,-40.0);
	tempEvent->rotation = D3DXVECTOR3(0*(D3DX_PI/180),0,0);
	tempEvent->friendly = true;
	tempEvent->time = 0.0f;
	tempEvent->type = 'f';
	tempEvent->missionCritical = false;
	tempEvent->navPointsList = navPointsList;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(-10,0,20.0);
	tempEvent->rotation = D3DXVECTOR3(0*(D3DX_PI/180),0,0);
	tempEvent->friendly = true;
	tempEvent->time = 0.0f;
	tempEvent->type = 'f';
	tempEvent->missionCritical = false;
	tempEvent->navPointsList = navPointsList;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(10,0,20.0);
	tempEvent->rotation = D3DXVECTOR3(0*(D3DX_PI/180),0,0);
	tempEvent->friendly = true;
	tempEvent->time = 0.0f;
	tempEvent->type = 'f';
	tempEvent->missionCritical = false;
	tempEvent->navPointsList = navPointsList;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "";

	eventsList.push_back(tempEvent);

	// Enemies
	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(0,0,1000.0);
	tempEvent->rotation = D3DXVECTOR3(180*(D3DX_PI/180),0,0);
	tempEvent->friendly = false;
	tempEvent->time = 120.0f;
	tempEvent->type = 'c';
	tempEvent->missionCritical = true;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = true;
	tempEvent->objectiveText = "HMS Wellington:\n(Destroy)";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(-100,100.0,1000.0);
	tempEvent->rotation = D3DXVECTOR3(180*(D3DX_PI/180),0,0);
	tempEvent->friendly = false;
	tempEvent->time = 130.0f;
	tempEvent->type = 'c';
	tempEvent->missionCritical = true;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = true;
	tempEvent->objectiveText = "EAS Strasbourg:\n(Destroy)";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(100,100.0,1000.0);
	tempEvent->rotation = D3DXVECTOR3(180*(D3DX_PI/180),0,0);
	tempEvent->friendly = false;
	tempEvent->time = 125.0f;
	tempEvent->type = 'c';
	tempEvent->missionCritical = true;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = true;
	tempEvent->objectiveText = "HMS FearLess:\n(Destroy)";

	eventsList.push_back(tempEvent);

	// Fighters
	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(0,0,0);    // these dont matter when sporning
	tempEvent->rotation = D3DXVECTOR3(0,0,0); // these dont matter when sporning
	tempEvent->friendly = false; // these dont matter when sporning
	tempEvent->time = 150.0f;
	tempEvent->type = 's'; // ship is being sporned from carrier
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "";

	eventsList.push_back(tempEvent);

	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(0,0,0);    // these dont matter when sporning
	tempEvent->rotation = D3DXVECTOR3(0,0,0); // these dont matter when sporning
	tempEvent->friendly = false; // these dont matter when sporning
	tempEvent->time = 160.0f;
	tempEvent->type = 's'; // ship is being sporned from carrier
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = false;
	tempEvent->objectiveText = "";

	eventsList.push_back(tempEvent);

/*


	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(0,0,1000.0);
	tempEvent->rotation = D3DXVECTOR3(180*(D3DX_PI/180),0,0);
	tempEvent->friendly = false;
	tempEvent->time = 20.0f;
	tempEvent->type = 'f';
	tempEvent->missionCritical = true;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = true;
	tempEvent->objectiveText = "HMS Wellington:\n(Destroy)";

	eventsList.push_back(tempEvent);


	tempEvent = new Event();
	tempEvent->location = D3DXVECTOR3(-100,100.0,1000.0);
	tempEvent->rotation = D3DXVECTOR3(180*(D3DX_PI/180),0,0);
	tempEvent->friendly = false;
	tempEvent->time = 30.0f;
	tempEvent->type = 'f';
	tempEvent->missionCritical = true;
	tempEvent->isPlayersCarrier = false;
	tempEvent->jumpingIn = true;
	tempEvent->objectiveText = "EAS Strasbourg:\n(Destroy)";*/
}

void MissionSystem::checkCriticalList(GameObjects* pGameObjects)
{
	D3DXVECTOR3 carrierLandingBayPosition;

	pGameObjects->getShipList(&pShipList);
	int numberOfCriticalFriendlies = 0;
	int numberOfCriticalEnemies = 0;

	stringObjectivesList = "Objectives:\n";

	if(playerShipRef->getHealth() <= 0)
	{
		missionLost=true;
		winLoseTime = -1.0f;
	}

	for(int i = 0;i < (int)pShipList.size(); i++)
	{

		// Check if a friendly critical ship has been added, if so the mission can now be lost
		if((pShipList[i]->getIFF()== true)&&(pShipList[i]->getMissionCritical() == true)&&(missionCriticalFriendlyAdded == false))
		{
			missionCriticalFriendlyAdded = true;
		}

		// Check if a enemy critical ship has been added, if so the mission can now be won
		if((pShipList[i]->getIFF()== false)&&(pShipList[i]->getMissionCritical() == true)&&(missionCriticalEnemyAdded == false))
		{
			missionCriticalEnemyAdded = true;
		}

		// count number of critical friendly ships
		if((pShipList[i]->getIFF()== true)&&(pShipList[i]->getMissionCritical() == true)&&(missionCriticalFriendlyAdded == true))
		{
			numberOfCriticalFriendlies++;
			char tempString[250];
			sprintf(tempString," Health:%.0f\n",pShipList[i]->getHealth());
			tempString[249] = '\0';
			stringObjectivesList = stringObjectivesList + pShipList[i]->getComments() + tempString;

			// We only need to know this when the mission is complete
			if((pShipList[i]->getIsPlayerCarrier() == true)&&(missionWon == true))
			{
				carrierLandingBayPosition = pShipList[i]->getBayLocation();
			}
		}

		// count number of enemy critical ships
		if((pShipList[i]->getIFF() == false)&&(pShipList[i]->getMissionCritical() == true)&&(missionCriticalEnemyAdded == true))
		{
			numberOfCriticalEnemies++;
			char tempString[250];
			sprintf(tempString," Health:%.0f\n",pShipList[i]->getHealth());
			tempString[249] = '\0';
			stringObjectivesList = stringObjectivesList + pShipList[i]->getComments() + tempString;
		}
	}

	// Mission lost
	if((numberOfCriticalFriendlies == 0)&&(missionCriticalFriendlyAdded == true))
	{
		// on first time through reset text time
		if(missionLost == false)
		{
			textTime = 0.0f;
		}

		missionLost = true;
		missionWon = false; // we can still lose if all enemies are defeated by killing the carrier
		stringObjectivesList = "Mission Failed, HMS Exeter has been destroyed!";
	}

	// Mission won
	if((numberOfCriticalEnemies == 0)&&(missionCriticalEnemyAdded == true))
	{
		// on first time through reset text time
		if(missionWon == false)
		{
			textTime = 0.0f;
		}

		missionWon = true;
		stringObjectivesList = "Mission Complete, Land at HMS Exeter";

		if((playerShipRef->distanceToTarget(carrierLandingBayPosition) < 10000)&&(missionWon == true))
		{
			missionCompleted = true;
		}
	}

	playerShipRef->setObjectivesList(stringObjectivesList);
}


void MissionSystem::checkMusic(GameObjects* pGameObjects)
{
	int numberOfFriendlies = 0;
	int numberOfEnemys = 0;

	pGameObjects->getShipList(&pShipList);

	if(musicOn == true)
	{
		if(missionStarted == true)
		{
			for(int i = 0;i < (int)pShipList.size(); i++)
			{
				if(pShipList[i]->getIFF()== true)
				{
					numberOfFriendlies++;
				}

				if(pShipList[i]->getIFF() == false)
				{
					numberOfEnemys++;

					if(pShipList[i]->isCapital() == true)
					{
						if(pShipList[i]->getHealth() < 1000)
						{
							battleStarted = true;
						}

					}else
					{
						if(pShipList[i]->getHealth() < 100)
						{
							battleStarted = true;
						}
					}
				}
			}

			if((missionWon==false)&&(missionLost==false))
			{
				// play surspense music
				if(numberOfEnemys == 0)
				{
					// stop any other music
					if(enemyArriveMusic.isPlaying() == true)
					{
						enemyArriveMusic.stop();
					}

					if(briefingMusic.isPlaying() == true)
					{
						briefingMusic.stop();
					}

					if(failMusic.isPlaying() == true)
					{
						failMusic.stop();
					}

					if(friendLostMusic.isPlaying() == true)
					{
						friendLostMusic.stop();
					}

					if(winMusic.isPlaying() == true)
					{
						winMusic.stop();
					}

					if(dogfightMusic.isPlaying() == true)
					{
						dogfightMusic.stop();
					}

					// Play tune
					if(surspence.isPlaying() == false)
					{
						surspence.play();
					}
				}

				// play enemy arrive music
				if((numberOfEnemys > 0)&&(firstEnemyShipHasArrived==false))
				{
					firstEnemyShipHasArrived = true;

					// stop any other music
					if(surspence.isPlaying() == true)
					{
						surspence.stop();
					}

					if(briefingMusic.isPlaying() == true)
					{
						briefingMusic.stop();
					}

					if(failMusic.isPlaying() == true)
					{
						failMusic.stop();
					}

					if(friendLostMusic.isPlaying() == true)
					{
						friendLostMusic.stop();
					}

					if(winMusic.isPlaying() == true)
					{
						winMusic.stop();
					}

					if(dogfightMusic.isPlaying() == true)
					{
						dogfightMusic.stop();
					}

					// Play tune
					if(enemyArriveMusic.isPlaying() == false)
					{
						enemyArriveMusic.play();
					}
				}

				// play dogfighting
				if((numberOfEnemys > 0)&&(battleStarted==true))
				{
					// stop any other music
					if(surspence.isPlaying() == true)
					{
						surspence.stop();
					}

					if(briefingMusic.isPlaying() == true)
					{
						briefingMusic.stop();
					}

					if(failMusic.isPlaying() == true)
					{
						failMusic.stop();
					}

					if(friendLostMusic.isPlaying() == true)
					{
						friendLostMusic.stop();
					}

					if(winMusic.isPlaying() == true)
					{
						winMusic.stop();
					}

					if(enemyArriveMusic.isPlaying() == true)
					{
						enemyArriveMusic.stop();
					}

					// Play tune
					if(dogfightMusic.isPlaying() == false)
					{
						dogfightMusic.play();
					}
				}
			}

			if(numberOfEnemys == 0)
			{
				firstEnemyShipHasArrived = false;
				battleStarted = false;
			}


			if(missionWon == true)
			{
				// stop any other music
				if(surspence.isPlaying() == true)
				{
					surspence.stop();
				}

				if(briefingMusic.isPlaying() == true)
				{
					briefingMusic.stop();
				}

				if(failMusic.isPlaying() == true)
				{
					failMusic.stop();
				}

				if(friendLostMusic.isPlaying() == true)
				{
					friendLostMusic.stop();
				}

				if(dogfightMusic.isPlaying() == true)
				{
					dogfightMusic.stop();
				}

				if(enemyArriveMusic.isPlaying() == true)
				{
					enemyArriveMusic.stop();
				}

				// Play tune
				if(winMusic.isPlaying() == false)
				{
					winMusic.play();
				}
			}

			if(missionLost == true)
			{
				// stop any other music
				if(surspence.isPlaying() == true)
				{
					surspence.stop();
				}

				if(briefingMusic.isPlaying() == true)
				{
					briefingMusic.stop();
				}

				if(friendLostMusic.isPlaying() == true)
				{
					friendLostMusic.stop();
				}

				if(winMusic.isPlaying() == true)
				{
					winMusic.stop();
				}

				if(dogfightMusic.isPlaying() == true)
				{
					dogfightMusic.stop();
				}

				if(enemyArriveMusic.isPlaying() == true)
				{
					enemyArriveMusic.stop();
				}

				// Play tune
				if(failMusic.isPlaying() == false)
				{
					failMusic.play();
				}
			}
		}else
		{
			if(briefingMusic.isPlaying() == false)
			{
				briefingMusic.play();
			}
		}
	}
}

void MissionSystem::getBriefingText(std::string *text,float timeDelta)
{
	std::string briefText = "Confidential\n\n";
	briefText = briefText + "10/08/2265\n\n";
	briefText = briefText + "Intelligence Briefing:\n\n";
	briefText = briefText + "I am sure by now you are all aware of the reported incursion by United Planets forces into Alliance\n";
	briefText = briefText + "territory yesterday, it has now been established that over 11,000 alliance service man and women lost\n";
	briefText = briefText + "their lives in the strike at the Proxima Centauri ship yards deep within our territory. This attack\n";
	briefText = briefText + "was a desperate move by the UPA to not only cripple ship production but to also strike at morale\n";
	briefText = briefText + "across the whole Sol sector. For the first time in 16 years earth is under direct threat.\n\n";
	briefText = briefText + "Mission Briefing Follows:\n\n";
	briefText = briefText + "At 0743 this morning three Alliance carriers believed lost at Proxima Centauri, HMS FearLess,\n"; 
	briefText = briefText + "HMS Wellington, and the EAS Strasbourg attacked and destroyed a small listening outpost in the Sol\n"; 
	briefText = briefText + "system Ort cloud. These ships are now under UPA control and headed for earth.\n";
	briefText = briefText + "Command has ordered all available ships in this sector to defend earth. They predict that the\n"; 
	briefText = briefText + "UPA's most likely target is mainland Europe. HMS Exeter has been deployed to cover the Africa\n"; 
	briefText = briefText + "continent.\n\n";
	briefText = briefText + "Lieutenant you will fly as part of alpha wing on a standard diamond patrol route around Exeter. Our\n"; 
	briefText = briefText + "chances of encountering the enemy are low however you should be ready for redeployment should\n"; 
	briefText = briefText + "Exeter be recalled to assist in other sectors of planetary defence.\n\n";
	briefText = briefText + "If you do encounter the enemy for god sake watch your targets, your IFF codes have been updated to\n"; 
	briefText = briefText + "mark the FearLess, Wellington, and Strasbourg as enemy ships, but they will be flying with Alliance\n"; 
	briefText = briefText + "flags.\n\n";
	briefText = briefText + "Your primary objective is to defend HMS Exeter.\n\n";
	briefText = briefText + "GoodLuck Lieutenant\n\n\n";
	briefText = briefText + "--Click to Continue--";

	timePast += timeDelta;
	if(timePast >= 0.02f)
	{
		textTime++;
		timePast = 0.0f;
	}

	if(textTime < briefText.size())
	{
		briefText[textTime] = '\0';
	}
	*text = briefText;

}

void MissionSystem::getLoseText(std::string *text,float timeDelta)
{
	std::string loseText = "Confidential\n\n";
	loseText = loseText + "10/09/2265\n\n";
	loseText = loseText + "Mission Debriefing\n\n";
	loseText = loseText + "I sorry to report that at 0945 hours HMS Exeter went down with all hands. You were lucky that SAR\n";
	loseText = loseText + "teams detected your locater beacon when they did Lieutenant otherwise you would have been left\n";
	loseText = loseText + "drifting in earths orbit for decades. Understand there was nothing you could have done son,\n";
	loseText = loseText + "Exeter was out numbered three to one.\n\n";
	loseText = loseText + "This has been a tragic day for the Alliance, with the loss of six carrier groups across the sector\n";
	loseText = loseText + "battle for the Sol sector has turned distinctly in favour of the Americans. Currently they are\n";
	loseText = loseText + "reinforcing their positions in Proxima Centauri, however command believes that the invasion\n";
	loseText = loseText + "could start any day now.\n";
	loseText = loseText + "With so few ships left to defend Sol we have been tasked with providing cover for the outer\n"; 
	loseText = loseText + "planets while other EA forces are pulled from the outer systems to help defend earth.\n\n";

	loseText = loseText + "Lieutenant following the destruction of Exeter you have been reassigned to HMS Ark Royal\n\n\n";
	loseText = loseText + "--Click to Continue--";

	timePast += timeDelta;
	if(timePast >= 0.02f)
	{
		textTime++;
		timePast = 0.0f;
	}

	if(textTime < loseText.size())
	{
		loseText[textTime] = '\0';
	}
	*text = loseText;
}

void MissionSystem::getWinText(std::string *text,float timeDelta)
{
	std::string winText = "Confidential\n\n";
	winText = winText + "10/09/2265\n\n";
	winText = winText + "Mission Debriefing\n\n";
	winText = winText + "Good work alpha wing you all played a crucial role today, the destruction of the three captured\n";
	winText = winText + "carriers may have swung the battle for this system in our favour.\n\n";
	winText = winText + "Though this has been a somewhat tragic day for the Alliance, with the lose of four additional\n"; 
	winText = winText + "carrier groups across the system, EA forces managed to repel the American attack on Sol.\n";
	winText = winText + "Rumour has it that command is gearing up to send in HMS Exeter and the Coventry battle group\n";
	winText = winText + "to take back Proxima Centauri as we speak.\n\n";
	winText = winText + "Lieutenant for the critical role you played in defending HMS Exeter command has seen fit to\n"; 
	winText = winText + "reassign you to special operations. Your orders are to report to HMS Coventry from there\n";
	winText = winText + "you will travel to an undisclosed location to start your assignment.\n\n";

	winText = winText + "Good luck Lieutenant I know you will be missed on the Exeter.\n\n\n";

	winText = winText + "--Click to Continue--";

	timePast += timeDelta;
	if(timePast >= 0.02f)
	{
		textTime++;
		timePast = 0.01f;
	}

	if(textTime < winText.size())
	{
		winText[textTime] = '\0';
	}
	*text = winText;
}

void MissionSystem::checkEvents(float timeDelta,GameObjects* pGameObjects)
{
	timeFractions += timeDelta;

	if(timeFractions > 0.5f)
	{
		missionTime += 1.0f;
		timeFractions = 0.0f;

		if(missionLost == true)
		{
			winLoseTime -= 1.0f;
		}
	}

	for(int i = 0; i < (int)eventsList.size();i++)
	{
		if(missionTime >= eventsList[i]->time)
		{
			// do event
			if(eventsList[i]->type == 'f') // adds a fighter
			{
				switch(meshDetail)
				{
					case 2: pGameObjects->addAIShip(&fighterLow,&fighterMed,&fighterHigh,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText);
						break;
					case 1: pGameObjects->addAIShip(&fighterLow,&fighterMed,NULL,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText);
						break;
					case 0: pGameObjects->addAIShip(&fighterLow,NULL,NULL,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText);
						break;
				}
			}else if(eventsList[i]->type == 'c') // adds a capital ship
			{
				switch(meshDetail)
				{
				case 2: pGameObjects->addAICapShip(&capShipLow,&capShipMed,&capShipHigh,&fighterLow,&fighterMed,&fighterHigh,NULL,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText,eventsList[i]->isPlayersCarrier);
						break;
					case 1: pGameObjects->addAICapShip(&capShipLow,&capShipMed,&capShipHigh,&fighterLow,&fighterMed,NULL,NULL,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText,eventsList[i]->isPlayersCarrier);
						break;
					case 0: pGameObjects->addAICapShip(&capShipLow,&capShipMed,&capShipHigh,&fighterLow,NULL,NULL,NULL,NULL,eventsList[i]->location * 1000,eventsList[i]->rotation,D3DXVECTOR3(1.0f,1.0f,1.0f),eventsList[i]->friendly,eventsList[i]->navPointsList,eventsList[i]->missionCritical,eventsList[i]->jumpingIn,eventsList[i]->objectiveText,eventsList[i]->isPlayersCarrier);
						break;
				}
			}else if(eventsList[i]->type == 's') // provides events for launching fighters
			{
				if(eventsList[i]->friendly == true)
				{
					pGameObjects->sporneFriendly();
				}else
				{
					pGameObjects->sporneEnemy();
				}
			}

			// erase event
			eventsList.erase(eventsList.begin() + i);
		}
	}
}