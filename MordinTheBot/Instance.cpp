#include "Instance.h"

Instance::Instance(Instance* instance)
: dataset(instance->getDataset()),
values(instance->getValues()),
weight(weight)
{};

Instance::Instance(Instance& instance)
: dataset(instance.getDataset()),
values(instance.getValues()),
weight(weight)
{};

Instance::Instance(double weight, std::vector<double> values)
: dataset(NULL),
weight(weight),
values(values)
{};

Instance::Instance(int numAttributes)
: dataset(NULL),
weight(1.0)
{
	values.reserve(numAttributes);
}

/* Returns the string value of a nominal, string, or date attribute for the instance. 
 * If the attribute is not nominal, NULL is returned. */
char* Instance::getStringValue(int attrIndex)
{
	Attribute* attribute = getAttributeAt(attrIndex);
	if (attribute->getType != Attribute::NOMINAL)
		return NULL;

	int index = (int)values[attrIndex];
	return attribute->geValueAt(index);
}

void Instance::setClassValue(double value)
{
	values[classIndex] = value;

	return;
}

void Instance::setClassValue(char* value)
{
	Attribute* classAttr = getClassAttribute();
	setValue(classAttr, value);

	return;
}

void Instance::setDataset(Instances* dataset)
{
	this->dataset = dataset;
	return;
}

void Instance::setValue(Attribute* attribute, double value)
{
	int attrIndex = dataset->getAttributeIndex(attribute);
	values[attrIndex] = value;

	return;
}

void Instance::setValue(Attribute* attribute, char* value)
{
	int valueIndex = attribute->getValueIndex(value);
	setValue(attribute, valueIndex);
}

void Instance::setValue(int attrIndex, double value)
{
	values[attrIndex] = value;

	return;
}

void Instance::setValue(int attrIndex, char* value)
{
	Attribute* attribute = getAttributeAt(attrIndex);
	setValue(attribute, value);

	return;
}

void Instance::setWeight(double weight)
{
	this->weight = weight;

	return;
}

/* Removes an attribute at the given position (0 to numAttributes() - 1). 
 * Only succeeds if the instance does not have access to any dataset because 
 * otherwise inconsistencies could be introduced. */
void Instance::removeAttributeAt(int position)
{
	if (position < 0 || position >= numAttributes())
		return;

	if (dataset != NULL)
		return;

	values.erase(values.begin() + position);

	return;
}

int Instance::numAttributes()
{
	return numValues();
}

int Instance::numValues()
{
	return values.size();
}

/* Returns the instance as a string in ARFF format. 
 * Strings are quoted if they contain whitespace characters. */
std::string Instance::toString()
{
	std::string s;

	for (int i = 0; i < numValues; ++i)
	{
		Attribute* attribute = getAttributeAt(i);
		switch (attribute->getType())
		{
			case Attribute::NUMERIC:
				s += itoa((int)values[i]);
				s += ",";
				break;
			case Attribute::NOMINAL:
				char* stringValue = getStringValue(i);
				
				if (strchr(stringValue, ' ') != NULL)
					s += "\"" + stringValue + "\"";
				else
					s += stringValue;

				s += ",";
				break;
			default:
				s += "?,";
		}
	}

	s.erase(s.end() - 1);

	return s;
}