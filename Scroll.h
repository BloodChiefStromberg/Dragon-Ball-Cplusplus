#ifndef _Scroll
#define _Scroll

#include "Consumable.h"
#include <ostream>

class Scroll : public Consumable
{
public:
	//Constructor
	Scroll();

	//Other methods
	virtual void use();
	virtual void dumpObject();
	virtual void writeFragment(std::ostream & output, int iTabs);
};

#endif
