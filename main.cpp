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


using namespace std;

// parseElement:
//  returns a bool indicating success; false if invalid XML
//  was encountered, true if the XML was parsed correctly
//
// arguments:
//   istream & input - an input stream of the XML file
//     being processed
//
//   string sHierarchy - the current position in the XML
//     document's object hierarchy which is being processed
//
// note: this does *not* properly check for end of input
// in the XML document!
//
// This function assumes that we are on the first character
// AFTER the opening <.
bool parseElement(istream & input, XMLSerializable* element, vector<XMLSerializable*> & vGameWorld)
{
	// char to hold data as we process it
	char c;

	// The name of the element; initialized to
	// an empty string (as all strings are by default);
	// we get this by reading in the XML
	string sElementName;


	// Read in the XML one character at a time, checking
	// for the > at the end of the tag
	do
	{
		// Get the character off the stream
		c = input.get();

		// If it's not the end tag, add it to the element name
		if( c != '>' )
			sElementName.push_back(c);

	} while( c != '>' );

//	cout << "Element Name: " << sElementName << endl;

	if (sElementName == "Entity")
	{
		element = new Entity();
		vGameWorld.push_back(element);
	} else if (sElementName == "Item")
	{
		element = new Item();
		vGameWorld.push_back(element);
	} else if (sElementName == "Creature")
	{
		element = new Creature();
		vGameWorld.push_back(element);
	} else if (sElementName == "Weapon")
	{
		element = new Weapon();
		vGameWorld.push_back(element);
	} else	if (sElementName == "Armor")
	{
		element = new Armor();
		vGameWorld.push_back(element);
	} else	 if (sElementName == "Potion")
	{
		element = new Potion();
		vGameWorld.push_back(element);
	} else	if (sElementName == "Scroll")
	{
		element = new Scroll();
		vGameWorld.push_back(element);
	}

	// Holds the non-element content of the element
	string sContent = "";

	// while(true) can be dangerous, but we do have paths
	// out of the function.
	while( true )
	{
		// Read a character off the stream
		c = input.get();

		// The important thing is to check to see if
		// it is an open angled bracket.
		if( c == '<' )
		{
			// If it is, we have two possibilities (assuming
			// the XML is valid):
			//
			// Either this is the start tag for a new element
			// contained in the current element, or it's
			// the end tag for our current element.
			//
			// Note that if it is an end tag -- and the XML is
			// valid -- it MUST be the end tag of the current element
			// as elements are not allowed to overlap.

			// So we check for the first character
			// being a / -- which indicated an end tag
			if( input.peek() == '/' )
			{
				// We must burn off the / since
				// we only peeked it, and haven't
				// gotten it yet!
				input.get();

				// Variable to hold the end tag as
				// we read it in
				string sEndTag;

				// Read in the end tag until we get
				// to the > at the end of the tag
				do
				{
					c = input.get();
					if( c != '>' )
						sEndTag.push_back(c);

				} while( c != '>' );

				// Now, we test for the validity of the XML -- the 
				// end tag's name must match the element's name...
				if( sEndTag != sElementName )
				{
					cout << "Tag name mismatch" << endl;
					return false;
				}

				// Output what we know to the console --
				// the hierarchy (where we are in the document),
				// the current element, and its content
				if (element != NULL)
				{
					element->setElementData(sElementName, sContent);
				}

				// And since we have fully parsed an element, we
				// return to whatever called us in the first place
				return true;

			}
			else
			{
				// In this branch, we have already read in a <,
				// but it was NOT an end tag -- the input file
				// is currently positioned on the first character
				// after the opening <, so we can call parseElement
				// on it...
				//
				// Here we're passing the hierarchy we know plus
				// the current element name, so this next element
				// knows where it is in the overal document 
				// hiearchy
				if( !parseElement(input, element, vGameWorld) )
					return false;
			}
		}
		else
		{
			// In this branch, we have read in a character inside
			// the element which is not a < -- since it's not
			// part of an interior element, it's content, so
			// we add it to our variable which stores the
			// content (ignoring end-of-line characters).
			if( c != '\n' )
				sContent.push_back(c);
		}
	}


	return true;
}

// parseXML -- parses an XML document.  First it
// makes a very half-hearted check for the validity
// of the XML header, then it parses the root
// element of the document.
bool parseXML(istream & input, vector<XMLSerializable*> & vGameWorld)
{
	char c;

	// Read in the XML, one character at a time,
	// until we hit a <.
	do
	{
		c = input.get();
	} while( c != '<' );

	// Check the character after the < -- if it's
	// not a ?, we aren't seeing a valid XML header
	if( input.get() != '?' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	// Burn off the rest of the header, looking for
	// a ?
	do
	{
		c = input.get();
	} while( c != '?' );

	// Then we check for a > -- which tests for
	// the header ending with ?>
	if( input.get() != '>' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	// Now burn off characters until we get to the first
	// tag after the XML header...
	do
	{
		c = input.get();
	} while( c != '<' );


	// And so, we're now on the first character after
	// the opening < -- which is exactly what parseElement
	// expects.  So we call it.
	XMLSerializable* element = new XMLSerializable();
	return parseElement(input, element, vGameWorld);
}

int main(int argc, char* argv[])
{
	DungeonLevel* dlCaves = new DungeonLevel(79, 20);
	dlCaves->display();

	cout << "What file should I parse?" << endl;

	string sInput;

	cin >> sInput;
	ifstream fInput;
	fInput.open(sInput.c_str());

	vector<XMLSerializable*> vGameWorld; //here's my game world. I'll add everything too, it then iterate through it to write the xml

	parseXML(fInput, vGameWorld);


	//WHAT WE WILL DO: Read in the fInput into objects, and
	//store them in vGameWorld. Then make the XML from vGameWorld,
	//and dump all the objects in vGameWorld to the console.

	//Dump the objects we've just parsed to the console

	for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
	{
		(*itr)->dumpObject();
	}

	cout << "Where should I output the new XML file?" << endl;

	cin >> sInput;

	//Write it to XML

	ofstream fOutput;
	fOutput.open(sInput.c_str());
	fOutput << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl; //make it valid xml
	fOutput << "<World>" << endl;

	for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
	{
		(*itr)->writeFragment(fOutput, 1);
	}

	fOutput << "</World>"; //end the xml document

	//Delete my pointers

	for (vector<XMLSerializable*>::iterator itr = vGameWorld.begin(); itr != vGameWorld.end(); itr++)
	{
		delete (*itr);
	}

	return 0;
}
