#include "Light.h"
#include "RoomTile.h"
#include <cmath>
#include <ncurses.h>

using namespace std;

//Constructor
Light::Light(int iIntensity) : Item()
{
	setName("Light");
	setDisplayChar('l');
	m_iIntensity = iIntensity;
	m_bOn = true;
}

//Getters
int Light::getIntensity() const
{
	return m_iIntensity;
}

bool Light::getOn() const
{
	return m_bOn;
}

//Setters
void Light::setIntensity(int iIntensity)
{
	m_iIntensity = iIntensity;
}

void Light::setOn(bool bOn)
{
	m_bOn = bOn;
}

//Other methods
void Light::emitLight(bool bOn, DungeonLevel* dlLevel)
{
	//if it was on, regardless what the passed bOn is, filter through the
	//needed tiles. We'll either be shutting them off or re-emitting them.
	//If it was off but we're turning them on, we also need to filter
	//through. The only case we don't filter through is if the light was
	//already off and we still want it off. So if not already off and we
	//don't still want it off...
	if (m_bOn || bOn)
	{
		vector<vector<RoomTile*>> vvRoomTiles = dlLevel->getRoomTiles();
		double pi = atan(1)*4;
		int iRadius = m_iIntensity;
		Point* illuminatedPoint = new Point(0, 0);
		for (double theta = 0; theta < 2.0*pi; theta += (pi/(2.0 * (iRadius *iRadius))))
		{
			for (int r = 1; r <= iRadius; r++)
			{
				int iXCoord = r*cos(theta);
				//We have to divide by 2 because the
				//tiles are taller than they are wide
				int iYCoord = r*sin(theta);

				int iXCurrentLocation = getLocation()->getX();
				int iYCurrentLocation = getLocation()->getY();

				illuminatedPoint->setX(iXCoord + iXCurrentLocation);
				illuminatedPoint->setY(iYCoord + iYCurrentLocation);

				if(illuminatedPoint->getY() < vvRoomTiles.size() && illuminatedPoint->getX() < vvRoomTiles[0].size())
				{
					RoomTile* rtThisRoomTile = dlLevel->getTileAt(illuminatedPoint);
					char cDisplayChar = rtThisRoomTile->getDisplayChar();


					//if our light ray runs into a wall, creature, or item, end the ray
					bool bHitObject = false;
					if (bOn)
					{
						if (cDisplayChar == '|' || cDisplayChar == '-' || cDisplayChar == ' ' ||
						(rtThisRoomTile->getCreature() != NULL && rtThisRoomTile != dlLevel->getTileAt(getLocation())))
						{
							r = iRadius + 1;
							bHitObject = true;
						}
					}

					if (!bHitObject)
					{
						//Now we need to decide what to
						//do with the tiles
						int iHighIntensity = 2;
						int iLowIntensity = 1;

						//if its supposed to be off,
						//set the lights to zero
						if (!bOn)
						{
							iHighIntensity = 0;
							iLowIntensity = 0;
						}

						if (r < (3 * iRadius) / 4)
						{
							rtThisRoomTile->setIntensity(iHighIntensity);
						}
						else
						{
							rtThisRoomTile->setIntensity(iLowIntensity);
						}
					}
				}
			}
		}
		delete illuminatedPoint;
	}

	//Now set the light setting to whatever it needed to be changed to
	m_bOn = bOn;
}
