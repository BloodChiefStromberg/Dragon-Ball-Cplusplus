#ifndef _Weapon
#define _Weapon

#include "Item.h"
#include <string>
#include <ostream>

class Item;

class Weapon : public Item
{
public:
	//Constructor
	Weapon(std::string sName, int iDamage);

	//Copy constructor
	Weapon(const Weapon& aWeapon);

	//Getters
	virtual int getDamage() const;
	virtual std::string getType() const;
	virtual int getAccuracy() const;
	virtual long getRange() const;
	virtual std::string getAmmoType() const;

	//Setters
	virtual void setDamage(int iDamage);
	virtual void setType(std::string sType);
	virtual void setAccuracy(int iAccuracy);
	virtual void setRange(long lRange);
	virtual void setAmmoType(std::string sAmmoType);

	//Other methods
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	int m_iDamage;
	std::string m_sType;
	int m_iAccuracy;
	long m_lRange;
	std::string m_sAmmoType;
};

#endif
