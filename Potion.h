//Potion.h: header file for Potion.cpp. Use() method will grant benefits to
//player?
#ifndef _Potion
#define _Potion

#include "Consumable.h"
#include <ostream>

class Potion : public Consumable
{
public:
	//Constructor
	Potion();

	//Other methods
	virtual void use();
	virtual void dumpObject();
	virtual void writeFragment(std::ostream & output, int iTabs);
};

#endif
