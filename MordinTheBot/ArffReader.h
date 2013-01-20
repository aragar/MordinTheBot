#pragma once
#include "Attribute.h"
#include "Instance.h"

class Instances;

class ArffReader
{
private:
	const char*	arffFileName;
	Instances*	dataset;

public:
	// Constructors;
	ArffReader (const char* arffFileName);

	// Destructors;
	~ArffReader();
	
	// Getters;
	Instances* getData();

	// Methods;
	void read();
};