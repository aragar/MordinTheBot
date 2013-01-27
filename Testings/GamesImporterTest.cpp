#include "..\\MordinTheBot\\ArffReader.h"
#include "..\\MordinTheBot\\GameEncoder.h"
#include "..\\MordinTheBot\\Instance.h"
#include "..\\MordinTheBot\\Instances.h"
#include "..\\MordinTheBot\\Attribute.h"
#include "..\\MordinTheBot\\GamesImporter.h"
#include "..\\MordinTheBot\\TraceRetriever.h"
#include "..\\MordinTheBot\\BothUnitsTimingsResearchAndUpgradeFilter.h"
#include "..\\MordinTheBot\\MyUnitsOnlyFilter.h"

#include "..\\MordinTheBot\\GeneralBWAPI.h"

#include <vector>

#include <cstdlib>
#include <ctime>

int main()
{
	GameEncoder* encoder = new GameEncoder(&BWAPI::Races::Protoss, &BWAPI::Races::Zerg);
	std::vector<Instances*> games = GamesImporter::loadGames(encoder, "..\\Arffs\\tracesPvZ-Protoss.arff");

	FILE* file = fopen("GamesImporterTest", "w");
	fprintf(file, "Number of games: %d\n", (int)games.size());
	for (int i = 0; i < (int)games.size(); ++i)
		fprintf(file, "Number of instances in game %d: %d\n", i, games[i]->numInstances());
	fprintf(file, "\n");

	srand( (unsigned)time(NULL) );
	Instances* game = games[rand() % (int)games.size()];
	int index = rand() % game->numInstances();
	Instance* instance = game->getInstance(index);
	fprintf(file, "From trace %d instance %d was chosen\n", (int)instance->getValue(encoder->traceIndex), index);
	printf("Start\n");

	TraceRetriever* retriever = new TraceRetriever(games, 15);
	std::vector<char*> commands = retriever->getPlan(encoder, instance, 
		new BothUnitsTimingsResearchAndUpgradeFilter(encoder), 10);
	fprintf(file, "Commands:\n");
	for (int i = 0; i < 10; ++i)
		fprintf(file, "%d: %s\n", i+1, commands[i]);
	fprintf(file, "\n");
	printf("End\n");
	getchar();

	fclose(file);
	return 0;
}