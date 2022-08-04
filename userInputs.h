// My input structure that stores my games movement data, so I can update it all in one go

#ifndef INC_USERINPUTS_H
#define INC_USERINPUTS_H

struct UserInputs
{
	bool leftKey,rightKey,upKey,downKey;
	float xMouseMove, yMouseMove;
	bool mouseRole;
	bool forwardKey,backKey;
	bool roleLeft,roleRight;
	bool fireKey;
    bool escapeKey;
	bool targetEnemyKey;
	bool targetFriendlyKey;
	bool targetNearestEnemy;
};

#endif // INC_USERINPUTS_H