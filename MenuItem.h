//MenuItem.h: header file for MenuItem.cpp

#ifndef _MenuItem
#define _MenuItem

#include <string>

class MenuItem
{
public:
	//Constructor
	MenuItem(std::string sName);

	//Getters
	virtual std::string getName() const;
	virtual MenuItem* getParent() const;

	//Setters
	virtual void setName(std::string sName);
	virtual void setParent(MenuItem* miParent);

	//Other methods
	virtual void draw() = 0;
	virtual void run() = 0;
private:
	std::string m_sName;
	MenuItem* m_miParent;
};

#endif
