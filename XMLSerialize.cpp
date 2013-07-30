#include "XMLSerializable.h"
#include <ostream>
#include <string>

XMLSerializable::XMLSerializable()
{
}

void XMLSerializable::dumpObject()
{
}

void XMLSerializable::dumpObjectData()
{
}

void XMLSerializable::writeFragment(ostream & output, int iTabs)
{
	for(int i = 0; i < iTabs; i++)
	{
		output << "\t";
	}

	output << "<" << dumpObject() << ">";
	writeDataAsFragment(output, iTabs);
	output "</" << dumpObject() << ">";
}

void XMLSerializable::writeDataAsFragment(ostream & output, int iTabs)
{
}

void XMLSerializable::setElementData()
{
}
