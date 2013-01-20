#pragma once

#include "Instance.h"
#include "Instances.h"
#include "Attribute.h"

#include "GeneralBWAPI.h"

#include <vector>
#include <set>
#include <map>
#include <string>

using namespace BWAPI;

class GameEncoder
{
private:
	const Race*	self;
	const Race*	enemy;

	Instance*	lastInstance;

	std::vector<UnitType*>		selfTypes;
	std::vector<TechType*>		selfResearches;
	std::vector<UpgradeType*>	selfUpgrades;
	std::vector<UnitType*>		enemyTypes;
	std::vector<TechType*>		enemyResearches;
	std::vector<UpgradeType*>	enemyUpgrades;

public:
	Instances*			dataset;

	std::map<int, int>	selfTypeMap;
	std::map<int, int>	selfTimingMap;
	std::map<int, int>	selfResearchMap;
	std::map<int, int>	selfUpgradeMap;
	std::map<int, int>	enemyTypeMap;
	std::map<int, int>	enemyTimingMap;
	std::map<int, int>	enemyResearchMap;
	std::map<int, int>	enemyUpgradeMap;

	int	selfTypeIndex;
	int	selfTimingIndex;
	int	selfResearchIndex;
	int	selfUpgradeIndex;
	int enemyTypeIndex;
	int	enemyTimingIndex;
	int enemyResearchIndex;
	int enemyUpgradeIndex;
	int classIndex;

	int mapIndex;
	int winIndex;
	int traceIndex;
	int cycleIndex;

	// Constructors;
	GameEncoder(const Race* self, const Race* enemy);

	// Methods;
	Instance*	encodeGame(Game* game, BuildManager* buildManager);
	std::string	toString(Instance* instance = NULL);
};