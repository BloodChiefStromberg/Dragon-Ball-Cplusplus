#include "XMLSerializable.h"
#include <ostream>
#include <string>

using namespace std;

XMLSerializable::XMLSerializable()
{
}

void XMLSerializable::dumpObject()
{
}

void XMLSerializable::dumpObjectData()
{
}

//I don't think this will ever be called, because we never instantiate an
//XMLSerializable object. This is just for me to have right now.
void XMLSerializable::writeFragment(ostream & output, int iTabs)
{
	for(int i = 0; i < iTabs; i++)
	{
		output << "\t";
	}

	output << "<XMLSerializable>" << endl;
	writeDataAsFragment(output, iTabs + 1);
	output << "</XMLSerializable>" << endl;
}

void XMLSerializable::writeDataAsFragment(ostream & output, int iTabs)
{
}

void XMLSerializable::setElementData(string sElementName, string sValue)
{
}
