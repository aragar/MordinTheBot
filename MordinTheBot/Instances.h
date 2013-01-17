#pragma once
#include <vector>
#include <cstring>
#include <string>
#include "Attribute.h"

class Instance;

class Instances
{
private:
	char*					relationName;
	std::vector<Attribute*>	attributes;
	std::vector<Instance*>	instances;
	int						classIndex;

public:
	// Constructors
	Instances(char* relationName, std::vector<Attribute*>& attributes, int capacity = 0);
	Instances(Instances* dataset);
	Instances(Instances& dataset);

	// Getters
	Attribute*				getAttribute		(int index);
	Attribute*				getAttribute		(char* name);
	int						getAttributeIndex	(Attribute* attribute);
	std::vector<Attribute*>	getAttributes		();
	Attribute*				getClassAttribute	();
	int						getClassIndex		();
	std::vector<Instance*>	getInstances		();
	Instance*				getfirstInstance	();
	Instance*				getInstance			(int index);
	Instance*				getLastInstance		();
	char*					getRelationName		();

	// Setters
	void	setClass		(Attribute* attribute);
	void	setClassIndex	(int newClassIndex);
	void	setRelationName	(char* newRelationName);

	// Methods
	void		add					(Instance* instance);
	bool		checkInstance		(Instance* instance);
	void		remove				();
	void		remove				(int index);
	void		removeAttributeAt	(int position);
	void		insertAttributeAt	(Attribute* attribute, int position);
	int			numAttributes		();
	int			numInstances		();
	std::string	toString			();
};