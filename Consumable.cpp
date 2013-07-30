#include "Consumable.h"
#include "Item.h"
#include "Creature.h"
#include <iostream>
#include <ostream>
#include <cstdlib>

using namespace std;

//Constructor
Consumable::Consumable() : Item()
{
	m_iHealth = 0;
	m_iNutrition = 0;
}

//Getters
int Consumable::getHealth() const
{
	return m_iHealth;
}

int Consumable::getNutrition() const
{
	return m_iNutrition;
}

vector<string> Consumable::getPropertyBenefits() const
{
	return m_vPropertyBenefits;
}

//Setters
void Consumable::setHealth(int iHealth)
{
	m_iHealth = iHealth;
}

void Consumable::setNutrition(int iNutrition)
{
	m_iNutrition = iNutrition;
}

void Consumable::setPropertyBenefits(vector<string> vPropertyBenefits)
{
	m_vPropertyBenefits = vPropertyBenefits;
}

//Other methods
void Consumable::used(Creature* usingCreature)
{
	//First, add any health benefits the potion grants
	usingCreature->addHealth(getHealth());

	//Then, add any properties that the potion grants
	for (auto itr = m_vPropertyBenefits.begin(); itr != m_vPropertyBenefits.end(); itr++)
	{
		//If using creature doesn't already have this property, give it
		//to them
		if (!(usingCreature->hasProperty(*itr)))
			usingCreature->addProperty(*itr);
	}
}

void Consumable::dumpObject()
{
	cout << "OBJECT TYPE: Consumable" << endl;
	dumpObjectData();
}

void Consumable::dumpObjectData()
{
	Item::dumpObjectData();
	cout << "\t - m_iHealth: " << getHealth() << endl;
	cout << "\t - m_iNutrition: " << getNutrition() <<endl;
}

void Consumable::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Consumable>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Consumable>"  << endl;
}

void Consumable::writeDataAsFragment(ostream & output, int iTabs)
{
	Item::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<health>" << getHealth() << "</health>" << endl;

	insertTabs(output, iTabs);
	output << "<nutrition>" << getNutrition() << "</nutrition>" << endl;
}

void Consumable::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "health")
		setHealth(atoi(sValue.c_str()));
	else if (sElementName == "nutrition")
		setNutrition(atoi(sValue.c_str()));
}
