#include "playerShip.h"

PlayerShip::PlayerShip()
{
	objectivesList = "";
	health = 100.0f;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	speed = 0.0f;
	currentSpeedSetting = 0.0f;
	fireRate = 0.25f;
	timeTillFire = 0.0f;
	beingTargeted = false;

	angleOfCurrentObjective = 0.0f;
	targetedShip = NULL;

	width = 0;
	height = 0;
	font = 0;

	gunPosition1 = D3DXVECTOR3(-90.0f, -20.0f, 70.0f);
	gunPosition2 = D3DXVECTOR3(90.0f, -20.0f, 70.0f);
	angleToRotateX = 0;
	angleToRotateY = 0;
}

PlayerShip::~PlayerShip()
{
	Release<ID3DXFont*>(font);
}

void PlayerShip::initialiseFonts(int _width,int _height)
{
	//
	// Initialize a LOGFONT structure that describes the font
	// we want to create.
	//

	D3DXFONT_DESC lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));

	lf.Height         = 12;    // in logical units
	lf.Width          = 8;    // in logical units   
	lf.Weight         = 500;   // boldness, range 0(light) - 1000(bold) 
	lf.CharSet        = DEFAULT_CHARSET;
	lf.OutputPrecision  = 0;                       
	lf.Quality        = 0;           
	lf.PitchAndFamily = 0;           
	strcpy((char*)lf.FaceName, "Times New Roman"); // font style

	//
	// Create an ID3DXFont based on 'lf'.
	//

	if(FAILED(D3DXCreateFontIndirect(localDevice, &lf, &font)))
	{
		::MessageBox(0, _T("D3DXCreateFontIndirect() - FAILED"), 0, 0);
		::PostQuitMessage(0);
	}

	width = _width;       // screen width
	height = _height;     // screen height: Help scale fonts correctly to other resolutions
}

void PlayerShip::setTargetShip(CapitalShip* _targetedShip)
{
	targetedShip = _targetedShip;
	targetedShip->getPosition(&targetPos);
}

void PlayerShip::setObjectivesList(std::string newList)
{
	objectivesList = newList;
	//objectivesList.replace(0,objectivesList.length(),newList,0,newList.length());
}

void PlayerShip::displayTargetStatus()
{
	float x;
	float y;

	RECT rect = {(width/100)*16, (height/60)*57, width, height};
	RECT rect2 = {(width/100)*73, (height/60)*59, width, height};
	RECT hud = {0, (height/2)-(height/10), width, height};
	RECT objectivesListing = {(width/100)*50, (height/60)*1, width, height};

	std::string aiTextFinal;
	char aiValues[200];

	for(int i = 0;i < 50;i++)
	{
		hudValues[i] = 0;
	}

	for(int i = 0;i < 50;i++)
	{
		playerValues[i] = 0;
	}
	
	if(targetedShip)
	{
		getAngleToRotate(&x,&y);

		float distance = distanceToTarget();
		//distance = distance/1000; // Convert to meters

		// Display the position and speed of the ship
		if(targetedShip->getIFF() == false)
		{
			sprintf(aiValues,"Classifcation:Enemy\nHull:%.0f\nSpeed:%.2f\n",
				targetedShip->getHealth(),
				targetedShip->getCurrentSpeed());
			
			aiTextFinal.append(aiValues);
			
			std::string descriptionText = targetedShip->getComments();
			aiTextFinal.append(descriptionText);


		}else
		{
			sprintf(aiValues,"Classifcation:Friendly\nHull:%.0f\nSpeed:%.2f\n",
				targetedShip->getHealth(),
				targetedShip->getCurrentSpeed());
			
			aiTextFinal.append(aiValues);
			
			std::string descriptionText = targetedShip->getComments();
			aiTextFinal.append(descriptionText);
		}

		// Display the distance and direction
		if(x > rotation.x)
		{
			angleToRotateX = x - rotation.x;
		}

		if(x < rotation.x)
		{
			angleToRotateX = rotation.x - x;
			angleToRotateX = (360*(D3DX_PI/180)) - angleToRotateX;
		}

		if(y > rotation.y)
		{
			angleToRotateY = y - rotation.y;
		}

		if(y < rotation.y)
		{
			angleToRotateY = rotation.y - y;
			angleToRotateY = (360*(D3DX_PI/180)) - angleToRotateY;
		}
		
		sprintf(hudValues, "Distance:%.1f\nAngle:x:%.2f y:%.2f",
			distance,
			angleToRotateX*(180/D3DX_PI), // covert to degrees
			angleToRotateY*(180/D3DX_PI));

		hudValues[49] = '\0'; // mark end of string

		font->DrawText(NULL, (LPCWSTR)aiTextFinal.c_str(), -1,&rect,DT_TOP | DT_LEFT, 0xffffffff);
		font->DrawText(NULL, (LPCWSTR)hudValues, -1,&hud,DT_CENTER | DT_LEFT, 0xffffffff);
	}

	sprintf(playerValues, "Hull:%.0f\nSpeed:%.2f",
			getHealth(),
			getCurrentSpeed());
				
	playerValues[49] = '\0'; // mark end of string

	//Draw AI ship details
	font->DrawText(NULL, (LPCWSTR)playerValues, -1,&rect2,DT_TOP | DT_LEFT, 0xffffffff);
	font->DrawText(NULL, (LPCWSTR)objectivesList.c_str(), -1,&objectivesListing,DT_TOP | DT_CENTER, 0xffffffff);

	targetedShip = NULL; // Clear every frame so as to keep the HUD upto date
};

void PlayerShip::getAnglesToRotateForPlayer(float* xangle,float* yangle,D3DXVECTOR3* arrowPosition)
{
	*xangle=angleToRotateX;
	*yangle=angleToRotateY;

	D3DXVECTOR3 newPosition;
	updatePositionInRelationTo(D3DXVECTOR3(0.0f,150.0f,0.0f),rotation,&newPosition);
	*arrowPosition = newPosition;
}

void PlayerShip::updateAllsounds()
{
	for(int i = 0; i < sound.size(); i++)
	{
		sound[0].setListenerSoundPos(pos,0.0f);
	}
}