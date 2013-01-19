#include "Attribute.h"

/* Creates a numeric attribute with the given name. */
Attribute::Attribute(const char* name)
: name(name),
type(NUMERIC),
weight(1.0),
index(-1)
{
	values.clear();
}

/* Createes an attribute with the given name, type, and weight.
 * If the attribute is nominal, it would have empty list of values. */
Attribute::Attribute(const char* name, const int type, double weight)
: name(name),
type(type), 
weight(weight),
index(-1)
{
	values.clear();
}

/* Creates an attribute with given name, type, and weight. The given values are
 * set as possible for the attribute.
 * If the type is not nominal, the values won't be considered further. */
Attribute::Attribute(const char* name, const int type, std::vector<char*>& values, double weight)
: name(name),
type(type),
values(values),
weight(weight),
index(-1)
{}

/* Returns the name of the attribute */
const char* Attribute::getName()
{
	return name;
}

/* Returns the inner representation of the type of the attribute. */
const int Attribute::getType()
{
	return type;
}

/* Returns the string representation of the type. */
char* Attribute::getStringType()
{
	switch (type)
	{
	case NOMINAL:
		return "nominal";
	case NUMERIC:
		return "numeric";
	case STRING:
		return "string";
	default:
		return "";
	}
}

/* Returns the weight of the attribute */
double Attribute::getWeight()
{
	return weight;
}

/* Returns the values of the attribute. */
std::vector<char*> Attribute::getValues()
{
	return values;
}

/* Returns the value at the given position. If the attribute is not nominal, or
 * the position is out ot array bounds, an empty string would be returned. */
char* Attribute::getValueAt(int index)
{
	if (type != Attribute::NOMINAL)
		return "";

	if (index < 0 || index >= numValues())
		return "";

	return values[index];
}

/* Returns the attribute's index. If index is missing, it will return a negative value. */
int Attribute::getIndex()
{
	return index;
}

/* Set new weight to the attribute. */
void Attribute::setWeight(double newWeight)
{
	weight = newWeight;

	return;
}

/* Set value at the given position. If the attribute is not nominal, nothing will
 * happen. */
void Attribute::setValue(int index, char* value)
{
	if (type != Attribute::NOMINAL)
		return;

	values[index] = value;

	return;
}

/* Sets the attribute's index. */
void Attribute::setIndex(int index)
{
	this->index = index;

	return;
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

/* Returns the index of a given attribute value. (The index of the first occurence of this value.)
 * Returns -1 if the attribute is not nominal or the value cannot be found.	*/
int Attribute::indexOfValue(char* value)
{
	if (type != NOMINAL)
		return -1;

	for (int i = 0; i < numValues(); ++i)
	{
		if (strcmp(values[i], value) == 0)
			return i;
	}

	return -1;
}

/* Returns the number values. Returns 1 if the attribute is not nominal. */
int Attribute::numValues()
{
	if (type != NOMINAL)
		return 0;

	return (int)values.size();
}

/* Returns the attribute as a string in ARFF format. */
std::string Attribute::toString()
{
	std::string s("@attribute ");
	
	if (strchr(name, ' ') != NULL)
	{
		s += "\"";
		s += name;
		s += "\"";
	}
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
			for (int i = 0; i < numValues(); ++i)
			{
				s += values[i];
				s += ",";
			}
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
 
	if (type == NOMINAL)
	{
		if (values.size() != other->numValues())
			return false;

		std::vector<char*> otherValues = other->getValues();
		for (int i = 0; i < numValues(); ++i)
		{
			if (strcmp(values[i], otherValues[i]) != 0)
				return false;
		}
	}

	return true;
}

/* Adds an attribute value at last position. 
 * If the attribute is not nominal, nothing will happen. */
void Attribute::addValue(char* value)
{
	addValue(numValues(), value);

	return;
}

/* Adds an attribute value at given position. 
 * If the attribute is not nominal, nothing will happen. */
void Attribute::addValue(int index, char* value)
{
	if (type != Attribute::NOMINAL)
		return;

	values.insert(values.begin() + index, value);

	return;
}
/* Removes the last value of the nominal attribute.
 * If the attribute is not nominal, nothing would happen. */
void Attribute::removeValue()
{
	removeValue(numValues() - 1);

	return;
}

/* Removes a value of a nominal attribute. 
 * If the attribute is not nominal nothing would happen. */
void Attribute::removeValue(int index)
{
	if (type != Attribute::NOMINAL)
		return;

	values.erase(values.begin() + index);

	return;
}