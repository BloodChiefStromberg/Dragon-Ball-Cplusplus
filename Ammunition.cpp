//Ammunition.cpp: defines functions from Ammunition.h

#include "Weapon.h"
#include "Ammunition.h"
#include <ostream>
#include <iostream>
#include <cstdlib>

using namespace std;

//Constructor
Ammunition::Ammunition() : Item()
{
	m_iDamageBonus = 0;
	m_sType = "Default Type";
}

//Getters
int Ammunition::getDamageBonus() const
{
	return m_iDamageBonus;
}

string Ammunition::getType() const
{
	return m_sType;
}

//Setters
void Ammunition::setDamageBonus(int iDamageBonus)
{
	m_iDamageBonus = iDamageBonus;
}

void Ammunition::setType(string sType)
{
	m_sType = sType;
}

//Other methods
void Ammunition::dumpObject()
{
	cout << "OBJECT TYPE: Ammunition" << endl;
	dumpObjectData();
}

void Ammunition::dumpObjectData()
{
	Item::dumpObjectData();
	cout << "\t - m_iDamageBonus: " << getDamageBonus() << endl;
	cout << "\t - m_sType: " << getType() << endl;
}

void Ammunition::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Ammunition>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Ammunition>" << endl;
}

void Ammunition::writeDataAsFragment(ostream & output, int iTabs)
{
	Item::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<damageBonus>" << getDamageBonus() << "</damageBonus>" << endl;
	insertTabs(output, iTabs);
	output << "<type>" << getType() << "</type>" << endl;
}

void Ammunition::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "damageBonus")
		setDamageBonus(atoi(sValue.c_str()));
	else if (sElementName == "type")
		setType(sValue);
}
