#pragma once
#include "GameEncoder.h"
#include "Instance.h"

class Filter
{
protected:
	GameEncoder* encoder;

public:
	// Constructors;
	Filter(GameEncoder* encoder)
		: encoder(encoder)
	{}

	// Methods
	/* Returns the distance between the two instances */
	virtual double findDistance(Instance* lhs, Instance* rhs) = 0;
};