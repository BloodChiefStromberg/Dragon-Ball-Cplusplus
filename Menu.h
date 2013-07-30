//Menu.h: header file for Menu.cpp, used in Itemerizer.cpp to create items and
//stuff

#ifndef _Menu
#define _Menu

#include "MenuItem.h"
#include <vector>
#include <string>

class Menu : public MenuItem
{
public:
	//Constructor
	Menu(std::string sName);

	//Getters
	std::vector<MenuItem*> getMenuItems() const;

	//Setters
	void setMenuItems(std::vector<MenuItem*> vMenuItems);

	//Other methods
	void draw();
	void run();
private:
	std::vector<MenuItem*> m_vMenuItems;
};

#endif
