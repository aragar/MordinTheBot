#pragma once
#include "Attribute.h"
#include "Instance.h"
#include "Instances.h"

class ArffReader
{
private:
	char*		arffFileName;
	Instances*	dataset;

public:
	// Constructors;
	ArffReader	(char* arffFileName);

	// Destructors;
	~ArffReader	();
	
	// Getters;
	Instances*	getData();

	// Methods;
	void		read();
};