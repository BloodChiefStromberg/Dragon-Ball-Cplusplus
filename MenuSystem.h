#ifndef _MenuSystem
#define _MenuSystem

//What is a MenuSystem? At its core, a menu system is a vector of Menus (the
//m_vMenus member variable). Each Menu is made up three things: A name, a level,
//and a SubMenu number.

class MenuSystem
{
public:
	//Constructor
	MenuSystem();

private:
	vector<Menu*> m_vMenus;
};

#endif
