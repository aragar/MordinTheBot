#include "Attribute.h"
#include <cstring>

Attribute::Attribute()
{};

Attribute::Attribute(CHAR* name, int type, double weight = 1.0)
: name(name),
type(type), 
weight(weight)
{};

Attribute::Attribute(char* name, int type, vector<char*> values, double weight = 1.0)
: name(name),
type(type),
values(values),
weight(weight)
{};

/* Returns the index of a given attribute value. (The index of the first occurence of this value.)
 * Returns -1 if the attribute is not nominal or the value cannot be found.	*/
int Attribute::indexOfValue(char* value)
{
	if (type != NOMINAL)
		return -1;

	int index = 0;
	for (std::vector<char*>::iterator it = values.begin(); it != values.end(); ++it)
	{
		if (strcmp(*it, value) == 0)
			return index;

			++index;
	}

	return -1;
}

/* Returns true if the type of the attribute is Nominal. */
bool Attribute::isNominal()
{
	return type == Attribute::NOMINAL;
}

/* Returns true if the type of the attribute is Numeric. */
bool Attribute::isNumeric()
{
	return type == Attribute::NUMERIC;
}

/* Returns true if the type of the attribute is String. */
bool Attribute::isString()
{
	return type == Attribute::STRING;
}

int Attribute::numValues()
{
	return values.size();
}

string Attribute::toString()
{
	string s("@attribute ");
	
	if (strchr(name, ' ') != NULL)
		s += "\"" + name + "\"";
	else
		s += name;
	s += " ";

	switch(type)
	{
		case Attribute::NUMERIC:
			s += "numeric";
			break;
		case Attribute::STRING:
			s += "string";
			break;
		case Attribute::NOMINAL:
			s += "{";
			for (std::vector<char*>::iterator it = values.begein(); it != values.end(); ++it)
				s += *it + ",";
			s.replace(s.length() - 1, 1, "}");
			break;
	}

	return s;
}