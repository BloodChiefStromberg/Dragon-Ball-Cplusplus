//Item.cpp: this file implements functions declared in Item.h

#include "Weapon.h"
#include "Item.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

//Constructor
Item::Item() : Entity()
{
	m_iWeight = 0;
	m_iValue = 0;
	m_iRarity = 25;
	m_iEnchantment = 0;
	m_iQuantity = 0;
}

//Copy Constructor
Item::Item(const Item& anItem) : Entity(anItem)
{
	m_iWeight = anItem.getWeight();
	m_iValue = anItem.getValue();
	m_iRarity = anItem.getRarity();
	m_iEnchantment = anItem.getEnchantment();
	m_iQuantity = anItem.getQuantity();
}

//Destructor
Item::~Item()
{
/*	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addstr("I got deleted!\n");
	addch('\n');
	addstr("-------------");
	getch();
	getch();
	getch();
	getch();
	refresh();
*/
}


//Getters
int Item::getWeight() const
{
	return m_iWeight;
}

int Item::getValue() const
{
	return m_iValue;
}

int Item::getRarity() const
{
	return m_iRarity;
}

int Item::getEnchantment() const
{
	return m_iEnchantment;
}

int Item::getQuantity() const
{
	return m_iQuantity;
}

//Setters
void Item::setWeight(int iWeight)
{
	m_iWeight = iWeight;
}

void Item::setValue(int iValue)
{
	m_iValue = iValue;
}

void Item::setRarity(int iRarity)
{
	m_iRarity = iRarity;
}

void Item::setEnchantment(int iEnchantment)
{
	m_iEnchantment = iEnchantment;
}

void Item::setQuantity(int iQuantity)
{
	m_iQuantity = iQuantity;
}

//Other methods
void Item::changeLocation(DungeonLevel* dlLevel, Point* pNewLocation)
{
//      cout << "changeLocation(): called" << endl; //debug

        //When an entity changes location, 3 things need to happen.
        //1. Tell the old tile we're moving.
	vector<Item*> vUpdatedItems;
	for (size_t i = 0; i < dlLevel->getTileAt(getLocation())->getItems().size(); i++)
	{
		Item* pItem = (dlLevel->getTileAt(getLocation())->getItems())[i];
		if (pItem != NULL)
		{
			if (getID() != pItem->getID())
				vUpdatedItems.push_back(pItem);
		}
	}
	dlLevel->getTileAt(getLocation())->setItems(vUpdatedItems);

        //2. Delete the old location, and move
        delete getLocation();
        setLocation(pNewLocation);

        //3. Tell the new tile we're here
        dlLevel->getTileAt(pNewLocation)->add(this);
//      cout << "changeLocation(): completed" << endl;
}


void Item::pickUp()
{
	cout << "This is the pick up function. Dunno what it does yet.";
}

string Item::getDescription()
{
	return "This is the getDescription(). How rad is this?";
}

void Item::dumpObject()
{
	cout << "OBJECT TYPE: Item" << endl;
	dumpObjectData();
}

void Item::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "\t - m_iWeight: " << getWeight() << endl;
	cout << "\t - m_iValue: " << getValue() << endl;
	cout << "\t - m_iRarity: " << getRarity() << endl;
	cout << "\t - m_iEnchantment: " << getEnchantment() << endl;
	cout << "\t - m_iQuantity: " << getQuantity() << endl;
}

void Item::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Item>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Item>" << endl;
}

void Item::writeDataAsFragment(ostream & output, int iTabs)
{
	Entity::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<weight>" << getWeight() << "</weight>" << endl;
	insertTabs(output, iTabs);
	output << "<value>" << getValue() << "</value>" << endl;
	insertTabs(output, iTabs);
	output << "<rarity>" << getRarity() << "</rarity>" << endl;
	insertTabs(output, iTabs);
	output << "<enchantment>" << getEnchantment() << "</enchantment>" << endl;
	insertTabs(output, iTabs);
	output << "<quantity>" << getQuantity() << "</quantity>" << endl;
}

void Item::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if (sElementName == "weight")
		setWeight(atoi(sValue.c_str()));
	else if (sElementName == "value")
		setValue(atoi(sValue.c_str()));
	else if (sElementName == "rarity")
		setRarity(atoi(sValue.c_str()));
	else if (sElementName == "enchantment")
		setEnchantment(atoi(sValue.c_str()));
	else if (sElementName == "quantity")
		setQuantity(atoi(sValue.c_str()));

}




