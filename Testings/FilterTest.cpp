#include "..\\MordinTheBot\\ArffReader.h"
#include "..\\MordinTheBot\\MyUnitsOnlyFilter.h"
#include "..\\MordinTheBot\\GameEncoder.h"
#include "..\\MordinTheBot\\Instance.h"
#include "..\\MordinTheBot\\Instances.h"
#include "..\\MordinTheBot\\Attribute.h"

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "..\\MordinTheBot\\GeneralBWAPI.h"

int FilterTest_main()
{
	FILE* file = fopen("filterTest", "w");

	ArffReader* arffReader = new ArffReader("..\\Arffs\\tracesPvZ-Protoss.arff");

	arffReader->read();
	Instances* dataset = arffReader->getData();

	srand( (unsigned int)time(NULL) );
	int numInstances = dataset->numInstances();

	int ind1 = rand()%numInstances;
	int ind2 = rand()%numInstances;
	Instance* inst1 = dataset->getInstance(ind1);
	Instance* inst2 = dataset->getInstance(ind2);

	std::string inst1String = inst1->toString();
	const char* inst1CharStar = inst1String.c_str();

	std::string inst2String = inst2->toString();
	const char* inst2CharStar = inst2String.c_str();

	fprintf(file, "inst1 %d: %s\n\n", ind1, inst1CharStar);
	fprintf(file, "inst2 %d: %s\n\n", ind2, inst2CharStar);

	GameEncoder* encoder = new GameEncoder(&BWAPI::Races::Protoss, &BWAPI::Races::Zerg);
	MyUnitsOnlyFilter* filter = new MyUnitsOnlyFilter(encoder);
	fprintf(file, "Dist: %lf\n", filter->findDistance(inst1, inst2));

	fclose(file);

	return 0;
}