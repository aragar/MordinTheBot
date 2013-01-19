#pragma once
#include <string>
#include <cstring>
#include <vector>

class Attribute
{
private:
	const char*	name;
	const int	type;
	double		weight;
	int			index;

	std::vector<char*> values; // for NOMINAL attributes
public:
	static const enum {NUMERIC, NOMINAL, STRING};

	// Constructors
	Attribute(const char* name);
	Attribute(const char* name, const int type, double weight = 1.0);
	Attribute(const char* name, const int type, std::vector<char*>& values, double weight = 1.0);

	// Getters
	const char*			getName();
	const int			getType();
	char*				getStringType();
	double				getWeight();
	std::vector<char*>	getValues();
	char*				getValueAt(int index);
	int					getIndex();

	// Setters
	void	setWeight	(double newWeight);
	void	setValue	(int index, char* value);
	void	setIndex	(int index);

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