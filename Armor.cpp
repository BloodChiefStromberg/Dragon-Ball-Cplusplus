#include "Weapon.h"
#include "Armor.h"
#include "Item.h"
#include <string>
#include <ostream>
#include <cstdlib>
#include <iostream>

using namespace std;

//Constructor
Armor::Armor(string sName, int iArmorValue) : Item()
{
	m_sSlot = "BODY";
	m_sType = "";
	m_iArmorValue = iArmorValue;
	setName(sName);
}

//Copy constructor
Armor::Armor(const Armor& someArmor) : Item(someArmor)
{
	m_sSlot = someArmor.getSlot();
	m_sType = someArmor.getType();
	m_iArmorValue = someArmor.getArmorValue();
}

//Getters
string Armor::getSlot() const
{
	return m_sSlot;
}

string Armor::getType() const
{
	return m_sType;
}

int Armor::getArmorValue() const
{
	return m_iArmorValue;
}

//Setters
void Armor::setSlot(string sSlot)
{
	m_sSlot = sSlot;
}

void Armor::setType(string sType)
{
	m_sType = sType;
}

void Armor::setArmorValue(int iArmorValue)
{
	m_iArmorValue = iArmorValue;
}

//Other mehtods
void Armor::dumpObject()
{
	cout << "OBJECT TYPE: Armor" << endl;
	dumpObjectData();
}

void Armor::dumpObjectData()
{
	cout << "\t - m_sSlot: " << getSlot() << endl;
	cout << "\t - m_sType: " << getType() << endl;
	cout << "\t - m_iArmorValue: " << getArmorValue() << endl;
}

void Armor::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Armor>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Armor>" << endl;
}

void Armor::writeDataAsFragment(ostream & output, int iTabs)
{
	Item::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<slot>" << getSlot() << "</slot>" << endl;
	insertTabs(output, iTabs);
	output << "<type>" << getType() << "</type>" << endl;
	insertTabs(output, iTabs);
	output << "<armorValue>" << getArmorValue() << "</armorValue>" << endl;
}

void Armor::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "slot")
		setSlot(sValue);
	else if (sElementName == "type")
		setType(sValue);
	else if (sElementName == "armorValue")
		setArmorValue(atoi(sValue.c_str()));
}
