#ifndef INC_PLAYERSHIP_H
#define INC_PLAYERSHIP_H

#include "ship.h"
#include "CapitalShip.h"

class PlayerShip : public Ship
{
public:
	PlayerShip();
	~PlayerShip();

	void displayTargetStatus();
	void initialiseFonts(int _width,int _height);
	void setTargetShip(CapitalShip* _targetedShip);
	void setObjectivesList(std::string newList);
	void getAnglesToRotateForPlayer(float* x,float* y,D3DXVECTOR3* arrowPosition);
	void updateAllsounds();

private:
	std::string aiTextFinal;  // String to display current ai information
	char hudValues[50];       // String to display more current ai information
	char playerValues[50];

	std::string objectivesList; // objectives list.

	CapitalShip* targetedShip;
	ID3DXFont* font;
	LOGFONT lf;
	int width;
	int height;
};
#endif //INC_PLAYERSHIP_H