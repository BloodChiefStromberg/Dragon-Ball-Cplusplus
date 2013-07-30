#include "Menu.h"
#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

//Constructor
Menu::Menu(string sName) : MenuItem(sName)
{
}

//Getters
vector<MenuItem*> Menu::getMenuItems() const
{
	return m_vMenuItems;
}

//Setters
void Menu::setMenuItems(vector<MenuItem*> vMenuItems)
{
	m_vMenuItems = vMenuItems;
}

//Other methods
void Menu::run()
{
	int iCurrentSelected = 0;
	bool bSelected = false;
	clear();

	while (!bSelected)
	{
		for (size_t i = 0; i < m_vMenuItems.size(); i++)
		{
			if (iCurrentSelected == i)
				addch('\t');
			m_vMenuItems[i]->draw();
			addch('\n');
		}
		refresh();

		char cDirection = getch();

		if (cDirection == '2' && iCurrentSelected < (m_vMenuItems.size() - 1))
			iCurrentSelected++;
		else if (cDirection == '8' && iCurrentSelected > 0)
			iCurrentSelected--;
		else if (cDirection == '\n')
		{
			m_vMenuItems[iCurrentSelected]->run();
			bSelected = true;
		}
		else if (cDirection == '5')
			return;
		clear();
	}
}
