// My input structure that stores my games movement data, so I can update it all in one go

#ifndef INC_USERINPUTS_H
#define INC_USERINPUTS_H

struct UserInputs
{
	bool leftKey,rightKey,upKey,downKey;
	bool forwardKey,backKey;
	bool fireKey;
    bool escapeKey;
};

#endif // INC_USERINPUTS_H