#include <string>
#include <cstring>
#include <vector>

class Attribute
{
private:
	char*	name;
	int		type;
	double	weight;

	std::vector<char*> values;
public:
	static const enum {NUMERIC, NOMINAL, STRING};

	// Constructors
	Attribute();
	Attribute(char* name, int type, double weight = 1.0);
	Attribute(char* name, int type, std::vector<string> values, double weight = 1.0);

	// Getters
	string				getName()					{ return name; }	// TBD: To return copy
	int					getType()					{ return type; }
	double				getWeight()					{ return weight; }
	std::vector<char*>	getValues()					{ return values; }	// TBD: To return copy
	char*				geValueAt(int index)		{ return values[index]; } // TBD: To return copy
	int					getValueIndex(char* value);

	// Setters
	void setWeight(double newWeight)	{ weight = newWeight; }

	// Methods
	bool		isNumeric		();
	bool		isNominal		();
	bool		isString		();
	int			indexOfValue	(char* value);
	int			numValues		();
	std::string	toString		();
	bool		operator==		(Instance* other);
};