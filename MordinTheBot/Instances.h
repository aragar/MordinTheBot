#include <vector>
#include <cstring>
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
	Attribute*				getAttribute		(int index);	{ return attributes[index]; }
	Attribute*				getAttribute		(char* name);
	int						getAttributeIndex	(Attribute* attribute);
	std::vector<Attribute*>	getAttributes		()				{ return attributes; }
	Attribute*				getClassAttribute	()				{ return attributes[classIndex]; }
	/* Returns the class attribute's index. Returns negative number if it's undefined. */
	int						getClassIndex		()				{ return classIndex; }
	std::vector<Instance*>	getInstances		()				{ return instances;	 }
	Instance*				getfirstInstance	()				{ return getInstance(0); }
	Instance*				getInstance			(int index)		{ return instances[index]; }
	Instance*				getLastInstance		();
	char*					getRelationName		()				{ return relationName; }

	// Setters
	void	setClass		(Attribute attribute);
	/* Sets the class index of the set. If the class index is negative there is assumed to be no class. 
	 * (ie. it is undefined) */
	void	setClassIndex	(int classIndex)		{ this->classIndex = classIndex; }
	void	setRelationName	(char* name)			{ this->relationName = name; }

	// Methods
	void		add					(Instance instance);
	bool		checkInstance		(Instance* instance);
	void		remove				();
	void		remove				(int index);
	void		removeAttributeAt	(int position);
	void		insertAttributeAt	(Attribute* attribute, int position);
	/* Returns the number of attributes. */
	int			numAttributes		()	{ return attributes.size(); }
	/* Returns the number of instances in the dataset. */
	int			numInstances		()	{ return instances.size(); }
	std::string	toString			();
};