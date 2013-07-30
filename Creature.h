#ifndef _Creature_
#define _Creature_

#include "Entity.h"
#include "Item.h"
#include "Consumable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Light.h"
#include "DungeonLevel.h"
#include <string>
#include <vector>
#include <ostream>
#include <random>

class Creature : public Entity
{
public:

	//Constructor
	Creature();

	//Destructor
	~Creature();

	//Copy constructor
	Creature(const Creature& aCreature);

	//Getters
	virtual std::mt19937* getRandom() const;
	virtual bool getEnemy() const;
	virtual Light* getEquipedOffhand() const;
	virtual int getExperience() const;
	virtual int getLevel() const;
	virtual int getHP() const;
	virtual int getMaxHP() const;
	virtual int getPerceptionRange() const;
	virtual std::vector<Item*> getInventory() const;
	virtual Weapon* getEquipedWeapon() const;
	virtual Armor* getEquipedArmor() const;

	//Setters
	virtual void setEnemy(bool bEnemy);
	virtual void setEquipedOffhand(Light* pLight);
	virtual void setPerceptionRange(int iPerceptionRange);
	virtual void setExperience(int iExperience);
	virtual void setLevel(int iLevel);
	virtual void setHP(int iHP);
	virtual void setMaxHP(int iMaxHP);
	virtual void setInventory(std::vector<Item*> vInventory);
	virtual void setEquipedWeapon(Weapon* pWeapon);
	virtual void setEquipedArmor(Armor* pArmor);

	//Other methods
	virtual void addHealth(int iHealth);
	virtual void regenerate();
	virtual int runInventoryMenu(DungeonLevel* dlLevel);
	virtual bool levelUp();
	virtual Item* getItem(Item* anItem);
	virtual void recieveExperience(int iExperience);
	virtual void use(Consumable* aConsumamble);
//	virtual void remove(Item* pItem);
	virtual void pickUp(DungeonLevel* dlLevel);
	virtual void changeLocation(DungeonLevel* dlLevel, Point* pNewLocation);
	virtual void dropLoot(DungeonLevel* dlLevel);
	virtual void recieveDamage(Creature* pAttacker, int iDamage, DungeonLevel* dlLevel);
	virtual void attack(Creature* aCreature, DungeonLevel* dlLevel);
	virtual void useStairs(DungeonLevel* dlLevel, char cDirection);
	//move() returns true if the move is succesful
	virtual bool move(char cDirection, DungeonLevel* dlLevel);
	virtual void addItem(Item* item);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	bool m_bEnemy;
	int m_iLevel;
	int m_iMaxHP;
	int m_iHP;
	int m_iExperience;
	int m_iPerceptionRange;
	std::vector<Item*> m_vInventory;

	Weapon* m_wEquipedWeapon;
	Armor* m_aEquipedArmor;
	Light* m_lEquipedOffhand;

	std::mt19937* m_pRandom;
};

#endif
