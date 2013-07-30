#ifndef _Light
#define _Light

#include "Item.h"
#include <vector>

class RoomTile;

class Light : public Item
{
public:
	//Constructor
	Light(int iIntensity);

	//Getters
	virtual int getIntensity() const;
	virtual bool getOn() const;

	//Setters
	virtual void setIntensity(int iIntensity);
	virtual void setOn(bool bOn);

	//Other methods
	void emitLight(bool bOn, DungeonLevel* dlLevel);
private:
	bool m_bOn;
	int m_iIntensity;
};

#endif
