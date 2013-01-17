#pragma once
#include <string>
#include <cstring>
#include <vector>

class Attribute
{
private:
	char*	name;
	int		type;
	double	weight;

	std::vector<char*> values; // for NOMINAL attributes
public:
	static const enum {NUMERIC, NOMINAL, STRING};

	// Constructors
	Attribute(char* name);
	Attribute(char* name, int type, double weight = 1.0);
	Attribute(char* name, int type, std::vector<char*> values, double weight = 1.0);

	// Getters
	char*				getName();
	int					getType();
	char*				getStringType();
	double				getWeight();
	std::vector<char*>	getValues();
	char*				getValueAt(int index);

	// Setters
	void setWeight	(double newWeight);
	void setValue	(int index, char* value);

	// Methods
	bool		isNominal		();
	bool		isNumeric		();
	bool		isString		();
	int			indexOfValue	(char* value);
	int			numValues		();
	std::string	toString		();
	bool		operator==		(Attribute* other);
	void		addValue		(char* value);
	void		addValue		(int index, char* value);
	void		removeValue		();
	void		removeValue		(int index);
};