#include "Instances.h"

Instances::Instances(char* relationName, vector<Attribute*>& attributes, int capacity = 0)
: relationName(relationName),
attributes(attributes),
classIndex(-1)
{
	instances = std::vector<Instance*>(capacity);
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

/* Returns an attribute given its name. If there is more than one attribute with the
 * same name, it returns the first one. Returns null if the attribute can't be found. */
Attribute* Instances::getAttribute(char* name)
{
	for (std::vector<Attribute*> it = attributes.begin(); it != attributes.end(); ++it)
		if (strcmp((*it)->name, name) == 0)
			return (*it);

	return NULL;
}

/* Returns the last instance in the set. */
Instance* Instances::getLastInstance()
{
	int len = numInstances();
	
	return instances[len-1];
}

/* Sets the class attribute. */
void Instances::setClass(Attribute attribute)
{
	int classIndex = 0;
	for (std::vector<Attribute*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
	{
		if (attribute == (*it))
		{	
			this->classIndex = classIndex;
			return
		}

		++classIndex;
	}

	return;
};

/* Adds one instance to the end of the set. Shallow copies instance before it is added. 
 * Does not check if the instance is compatible with the dataset. */
void Instances::add(Instance instance)
{
	instances.push_back(new Instance(instance));
	return;
}

/* Checks if the given instance is compatible with this dataset. */
bool Instances::checkInstance(Instance* instance)
{
	std::vector<Attribute*> otherAttributes = instance->getAttributes();

	if (attributes.size() != otherAttributes.size())
		return false;
	for (std::vector<Attribute*>::iterator it1 = attributes.begin(), it2 = otherAttributes.begin(); 
			it1 != attributes.end(); ++it1, ++it2)
		if ( !((*it1) == (*it2)) )
			return false;

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
	if (position < 0 || position >= attributes.size())
		return;
	if (position == classIndex)
		return;
	if (instances.size() > 0)
		return;

	attributes.erase(attributes.begin() + position);

	return;
}

/* Inserts an attribute at the given position (0 to numAttributes()). 
 * If there is any instances in the dataset, the deletion won't happen. */
void Instances::insertAttributeAt(Attribute* attribute, int position)
{
	if (position < 0 || position > attributes.size())
		return;
	if (instances.size() > 0)
		return;

	attributes.insert(attributes.begin() + position, attribute);

	return;
}

/* Returns the dataset as a string in ARFF format. 
 * Strings are quoted if they contain whitespace characters. */
string Instances::toString()
{
	string s("@data\n");

	for (std::vector<Instance*>::iterator it = instances.begin(); it != instances.end(); ++it)
		s += (*it)->toString() + "\n";

	return s;
}