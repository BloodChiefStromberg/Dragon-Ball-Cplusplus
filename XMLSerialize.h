#ifndef _XMLSerializable
#define

#include <ostream>
#include <string>

class _XMLSerializable
{
public:
	//Constructor
	XMLSerializable();

	//Other methods
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, string sValue);
}

#endif
