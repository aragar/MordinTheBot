#include "Filter.h"
#include "Instance.h"
#include "GameEncoder.h"

#include <cmath>

class BothUnitsAndTimingsOnlyFilter : public Filter
{
public:
	// Constructors
	BothUnitsAndTimingsOnlyFilter(GameEncoder* encoder)
		: Filter(encoder)
	{}

	// Methods
	/* Returns the Euclidian distance between the subintances consisting of both
	 * players' units and timings. */
	double findDistance(Instance* lhs, Instance* rhs)
	{
		double dist = 0.0;

		for (int i = encoder->selfTypeIndex; i < encoder->selfTimingIndex ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i));
		for (int i = encoder->selfTimingIndex; i < encoder->selfResearchIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i)) * EXP;

		for (int i = encoder->enemyTypeIndex; i < encoder->enemyTimingIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i));
		for (int i = encoder->enemyTimingIndex; i < encoder->enemyResearchIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i)) * EXP;

		dist = sqrt(dist);

		return dist;
	}
};