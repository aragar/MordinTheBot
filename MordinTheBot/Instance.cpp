#include "Instance.h"
#include <cstdlib>

Instance::Instance(Instance* instance)
: dataset(NULL),
values(instance->getValues()),
weight(instance->getWeight())
{};

Instance::Instance(Instance& instance)
: dataset(NULL),
values(instance.getValues()),
weight(instance.getWeight())
{};

Instance::Instance(double weight, std::vector<double>& values)
: dataset(NULL),
weight(weight),
values(values)
{};

Instance::Instance(int numAttributes)
: dataset(NULL),
weight(1.0)
{
	if (numAttributes < 0)
		numAttributes = 0;

	values.reserve(numAttributes);
	for (int i = 0; i < numAttributes; ++i)
		values.push_back(0);
}

/* Returns the attribute with the given index. */
Attribute* Instance::getAttributeAt(int index)
{
	return dataset->getAttribute(index);
}

/* Returns the class attribute. */
Attribute* Instance::getClassAttribute()
{
	return dataset->getClassAttribute();
}

/* Returns the class index. */
int Instance::getClassIndex()
{
	return dataset->getClassIndex();
}

/* Returns the internal represantation of the class value. */
double Instance::getClassValue()
{
	return values[getClassIndex()];
}

/* Returns the dataset. */
Instances* Instance::getDataset()
{
	return dataset;
}

/* Returns the attributes of the instance. */
std::vector<Attribute*> Instance::getAttributes()
{
	return dataset->getAttributes();
}

/* Returns the string value of a nominal attribute for the instance. 
 * If the attribute is not nominal, NULL is returned. */
char* Instance::getStringValue(Attribute* attribute)
{
	int attrIndex = dataset->getAttributeIndex(attribute);
	return getStringValue(attrIndex);
}

/* Returns the string value of a nominal attribute for the instance. 
 * If the attribute is not nominal, NULL is returned. */
char* Instance::getStringValue(int attrIndex)
{
	Attribute* attribute = getAttributeAt(attrIndex);
	if (attribute->getType() != Attribute::NOMINAL)
		return NULL;

	int index = (int)values[attrIndex];
	return attribute->getValueAt(index);
}

/* Returns an instance's attribute value in internal format. */
double Instance::getValue(Attribute* attribute)
{
	int attrIndex = dataset->getAttributeIndex(attribute);
	return getValue(attrIndex);
}

/* Returns an instance's attribute value in internal format. */
double Instance::getValue(int attrIndex)
{
	return values[attrIndex];
}

/* Returns the internal representation of the instance's values. */
std::vector<double>	Instance::getValues()
{
	return values;
}

/* Returns the instance's weight. */
double Instance::getWeight()
{
	return weight;
}

/* Set the value in internal format of the class attribute. */
void Instance::setClassValue(double value)
{
	setValue(getClassIndex(), value);

	return;
}

/* Set the value of the class attribute. */
void Instance::setClassValue(char* value)
{
	setValue(getClassIndex(), value);

	return;
}

/* Set the dataset of the instance. */
void Instance::setDataset(Instances* dataset)
{
	this->dataset = dataset;

	return;
}

/* Set the value in internal format of the given attribute. */
void Instance::setValue(Attribute* attribute, double value)
{
	int attrIndex = dataset->getAttributeIndex(attribute);
	setValue(attrIndex, value);

	return;
}

/* Set the value of the given attribute. */
void Instance::setValue(Attribute* attribute, char* value)
{
	if (attribute->getType() != Attribute::NOMINAL)
		return;

	int attrIndex  = dataset->getAttributeIndex(attribute);
	int valueIndex = attribute->indexOfValue(value);
	setValue(attrIndex, (double)valueIndex);

	return;
}

/* Set the value in internal format for the given attribute index. */
void Instance::setValue(int attrIndex, double value)
{
	values[attrIndex] = value;

	return;
}

/* Set the value for the given attribute index. */
void Instance::setValue(int attrIndex, char* value)
{
	Attribute* attribute = getAttributeAt(attrIndex);
	if (attribute->getType() != Attribute::NOMINAL)
		return;

	int valueIndex = attribute->indexOfValue(value);
	setValue(attrIndex, (double)valueIndex);

	return;
}

/* Sets the weight of the instance. */
void Instance::setWeight(double weight)
{
	this->weight = weight;

	return;
}

/* Removes a value at the given position (0 to numAttributes() - 1). */
void Instance::removeValueAt(int position)
{
	values.erase(values.begin() + position);

	return;
}

/* Inserts a value at the given position (0 to numAtributes() - 1). */
void Instance::insertValueAt(int position)
{
	values.insert(values.begin() + position, 0);
}

/* Returns the number of attributes. */
int Instance::numAttributes()
{
	return dataset->numAttributes();
}

/* Returns the number of values. */
int Instance::numValues()
{
	return (int)values.size();
}

/* Returns the instance as a string in ARFF format. 
 * Strings are quoted if they contain whitespace characters. */
std::string Instance::toString()
{
	std::string s("");

	for (int i = 0; i < numAttributes(); ++i)
	{
		if (i > 0)
			s += ",";

		Attribute* attribute = getAttributeAt(i);
		switch (attribute->getType())
		{
			case Attribute::NUMERIC:
			{
				char tmp[64];
				s += _itoa_s((int)values[i], tmp, 64, 10);
			}
				break;
			case Attribute::NOMINAL:
			{
				char* stringValue = getStringValue(i);
				
				if (strchr(stringValue, ' ') != NULL)
				{
					s += "\"";
					s += stringValue;
					s += "\"";
				}
				else
					s += stringValue;
			}
				break;
			default:
				s += "?";
		}
	}

	return s;
}

/* Returns true if the instance is bound to a dataset. */
bool Instance::hasDataset()
{
	return dataset != NULL;
}