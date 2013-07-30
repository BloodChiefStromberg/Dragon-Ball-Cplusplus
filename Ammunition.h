//Ammunition.h: header file for Ammunition.cpp. Declares the functions defined
//in Ammunition.cpp
#ifndef _Ammunition
#define _Ammunition

#include "Item.h"
#include <ostream>
#include <string>

class Ammunition : public Item
{
public:
	//Constructor
	Ammunition();

	//Getters
	virtual int getDamageBonus() const;
	virtual std::string getType() const;

	//Setters
	virtual void setDamageBonus(int iDamageBonus);
	virtual void setType(std::string sType);

	//Other methods
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	int m_iDamageBonus;
	std::string m_sType;
};

#endif
