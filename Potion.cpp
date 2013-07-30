#include "Weapon.h"
#include "Potion.h"
#include "Consumable.h"
#include <iostream>
#include <ostream>


using namespace std;

//Constructor
Potion::Potion() : Consumable()
{
}

//Other methods
void Potion::use()
{
	cout << "This is the potions use() method. Dunno what it does yet.";
}

void Potion::dumpObject()
{
	cout << "OBJECT TYPE: Potion" << endl;
	dumpObjectData();
}

void Potion::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Potion>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Potion>" << endl;
}
