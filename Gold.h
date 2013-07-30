//Gold.h: header file for the Gold.cpp. Will be the currency of the game
#ifndef _Gold
#define _Gold

#include "Item.h"
#include <ostream>

class Gold : public Item
{
public:
	//Constructor
	Gold();

	//Other methods
	virtual void pickUp();
	virtual void dumpObject();
	virtual void writeFragment(std::ostream & output, int iTabs);
};

#endif
