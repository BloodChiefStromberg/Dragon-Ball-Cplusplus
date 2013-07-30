//main_console.cpp:
//implements the main function. It parses
//through the input XML, instantiates objects, re-writes
//the XML, then deletes all your pointers.

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "Item.h"
#include "Creature.h"
#include "XMLSerializable.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Scroll.h"
#include "Entity.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "What file should I parse?" << endl;

	string sInput;

	cin >> sInput;
	ifstream fInput;
	fInput.open(sInput.c_str());

	//Check that the files good
	if (!fInput.good())
	{
		cout << "Bad input file! You gave me " << sInput << " but it didn't work!" << endl;
		return 1;
	}

	//here's my game world. I'll add everything too, it then iterate
	//through it to write the xml
	vector<XMLSerializable*> vGameWorld;


	//WHAT WE WILL DO: Read in the fInput into objects, and
	//store them in vGameWorld. Then make the XML from vGameWorld,
	//and dump all the objects in vGameWorld to the console.

	if (parseXML(fInput, vGameWorld))
	{
		//We've just parsed, so we can close the input now
		fInput.close();

		cout << "This is what we parsed in: " << endl;

		//Dump the objects we've just parsed to the console
		for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
		{
			(*itr)->dumpObject();
		}

		//Get XML file name
		cout << "Where should I output the new XML file?" << endl;

		cin >> sInput;

		//Deal with output file
		ofstream fOutput;
		fOutput.open(sInput.c_str());

		if (!fOutput.good())
		{
			cout << "Bad output file! You gave me " << sInput << " but it didn't work correctly!" << endl;
			return 1;
		}

		//Now that we know it's good, output to XML
		fOutput << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl; //make it valid xml
		fOutput << "<World>" << endl;

		for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
		{
			(*itr)->writeFragment(fOutput, 1);
		}

		fOutput << "</World>"; //end the xml document

		//Close the output
		fOutput.close();

		//Delete my pointers

		for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
		{
			delete (*itr);
		}
	}
	return 0;
}
