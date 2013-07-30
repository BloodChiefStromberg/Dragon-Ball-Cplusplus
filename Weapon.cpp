#include "Weapon.h"
#include "Item.h"
#include <string>
#include <ostream>
#include <cstdlib>
#include <iostream>

using namespace std;

//Constructor
Weapon::Weapon(string sName, int iDamage) : Item()
{
	setName(sName);
	m_iDamage = iDamage;
	m_sType = "default type";
	m_iAccuracy = 0;
	m_lRange = 0;
	m_sAmmoType = "defaulty ammo type";
}

Weapon::Weapon(const Weapon& aWeapon) : Item(aWeapon)
{
	m_iDamage = aWeapon.getDamage();
	m_sType = aWeapon.getType();
	m_iAccuracy = aWeapon.getAccuracy();
	m_lRange = aWeapon.getRange();
	m_sAmmoType = aWeapon.getAmmoType();
}

//Getters
int Weapon::getDamage() const
{
	return m_iDamage;
}

string Weapon::getType() const
{
	return m_sType;
}

int Weapon::getAccuracy() const
{
	return m_iAccuracy;
}

long Weapon::getRange() const
{
	return m_lRange;
}

string Weapon::getAmmoType() const
{
	return m_sAmmoType;
}

//Setters
void Weapon::setDamage(int iDamage)
{
	m_iDamage = iDamage;
}

void Weapon::setType(string sType)
{
	m_sType = sType;
}

void Weapon::setAccuracy(int iAccuracy)
{
	m_iAccuracy = iAccuracy;
}

void Weapon::setRange(long lRange)
{
	m_lRange = lRange;
}

void Weapon::setAmmoType(string sAmmoType)
{
	m_sAmmoType = sAmmoType;
}

//Other methods

void Weapon::dumpObject()
{
	cout << "OBJECT TYPE: Weapon" << endl;
	dumpObjectData();
}

void Weapon::dumpObjectData()
{
	Item::dumpObjectData();
	cout << "\t - m_iDamage: " << getDamage() << endl;
	cout << "\t - m_sType: " << getType() << endl;
	cout << "\t - m_iAccuracy: " << getAccuracy() << endl;
	cout << "\t - m_lRange: " << getRange() << endl;
	cout << "\t - m_sAmmoType: " << getAmmoType() << endl;
}

void Weapon::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Weapon>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Weapon>" << endl;
}

void Weapon::writeDataAsFragment(ostream & output, int iTabs)
{
	Item::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<damage>" << getDamage() << "</damage>" << endl;
	insertTabs(output, iTabs);
	output << "<type>" << getType() << "</type>" << endl;
	insertTabs(output, iTabs);
	output << "<accuracy>" << getAccuracy() << "</accuracy>" <<  endl;
	insertTabs(output, iTabs);
	output << "<range>" << getRange() << "</range>" <<  endl;
	insertTabs(output, iTabs);
	output << "<ammoType>" << getAmmoType() << "</ammoType>" <<  endl;
}

void Weapon::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "damage")
		setDamage(atoi(sValue.c_str()));
	else if (sElementName == "type")
		setType(sValue);
	else if (sElementName == "accuracy")
		setAccuracy(atoi(sValue.c_str()));
	else if (sElementName == "range")
		setRange(atoi(sValue.c_str()));
	else if (sElementName == "ammoType")
		setAmmoType(sValue);
}
