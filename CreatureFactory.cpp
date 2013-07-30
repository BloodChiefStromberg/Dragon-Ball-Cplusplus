#include "CreatureFactory.h"
#include "Parser.h"
#include <ncurses.h>
#include <iostream>
#include <fstream>

using namespace std;

//Singleton constructor
CreatureFactory& CreatureFactory::instance()
{
	static CreatureFactory cfCreatureFactory = CreatureFactory();
	return cfCreatureFactory;
}

//Constructor
CreatureFactory::CreatureFactory()
{
	ifstream ifInputFile;
	ifInputFile.open("critters.xml");

	//Create the world
	vector<XMLSerializable*> vCritters;
	parseXML(ifInputFile, vCritters);

	//Put the creatures in the m_vCreatures
	for (auto itr = vCritters.begin(); itr != vCritters.end(); itr++)
	{
		Creature* pCreature = dynamic_cast<Creature*>(*itr);

		//Just in case...
		if (pCreature != NULL)
			m_vCreatures.push_back(pCreature);
	}

	//Seed the random number generator
	m_mtRandom.seed(time(NULL));
}

//Destructor
CreatureFactory::~CreatureFactory()
{
	//Deallocate m_vCreatures
	for (auto itr = m_vCreatures.begin(); itr != m_vCreatures.end(); itr++)
	{
		delete (*itr);
	}
}

Creature* CreatureFactory::generateCreature(int iMaxLevel)
{
	//Create a vector of creatures of a fair level
	vector<Creature*> vFairCreatures;
	for (auto itr = m_vCreatures.begin(); itr != m_vCreatures.end(); itr++)
	{
		//Check if they're too high of a level
		if ((*itr)->getLevel() <= iMaxLevel)
			vFairCreatures.push_back(*itr);
	}

	//Choose a creature
	int iCreature = m_mtRandom() % (vFairCreatures.size());

	//Create a new creature from that template
	Creature* pChosenCreature = new Creature(*(vFairCreatures[iCreature]));

//	cout << "CREATURE GENERATED AT: " << pChosenCreature << endl; //debug

//	cout << "generateCreature(): complete" << endl; //debug

	return pChosenCreature;
}
