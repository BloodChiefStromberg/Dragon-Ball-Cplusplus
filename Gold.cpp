//Gold.cpp: defines functions declared in Gold.h

#include "Weapon.h"
#include "Item.h"
#include "Gold.h"
#include <ostream>
#include <iostream>

using namespace std;

//Constructor
Gold::Gold() : Item()
{
}

//Other methods
void Gold::pickUp()
{
	cout << "This is the Golds pickUp() function. IDK what it does yet." << endl;
}

void Gold::dumpObject()
{
	cout << "OBJECT TYPE: Gold" << endl;
	dumpObjectData();
}

void Gold::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Gold>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Gold>" << endl;
}
