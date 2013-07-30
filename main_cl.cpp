//main_console.cpp:
//implements the main function. It parses
//through the input XML, instantiates objects, re-writes
//the XML, then deletes all your pointers.

#include<ncurses.h>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include<cmath>
#include "Weapon.h"
#include "Item.h"
#include "Creature.h"
#include "XMLSerializable.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Entity.h"
#include "Parser.h"
#include "Gold.h"
#include "Ammunition.h"
#include "DungeonLevel.h"
#include "Point.h"
#include "CreatureFactory.h"
#include "Point.h"
#include "Light.h"

using namespace std;

int g_iID = 0;

void randomPlace(mt19937& mt, DungeonLevel* dlLevel, Entity* anEntity)
{
        int iRandomY = 0;
        int iRandomX = 0;

        //Pick a random room point from available rooms points
        while (dlLevel->getRoomTiles()[iRandomY][iRandomX]->getDisplayChar() != '.')
        {
                iRandomY = mt() % dlLevel->getRoomTiles().size();
                iRandomX = mt() % dlLevel->getRoomTiles()[0].size();
        }
/*
	addstr("Randomly placing at (");
	addstr(to_string(iRandomX).c_str());
	addstr(", ");
	addstr(to_string(iRandomY).c_str());
	addch('\n');
	refresh();
	getch();
*/
        anEntity->changeLocation(dlLevel, new Point(iRandomX, iRandomY));

//      cout << "randomPlace(): completed" << endl; //debug
}

void addLights(mt19937& mt, DungeonLevel* dlLevel, vector<Light*>& vLights)
{
	for (int i = 0; i < 3; i++)
	{
		int iRandom = mt() % 5 + 2;
		Light* pLight = new Light(iRandom);
		pLight->setOn(true);
		randomPlace(mt, dlLevel, pLight);
		vLights.push_back(pLight);
	}
}

void populateDungeonLevel(mt19937& mt, DungeonLevel* dlLevel, vector<Creature*>& vNewFloor, CreatureFactory* cfFactory, int iAmmount, int iMaxLevel)
{
        //Generate some creature*, randomly place them, and add them to
        //m_vCreatures
        for (int i = 0; i < iAmmount; i++)
        {
                Creature* aCreature = cfFactory->generateCreature(iMaxLevel);
                randomPlace(mt, dlLevel, aCreature);
                vNewFloor.push_back(aCreature);
        }
}

int handleUserInput(char cInput, Creature* pPlayer, vector<DungeonLevel*>& vDungeonLevels, int* pCurrentFloor, mt19937& mt, CreatureFactory* cfFactory, vector<vector<Creature*>>& vvActiveCreatures, vector<vector<Light*>>& vvLights)
{
	DungeonLevel* dlCurrentLevel = vDungeonLevels[(*pCurrentFloor)];
	if (cInput == 'q')
	{
		addch('\n');
		refresh();
		return 0;
	}
	else if (cInput == '8' || cInput == '4' || cInput == '2' || cInput == '6')
	{
		pPlayer->move(cInput, dlCurrentLevel);
	}
	else if (cInput == 'u')
	{
		//Interpreting ints returned by runInventoryMenu():
		//	-0: not returned
		//	-1: item used, turn passes
		//	-2: they pushed '5' to go back
		return pPlayer->runInventoryMenu(dlCurrentLevel);
	}
	else if (cInput == 'i')
	{
		for (size_t i = 0; i < vvActiveCreatures[(*pCurrentFloor)].size(); i++)
		{
			Creature* pCreature = vvActiveCreatures[(*pCurrentFloor)][i];
			if(pCreature != NULL)
				pCreature->runInventoryMenu(dlCurrentLevel);
		}
	}
	else if (cInput == 's')
	{
		RoomTile* rtThisRoomTile = dlCurrentLevel->getTileAt(pPlayer->getLocation());
		//if they're on a downstairs, make a new dungeon level, add it
		//to the vector of dungeon levels, and populate it.
		if (rtThisRoomTile->getDisplayChar() == '<')
		{
			//if we're on the current bottom floor
			if ((*pCurrentFloor) == vDungeonLevels.size() -1 )
			{
				//Say were on the next floor
				(*pCurrentFloor)++;

				//Make a new dungeon level, and add it to our vector
				DungeonLevel* pNewLevel = new DungeonLevel(79, 20);
				vDungeonLevels.push_back(pNewLevel);

				//Also, add a new level to our creature and light vectors so we
				//have a vector to populate
				vvActiveCreatures.resize(vvActiveCreatures.size() + 1);
				vvLights.resize(vvLights.size() + 1);
				populateDungeonLevel(mt, pNewLevel, vvActiveCreatures[(*pCurrentFloor)], cfFactory, 1 + (mt() % 5), pPlayer->getLevel() + *pCurrentFloor);
				addLights(mt, pNewLevel, vvLights[*pCurrentFloor]);

				pPlayer->useStairs(pNewLevel, 'd');
			}
			else
			{
				(*pCurrentFloor)++;
				pPlayer->useStairs(vDungeonLevels[(*pCurrentFloor)], 'd');
			}


//			addstr("pCurrentFloor after moving down steps: "); //debug
//			addstr(to_string(*pCurrentFloor).c_str()); //debug
//			addch('\n'); //debug
//			refresh(); //debug
		}
		else if (rtThisRoomTile->getDisplayChar() == '>')
		{
			if(*pCurrentFloor == 0)
				return 0;
			(*pCurrentFloor)--;
			pPlayer->useStairs(vDungeonLevels[*pCurrentFloor], 'u');
		}
	}
	else if (cInput == 'p')
	{
		pPlayer->pickUp(dlCurrentLevel);
	}
	return 1;
}

void recalculateLights(vector<Light*>& vLights, DungeonLevel* dlLevel)
{
	for (size_t i = 0; i < vLights.size(); i++)
	{
		Light* pLight = vLights[i];
		if (pLight->getOn())
		{
			pLight->emitLight(false, dlLevel);
			pLight->emitLight(true, dlLevel);
		}
	}
}

vector<vector<char>> dungeonToChars(mt19937& mt, DungeonLevel* dlLevel)
{
	start_color();
	//To light, we have 3 sets of color pairs. One with black backgrounds,
	//one with yellow, and one with red. We calculate how lit the tile is,
	//and then set then choose the appropriate color pair for the tile.

	//Non lit color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);

	//Dimly lit color pairs
	init_pair(11, COLOR_RED, COLOR_YELLOW);
	init_pair(12, COLOR_GREEN, COLOR_YELLOW);
	init_pair(13, COLOR_WHITE, COLOR_YELLOW);
	init_pair(14, COLOR_BLUE, COLOR_YELLOW);

	//Strongly lit color pairs
	init_pair(21, COLOR_RED, COLOR_RED);
	init_pair(22, COLOR_GREEN, COLOR_RED);
	init_pair(23, COLOR_WHITE, COLOR_RED);
	init_pair(24, COLOR_BLUE, COLOR_RED);

        vector<vector<char>> vvDungeon;
        vvDungeon.resize(dlLevel->getRoomTiles().size());

        //Filter through m_vvRoomTiles, and save the tiles to chars
        for (size_t y = 0; y < (dlLevel->getRoomTiles()).size(); y++)
        {
//              cerr << "i: " << y << endl; //debug
                for (size_t x = 0; x < (dlLevel->getRoomTiles())[y].size(); x++)
                {
			Creature* pCreature = ((dlLevel->getRoomTiles())[y][x])->getCreature();
			vector<Item*> vItems = ((dlLevel->getRoomTiles())[y][x])->getItems();
			Point* pThisLocation = new Point(x, y);
			RoomTile* rtThisRoomTile = dlLevel->getTileAt(pThisLocation);
			delete pThisLocation;

			//Determine level of lighting to choose
			int iHowLit = 0;
			if (rtThisRoomTile->getIntensity() == 0)
				iHowLit = 0;
			else if (rtThisRoomTile->getIntensity() == 1)
				iHowLit = 1;
			else //if (rtThisRoomTile->getIntensity() == 2)
			{
				iHowLit = 2;
//				addstr("Found a tile that needs to be lit!\n");
//				getch();
			}

			iHowLit = iHowLit * 10;

//			cerr << "This is what RoomTile thinks it has: " << pCreature << endl; //debug
			char cDisplayChar = rtThisRoomTile->getDisplayChar();

                        if (pCreature != NULL)
                        {
				if (pCreature->getName() == "Goku")
				{
					attron(COLOR_PAIR(4 + iHowLit));
					addch(pCreature->getDisplayChar());
					attroff(COLOR_PAIR(4 + iHowLit));
				}
				else
				{
	                                //If there's a creature, display it's char
					attron(COLOR_PAIR(1 + iHowLit));
					addch(pCreature->getDisplayChar());
					attroff(COLOR_PAIR(1 + iHowLit));
					//vvDungeon[y].push_back(pCreature->getDisplayChar());
                        	}
			}
                        else if (vItems.size() >= 1)
			{
				if (vItems.size() == 1)
				{
	                                //if there's only one item, display it's char
					attron(COLOR_PAIR(2 + iHowLit));
					addch(vItems[0]->getDisplayChar());
					attroff(COLOR_PAIR(2 + iHowLit));
				}
				else if (vItems.size() > 1)
				{
					//if there's more than one itme, display 'L' for
                                	//loot
					attron(COLOR_PAIR(2 + iHowLit));
					addch('L');
					attroff(COLOR_PAIR(2 + iHowLit));
				}
			}
			else
			{
				attron(COLOR_PAIR(3 + iHowLit));
				addch(cDisplayChar);
				attroff(COLOR_PAIR(3 + iHowLit));
			}
//			else
//			{
//				attron(COLOR_PAIR(3));
//				addch(cDisplayChar);
//				attroff(COLOR_PAIR(3));
//			}
                }
		addch('\n');
        }
	return vvDungeon;
}

void removeCarcasses(DungeonLevel* dlLevel, vector<Creature*>& vActiveCreatures, Creature* pPlayer)
{
//	addstr("removeCarcasses: called\n");
//	getch();
//	refresh();
//	auto itr = vActiveCreatures.begin();
	for (size_t i = 0; i < vActiveCreatures.size(); i++)
	{
//		addstr("at index ");
//		addstr(to_string(i).c_str());
//		addch('\n');
//		refresh();
		Creature* pCreature = vActiveCreatures[i];

		if (pCreature != NULL && pCreature->getHP() <= 0)
		{
			//Remove the carcass
			RoomTile* rtCrimeScene = dlLevel->getTileAt(pCreature->getLocation());
			rtCrimeScene->setCreature(NULL);

			//Tell the carcass to drop loot
			pCreature->dropLoot(dlLevel);

			//Reward the player w XP
			pPlayer->recieveExperience(pCreature->getLevel());

			//Get rid of it's data
//			addstr("about to delete the creature");
//			addch('\n');
//			refresh();
//			getch();
			vActiveCreatures[i] = NULL;
			delete pCreature;
//			addstr("deleted creature");
//			addch('\n');
//			refresh();
//			getch();
		}
	}

//	addstr("removeCarcasses: finished\n");
//	refresh();

/*
	while (itr != vActiveCreatures.end())
	{
		if ((*itr)->getHP() <= 0)
		{
			//Remove the carcass
			RoomTile* rtCrimeScene = dlLevel->getTileAt((*itr)->getLocation());
			rtCrimeScene->setCreature(NULL);

			//Tell the carcass to die
			(*itr)->die(dlLevel);

			//Reward the player w XP
			pPlayer->recieveExperience((*itr)->getLevel());

			//Get rid of it's data
			delete (*itr);
			itr = vActiveCreatures.erase(itr);
		}
		else
			itr++;
	}
*/
}

void displayTopBarStatus(Creature* pPlayer, int* pCurrentFloor, int iTurns)
{
	addstr("FLOOR: ");
	addstr(to_string((*pCurrentFloor) + 1).c_str());
	addch('\t');
	addstr("LEVEL: ");
	addstr(to_string(pPlayer->getLevel()).c_str());
	addch('\t');
	addstr("HP: ");
	addstr(to_string(pPlayer->getHP()).c_str());
	addch('/');
	addstr(to_string(pPlayer->getMaxHP()).c_str());
	addch('\t');
	addstr("XP: ");
	addstr(to_string(pPlayer->getExperience()).c_str());
	//Formula for level up:
	//	= (Current Level + (1/2 Current Level))^2
	addch('/');
	addstr(to_string((pPlayer->getLevel() + (pPlayer->getLevel() / 2)) * (pPlayer->getLevel() + (pPlayer->getLevel() / 2))).c_str());
	addch('\t');
	addstr("TURNS: ");
	addstr(to_string(iTurns).c_str());
	addch('\n');
}

/*
void display(mt19937& mt, DungeonLevel* dlCurrentLevel)
{
	vector<vector<char>> vvDisplay = dungeonToChars(mt, dlCurrentLevel);
	for (size_t y = 0; y < vvDisplay.size(); y++)
	{
		for (size_t x = 0; x < vvDisplay[y].size(); x++)
		{
			//Make the ground gray, the player green, and enemies
			//red
			addch(vvDisplay[y][x]);
			//cout << (*itrX);
		}
		addch('\n');
		//cout << '\n';
	}
}
*/

int distance(Point* aPoint, Point* anotherPoint)
{
	return (int) sqrt(pow((double) aPoint->getX() - anotherPoint->getX(), 2.0) + pow((double) aPoint->getY() - anotherPoint->getY(), 2.0));
}

void moveTowards(Creature* movingCreature, Point* pTarget, DungeonLevel* dlLevel)
{
	int iMyX = movingCreature->getLocation()->getX();
	int iMyY = movingCreature->getLocation()->getY();
	int iTargetX = pTarget->getX();
	int iTargetY = pTarget->getY();
	bool bMoved = false;

	if (iMyX < iTargetX && !bMoved)
		bMoved = movingCreature->move('6', dlLevel);
	if (iMyX > iTargetX & !bMoved)
		bMoved = movingCreature->move('4', dlLevel);
	if (iMyY < iTargetY && !bMoved)
		bMoved = movingCreature->move('2', dlLevel);
	if (iMyY > iTargetY && !bMoved)
		bMoved = movingCreature->move('8', dlLevel);
}

int main(int argc, char* argv[])
{

//Got rid of all parsing stuff untill needed later

/*
	string sInput;
	string sInputFile;
	string sOutputFile;

	if (argc >= 3)
	{
		sInputFile = argv[1];
		sOutputFile = argv[2];
	}
	else
	{
		cout << "No input/output file detected. What would you like your input file to be?" << endl;
		cin >> sInputFile;

		cout << "What would you like your output file to be?" << endl;
		cin >> sOutputFile;
	}

	ifstream fInput;
	fInput.open(sInputFile.c_str());

	if (!fInput.good())
	{
		cout << "Bad input file! You gave me " << sInputFile << " and I couldn't get it to work!" << endl;
		return 1;
	}

	//Deal with the output file
	ofstream fOutput;
	fOutput.open(sOutputFile.c_str());

	if(!fOutput.good())
	{
		cout << "Bad file! Couldn't find or make the output file " << sOutputFile << endl;
		return 1;
	}

	//We the XML File data into this vector, re-write to XML from this
	//vector, output the data to console, then delete it. Operating as if
	//this isn't even necessary for now
	vector<XMLSerializable*> vSetup;

	//WHAT WE WILL DO: Read in the fInput into objects, and
	//store them in vSetup. Then make the XML from vSetup,
	//and dump all the objects in vGameWorld to the console.
	if (parseXML(fInput, vSetup))
	{
		//We've just parsed, so we can close the input now.
		fInput.close();

		cout << "This is what I parsed in: " << endl;

		//Dump the objects we've just parsed to the console;
		for (auto itr = vSetup.begin(); itr != vSetup.end(); itr++)
		{
			(*itr)->dumpObject();
		}

		//Start writing the xml
		fOutput << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl; //make it valid xml
		fOutput << "<World>" << endl;

		//Write vSetup to xml
		for (auto itr = vSetup.begin(); itr != vSetup.end(); itr++)
		{
			(*itr)->writeFragment(fOutput, 1);
		}

		//end the xml document
		fOutput << "</World>";

		//Close my output
		fOutput.close();

		//Delete my pointers
		for (auto itr = vSetup.begin(); itr != vSetup.end(); itr++)
		{
			delete (*itr);
		}
	}

*/

	//PLAYING

	//Now, time to actually play

	mt19937 mt;
	mt.seed(time(NULL));
	bool bEscaped = false;
	CreatureFactory* cfFactory = &(CreatureFactory::instance());

	vector<DungeonLevel*> vDungeonLevels;   //holds all the DungeonLevels
						//(or floors)
	vector<vector<Creature*>> vvActiveCreatures;    //holds all the creatures on the
							//battle field.
//	vector<Item*> vActiveItems;		//items on the battle field

	vector<vector<Light*>> vvLights; //ALL OF THE LIGHTS

	initscr();
	noecho();

	//Create our player
	Creature* pPlayer = new Creature();
	pPlayer->setName("Goku");
	pPlayer->setDisplayChar('@');
	pPlayer->setMaxHP(30);
	pPlayer->setHP(30);
	pPlayer->setEnemy(false);
	Weapon* pGokuPunch = new Weapon("GOKU PUNCH", 7);
	Armor* pBareChest = new Armor("Bare Chest", 4);

	pPlayer->setEquipedWeapon(pGokuPunch);
	pPlayer->setEquipedArmor(pBareChest);

	//Get rid of the default weapon and armor
	vector<Item*> vEmpty;
	pPlayer->setInventory(vEmpty);

	pPlayer->addItem(pGokuPunch);
	pPlayer->addItem(pBareChest);


	//Create the basic potion for the player
	Consumable* cPotion = new Consumable();
	cPotion->setHealth(20);
	cPotion->setName("Red Potion");
	cPotion->setRarity(50);
	pPlayer->addItem(cPotion);

	//Create the dungeon level
	int* pCurrentFloor = new int;
	*pCurrentFloor = 0;
	DungeonLevel* pLevel = new DungeonLevel(79, 20);
	vvActiveCreatures.resize(1);
	populateDungeonLevel(mt, pLevel, vvActiveCreatures[(*pCurrentFloor)], cfFactory, 1 + (mt() % 5), 2);
	vDungeonLevels.push_back(pLevel);
	int iTurns = -1;

	//Light the dungeon w random lights up to strength 5
	vvLights.resize(1);
	addLights(mt, pLevel, vvLights[0]);

	pPlayer->useStairs(pLevel, 'd');

//	initscr();
//	noecho();
	addstr("DRAGON BALL C++");
	addch('\n');
	addch('\n');
	addstr("Press any button to begin! Confused? Read the README to learn how to play!");
	refresh();



	char cInput = getch();
	clear();

	while (pPlayer->getHP() > 0 && !bEscaped)
	{
		//The game runs like this:
		//Players move on even turns. Monsters move on odd turns.
		//First things first, the map is displayed. You move, then the
		//turns over.
		//Then the map redraws. Now the monsters move.
		//Then the map redraws. Now you move. And so on.
		//Increase turn counter
		iTurns++;

		//The DungeonLevel is like a great map for us. It's main field
		//is m_vvRoomTiles, which holds a butt ton of room tiles.
		//Intelligently, I've given the room tiles access to all the
		//Creatures on them, and all the items. AKA everything we need
		//to draw.
		DungeonLevel* dlCurrentLevel = vDungeonLevels[(*pCurrentFloor)];

		//Display the status of stuff on the top bar
		displayTopBarStatus(pPlayer, pCurrentFloor, iTurns);

		//light the dungeon
		recalculateLights(vvLights[(*pCurrentFloor)], dlCurrentLevel);

		//Begin displaying
		dungeonToChars(mt, dlCurrentLevel);

		//See who's turn it is
		//If it's the players turn, handle their move.
		if (iTurns % 2 == 0)
		{
			//Now ask the player what to do
			addstr("You're move. What do you want to do?");
			addch('\n');
			refresh();
			cInput = getch();

			//handleUserInput() returns an int
			//	-0: they want to quit
			//	-1: they take some other action
			//	-2: no action was taken, redraw the screen
			int iUserInputReturn = handleUserInput(cInput, pPlayer, vDungeonLevels, pCurrentFloor, mt, cfFactory, vvActiveCreatures, vvLights);
			if(iUserInputReturn == 0)
				bEscaped = true;
			else if (iUserInputReturn == 2)
				//They took no action. Redraw the screen
				iTurns--;
		}


		//MONSTERS' TURN
		//If it's the monsters turn, handle their moves.
		else
		{
//			addstr("monsters turn\n");
//			refresh();
			//Player regenerates half of his level back as health each turn
			//min 1
			pPlayer->regenerate();

			for (size_t i = 0; i < vvActiveCreatures[(*pCurrentFloor)].size(); i++)
			{
				Creature* pCreature = vvActiveCreatures[(*pCurrentFloor)][i];
				if (pCreature != NULL)
				{
					Point* pPlayerLocation = pPlayer->getLocation();
					bool bAware = distance(pPlayerLocation, pCreature->getLocation()) < (pCreature->getPerceptionRange());
					if (bAware)
					{
						//Now we know that the creature is aware of our
						//hero. They should move towards him.
						moveTowards(pCreature, pPlayerLocation, vDungeonLevels[(*pCurrentFloor)]);
					}
					else
					{
						Point* randomSpot = new Point(mt() % 79, mt() % 20);
						moveTowards(pCreature, randomSpot, vDungeonLevels[(*pCurrentFloor)]);
						delete randomSpot;
					}
				}
			}
		}

		//remove anyone who died and award XP
		removeCarcasses(dlCurrentLevel, vvActiveCreatures[(*pCurrentFloor)], pPlayer);

		//Clear the window for the next run
		clear();
	}

	//Display the score
	addstr("The game is over! Thanks for playing!");
	addch('\n');
	refresh();
	getch();
	addstr("YOUR SCORE (press a key to see next thing):");
	addch('\n');
	addch('\n');
	refresh();
	getch();
	addstr("Experience: +");
	int iExperience = pPlayer->getExperience();
	addstr(to_string(iExperience).c_str());
	addch('\n');
	refresh();
	getch();
	addstr("Loot: ");
	addch('\n');

	int iTotalItems = 0;
	vector<Item*> vPlayerInventory = pPlayer->getInventory();
	for (auto itr = vPlayerInventory.begin(); itr != vPlayerInventory.end(); itr++)
	{
		addch('\t');
		refresh();
		getch();
		addstr((*itr)->getName().c_str());
		addstr(": +");
		int iCurrentItem = 100 - (*itr)->getRarity();
		iTotalItems += iCurrentItem;
		addstr(to_string(iCurrentItem).c_str());
		addch('\n');
	}

	addch('\n');
	addstr("TOTAL: ");
	refresh();
	getch();
	addstr(to_string(iTotalItems + iExperience).c_str());
	addch('\n');
	getch();
	endwin();

	delete pCurrentFloor;
	delete pPlayer;
	for (size_t i = 0; i < vDungeonLevels.size(); i++)
	{
		delete vDungeonLevels[i];
	}
	for (size_t i = 0; i < vvActiveCreatures.size(); i++)
	{
		for (size_t j = 0; j < vvActiveCreatures[i].size(); j++)
		{
			delete vvActiveCreatures[i][j];
		}
	}

	//Don't need to deallocate lights. Because they're stored as items,
	//they'll get deallocated when the rooms are destroyed.

/*	for (size_t i = 0; i < vvLights.size(); i++)
	{
		for (size_t j = 0; j < vvLights[i].size(); j++)
		{
			delete vvLights[i][j];
		}
	}

*/

	return 0;
}
