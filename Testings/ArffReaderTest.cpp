#include "..\\MordinTheBot\\ArffReader.h"


#include <cstdio>

void printDataset(Instances* dataset);

int ArffReaderTest_main()
{
	ArffReader* arffReader = new ArffReader("..\\Arffs\\tracesPvZ-Protoss.arff");

	arffReader->read();
	Instances* dataset = arffReader->getData();

	return 0;
}

void printDataset(Instances* dataset)
{
	// Print test;
	FILE* file;
	file = fopen("test.out", "w");
	{
		// fprintf(file, "%s", arffString);
		fprintf(file, "@relation %s\n\n", dataset->getRelationName());
		for (int i = 0; i < dataset->numAttributes(); ++i)
		{
			fprintf(file, "@attribute %s ", dataset->getAttribute(i)->getName());
			if (dataset->getAttribute(i)->getType() == Attribute::NOMINAL)
			{
				fprintf(file, "{");
				for (int j = 0; j < dataset->getAttribute(i)->numValues(); ++j)
				{
					if (j > 0)
						fprintf(file, ",");
					fprintf(file, "%s", dataset->getAttribute(i)->getValueAt(j));
				}
				fprintf(file, "}");
			}
			else
				fprintf(file, "%s", dataset->getAttribute(i)->getStringType());
			fprintf(file, "\n");
		}
		fprintf(file, "\n@data\n");
		for (int i = 0; i < dataset->numInstances(); ++i)
		{
			for (int j = 0; j < dataset->getInstance(i)->numValues(); ++j)
			{
				if (j > 0)
					fprintf(file, ",");

				if (dataset->getAttribute(j)->getType() == Attribute::NUMERIC)
					fprintf(file, "%d", (int)dataset->getInstance(i)->getValue(j));
				else
					fprintf(file, "%s", dataset->getInstance(i)->getStringValue(j));
			}
			fprintf(file, "\n");
		}

	}
	fclose(file);
}