//Item.h: header file for Item.cpp. Things like ammo, weapons, and other stuff
//will extend this class

#ifndef _Item
#define _Item

#include "Entity.h"
#include <string>
#include <ostream>

class Item : public Entity
{
public:
	//Constructor
	Item();

	//Copy Constructor
	Item(const Item& anItem);

	//Destructor
	~Item();

	//Getters
	virtual int getWeight() const;
	virtual int getValue() const;
	virtual int getRarity() const;
	virtual int getEnchantment() const;
	virtual int getQuantity() const;

	//Setters
	virtual void setWeight(int iWeight);
	virtual void setValue(int iValue);
	virtual void setRarity(int iRarity);
	virtual void setEnchantment(int iEnchantment);
	virtual void setQuantity(int iQuantity);

	//Other methods
	virtual void changeLocation(DungeonLevel* dlLevel, Point* pNewLocation);
	virtual void pickUp();
	virtual std::string getDescription();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	int m_iWeight;
	int m_iValue;
	int m_iRarity;
	int m_iEnchantment;
	int m_iQuantity;
};

#endif
