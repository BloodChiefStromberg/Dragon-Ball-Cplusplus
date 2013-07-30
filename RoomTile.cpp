//RoomTile.cpp: implements the functions declared in RoomTile.h

#include <ncurses.h>
#include <iostream>
#include "RoomTile.h"
#include "Creature.h"
//See note 6

using namespace std;

//Constructor
RoomTile::RoomTile(bool bCollectable, bool bWalkable, char cDisplayChar)
{
	m_iIntensity = 0;
	m_bCollectable = bCollectable;
	m_bWalkable = bWalkable;
	m_cDisplayChar = cDisplayChar;
	m_pCreature = NULL;
	m_vItems;
}

//Destructor
RoomTile::~RoomTile()
{
	for (auto itr = m_vItems.begin(); itr != m_vItems.end(); itr++)
	{
		delete (*itr);
	}
}

//Getters
int RoomTile::getIntensity() const
{
	return m_iIntensity;
}

bool RoomTile::getCollectable() const
{
	return m_bCollectable;
}

bool RoomTile::getWalkable() const
{
	return m_bWalkable;
}

char RoomTile::getDisplayChar() const
{
	return m_cDisplayChar;
}

vector<Item*> RoomTile::getItems() const
{
	return m_vItems;
}

Creature* RoomTile::getCreature() const
{
	return m_pCreature;
}

//Setters
void RoomTile::setIntensity(int iIntensity)
{
/*	addstr("set intensity was called");
	addch('\n');
	addstr("set intensity was called");
	addch('\n');
	addstr("set intensity was called");
	addch('\n');
	addstr("set intensity was called");
	addch('\n');
	addstr("set intensity was called");
	addch('\n');
	addstr("set intensity was called");
	addch('\n');
	getch();
	getch();
	getch();
	getch();
	getch();
	getch();
	getch();
	getch();
	getch();
	getch();
*/
	m_iIntensity = iIntensity;
}

void RoomTile::setItems(vector<Item*> vItems)
{
	m_vItems = vItems;
}

void RoomTile::setCollectable(bool bCollectable)
{
	m_bCollectable = bCollectable;
}

void RoomTile::setWalkable(bool bWalkable)
{
	m_bWalkable = bWalkable;
}

void RoomTile::setDisplayChar(char cDisplayChar)
{
	m_cDisplayChar = cDisplayChar;
}

void RoomTile::setCreature(Creature* aCreature)
{
//	cout << "setCreature(): " << aCreature << endl; //debug
	m_pCreature = aCreature;
}

//Other methods
/*
void RoomTile::remove(Entity* aContainedEntity)
{
//	cout << "remove(): called" << endl; //debug

	//if it's a creature, set m_Creature to NULL
	if (static_cast<Creature*>(aContainedEntity) != NULL)
		m_Creature = NULL;
	//Otherwise, it's an item. Find the item and get rid of it!
	else
	{
		for (auto itr = m_vItems.begin(); itr != m_vItems.end(); itr++)
		{
			if (aContainedEntity->getID() == (*itr)->getID())
				m_vItems.erase(itr);
		}
	}

//	cout << "remove(): completed" << endl;
}
*/


void RoomTile::add(Item* anItem)
{
	m_vItems.push_back(anItem);
}

/*
void RoomTile::addIntensity(int iIntensity)
{
	if (iIntensity + getIntensity() >= 2)
		setIntensity(2);
	else
		setIntensity(iIntensity + getIntensity());
}
*/
