#include "Filter.h"
#include "Instance.h"
#include "GameEncoder.h"

#include <cmath>

class MyUnitsOnlyFilter : public Filter
{
public:
	// Constructors
	MyUnitsOnlyFilter(GameEncoder* encoder)
		: Filter(encoder)
	{}

	// Methods
	/* Returns the Euclidian distance between the self units subintances. */
	double findDistance(Instance* lhs, Instance* rhs)
	{
		double dist = 0.0;

		for (int i = encoder->selfTypeIndex; i < encoder->selfTimingIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i));
		dist = sqrt(dist);

		return dist;
	}
};