#include "Instances.h"
#include "Attribute.h"
#include <vector>
#include <string>

class Instance 
{
private:
	Instances* dataset;
	std::vector<double> values;
	double weight;

	
public:
	// Constructors
	Instance	(Instance* instance);
	Instance	(Instance& instance);
	Instance	(double weight, std::vector<double>& values);
	Instance	(int numAttributes);

	// Getters
	Attribute*					getAttributeAt		(int index)				{ return dataset->getAttribute(index); }
	Attribute*					getClassAttribute	()						{ return dataset->getClassAttribute(); }
	int							getClassIndex		()						{ return dataset->getClassIndex(); }
	double						getClassValue		()						{ return values[getClassIndex()]; }
	Instances*					getDataset			()						{ return dataset; }
	std::vector<Attribute*>		getAttributes		()						{ return dataset->getAtributes(); }
	char*						getStringValue		(Attribute* attribute)  { return getStringValue(dataset->getAttributeIndex(attribute)); }
	char*						getStringValue		(int attrIndex);
	double						getValue			(Attribute* attribute)	{ return getValue(dataset->getAttributeIndex(attribute)); }
	double						getValue			(int attrIndex)			{ return values[attrIndex]; }
	std::vector<double>			getValues			()						{ return values; }
	double						getWeight			()						{ return weight; }

	// Setters
	void	setClassValue	(double value);
	void	setClassValue	(char* value);
	void	setDataset		(Instances* dataset);
	void	setValue		(Attribute* attribute, double value);
	void	setValue		(Attribute* attribute, char* value);
	void	setValue		(int attrIndex, double value);
	void	setValue		(int attrIndex, char* value);
	void	setWeight		(double weight);

	// Methods
	void		removeAttributeAt	(int position);
	int			numAttributes		();
	int			numValues			();
	std::string	toString			();
};