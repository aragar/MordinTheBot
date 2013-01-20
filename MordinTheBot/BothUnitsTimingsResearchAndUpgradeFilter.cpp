#include "Filter.h"
#include "Instance.h"
#include "GameEncoder.h"

#include <cmath>

class BothUnitsTimingsResearchAndUpgradeFilter : public Filter
{
public:
	// Constructors
	BothUnitsTimingsResearchAndUpgradeFilter(GameEncoder* encoder)
		: Filter(encoder)
	{}

	// Methods
	/* Returns the Euclidian distance between the subintances consisting of both
	 * players' units, timings, research, and upgrades. */
	double findDistance(Instance* lhs, Instance* rhs)
	{
		double dist = 0.0;

		for (int i = encoder->selfTypeIndex; i < encoder->classIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i));

		dist = sqrt(dist);

		return dist;
	}
};