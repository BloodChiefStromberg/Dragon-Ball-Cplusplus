//Field.h: header file for Field.cpp

#ifndef _Field
#define _Field

#include "MenuItem.h"

class Item;

class Field : public MenuItem
{
public:
	//Constructor
	Field(std::string sName, bool bStringValue);

	//Getters
	Item* getItemBeingModified() const;
	int getIntValue() const;
	std::string getStringValue() const;

	//Setters
	void setItemBeingModified(Item* iItemBeingModified);
	void setIntValue(int iIntValue);
	void setStringValue(std::string sStringValue);

	//Other methods
	void draw();
	void run();

private:
	Item* m_iItemBeingModified;
	int m_iIntValue;
	std::string m_sStringValue;
	bool m_bStringValue;
};

#endif
