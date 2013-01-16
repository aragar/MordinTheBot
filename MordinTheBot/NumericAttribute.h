#include <Attribute.h>

class NumericAttribute : public Attribute
{
private:
	double value;

public:
	NumericAttribute(string& name)
		: Attribute(name, NUMERIC)
	{};

	NumericAttribute(string& name, double value)
		: Attribute(name, NUMERIC),
		value(value)
	{};

	double	getValue()	{ return value; }

	void	setValue(double newValue)	{ value = newValue; }
};