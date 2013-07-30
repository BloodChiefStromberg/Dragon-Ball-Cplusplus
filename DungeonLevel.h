//DungeonLevel.h: declares the class DungeonLevel and it's functions
#ifndef _DungeonLevel
#define _DungeonLevel

#include "XMLSerializable.h"
#include "RoomTile.h"
#include "Point.h"
#include <vector>
#include <random>
#include <iostream>

//Forward declarations due to cyclical dependencies. Not sure how to debug these
//really, needs clearing up
class Creature;

class DungeonLevel : XMLSerializable
{
public:
	//Constructor
	DungeonLevel(int iWidth, int iHeight);

	//Destructor
	~DungeonLevel();

	//Copy constructor
	DungeonLevel(const DungeonLevel & dlLevel);

	//Getters
	std::vector<std::vector<RoomTile*>> getRoomTiles();
	std::vector<Point*> getRoomPoints();

	//Setters
	void setRoomTiles(std::vector<std::vector<RoomTile*>> vvRoomTiles);

	//Other methods
//	void display();
	std::vector<std::string> toString();
	//Used to populate the level
//	void populate(std::mt19937& mt, int iAmmount, int iMaxLevel);
	RoomTile* getTileAt(Point* aPoint);
	void clearIntensity();
private:
	//Private methods
	//buildRoom(): Returned vector used for unit testing
	std::vector<Point*> buildRoom(std::vector<std::vector<RoomTile*>>& vvRoomTiles, const std::vector<Point*>& vSection, std::mt19937& mt);
	void drawHallway(const std::vector<Point*> vSection1, const std::vector<Point*> vSection2, std::vector<std::vector<RoomTile*>>& vvRoomTiles, std::mt19937& mt);
	//Used to randomly place stairs. Maybe modify to take any item?
//	void randomPlace(std::mt19937& mt, Entity* anEntity);
	void randomPlace(std::mt19937& mt, RoomTile* aRoomTile);

	//Member variables
	std::vector<std::vector<RoomTile*>> m_vvRoomTiles;
	std::vector<Point*> m_vRoomPoints;
	std::vector<Item*> m_vItems;
	int m_iHeight;
	int m_iWidth;
};

#endif
