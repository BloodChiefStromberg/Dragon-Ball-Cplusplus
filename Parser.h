//Parser.h: declares functions for parsing xml

#ifndef _parser
#define _parser

#include <iostream>
#include <vector>
#include "XMLSerializable.h"

class Weapon;

//Parses Elements and creates the objects in vGameWorld
bool parseElement(std::istream & input, XMLSerializable* element,
	 std::vector<XMLSerializable*> & vGameWorld);

//Begins the parsing process
bool parseXML(std::istream & input, std::vector<XMLSerializable*> & vGameWorld);

#endif
