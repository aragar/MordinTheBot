#pragma once
#include "GameEncoder.h"
#include "Instance.h"

class Filter
{
protected:
	GameEncoder*		encoder;
	static const double	EXP;

public:
	// Constructors;
	Filter(GameEncoder* encoder);

	// Methods
	/* Returns the distance between the two instances */
	virtual double findDistance(Instance* lhs, Instance* rhs) = 0;
};