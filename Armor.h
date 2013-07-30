#ifndef _Armor
#define _Armor

#include "Item.h"
#include <string>
#include <ostream>

class Armor : public Item
{
public:
	//Constructor
	Armor(std::string sName, int iArmorValue);

	//Copy constructor
	Armor(const Armor& someArmor);

	//Getters
	virtual std::string getSlot() const;
	virtual std::string getType() const;
	virtual int getArmorValue() const; 	//is this defense bonus?
						//consider renaming


	//Setters
	virtual void setSlot(std::string sSlot);
	virtual void setType(std::string sType);
	virtual void setArmorValue(int iArmorValue);

	//Other methods
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	std::string m_sSlot;
	std::string m_sType;
	int m_iArmorValue;
};

#endif
