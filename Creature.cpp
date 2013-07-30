//Creature.cpp: defines functions for the Creature type. Header file is Creature.h

#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Creature.h"
#include "Light.h"
#include "Point.h"
#include "DungeonLevel.h"
#include "RoomTile.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ncurses.h>

using namespace std;

//Constructor
Creature::Creature() : Entity()
{
	m_iHP = 40;
	m_iLevel = 1;
	m_iMaxHP = 40;
	m_iExperience = 0;
	m_wEquipedWeapon = new Weapon("Default Weapon", 10);
	m_lEquipedOffhand = NULL;
	m_aEquipedArmor = new Armor("Default Armor", 2);
	m_vInventory.push_back(m_wEquipedWeapon);
	m_vInventory.push_back(m_aEquipedArmor);
	m_iPerceptionRange = 15;
	m_bEnemy = true;
	//Seed the random number generator used for all creatures
	static mt19937 iRandom;
	m_pRandom = &iRandom;
	m_pRandom->seed(time(NULL));
}

//Destructor
Creature::~Creature()
{
//	cout << "Creature destructor called at: " << this << endl; //debug
//	refresh();
	for (size_t i = 0; i < m_vInventory.size(); i++)
	{
		Item* pItem = m_vInventory[i];

		//Delete the Item* from memory
		delete pItem;

		//and set the pointers to NULL (overkill, but it's sick)
		m_vInventory[i] = NULL;
	}
}

//Copy constructor
Creature::Creature(const Creature& aCreature) : Entity(aCreature)
{
//	addstr("CREATURE COPY CONSTRUCTOR CALLED!\n");
//	refresh();
//	getch();
	m_iHP = aCreature.getHP();
	m_iLevel = aCreature.getLevel();
	m_iMaxHP = aCreature.getMaxHP();
	m_iExperience = aCreature.getExperience();
	m_wEquipedWeapon = new Weapon(*(aCreature.getEquipedWeapon()));
	m_lEquipedOffhand = NULL;
	m_aEquipedArmor = new Armor(*(aCreature.getEquipedArmor()));
	m_vInventory.push_back(m_wEquipedWeapon);
	m_vInventory.push_back(m_aEquipedArmor);
	m_iPerceptionRange = aCreature.getPerceptionRange();
	m_bEnemy = aCreature.getEnemy();
	m_pRandom = aCreature.getRandom();
}

//Getters
mt19937* Creature::getRandom() const
{
	return m_pRandom;
}

int Creature::getPerceptionRange() const
{
	return m_iPerceptionRange;
}

int Creature::getExperience() const
{
	return m_iExperience;
}

int Creature::getHP() const
{
	return m_iHP;
}

int Creature::getLevel() const
{
	return m_iLevel;
}

int Creature::getMaxHP() const
{
	return m_iMaxHP;
}

vector<Item*> Creature::getInventory() const
{
	return m_vInventory;
}

Weapon* Creature::getEquipedWeapon() const
{
	return m_wEquipedWeapon;
}

Armor* Creature::getEquipedArmor() const
{
	return m_aEquipedArmor;
}

Light* Creature::getEquipedOffhand() const
{
	return m_lEquipedOffhand;
}

bool Creature::getEnemy() const
{
	return m_bEnemy;
}

//Setters
//Make this take a Wieldable* in the futre. Same w setEquipedWeapon
void Creature::setEquipedOffhand(Light* pLight)
{
	m_lEquipedOffhand = pLight;
}

void Creature::setPerceptionRange(int iPerceptionRange)
{
	m_iPerceptionRange = iPerceptionRange;
}

void Creature::setExperience(int iExperience)
{
	m_iExperience = iExperience;
}

void Creature::setHP(int iHP)
{
	m_iHP = iHP;
}

void Creature::setLevel(int iLevel)
{
	m_iLevel = iLevel;
}

void Creature::setMaxHP(int iMaxHP)
{
	m_iMaxHP = iMaxHP;
}

void Creature::setInventory(vector<Item*> vInventory)
{
	m_vInventory = vInventory;
}

void Creature::setEquipedWeapon(Weapon* pWeapon)
{
	m_wEquipedWeapon = pWeapon;
}

void Creature::setEquipedArmor(Armor* pArmor)
{
	m_aEquipedArmor = pArmor;
}

void Creature::setEnemy(bool bEnemy)
{
	m_bEnemy = bEnemy;
}

//Other methods
void Creature::addHealth(int iHealth)
{
	if (iHealth + getHP() > getMaxHP())
		iHealth = getMaxHP();
	else
		iHealth += getHP();

	setHP(iHealth);
}


void Creature::regenerate()
{
	int iRegen = getLevel() / 2;
	if (iRegen < 1)
		iRegen = 1;
	addHealth(iRegen);
}

int Creature::runInventoryMenu(DungeonLevel* dlLevel)
{
	int iIndex = 0;
	Item* pItem = NULL;
	bool bSelected = false;
	clear();

	while (!bSelected)
	{
		//Tell the user what to do
		addstr("Use 8 and 2 to select the item you wish to use. Press 5 to go back.");
		addch('\n');

		//Show the inventory, with the first item selected
		addstr("Select the item you want to use");
		addch('\n');
		refresh(); //debug
		for (size_t i = 0; i < m_vInventory.size(); i++)
		{
			if(m_vInventory[i] != NULL)
			{
				if (i == iIndex)
				{
					addch('\t');
				}
				if (m_vInventory[i]->getID() == getEquipedWeapon()->getID() || m_vInventory[i]->getID() == getEquipedArmor()->getID() ||
					(getEquipedOffhand() != NULL && m_vInventory[i]->getID() == getEquipedOffhand()->getID()))
					addstr("(E)");
				addstr(m_vInventory[i]->getName().c_str());
				addch('\n');
			}
		}
		refresh();

		char cDirection = getch();

		if (cDirection == '2' && iIndex < (getInventory().size() - 1))
			iIndex++;
		else if (cDirection == '8' && iIndex > 0)
			iIndex--;
		else if (cDirection == '\n')
		{
			pItem = getItem(getInventory()[iIndex]);
			bSelected = true;
		}
		else if (cDirection == '5')
			//The return value 2 here will be interpreted by the
			//main function as "don't increase the turn counter,
			//just redraw the screen"
			return 2;

		clear();
	}

	if (pItem != NULL)
	{
		//They've selected an Item! Try to handle it!
		Consumable* pImAConsumable = dynamic_cast<Consumable*>(pItem);
		Weapon* pImAWeapon = dynamic_cast<Weapon*>(pItem);
		Armor* pImArmor = dynamic_cast<Armor*>(pItem);
		Light* pImALight = dynamic_cast<Light*>(pItem);
		if (pImAConsumable != NULL)
		{
			use(pImAConsumable);
		}
		else if (pImAWeapon != NULL)
		{
			setEquipedWeapon(pImAWeapon);
		}
		else if (pImArmor != NULL)
		{
			setEquipedArmor(pImArmor);
		}
		else if (pImALight != NULL)
		{
			//No matter what, turn the light we have on now off
			if (m_lEquipedOffhand != NULL)
				m_lEquipedOffhand->emitLight(false, dlLevel);

			//Then unequip if we need too
			if (m_lEquipedOffhand == pImALight)
				setEquipedOffhand(NULL);
			else
			{
				setEquipedOffhand(pImALight);
				m_lEquipedOffhand->emitLight(true, dlLevel);
			}
		}
	}
	return 1;
}

Item* Creature::getItem(Item* anItem)
{
	for (auto itr = m_vInventory.begin(); itr != m_vInventory.end(); itr++)
	{
		if ((*itr)->getID() == anItem->getID())
			return *itr;
	}
	return NULL;
}

void Creature::recieveExperience(int iExperience)
{
	setExperience(getExperience() + iExperience);
	if (levelUp())
	{
		addstr("YOU LEVELED UP! Press any button to continue rockin' it.");
		addch('\n');
		getch();
	}
}

bool Creature::levelUp()
{
	//Formula for level up:
	//	= (Current Level + (1/2 Current Level))^2
	//	Level 1: (1 + 0)^2 = 1		| Defeat 1 level 1 monster
	//	Level 2: (2 + 1)^2 = 9 		| Defeat 5 level 2 monsters
	//	Level 3: (3 + 1)^2 = 16		| Defeat 6 level 3 monsters
	//	Level 4: (4 + 2)^2 = 36 	| Defeat 9 level 4 monsters
	//	Level 10: (10 + 5)^2 =225 	| Defeat 23 level 10 monsters
	int iNeedToLevelUp = (getLevel() + (getLevel() / 2))*(getLevel() + (getLevel() / 2));
	if (m_iExperience >= iNeedToLevelUp)
	{
		setLevel(getLevel() + 1);
		setMaxHP(getMaxHP() + 10);
		setHP(getMaxHP());
		return true;
	}
	else
		return false;
}

void Creature::use(Consumable* aConsumable)
{
	addstr("use(): called");
	addch('\n');
	refresh();

	aConsumable->used(this);

	//Delete the consumable from your inventory
	for (auto itr = m_vInventory.begin(); itr != m_vInventory.end(); itr++)
	{
		if (aConsumable->getID() == (*itr)->getID())
		{
			delete (*itr);
			m_vInventory.erase(itr);
			return;
		}
	}
}

/*void Creature::remove(Item* pItem)
{
        for (auto itr = m_vInventory.begin(); itr != m_vInventory.end(); itr++)
        {
                if (pItem->getID() == (*itr)->getID())
                {
                        delete (*itr);
                        m_vInventory.erase(itr);
                }
        }
}*/

void Creature::changeLocation(DungeonLevel* dlLevel, Point* pNewLocation)
{
	//addstr("changeLocation(): called"); //debug
	//addch('\n'); //debug
	//refresh(); //debug
        //When an entity changes location, 3 things need to happen.
        //1. Tell the old tile we're moving
        dlLevel->getTileAt(getLocation())->setCreature(NULL);

        //2. Delete the old location, and move.
        delete getLocation();
        setLocation(pNewLocation);

        //3. Tell the new tile we're here.
	dlLevel->getTileAt(pNewLocation)->setCreature(this);

	//If they have a light, turn it off
	if (m_lEquipedOffhand != NULL)
	{
//		addstr("about to turn light off");
//		addch('\n');
//		refresh();
		m_lEquipedOffhand->emitLight(false, dlLevel);
	}

	//And do the same things for the players inventory to move them
	//see note 10
	for (size_t i = 0; i < m_vInventory.size(); i++)
	{
		Item* pItem = m_vInventory[i];
		if (pItem != NULL)
		{
			delete pItem->getLocation();

			Point* pItemLocation = new Point(*(getLocation()));

			pItem->setLocation(pItemLocation);
		}
	}

	//Now turn the light back on
	if(m_lEquipedOffhand != NULL)
	{
//		addstr("turning light on");
//		addch('\n');
//		refresh();

		m_lEquipedOffhand->emitLight(true, dlLevel);
	}
}


void Creature::pickUp(DungeonLevel* dlLevel)
{
	RoomTile* rtMyRoomTile = dlLevel->getTileAt(getLocation());
	vector<Item*> vEmptyVector;
	vector<Item*> vLoot = rtMyRoomTile->getItems();

	//Delete the item from the room tiles list.
	//See note 5
	for (size_t i = 0; i < vLoot.size(); i++)
	{
		Light* pImALight = dynamic_cast<Light*>(vLoot[i]);
		if(pImALight != NULL)
			pImALight->emitLight(false, dlLevel);
		addItem(vLoot[i]);
	}

	rtMyRoomTile->setItems(vEmptyVector);
}

void Creature::useStairs(DungeonLevel* dlLevel, char cDirection)
{
//	addstr("useStairs: called");
//	refresh();
	//Player has descended the steps. Put him on the stairs.
	//First, tell old tile he (or she) is not there anymore
	for (int i = 0; i < dlLevel->getRoomTiles().size(); i++)
	{
		for (int j = 0; j < dlLevel->getRoomTiles()[0].size(); j++)
		{
			if (cDirection == 'd')
			{
				if (dlLevel->getRoomTiles()[i][j]->getDisplayChar() == '>')
				{
					changeLocation(dlLevel, new Point(j, i));
				}
			}
			else if (cDirection == 'u')
			{
				if (dlLevel->getRoomTiles()[i][j]->getDisplayChar() == '<')
				{
					changeLocation(dlLevel, new Point(j, i));
				}
			}
		}
	}
//	addstr("usedStairs: COMPLETED");
//	addch('\n');
//	refresh();
}

void Creature::dropLoot(DungeonLevel* dlLevel)
{
	RoomTile* rtMyTile = dlLevel->getTileAt(getLocation());

	for (size_t i = 0; i < m_vInventory.size(); i++)
	{
//		addstr("Looking at ");
		Item* pItem = m_vInventory[i];
//		if (pItem != NULL)
//			addstr(pItem->getName().c_str());
//		else
//			addstr("NULL");
//		addch('\n');

		if (((*m_pRandom)() % 100) <= pItem->getRarity())
		{
//			addstr("Dropping: "); //debug
//			addstr(m_vInventory[i]->getName().c_str()); //debug
//			addch('\n'); //debug
//			getch(); //debug
//			refresh();

			rtMyTile->add(pItem);

			//Set the item to NULL in m_vInventory so when the
			//creature destructs, the data won't be lost
			m_vInventory[i] = NULL;
		}

	}
	//See note 7
}


void Creature::recieveDamage(Creature* pAttacker, int iDamage, DungeonLevel* dlLevel)
{
	//iDamageTaken 	= Damage after modifiers (none yet implemented)
	//		- Armor Value
	//		- Random value up to your level

//	addstr("getting attackers weapon\n");
//	refresh();
//	getch();

//	addstr("recieveDamage(): called");
//	addch('\n');
//	refresh();

	Weapon* pWeapon = pAttacker->getEquipedWeapon();

//	addstr("got attackers weapon\n");
//	refresh();

	int iArmorDefense = getEquipedArmor()->getArmorValue();

//	addstr("got armor!\n");
//	refresh();

	int iRandom = (*m_pRandom)() % (getLevel() + 1);

//	addstr("got random and level!\n");
//	refresh();

	int iDamageTaken = iDamage - iArmorDefense - iRandom;
	addstr(getName().c_str());
	addstr(" has been attacked by ");
	addstr(pAttacker->getName().c_str());
	addch('!');
	addch('\n');
	addstr("-HP before damage: ");
	addstr(to_string(getHP()).c_str());
	addch('/');
	addstr(to_string(getMaxHP()).c_str());
	addch('\n');
	addstr("-They take ");
//	refresh(); //debug
//	getch();
	if (iDamageTaken < 0)
		iDamageTaken = 0;
	if (iDamageTaken > getHP())
		setHP(0);
	else
		setHP(getHP() - iDamageTaken);
	addstr(to_string(iDamageTaken).c_str());
	addstr(" damage!");
	addch('\n');
	addstr("-Current HP: ");
	addstr(to_string(getHP()).c_str());
	addch('/');
	addstr(to_string(getMaxHP()).c_str());
	addch('\n');
	addstr("Press any key to continue questing.");
	addch('\n');
	refresh();
	getch();
}

//See note 3
void Creature::attack(Creature* aCreature, DungeonLevel* dlLevel)
{
	addstr(getName().c_str());
	addstr(" has just started an attack against ");
	addstr(aCreature->getName().c_str());
	addch('\n');
//	addstr("Now we move slowly to because we have to debug. Press any key to continue. \n");
//	addch('\n');
//	refresh();
//	getch();
	//iDamage =	  Weapon damage
	//		+ Random value up to your level
	//Add strength later if I have time to add stats
//	addstr("accessing equipedWeapon and damage");
//	addch('\n');
//	refresh();
//	getch();

	int iWeaponDamage = getEquipedWeapon()->getDamage();

//	addstr("accessing random and getLevel() \n");
//	addch('\n');
//	refresh();
//	getch();

	int iDamageMod = (*m_pRandom)() % (getLevel() + 1);
	int iDamage = iWeaponDamage + iDamageMod;

//	addstr("calculated damage \n");
//	addch('\n');
//	refresh();
	//recieveDamage takes the weapon to look for properties like silver,
	//damage for damage, and dlLevel to know where to drop loot
	aCreature->recieveDamage(this, iDamage, dlLevel);
}

//See note 2
bool Creature::move(char cDirection, DungeonLevel* dlLevel)
{
	//Remember, iDirection is
		//8 : up
		//4 : left
		//2 : down
		//6 : right

	int iYChange = 0;
	int iXChange = 0;

	int iOldY = getLocation()->getY();
	int iOldX = getLocation()->getX();
	Point* pOldLocation = getLocation();

	//We check the direction, and say this is how much x or y we should
	//change. should save code repetition.
	if (cDirection == '8') //up
	{
		iYChange = -1;
	}
	else if (cDirection == '2') //down
	{
		iYChange = 1;
	}
	else if (cDirection == '4') //left
	{
		iXChange = -1;
	}
	else if (cDirection == '6') //right
	{
		iXChange = 1;
	}

//	cout << "iYChange: " << iYChange << endl; //debug
//	cout << "iXChange: " << iXChange << endl; //debug

	//now get the room tile where were thinking about moving
	RoomTile* newRoomTile = (dlLevel->getRoomTiles())[iOldY + iYChange][iOldX + iXChange];

//	bool bSelected = false;

	//Now make any modifications to this move. These are behavioral changes, such as if the creature is afraid of light
	if (hasProperty("light sensitive") && newRoomTile->getIntensity() > 0)
	{
		iXChange = iXChange * (-1);
		iYChange = iYChange * (-1);
		newRoomTile = (dlLevel->getRoomTiles())[iOldY + iYChange][iOldX + iXChange];
	}


	//and check if we want to/can move here
	if (newRoomTile->getWalkable())
	{
		if (newRoomTile->getCreature() == NULL)
		{
			//If it is walkable, and there's no creature here, move it.
			//changeLocation() will handle all of the necessary memory allocations and
			//deallocation for us
			changeLocation(dlLevel, new Point(iOldX + iXChange, iOldY + iYChange));

			//And say that we've successfully moved!
		}
		else
		{
			//There is a creature here. Initiate an attack.
			if (!m_bEnemy || !(newRoomTile->getCreature()->getEnemy()))
				attack(newRoomTile->getCreature(), dlLevel);
		}
		return true;
	}

	return false;
}

void Creature::addItem(Item* item)
{
	m_vInventory.push_back(item);
}

void Creature::dumpObject()
{
	cout << "OBJECT TYPE: Creature" << endl;
	dumpObjectData();
}

void Creature::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "\t - m_iLevel: " << getLevel() << endl;
	cout << "\t - m_iMaxHP: " << getMaxHP() << endl;
	cout << "\t - m_iHP: " << getHP() << endl;
	cout << "\t - m_vInventory: ";
	for (vector<Item*>::iterator itr = m_vInventory.begin(); itr != m_vInventory.end(); itr++)
	{
		cout << (*itr)->getName() << " " << endl;
	}
	cout << endl;

}

void Creature::writeFragment(ostream & output, int iTabs)
{
	insertTabs(output, iTabs);
	output << "<Creature>" << endl;

	writeDataAsFragment(output, iTabs + 1);

	insertTabs(output, iTabs);
	output << "</Creature>" << endl;
}

void Creature::writeDataAsFragment(ostream & output, int iTabs)
{
	Entity::writeDataAsFragment(output, iTabs);
	insertTabs(output, iTabs);
	output << "<level>" << getLevel() << "</level>" << endl;
	insertTabs(output, iTabs);
	output << "<maxHP>" << getMaxHP() << "</maxHP>" << endl;
	insertTabs(output, iTabs);
	output << "<HP>" << getHP() << "</HP>" << endl;
//	insertTabs(output, iTabs);
//	output << "<inventory>" << endl;
//	for (vector<Item*>::iterator itr = m_vInventory.begin(); itr != m_vInventory.end(); itr++)
//	{
//		insertTabs(output, iTabs);
//		cout << "<inventory>" << *itr << "</property>" << endl;
//	}
//	insertTabs(output, iTabs);
//	output << "</Inventory>" << endl;
}

void Creature::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if (sElementName == "level")
		setLevel(atoi(sValue.c_str()));
	else if (sElementName == "HP")
		setHP(atoi(sValue.c_str()));
	else if (sElementName == "maxHP")
	{
		setHP(atoi(sValue.c_str()));
		setMaxHP(atoi(sValue.c_str()));
	}
	else if (sElementName == "inventory")
		//worry about this later
		cout << "Were we supposed to handle inventory's already?";
}

