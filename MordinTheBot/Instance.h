#pragma once
#include "Instances.h"
#include "Attribute.h"
#include <vector>
#include <string>
#include <cstring>

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
	Attribute*					getAttributeAt		(int index);
	Attribute*					getClassAttribute	();
	int							getClassIndex		();
	double						getClassValue		();
	Instances*					getDataset			();
	std::vector<Attribute*>		getAttributes		();
	char*						getStringValue		(Attribute* attribute);
	char*						getStringValue		(int attrIndex);
	double						getValue			(Attribute* attribute);
	double						getValue			(int attrIndex);
	std::vector<double>			getValues			();
	double						getWeight			();

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
	void		removeAttribute	(int position);
	void		insertAttribute	(int position);
	void		removeValueAt	(int position);
	void		insertValueAt	(int position);
	int			numAttributes	();
	int			numValues		();
	std::string	toString		();
	bool		hasDataset		();
};