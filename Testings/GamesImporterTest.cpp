#include "..\\MordinTheBot\\ArffReader.h"
#include "..\\MordinTheBot\\GameEncoder.h"
#include "..\\MordinTheBot\\Instance.h"
#include "..\\MordinTheBot\\Instances.h"
#include "..\\MordinTheBot\\Attribute.h"
#include "..\\MordinTheBot\\GamesImporter.h"

#include "..\\MordinTheBot\\GeneralBWAPI.h"

#include <vector>

int GamesImporterTest_main()
{
	GameEncoder* encoder = new GameEncoder(&BWAPI::Races::Protoss, &BWAPI::Races::Zerg);
	std::vector<Instances*> games = GamesImporter::loadGames(encoder, "..\\Arffs\\tracesPvZ-Protoss.arff");

	FILE* file = fopen("GamesImporterTest", "w");
	fprintf(file, "Number of games: %d\n", (int)games.size());
	for (int i = 0; i < (int)games.size(); ++i)
		fprintf(file, "Number of instances in game %d: %d\n", i, games[i]->numInstances());

	return 0;
}