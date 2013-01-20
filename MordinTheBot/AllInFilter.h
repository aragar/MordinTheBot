#include "Filter.h"
#include "Instance.h"
#include "GameEncoder.h"

#include <cmath>

class AllInFilter : public Filter
{
public:
	// Constructors
	AllInFilter(GameEncoder* encoder)
		: Filter(encoder)
	{}

	// Methods
	/* Returns the Euclidian distance between the feature vectures, i.e.all values except the 
	 * class attribute. */
	double findDistance(Instance* lhs, Instance* rhs)
	{
		double dist = 0.0;

		for (int i = 0; i < encoder->classIndex; ++i)
			dist += (lhs->getValue(i) - rhs->getValue(i)) * (lhs->getValue(i) - rhs->getValue(i));

		dist = sqrt(dist);

		return dist;
	}
};