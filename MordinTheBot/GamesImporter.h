#pragma once
#include "Instance.h"
#include "Instances.h"
#include "Attribute.h"

#include "GameEncoder.h"
#include "ArffReader.h"

#include "..//Addons//Util.h"

#include <vector>
#include <map>

class GamesImporter
{
public:
	/* Loads a list of all games in the specified file. */
	static std::vector<Instances*> loadGames(GameEncoder* encoder, const char* filename)
	{
		// All instances;
		Instances* allGames = new Instances(new ArffReader(filename));

		// Groups instances by trace id;
		log("Start grouping the instances...\n");
		std::map<int, Instances*> traces;
		for (int i = 0; i < allGames->numInstances(); ++i)
		{
			Instance* instance = allGames->getInstance(i);
			int traceId = (int)instance->getValue(encoder->traceIndex);

			std::map<int, Instances*>::iterator trace = traces.find(traceId);
			if (trace == traces.end())
			{
				Instances* instances = new Instances(allGames->getRelationName(), 
					allGames->getAttributes());
				instances->setClassIndex(allGames->getClassIndex());

				trace = traces.insert(std::pair<int, Instances*>(traceId, instances)).first;
			}

			trace->second->add(instance);
		}

		// Create the list;
		std::vector<Instances*> games;
		for (std::map<int, Instances*>::iterator it = traces.begin(); it != traces.end(); ++it)
			games.push_back(it->second);

		log("End grouping the instances...\nNumber of games %d\n", (int)games.size());

		return games;
	}
};