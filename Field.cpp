#include "Field.h"
#include <ncurses.h>

using namespace std;

//Constructor
Field::Field(string sName, bool bStringValue) : MenuItem(sName)
{
	m_bStringValue = bStringValue;
	m_iIntValue = 0;
}

//Getters
Item* Field::getItemBeingModified() const
{
	return m_iItemBeingModified;
}

int Field::getIntValue() const
{
	return m_iIntValue;
}

string Field::getStringValue() const
{
	return m_sStringValue;
}

//Setters
void Field::setItemBeingModified(Item* iItemBeingModified)
{
	m_iItemBeingModified = iItemBeingModified;
}

void Field::setIntValue(int iIntValue)
{
	m_iIntValue = iIntValue;
}

void Field::setStringValue(string sStringValue)
{
	m_sStringValue = sStringValue;
}

//Other methods
void Field::draw()
{
	addstr(getName().c_str());
	addstr(" = ");
	if (!m_bStringValue)
		addstr(to_string(m_iIntValue).c_str());
	else
		addstr(m_sStringValue.c_str());
}

void Field::run()
{
	clear();
	addstr(getName().c_str());
	addstr(" = ");
	refresh();
	char cInput = getch();
	//Take in the int as a string. We'll convert it later
	char* cStringValue;
	char* cIntValue;
//	if (m_bStringValue)
//	{
		if (m_bStringValue)
		{
			echo();
			getstr(cStringValue);
			m_sStringValue = cStringValue;
//			m_sStringValue += cInput;
		}
		else
		{
			echo();
			getstr(cIntValue);
			m_iIntValue = atoi(cIntValue);
//			sIntValue += cInput;
		}
/*		refresh();
		cInput = getch();
		clear();
		addstr(getName().c_str());
		addstr(" = ");
*/
//	}
}
