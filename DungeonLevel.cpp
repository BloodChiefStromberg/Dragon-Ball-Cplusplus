//DungeonLevel.cpp: implements the functions declared in DungeonLevel.h

#include "Point.h"
#include "CreatureFactory.h"
#include "DungeonLevel.h"
#include "RoomTile.h"
#include <ncurses.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

//Constructor
DungeonLevel::DungeonLevel(int iWidth, int iHeight) : XMLSerializable()
{
	m_vvRoomTiles.resize(iHeight);
	for (auto itr = m_vvRoomTiles.begin(); itr != m_vvRoomTiles.end(); itr++)
	{

		(*itr).resize(iWidth);
		for (auto itrR = (*itr).begin(); itrR != (*itr).end(); itrR++)
		{
			(*itrR) = new RoomTile(false, false, ' ');
		}
	}

	m_iHeight = iHeight;
	m_iWidth = iWidth;

	//Divide it into 4x2ish grid (rooms 0 through 6)
	int iSectionWidth = iWidth/4;
//	int iRoomCounter = 0; //debug

	//Make the random number generator
	mt19937 mt;
	mt.seed(time(NULL));

	//Make sections of points to build rooms with, and add them to a vector
	//of sections to loop through.
	//NOTE: Make this into a loop if you have time
	vector<vector<Point*>> vvSections;
	for (int i = 0; i < 4; i++)
	{
//		cout << "Making sections..." << endl; //debug
		//Create the top section in the ith partition
		vector<Point*> vSectionTop;
		vSectionTop.resize(2);
		vSectionTop[0] = new Point(iSectionWidth * i, 0);
		vSectionTop[1] = new Point(iSectionWidth * (i + 1), iHeight /2);
		vvSections.push_back(vSectionTop);

//		cout << "Section Points: (" << vvSections[i][0]->getX() << ", " << vvSections[i][0]->getY() << "), (" << vvSections[i][1]->getX() << ", " << vvSections[i][1]->getY() << ")" << endl; //debug

		//bottom section
		vector<Point*> vSectionBottom;
		vSectionBottom.resize(2);
		vSectionBottom[0] = new Point(iSectionWidth * i, iHeight / 2);
		vSectionBottom[1] = new Point(iSectionWidth * (i + 1), iHeight);
		vvSections.push_back(vSectionBottom);

//		cout << "Section Points: (" << vvSections[i + 1][0]->getX() << ", " << vvSections[i + 1][0]->getY() << "), (" << vvSections[i + 1][1]->getX() << ", " << vvSections[i + 1][1]->getY() << ")" << endl; //debug
	}

	//Build the rooms
	vector<Point*> vRoom;
	for (int iSection = 0; iSection < vvSections.size(); iSection++)
	{
//		cout << "Building the rooms"<< endl; //debug
		//buildRoom() returns the points where we actually make room
		//tiles.
		vRoom = buildRoom(m_vvRoomTiles, vvSections[iSection], mt);

//		cout << "Points in room I just made: " << vRoom.size() << endl; //debug

		for (auto itr = vRoom.begin(); itr != vRoom.end(); itr++)
		{
//			cout << "Pushing points into m_vRoomPoints" << endl; //debug
			m_vRoomPoints.push_back((*itr));
		}
	}

	//Draw the hallways
	for (int iPartition = 0; iPartition < vvSections.size()/2; iPartition++)
	{
//		cout << "Drawing hallways..." << endl; //debug
		//connect top and bottom sections at partition iSection
		drawHallway(vvSections[iPartition * 2], vvSections[(iPartition * 2) + 1], m_vvRoomTiles, mt);
		//decide whether to bridge the upper sections or lower sections
		if (((mt() % 2) == 0) &&
		(iPartition < (vvSections.size()/2 - 1)))
			drawHallway(vvSections[iPartition * 2 + 1], vvSections[(iPartition * 2) + 3], m_vvRoomTiles, mt);
		else if	(iPartition < (vvSections.size()/2 - 1))
			drawHallway(vvSections[iPartition * 2], vvSections[iPartition * 2 + 2], m_vvRoomTiles, mt);
//		display(); //debug
//		char cPause = cin.get(); //debug pause
	}

	randomPlace(mt, new RoomTile(false, true, '<'));
	randomPlace(mt, new RoomTile(false, true, '>'));

	//Deallocate the Point* in vvSections
	for (auto itr = vvSections.begin(); itr != vvSections.end(); itr++)
	{
		for (auto itrP = (*itr).begin(); itrP != (*itr).end(); itrP++)
		{
			delete (*itrP);
		}
	}
}

//Destructor
DungeonLevel::~DungeonLevel()
{
//	cout << "Destructor called at " << this << "..." << endl;
	//Deallocate the Point* from m_vvRoomPoints
//	cout << "Deallocating m_vRoomPoints..."; //debug
	for (auto itr = m_vRoomPoints.begin(); itr != m_vRoomPoints.end(); itr++)
	{
		delete (*itr);
	}

//	cout << "Success!" << endl; //debug
//	cout << "Deallcoating m_vvRoomTiles..."; //debug
	//Deallocate the RoomTile* from m_vvRoomTiles
	for (auto itr = m_vvRoomTiles.begin(); itr != m_vvRoomTiles.end(); itr++)
	{
		int iCount = 0;
		for (auto itrR = (*itr).begin(); itrR != (*itr).end(); itrR++)
		{
			//cout << "Number: " << iCount << "Location of RoomTile*" << (*itrR) << endl;
			delete (*itrR);
		}
	}
//	cout << "Success!" << endl;
}

//Copy constructor
DungeonLevel::DungeonLevel(const DungeonLevel& dlLevel)
{
//	cout << "copy constructor called at " << this << endl; //debug
}

//Getters
vector<vector<RoomTile*>> DungeonLevel::getRoomTiles()
{
	return m_vvRoomTiles;
}

vector<Point*> DungeonLevel::getRoomPoints()
{
	return m_vRoomPoints;
}

//Setters
void DungeonLevel::setRoomTiles(vector<vector<RoomTile*>> vvRoomTiles)
{
	m_vvRoomTiles = vvRoomTiles;
}


//Other methods
/*
void DungeonLevel::display()
{
	//Filter through m_vvRoomTiles. Display the Creatures on top, then Items
	//and then display the tiles
	for (auto itrY = m_vvRoomTiles.begin(); itrY != m_vvRoomTiles.end(); itrY++)
	{
		for (auto itrX = (*itrY).begin(); itrX != (*itrY).end(); itrX++)
		{
				//Return is a creature. Display his tile
			cout << (*itrX)->getDisplayChar();
		}
		cout << endl;
	}
}
*/


vector<string> DungeonLevel::toString()
{
	vector<string> vDungeon;
	vDungeon.resize(m_vvRoomTiles.size());

	//Filter through m_vvRoomTiles, and save the tiles to chars
	for (int i = 0; i < m_vvRoomTiles.size(); i++)
	{
		vDungeon[i] = "";
		for (auto itrX = m_vvRoomTiles[i].begin(); itrX != m_vvRoomTiles[i].end(); itrX++)
		{
			if ((*itrX)->getCreature() != NULL)
			{
//				cout << "found a creature" << endl; //debug
				//If there's a creature, display it's char
				vDungeon[i].push_back((*itrX)->getCreature()->getDisplayChar());
			}
			else if ((*itrX)->getItems().size() == 1)
				//if there's only one item, display it's char
				vDungeon[i].push_back((*itrX)->getItems()[0]->getDisplayChar());
			else if ((*itrX)->getItems().size() > 1)
				//if there's more than one itme, display 'L' for
				//loot
				vDungeon[i].push_back('L');
			else
			{
				//Nothings here but the tile. Display it's char
				vDungeon[i].push_back((*itrX)->getDisplayChar());
			}
		}
//		cout << "i: " << i << endl; //debug
	}
	return vDungeon;
}


/*
void DungeonLevel::populate(mt19937& mt, int iAmmount, int iMaxLevel)
{
	cout << "populate() was called." << endl; //debug
	//Generate some creature*, randomly place them, and add them to
	//m_vCreatures
	for (int i = 0; i < iAmmount; i++)
	{
		Creature* aCreature = m_CreatureFactory->generateCreature(iMaxLevel);
		randomPlace(mt, aCreature);
		m_vCreatures.push_back(aCreature);
	}
	cout << "populate(): complete" << endl;
}
*/

RoomTile* DungeonLevel::getTileAt(Point* aPoint)
{
	return m_vvRoomTiles[aPoint->getY()][aPoint->getX()];
}

//Private methods
vector<Point*> DungeonLevel::buildRoom(vector<vector<RoomTile*>>& vvRoomTiles,
	const vector<Point*>& vSection, mt19937& mt)
{
	//Define starting and ending points of the section
	Point* pStart = vSection[0];
	Point* pEnd = vSection[1];

	//Make sure the arguments are in bounds. It's possible that they might
	//go out because of uneven dividing in the constructor

	//Calculate the height and width of the section we're building a room in
	//+ 1 because we include the starting points
	int iSectionHeight = pEnd->getY() - pStart->getY() + 1;
	int iSectionWidth = pEnd->getX() - pStart->getX() + 1;

	//Generate a random room height
	int iMinRoomHeight = 6;
	int iMaxRoomHeight = iSectionHeight - 2; //leave a little room
	int iRandomHeight = mt() % (iMaxRoomHeight - iMinRoomHeight + 1);
	int iRoomHeight = iMinRoomHeight + iRandomHeight;

	//Generate a random room width
	int iMinRoomWidth = 6;
	int iMaxRoomWidth = iSectionWidth - 2; //leave some room again
	int iRandomWidth = mt() % (iMaxRoomWidth - iMinRoomWidth + 1);
	int iRoomWidth = iMinRoomWidth + iRandomWidth;

	//starting points for room
	int iRoomY = pStart->getY() +
		     (mt() % (iSectionHeight - iMinRoomHeight - 1));
	int iRoomX= pStart->getX() +
		    (mt() % (iSectionWidth - iMinRoomWidth - 1));

/*	cout << endl << "iRoomHeight (random): " << iRoomHeight << endl; //debug
	cout << "iRoomWidth (random): " << iRoomWidth << endl; //debug
	cout << "Starting Y Position (random): " << iRoomY << endl; //debug
	cout  << "Starting X Position (random): " << iRoomX << endl; //debug
	cout << "End of section at X Postion: "  << pEnd->getX() << endl;; //debug
	cout << "End of section at Y Postion: "  << pEnd->getY() << endl;; //debug
*/
	//Make sure the room will stay in the section
	while (iRoomWidth + iRoomX > pEnd->getX() - 1)
	{
		iRoomWidth--;
	}
	while (iRoomHeight + iRoomY > pEnd->getY() - 1)
	{
		iRoomHeight--;
	}

	//Make the vector of points to return. Will contain all points that are
	//a part of a room
	vector<Point*> vvOccupiedPoints;

	//Build the room! This is fun!
	for (int y = pStart->getY(); y <= pEnd->getY(); y++)
	{
		for (int x = pStart->getX(); x <= pEnd->getX(); x++)
		{
			//Check if this is an empty part of the section, or a
			//room part
			if ((y >= iRoomY && y < iRoomY + iRoomHeight) &&
			    (x >= iRoomX && x < iRoomX + iRoomWidth))
			{
				//Check if it's a wall
				if (y == iRoomY || y == iRoomY + iRoomHeight - 1)
				{
					vvRoomTiles[y][x] = new RoomTile(false, false, '-');
					vvOccupiedPoints.push_back(new Point(x, y));
				}
				else if (x == iRoomX || x == iRoomX + iRoomWidth - 1)
				{
					vvRoomTiles[y][x] = new RoomTile(false, false, '|');
					vvOccupiedPoints.push_back(new Point(x, y));
				}
				//Otherwise, make it the floor
				else
				{
					vvRoomTiles[y][x] = new RoomTile(false, true, '.');
					vvOccupiedPoints.push_back(new Point(x, y));
				}
			}
		}
	}
	return vvOccupiedPoints;
}

void DungeonLevel::drawHallway(const vector<Point*> vSection1, const vector<Point*> vSection2, vector<vector<RoomTile*>>& vvRoomTiles, mt19937& mt)
{
	//Determine where vSection1 is relative to vSection2
	Point* pSection1Start = vSection1[0];
	Point* pSection2Start = vSection2[0];
	Point* pSection1End = vSection1[1];
	Point* pSection2End = vSection2[1];

	int iRandomY = 0;
	int iRandomX = 0;
/*	cout << "Attempting to access vvRoomTiles[" << iRandomY << "][" << iRandomX << "]..."; //debug
	vvRoomTiles[iRandomY][iRandomX]; //debug
	cout << "success!" << endl; //debug
*/
	//Pick a random room point from vSection1
	while (vvRoomTiles[iRandomY][iRandomX]->getDisplayChar() != '.')
	{
		iRandomY = pSection1Start->getY() + (mt() % (pSection1End->getY() - pSection1Start->getY()));
		iRandomX = pSection1Start->getX() + (mt() % (pSection1End->getX() - pSection1Start->getX()));
/*		cout << "Attempting to access vvRoomTiles[" << iRandomY << "][" << iRandomX << "]..."; //debug
		vvRoomTiles[iRandomY][iRandomX]; //debug
		cout << "success!" << endl; //debug
*/
	}

//	cout << "Found a point in section 1!" << endl; //debug
	Point* pRandom1 = new Point(iRandomX, iRandomY);
	//pCurrentLocation will be used in the while loop to draw the hallway
	Point* pCurrentLocation = new Point(iRandomX, iRandomY);

	iRandomY = 0;
	iRandomX = 0;

	//Pick a random room point from vSection2
	while (vvRoomTiles[iRandomY][iRandomX]->getDisplayChar() != '.')
	{
		iRandomY = pSection2Start->getY() + (mt() % (pSection2End->getY() - pSection2Start->getY()));
		iRandomX = pSection2Start->getX() + (mt() % (pSection2End->getX() - pSection2Start->getX()));
/*		cout << "Attempteing to access vvRoomTiles[" << iRandomY << "][" << iRandomX << "]..."; //debug
		vvRoomTiles[iRandomY][iRandomX]; //debug
		cout << "success!" << endl; //debug
*/
	}
//	cout << "Found a point in section 2!" << endl; //debug
	Point* pRandom3 = new Point(iRandomX, iRandomY);

	//Draw the hallway between the points
	bool bConnected = false;
//	cout << "Building hallways..." << endl; //debug
	int iCounter = 0;
	while (!bConnected)
	{
		iCounter++;
//		cout << endl << "Iteration of while loop: " << iCounter << endl; //debug
		//Check if the spot here should be a hallway
		char cDisplayChar = vvRoomTiles[pCurrentLocation->getY()][pCurrentLocation->getX()]->getDisplayChar();
		if (cDisplayChar == ' ' || cDisplayChar == '|' || cDisplayChar == '-')
			vvRoomTiles[pCurrentLocation->getY()][pCurrentLocation->getX()] = new RoomTile(false, true, '#');

		//See if pCurrentLocation is to the left of pRandom2...
		if (pCurrentLocation->getX() < pRandom3->getX())
		{
//			cout << "Checked x, moved right. bConnected is now false" << endl; //debug
			pCurrentLocation->setX(pCurrentLocation->getX() + 1);
			bConnected = false;
		}
		//...or right
		else if (pCurrentLocation->getX() > pRandom3->getX())
		{
//			cout << "Checked x, moved left. bConnected is now false" << endl; //debug
			pCurrentLocation->setX(pCurrentLocation->getX() -1);
			bConnected = false;
		}
		//If it's on the right column, set bConnected to true. We'll
		//change it later if we need to
		else
		{
//			cout << "In the correct X column! bConnected is true!..."; //debug
			bConnected = true;
		}

		//Since we've moved, we need to check if the spot here should be a hallway again
		//note: copy and pasted code. look for better way if you have time
		cDisplayChar = vvRoomTiles[pCurrentLocation->getY()][pCurrentLocation->getX()]->getDisplayChar();
		if (cDisplayChar == ' ' || cDisplayChar == '|' || cDisplayChar == '-')
			vvRoomTiles[pCurrentLocation->getY()][pCurrentLocation->getX()] = new RoomTile(false, true, '#');

		//Now see if it's above...
		if (pCurrentLocation->getY() < pRandom3->getY())
		{
//			cout << "Checked y, moved down. bConnected is now false." << endl; //debug
			pCurrentLocation->setY(pCurrentLocation->getY() + 1);
			bConnected = false;
		}
		//... or below
		else if (pCurrentLocation->getY() > pRandom3->getY())
		{
//			cout << "Checked y, moved up. bConnected is now false." << endl; //debug
			pCurrentLocation->setY(pCurrentLocation->getY() - 1);
			bConnected = false;
		}
	}
//	cout << "Success!" << endl; //debug;
	delete pRandom1;
	delete pRandom3;
	delete pCurrentLocation;
}

/*
void DungeonLevel::randomPlace(mt19937& mt, Entity* anEntity)
{
	cout << "randomPlace(): called" << endl; //debug
	int iRandomY = 0;
	int iRandomX = 0;

	//Pick a random room point from available rooms points
	while (m_vvRoomTiles[iRandomY][iRandomX]->getDisplayChar() != '.')
	{
		iRandomY = mt() % (m_vvRoomTiles.size());
		iRandomX = mt() % (m_vvRoomTiles[0].size());
	}
	anEntity->changeLocation(this, new Point(iRandomX, iRandomY));

	cout << "randomPlace(): completed" << endl; //debug
}
*/

void DungeonLevel::randomPlace(mt19937& mt, RoomTile* aRoomTile)
{
	int iRandomY = 0;
	int iRandomX = 0;

	//Pick a random room point from available room points
	while (m_vvRoomTiles[iRandomY][iRandomX]->getDisplayChar() != '.')
	{
		iRandomY = mt() % (m_vvRoomTiles.size());
		iRandomX = mt() % (m_vvRoomTiles[0].size());
	}

	m_vvRoomTiles[iRandomY][iRandomX] = aRoomTile;
}

void DungeonLevel::clearIntensity()
{
	for (size_t i = 0; i < m_vvRoomTiles.size(); i++)
	{
		for (size_t j = 0; j < m_vvRoomTiles[j].size(); j++)
		{
			m_vvRoomTiles[i][j]->setIntensity(0);
		}
	}
}
