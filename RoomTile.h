//RoomTile.h: declares the class RoomTile. RoomTiles will make up all DungeonLevels
#ifndef _RoomTile
#define _RoomTile

#include<vector>

class Item;
class Creature;

class RoomTile
{
public:
	//Constructor
	RoomTile(bool bCollectable, bool bWalkable, char cDisplayChar);

	//Destructor
	~RoomTile();

	//Setters
	void setIntensity(int iIntensity);
	void setCollectable(bool bCollectable);
	void setWalkable(bool bWalkable);
	void setDisplayChar(char cDisplayChar);
	void setCreature(Creature* aCreature);
	void setItems(std::vector<Item*> vItems);
//	void std::vector<Entity*> setContainedEntities();

	//Getters
	int getIntensity() const;
	std::vector<Item*> getItems() const;
	Creature* getCreature() const;
	bool getCollectable() const;
	bool getWalkable() const;
	char getDisplayChar() const;

	//Other methods
//	void addIntensity(int iIntensity);
	void add(Item* anItem);
	void remove(Item* anItem);

private:
	int m_iIntensity;
	std::vector<Item*> m_vItems;
	bool m_bCollectable;
	bool m_bWalkable;
	char m_cDisplayChar;
	Creature* m_pCreature;
};

#endif
