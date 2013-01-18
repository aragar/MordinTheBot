#include "ArffReader.h"
#include "Instances.h"

#include <vector>

/* Creates an arff file reader. */
ArffReader::ArffReader(char* arffFileName)
: arffFileName(arffFileName)
{}

/* Destroys the arff reader. */
ArffReader::~ArffReader()
{}

/* Returs the instances dataset, contained in the specified arff file. */
Instances* ArffReader::getData()
{
	return dataset;
}


/* Reads the specified arff file and creates the instances dataset. */
void ArffReader::read()
{
// Open the file;
	FILE* arffFile;
	arffFile = fopen(arffFileName, "r");

// Find the size of the file;
	int fileSize = 0;

	fseek(arffFile, 0, SEEK_END);
	fileSize = ftell(arffFile);
	rewind(arffFile);

// Read the whole file;
	char* arffString = new char[fileSize + 1];
	fread(arffString, 1, fileSize, arffFile);


	char* line;
	char* tmp;
// Find the relation name;
	tmp = strchr(arffString, '\n');
	tmp += strspn(tmp, "\n");
	line = strtok(arffString, "\n");
	arffString = tmp;

	while (strncmp(line, "@relation", strlen("@relation")) != 0)
	{
		tmp = strchr(arffString, '\n');
		tmp += strspn(tmp, "\n");
		line = strtok(arffString, "\n");
		arffString = tmp;
	}
	strtok(line, " ");
	char* relationName = strtok(NULL, " ");


//Find the atributes;
	std::vector<Attribute*> attributes;
	
	tmp = strchr(arffString, '\n');
	tmp += strspn(tmp, "\n");
	line = strtok(arffString, "\n");
	arffString = tmp;
	
	while (strncmp(line, "@attribute", strlen("@attribute")) != 0)
	{
		tmp = strchr(arffString, '\n') + 1;
		line = strtok(arffString, "\n");
		arffString = tmp;
	}

	while (strncmp(line, "@attribute", strlen("@attribute")) == 0)
	{
		strtok(line, " ");

		char* attrName;
		attrName = strtok(NULL, " ");
		
		char* attrType = strtok(NULL, " \0");
		if (attrType[0] != '{')
		{
			if (strcmp (attrType, "numeric") == 0)
				attributes.push_back(new Attribute(attrName, Attribute::NUMERIC));
		}
		else
		{
			++attrType;

			std::vector<char*> values;
			char* value = strtok(attrType, ",}");
			while (value != NULL)
			{
				values.push_back(value);
				value = strtok(NULL, ",}");
			}
			attributes.push_back(new Attribute(attrName, Attribute::NOMINAL, values));
		}

		tmp = strchr(arffString, '\n');
		tmp += strspn(tmp, "\n");
		line = strtok(arffString, "\n");
		arffString = tmp;
	}
	dataset = new Instances(relationName, attributes);
	dataset->setClassIndex(dataset->numAttributes() - 1);


// Find all instances;
	while (strncmp(line, "@data", strlen("@data")) != 0)
	{
		tmp = strchr(arffString, '\n');
		tmp += strspn(tmp, "\n");
		line = strtok(arffString, "\n");
		arffString = tmp;
	}
	
	tmp = strchr(arffString, '\n');
	tmp += strspn(tmp, "\n");
	line = strtok(arffString, "\n");
	arffString = tmp;
	while (line != NULL)
	{
		Instance* instance = new Instance(dataset->numAttributes());
		instance->setDataset(dataset);

		char* value;
		for (int i = 0; i < dataset->numAttributes(); ++i)
		{
			if (i > 0)
				value = strtok(NULL, ",\0");
			else
				value = strtok(line, ",\0");

			switch (dataset->getAttribute(i)->getType())
			{
			case Attribute::NOMINAL:
				instance->setValue(i, value);
				break;
			case Attribute::NUMERIC:
				instance->setValue(i, atof(value));
				break;
			}
		}

		dataset->add(instance);

		tmp = strchr(arffString, '\n');
		if (tmp == NULL)
			break;
		tmp += strspn(tmp, "\n");
		line = strtok(arffString, "\n");
		arffString = tmp;
	}

	fclose(arffFile);
	return;
}