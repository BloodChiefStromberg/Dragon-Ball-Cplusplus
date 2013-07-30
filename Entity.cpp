//Entity.cpp: implements functions declared in Entity.h

#include "Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <ncurses.h>

using namespace std;

extern int g_iID;

//Constructor
Entity::Entity()
{
	g_iID++;
	m_iID = g_iID;
//	addstr("Entity constructed! Heres the ID: ");
//	addstr(to_string(m_iID).c_str());
//	addch('\n');

	m_sName = "No-Name Entity!";
	m_vProperties; //do something later w this
	m_cDisplayChar = 'E';
	m_pLocation = new Point(0, 0);
}

//Destructor
Entity::~Entity()
{
	//Deallocate memory
	delete m_pLocation;
	m_pLocation = NULL;
}

//Copy constructor. what a horrible thing
Entity::Entity(const Entity& anEntity)
{
	m_iID = g_iID++;
	m_sName = anEntity.getName();
	m_vProperties = anEntity.getProperties();
	m_cDisplayChar = anEntity.getDisplayChar();
	m_pLocation = new Point(*(anEntity.getLocation()));
}


//Getters
string Entity::getName() const
{
	return m_sName;
}

vector<string> Entity::getProperties() const
{
	return m_vProperties;
}

char Entity::getDisplayChar() const
{
//	cerr << "Called getDisplayChar()" << endl; //debug
	return m_cDisplayChar;
}

Point* Entity::getLocation() const
{
	return m_pLocation;
}

int Entity::getID() const
{
	return m_iID;
}

//Setters
void Entity::setName(string sName)
{
	m_sName = sName;
}

void Entity::setProperties(vector<string> vProperties)
{
	m_vProperties = vProperties;
}

void Entity::setDisplayChar(char cDisplayChar)
{
	m_cDisplayChar = cDisplayChar;
}

void Entity::setLocation(Point* pLocation)
{
	m_pLocation = pLocation;
}

//Other methods
void Entity::addProperty(string sProperty)
{
	m_vProperties.push_back(sProperty);
}

void Entity::changeLocation(DungeonLevel* dlLevel, Point* pNewLocation)
{
//	cout << "Entities change location was called. this is bad." << endl;
}

/*
void Entity::changeLocation(DungeonLevel* dlLevel, Point* pNewLocation)
{
//	cout << "changeLocation(): called" << endl; //debug
	Creature* pImACreature = dynamic_cast<Creature*>(this);
	Item* pImAnItem = dynamic_cast<Item*>(this);

        //When an entity changes location, 3 things need to happen.
        //1. Tell the old tile we're moving.
	//See note 6
        dlLevel->getTileAt(getLocation())->setCreature(NULL);

        //2. Delete the old location, and move
        delete getLocation();
	setLocation(pNewLocation);

        //3. Tell the new tile we're here
	if (pImACreature != NULL)
        	dlLevel->getTileAt(pNewLocation)->setCreature(pImACreature);
	else
		dlLevel->getTileAt(pNewLocation)->add(pImAnItem);
//	cout << "changeLocation(): completed" << endl;
}
*/

bool Entity::hasProperty(string sProperty)
{
	for(vector<string>::iterator itr = m_vProperties.begin(); itr != m_vProperties.end(); itr++) //search the vector
	{
		string sCurrentProperty = *itr;
		if(sCurrentProperty == sProperty) //for sProperty
		{
			return true; //if you find it, return true
		}
	}

	return false; //if you don't, return false
}

string Entity::getDescription()
{
	return "This is supposed to print a description eventually!";
}

void Entity::dumpObject()
{
	cout << "OBJECT TYPE: Entity" << endl;
	dumpObjectData();
}

void Entity::dumpObjectData()
{
	cout << "\t - m_sName: " << getName() << endl;
	cout << "\t - m_cDisplayChar: " << getDisplayChar() << endl;
	cout << "\t - m_vProperties: ";
	for (vector<string>::iterator itr = m_vProperties.begin(); itr != m_vProperties.end(); itr++)
	{
		cout << *itr << " " << endl;
	}
	cout << endl;
}

void Entity::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Entity>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Entity>" << endl;
}

void Entity::writeDataAsFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<name>" << getName() << "</name>" << endl;
	if (m_vProperties.size() != 0)
	{
		insertTabs(output, iTabs);
		output << "<properties>" << endl;
		for (vector<string>::iterator itr = m_vProperties.begin(); itr != m_vProperties.end(); itr++)
		{
			insertTabs(output, iTabs);
			cout << "<property>" << *itr << "</property>" << endl;
		}

		insertTabs(output, iTabs);
		output << "</properties>" << endl;
	}
	insertTabs(output, iTabs);
	output << "<displayChar>" << getDisplayChar() << "</displayChar>" << endl;
	//See notes.txt, note 1
	//output << "<location>(" << getLocation().getX() << ", " << getLocation().getY() << ")</location>" << endl;
}

void Entity::setElementData(string sElementName, string sValue)
{
	if (sElementName == "name")
		setName(sValue);
	else if (sElementName == "displayChar")
		setDisplayChar(sValue.at(0));
	else if (sElementName == "property")
		addProperty(sValue);
}

void Entity::insertTabs(ostream & output, int iTabs)
{
	for (int i = 0; i < iTabs; i++)
	{
		output << "\t";
	}
}
