#ifndef _XMLSerializable
#define _XMLSerializable

#include <ostream>
#include <string>

class XMLSerializable
{
public:
	//Constructor
	XMLSerializable();

	//Other methods
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output, int iTabs);
	virtual void writeDataAsFragment(std::ostream & output, int iTabs);
	virtual void setElementData(std::string sElementName, std::string sValue);
};

#endif
