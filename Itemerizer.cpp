#include <ncurses.h>
#include <vector>
#include <string>
#include "MenuItem.h"
#include "Menu.h"
#include "Field.h"

using namespace std;

void buildMenus()
{
	Menu* mPrimary = new Menu("Home");
	vector<MenuItem*> vSubMenus;
	Menu* mWeapon = new Menu("Weapon");
	Menu* mArmor = new Menu("Armor");
	Menu* mItem = new Menu("Item");
	vSubMenus.push_back(mWeapon);
	vSubMenus.push_back(mArmor);
	vSubMenus.push_back(mItem);
	mPrimary->setMenuItems(vSubMenus);

	//Make the Weapon branch
	vector<MenuItem*> vWeaponFields;
	Field* fName = new Field("Name", true);

	mPrimary->run();
}

int main()
{
	initscr();
	noecho();
	buildMenus();
	endwin();
	return 0;
}
