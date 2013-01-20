#include "GameEncoder.h"

#include <cstring>
#include <string>
#include <sstream>

GameEncoder::GameEncoder(const Race* self, const Race* enemy)
: self(self),
enemy(enemy), 
mapIndex(0),
winIndex(1),
traceIndex(2),
cycleIndex(3)
{
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Corsair.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Dark_Templar.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Dark_Archon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Probe.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Zealot.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Dragoon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_High_Templar.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Archon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Shuttle.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Scout.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Arbiter.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Carrier.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Interceptor.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Reaver.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Observer.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Scarab.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Nexus.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Robotics_Facility.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Pylon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Assimilator.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Observatory.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Gateway.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Photon_Cannon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Citadel_of_Adun.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Cybernetics_Core.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Templar_Archives.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Forge.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Stargate.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Fleet_Beacon.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Arbiter_Tribunal.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Robotics_Support_Bay.getID()));
	selfTypes.push_back(new UnitType(UnitTypes::Protoss_Shield_Battery.getID()));
	
	selfResearches.push_back(new TechType(TechTypes::Psionic_Storm.getID()));
	selfResearches.push_back(new TechType(TechTypes::Hallucination.getID()));
	selfResearches.push_back(new TechType(TechTypes::Recall.getID()));
	selfResearches.push_back(new TechType(TechTypes::Stasis_Field.getID()));
	selfResearches.push_back(new TechType(TechTypes::Archon_Warp.getID()));
	selfResearches.push_back(new TechType(TechTypes::Disruption_Web.getID()));
	selfResearches.push_back(new TechType(TechTypes::Mind_Control.getID()));
	selfResearches.push_back(new TechType(TechTypes::Dark_Archon_Meld.getID()));
	selfResearches.push_back(new TechType(TechTypes::Feedback.getID()));
	selfResearches.push_back(new TechType(TechTypes::Maelstrom.getID()));
	
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Protoss_Ground_Armor.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Protoss_Air_Armor.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Protoss_Ground_Weapons.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Protoss_Air_Weapons.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Protoss_Plasma_Shields.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Singularity_Charge.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Leg_Enhancements.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Scarab_Damage.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Reaver_Capacity.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Carrier_Capacity.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Gravitic_Drive.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Sensor_Array.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Gravitic_Boosters.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Khaydarin_Amulet.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Apial_Sensors.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Gravitic_Thrusters.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Khaydarin_Core.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Argus_Jewel.getID()));
	selfUpgrades.push_back(new UpgradeType(UpgradeTypes::Argus_Talisman.getID()));


	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Larva.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Egg.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Zergling.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Hydralisk.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Ultralisk.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Broodling.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Drone.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Overlord.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Mutalisk.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Guardian.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Queen.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Defiler.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Scourge.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Infested_Terran.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Cocoon.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Devourer.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Lurker_Egg.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Lurker.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Infested_Command_Center.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Hatchery.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Lair.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Hive.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Nydus_Canal.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Hydralisk_Den.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Defiler_Mound.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Greater_Spire.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Queens_Nest.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Evolution_Chamber.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Ultralisk_Cavern.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Spire.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Spawning_Pool.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Creep_Colony.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Spore_Colony.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Sunken_Colony.getID()));
	enemyTypes.push_back(new UnitType(UnitTypes::Zerg_Extractor.getID()));

	enemyResearches.push_back(new TechType(TechTypes::Burrowing.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Infestation.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Spawn_Broodlings.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Dark_Swarm.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Plague.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Consume.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Ensnare.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Parasite.getID()));
	enemyResearches.push_back(new TechType(TechTypes::Lurker_Aspect.getID()));

	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Zerg_Carapace.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Zerg_Flyer_Carapace.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Zerg_Melee_Attacks.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Zerg_Missile_Attacks.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Zerg_Flyer_Attacks.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Chitinous_Plating.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Anabolic_Synthesis.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Ventral_Sacs.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Antennae.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Pneumatized_Carapace.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Metabolic_Boost.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Adrenal_Glands.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Muscular_Augments.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Grooved_Spines.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Gamete_Meiosis.getID()));
	enemyUpgrades.push_back(new UpgradeType(UpgradeTypes::Metasynaptic_Node.getID()));



// Build the instances attributes;
	char* relationName = "StarCraftGameState";
	std::vector<Attribute*> attributes;
	std::vector<char*> labels;

	attributes.push_back(new Attribute("Map"));
	attributes.push_back(new Attribute("Won"));
	attributes.push_back(new Attribute("TraceID"));
	attributes.push_back(new Attribute("Cycle"));

	selfTypeIndex = (int)attributes.size();
	for (int i = 0; i < (int)selfTypes.size(); ++i)
	{
		UnitType* type = selfTypes[i];
		std::string attrName = type->getName() + "Count";

		selfTypeMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	selfTimingIndex = (int)attributes.size();
	for (int i = 0; i < (int)selfTypes.size(); ++i)
	{
		UnitType* type = selfTypes[i];
		std::string attrName = type->getName() + "Timing";

		selfTimingMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	selfResearchIndex = (int)attributes.size();
	for (int i = 0; i < (int)selfResearches.size(); ++i)
	{
		TechType* type = selfResearches[i];
		std::string attrName = type->getName();

		selfResearchMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	selfUpgradeIndex = (int)attributes.size();
	for (int i = 0; i < (int)selfUpgrades.size(); ++i)
	{
		UpgradeType* type = selfUpgrades[i];
		std::string attrName = type->getName();

		selfResearchMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}


	enemyTypeIndex = (int)attributes.size();
	for (int i = 0; i < (int)enemyTypes.size(); ++i)
	{
		UnitType* type = enemyTypes[i];
		std::string attrName = type->getName() + "Count";

		enemyTypeMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	enemyTimingIndex = (int)attributes.size();
	for (int i = 0; i < (int)enemyTypes.size(); ++i)
	{
		UnitType* type = enemyTypes[i];
		std::string attrName = type->getName() + "Timing";

		enemyTimingMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	enemyResearchIndex = (int)attributes.size();
	for (int i = 0; i < (int)enemyResearches.size(); ++i)
	{
		TechType* type = enemyResearches[i];
		std::string attrName = type->getName();

		enemyResearchMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	enemyUpgradeIndex = (int)attributes.size();
	for (int i = 0; i < (int)enemyUpgrades.size(); ++i)
	{
		UpgradeType* type = enemyUpgrades[i];
		std::string attrName = type->getName();

		enemyResearchMap[type->getID()] = (int)attributes.size();
		attributes.push_back(new Attribute(attrName.c_str()));
	}

	for (int i = selfTypeIndex; i < (int)attributes.size(); ++i)
	{
		char* tmp = new char[strlen(attributes[i]->getName()) + 1];
		strcmp(tmp, attributes[i]->getName());
		labels.push_back(tmp);
	}

	classIndex = (int)attributes.size();
	attributes.push_back(new Attribute("Label", Attribute::NOMINAL, labels));


	dataset = new Instances(relationName, attributes);
	dataset->setClassIndex(classIndex);

	
	lastInstance = new Instance(dataset->numAttributes());
	lastInstance->setDataset(dataset);
}


/* Returns the current game state encoding. */
Instance* GameEncoder::encodeGame(Game* game, BuildManager* buildManager)
{
	//Player* selfPlayer = game->self();
	//Player* enemyPlayer = game->enemy();

	//Instance* instance = new Instance(lastInstance);
	//instance->setDataset(dataset);

	//// Sets fundamentals;
	//instance->setValue(mapIndex, 0.0);
	//instance->setValue(winIndex, 0.0);
	//instance->setValue(traceIndex, 0.0);
	//instance->setValue(cycleIndex, (double)game->getFrameCount());

	//// Sets self units;
	//for (int i = 0; i < (int)selfTypes.size(); ++i)
	//{
	//	UnitType* type = selfTypes[i];
	//	int count = selfPlayer->allUnitCount(*type);
	//	// planned;
	//	count += buildManager->getCompletedCount(*type) -
	//		buildManager->getStartedCount(*type);

	//	instance->setValue(selfTypeMap[type->getID()], count);

	//	if (count > 0 && lastInstance->getValue(selfTimingMap[type->getID()]) == 0)
	//		instance->setValue(selfTimingMap[type->getID()], (double)game->getFrameCount());
	//}

	//// Sets self researches;
	//for (int i = 0; i < (int)selfResearches.size(); ++i)
	//{
	//	TechType* type = selfResearches[i];
	//	if (lastInstance->getValue(selfResearchMap[type->getID()]) == 0)
	//		if (selfPlayer->hasResearched(*type) == true)
	//			instance->setValue(selfResearchMap[type->getID()], (double)game->getFrameCount());
	//}

	//// Sets self upgrades;
	//for (int i = 0; i < (int)selfUpgrades.size(); ++i)
	//{
	//	UpgradeType* type = selfUpgrades[i];
	//	if (lastInstance->getValue(selfUpgradeMap[type->getID()]) == 0)
	//		if (selfPlayer->getUpgradeLevel(*type) > 0)
	//			instance->setValue(selfUpgradeMap[type->getID()], (double)game->getFrameCount());
	//}


	//// Sets enemy units;
	//for (int i = 0; i < (int)enemyTypes.size(); ++i)
	//{
	//	UnitType* type = enemyTypes[i];
	//	int count = enemyPlayer->allUnitCount(*type);
	//	// planned;
	//	count += buildManager->getCompletedCount(*type) -
	//		buildManager->getStartedCount(*type);
	//	
	//	instance->setValue(enemyTypeMap[type->getID()], count);

	//	if (count > 0 && lastInstance->getValue(enemyTimingMap[type->getID()]) == 0)
	//		instance->setValue(enemyTimingMap[type->getID()], (double)game->getFrameCount());
	//}

	//// Sets enemy researches;
	//for (int i = 0; i < (int)enemyResearches.size(); ++i)
	//{
	//	TechType* type = enemyResearches[i];
	//	if (lastInstance->getValue(enemyResearchMap[type->getID()]) == 0)
	//		if (enemyPlayer->hasResearched(*type) == true)
	//			instance->setValue(enemyResearchMap[type->getID()], (double)game->getFrameCount());
	//}

	//// Sets enemy upgrades;
	//for (int i = 0; i < (int)enemyUpgrades.size(); ++i)
	//{
	//	UpgradeType* type = enemyUpgrades[i];
	//	if (lastInstance->getValue(enemyUpgradeMap[type->getID()]) == 0)
	//		if (enemyPlayer->getUpgradeLevel(*type) > 0)
	//			instance->setValue(enemyUpgradeMap[type->getID()], (double)game->getFrameCount());
	//}

	//lastInstance = instance;
	//return instance;

	return new Instance(3);
}

/* Returns a string representation of the state. */
std::string GameEncoder::toString(Instance* instance)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);

	if (instance == NULL)
		instance = lastInstance;

	int numAttributes = dataset->numAttributes() - 1;
	for (int i = 0; i < numAttributes; ++i)
		ss << (int)instance->getValue(i) << ",";

	std::string s;
	ss >> s;

	return s;
}