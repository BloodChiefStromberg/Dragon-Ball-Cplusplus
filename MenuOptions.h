#ifndef _MenuItem
#define _MenuItem

#include <string>

class MenuOptions : MenuItem
{
public:
	//Constructor
	MenuItem();

	//Getters
	std::string getName() const;

private:
	std::string m_sName;
};

#endif
