#include "Weapon.h"
#include "Scroll.h"
#include "Consumable.h"
#include <iostream>
#include <ostream>

using namespace std;

//Constructor
Scroll::Scroll() : Consumable()
{
}

//Other methods
void Scroll::use()
{
	cout << "This is the Scrolls use() method. Dunno what it does yet.";
}

void Scroll::dumpObject()
{
	cout << "OBJECT TYPE: Scroll" << endl;
	dumpObjectData();
}

void Scroll::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Scroll>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Scroll>" << endl;
}
