//MenuItem.cpp: implements functions defined in the MenuItem.h header file

#include "MenuItem.h"

using namespace std;

//Constructor
MenuItem::MenuItem(string sName)
{
	m_sName = sName;
}

//Getters
string MenuItem::getName() const
{
	return m_sName;
}

MenuItem* MenuItem::getParent() const
{
	return m_miParent;
}

//Setters
void MenuItem::setName(string sName)
{
	m_sName = sName;
}

void MenuItem::setParent(MenuItem* miParent)
{
	m_miParent = miParent;
}
