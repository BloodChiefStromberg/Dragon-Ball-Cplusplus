#ifndef _Consumable
#define _Consumable

#include "Item.h"
#include <ostream>
#include <string>

class Creature;

class Consumable : public Item
{
public:
	//Constructor
	Consumable();

	//Getters
	virtual int getHealth() const;
	virtual int getNutrition() const;
	virtual std::vector<std::string> getPropertyBenefits() const;

	//Setters
	virtual void setHealth(int iHealth);
	virtual void setNutrition(int iNutrition);
	virtual void setPropertyBenefits(std::vector<std::string> vPropertyBenefits);

	//Other methods
	virtual void used(Creature* usingCreature);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	int m_iHealth;
	int m_iNutrition;
	std::vector<std::string> m_vPropertyBenefits;
};

#endif
