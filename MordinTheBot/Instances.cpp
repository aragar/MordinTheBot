#include "Instances.h"
#include "Instance.h"

Instances::Instances(char* relationName, std::vector<Attribute*>& attributes, int capacity)
: relationName(relationName),
attributes(attributes),
classIndex(-1)
{
	if (capacity < 0)
		capacity = 0;

	instances.reserve(capacity);
}

Instances::Instances(Instances* dataset)
: relationName(dataset->getRelationName()),
attributes(dataset->getAttributes()),
instances(dataset->getInstances()),
classIndex(dataset->getClassIndex())
{}

Instances::Instances(Instances& dataset)
: relationName(dataset.getRelationName()),
attributes(dataset.getAttributes()),
instances(dataset.getInstances()),
classIndex(dataset.getClassIndex())
{}

/* Returns an attribue at the given position. */
Attribute* Instances::getAttribute(int index)
{
	return attributes[index];
}

/* Returns an attribute given its name. If there is more than one attribute with the
 * same name, it returns the first one. Returns null if the attribute can't be found. */
Attribute* Instances::getAttribute(char* name)
{
	for (int i = 0; i < numAttributes(); ++i)
		if (strcmp(attributes[i]->getName(), name) == 0)
			return attributes[i];

	return NULL;
}

/* Returns the index of the given attribute in the set of attributes. If there is more
 * than one attribute with the same name, it return the first one. Returns -1 if the attribute
 * can't be found. */
int Instances::getAttributeIndex(Attribute* attribute)
{
	int index = 0;

	for (std::vector<Attribute*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
	{
		if (attribute == (*it))
			return index;

		++index;
	}

	return -1;
}

/* Returns the attributes of the dataset. */
std::vector<Attribute*> Instances::getAttributes()
{
	return attributes;
}

/* Returns the class attribute. */
Attribute* Instances::getClassAttribute	()
{
	return getAttribute(classIndex);
}

/* Returns the index of the class attribute. 
 * Returns -1, if one is not defined. */
int Instances::getClassIndex()
{
	return classIndex;
}

/* Returns all instances in the dataset. */
std::vector<Instance*> Instances::getInstances()
{
	return instances;
}

/* Returns the first instance of the dataset. */
Instance* Instances::getFirstInstance()
{
	return getInstance(0);
}

/* Returns the instance with the given index. */
Instance* Instances::getInstance(int index)
{
	return instances[index];
}

/* Return the last instance of the dataset. */
Instance* Instances::getLastInstance()
{
	int len = numInstances();
	
	return instances[len-1];
}

/* Returns the relation name. */
char* Instances::getRelationName()
{
	return relationName;
}

/* Sets the given attribute as a class attribute. */
void Instances::setClass(Attribute* attribute)
{
	classIndex = getAttributeIndex(attribute);

	return;
}

/* Sets the class index with the given one. */
void Instances::setClassIndex(int newClassIndex)
{
	classIndex = newClassIndex;

	return;
}

/* Sets the relation name to the given one. */
void Instances::setRelationName(char* newRelationName)
{
	relationName = newRelationName;

	return;
}

/* Adds one instance to the end of the set. 
 * Does not check if the instance is compatible with the dataset. */
void Instances::add(Instance* instance)
{
	Instance* result = new Instance(instance);
	result->setDataset(this);
	
	instances.push_back(result);

	return;
}

/* Checks if the given instance is compatible with this dataset. */
bool Instances::checkInstance(Instance* instance)
{
	if (numAttributes() != instance->numAttributes())
		return false;

	std::vector<Attribute*> otherAttributes = instance->getAttributes();
	for (int i = 0; i < numAttributes(); ++i)
	{
		if ( !(attributes[i] == otherAttributes[i]) )
			return false;
	}

	return true;
}

/* Removes all instances from the set. */
void Instances::remove()
{
	instances.clear();

	return;
}

/* Removes an instance at the given position from the set. */
void Instances::remove(int index)
{
	instances.erase(instances.begin() + index);

	return;
}

/* Deletes an attribute at the given position (0 to numAttributes() - 1). 
 * If there is any instances in the dataset, the deletion won't happen. 
 * Class attribute can't be deleted. */
void Instances::removeAttributeAt(int position)
{
	if (position < 0 || position >= numAttributes())
		return;

	if (position == classIndex)
		return;

	if (classIndex > position)
		--classIndex;
	attributes.erase(attributes.begin() + position);

	for (int i = 0; i < numInstances(); ++i)
	{
		Instance* instance = getInstance(i);
		instance->removeValueAt(position);
    }

	return;
}

/* Inserts an attribute at the given position (0 to numAttributes()). */
void Instances::insertAttributeAt(Attribute* attribute, int position)
{
	if (position < 0 || position > numAttributes())
		return;

	if (getAttribute(attribute->getName()) != NULL)
		return;

	attributes.insert(attributes.begin() + position, attribute);
	if (classIndex >= position)
		++classIndex;
	for (int i = 0; i < numInstances(); ++i)
	{
		Instance* instance = instances[i];
		instance->insertValueAt(position);
	}

	return;
}

/* Returns the number of attributes. */
int Instances::numAttributes()
{ 
	return (int)attributes.size(); 
}

/* Returns the number of instances in the dataset. */
int Instances::numInstances()
{ 
	return (int)instances.size(); 
}

/* Returns the dataset as a string in ARFF format. 
 * Strings are quoted if they contain whitespace characters. */
std::string Instances::toString()
{
	std::string s("@relation ");
	
	if (strchr(relationName, ' ') != NULL)
	{
		s += "\"";
		s += relationName;
		s += "\"";
	}
	else	
		s += relationName;
	s += "\n\n";

	for (int i = 0; i < numAttributes(); ++i)
	{
		s += attributes[i]->toString();
		s += "\n";
	}

	s += "\n@data\n";
	for (int i = 0; i < numInstances(); ++i)
	{
		s += instances[i]->toString();
		s += "\n";
	}

	return s;
}
