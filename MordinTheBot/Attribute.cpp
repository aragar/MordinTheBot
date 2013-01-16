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

/* Returns the number values. Returns 1 if the attribute is not nominal. */
int Attribute::numValues()
{
	if (type != NOMINAL)
		return 1;

	return values.size();
}

/* Returns the attribute as a string in ARFF format. */
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

/* Returns true if the `other` attribute is equal to the current. */
bool Attribute::operator==(Attribute* other)
{
	if (other == NULL)
		return false;

	if (strcmp(name, other->getName()) != 0)
		return false;

	if (type != other->getType())
		return false;

	if (weight != other->getWeight())
		return false;
 
	if (type == NOMINAL)
	{
		if (values.size() != other->getValues.size())
			return false;

		for (std::vector<char*>::iterator it1 = values.begin(), it2 = other->getValues.begin();
				it1 != values.end(); ++it1, ++it2)
		{
			if (strcmp((*it1), (*it2)) != 0)
				return false;
		}
	}

	return true;
}