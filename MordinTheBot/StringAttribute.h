#include <Attribute.h>
#include <string>

class StringAttribute : public Attribute
{
private:

public:
	StringAttribute(string& name)
		: Attribute(name, STRING)
	{};

	StringAttribute(string& name, string& value)
		: Attribute(name, STRING),
		value(value)
	{};

	string getValue()	{ return value; }

	void setValue(string& newValue)	{ value = newValue; }
		
};