#include "..\\MordinTheBot\\Instance.h"
#include "..\\MordinTheBot\\Instances.h"
#include "..\\MordinTheBot\\Attribute.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

void printAttr(Attribute* attribute);
void printInstances(Instances* instances);
void printInstance(Instance* instance);

int _main()
{
	// Attribute Test;
	Attribute* attribute = new Attribute("Length", Attribute::NOMINAL);
	attribute->addValue("Rado");
	attribute->addValue("Toni");
	attribute->addValue("Grozen");

	printAttr(attribute);

	std::vector<char*> charArray(attribute->getValues());
	Attribute* attribute2 = new Attribute("Names", Attribute::NOMINAL, charArray);
	attribute2->setValue(1, "Toniii");

	printAttr(attribute);
	printAttr(attribute2);

	Attribute* attribute3 = new Attribute("Number");
	printAttr(attribute3);

	// Instances test;
	std::vector<Attribute*> attributes;
	attributes.push_back(attribute);
	attributes.push_back(attribute3);
	attributes.push_back(attribute2);
	Instances* instances = new Instances("DATASET", attributes);
	instances->setClassIndex(instances->numAttributes() - 1);

	printInstances(instances);

	// Instance test;
	printf("Attributes size: %d\n", (int)attributes.size());
	Instance* instance = new Instance((int)attributes.size());
	instance->setValue(1, 2);

	printInstance(instance);

	instances->add(instance);

	printInstances(instances);
	printInstance(instance);

	getchar();

	return 0;
}

void printAttr(Attribute* attr)
{
	printf("Name: %s\n", attr->getName());
	printf("Type: %s\n", attr->getStringType());
	printf("Number of values: %d\n", attr->numValues());

	for (int i = 0; i < attr->numValues(); ++i)
		printf("Value %d: %s\n", i, attr->getValueAt(i));

	if (attr->numValues() > 0)
	{
		srand( (unsigned)time(NULL) );
		int index = rand() % attr->numValues();
		printf("Index of %s: %d\n", attr->getValueAt(index), attr->indexOfValue(attr->getValueAt(index)));
	}

	printf("\n");

	return;
}

void printInstances(Instances* instances)
{
	printf("Relation: %s\n", instances->getRelationName());
	printf("Class Index: %d\n", instances->getClassIndex());
	printf("Class Attribute:\n");
	printAttr(instances->getClassAttribute());
	printf("Number of Attributes: %d\n", instances->numAttributes());
	printf("Number of Instances: %d\n", instances->numInstances());
	for (int i = 0; i < instances->numInstances(); ++i)
		printf("Instance %d dataset: %s\n", i, instances->getInstance(i)->getDataset()->getRelationName());

	printf("\n");

	return;
}

void printInstance(Instance* instance)
{
	printf("Has dataset: %s\n", instance->hasDataset() ? "true" : "false");
	if (instance->hasDataset())
		printf("Dataset relation name: %s\n", instance->getDataset()->getRelationName());

	for (int i = 0; i < instance->numValues(); ++i)
		printf("Instance Value %d: %lf\n", i, instance->getValue(i));

	printf("\n");

	return;
}