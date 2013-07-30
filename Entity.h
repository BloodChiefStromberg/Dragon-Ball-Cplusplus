//Entity.h: declares functions to be implemented in Entity.cpp. This is the
//main class for other classes to extend.

#ifndef _Entity
#define _Entity

#include "XMLSerializable.h"
#include "DungeonLevel.h"
#include "RoomTile.h"
#include "Point.h"
#include <string>
#include <vector>
#include <ostream>

class Entity : public XMLSerializable
{
public:
	//Constructor
	Entity();

	//Destructor
	~Entity();

	//COPY CONSTRUCTOR THIS THING IS THE DEVIL
	Entity(const Entity& anEntity);

	//Getters
	virtual std::string getName() const;
	virtual std::vector<std::string> getProperties() const;
	virtual char getDisplayChar() const;
	virtual Point* getLocation() const;
	virtual int getID() const;

	//Setters
	virtual void setName(std::string sName);
	virtual void setProperties(std::vector<std::string> vProperties);
	virtual void setDisplayChar(char cDisplayChar);
	virtual void setLocation(Point* pLocation);

	//Other methods
	virtual void addProperty(std::string sProperty);
	virtual void changeLocation(DungeonLevel* dlLevel, Point* pNewLocation);
	virtual bool hasProperty(std::string);
	virtual std::string getDescription();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual void insertTabs(std::ostream & output, int iTabs); //use this to create the hierarchy. hopefully this works
private:
	std::string m_sName;
	std::vector<std::string> m_vProperties;
	char m_cDisplayChar;
	Point* m_pLocation;
	int m_iID;
};

#endif

