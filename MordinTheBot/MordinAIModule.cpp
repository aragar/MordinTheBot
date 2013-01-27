#include "MordinAIModule.h"
#include "../Addons/Util.h"

#include "Instance.h"
#include "Attribute.h"
#include "Instances.h"
#include "ArffReader.h"
#include "GameEncoder.h"
#include "GamesImporter.h"
#include "TraceRetriever.h"

#include "BothUnitsTimingsResearchAndUpgradeFilter.h"

#include <cstring>

using namespace BWAPI;

void MordinAIModule::onStart()
{
	log("Start\n-----\n");

	this->showManagerAssignments = false;

	if (Broodwar->isReplay()) 
		return;

	// Enable some cheat flags;
	Broodwar->enableFlag(Flag::UserInput);
	Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Read map information into BWTA so terrain analysis can be done in another thread;
	BWTA::readMap();
	BWTA::analyze();
	analysis_just_finished = true;
	analyzed = true;

	// Train the CBR;
	selfRace = Broodwar->self()->getRace();
	enemyRace = Broodwar->enemy()->getRace();
	encoder = new GameEncoder(&selfRace, &enemyRace);
	trained = false;
	boost::thread trainingThread(&MordinAIModule::trainCBRThread, encoder, &games, &retriever, &trained);

	planningTime = false;
	planningReturn = false;
	
	// Managers' initialization;
	this->buildManager       = new BuildManager(&this->arbitrator);
	this->techManager        = new TechManager(&this->arbitrator);
	this->upgradeManager     = new UpgradeManager(&this->arbitrator);
	this->scoutManager       = new ScoutManager(&this->arbitrator);
	this->workerManager      = new WorkerManager(&this->arbitrator);
	this->supplyManager      = new SupplyManager();
	this->baseManager        = new BaseManager();
	this->buildOrderManager  = new BuildOrderManager(this->buildManager,this->techManager,this->upgradeManager,this->workerManager,this->supplyManager);
	this->defenseManager     = new DefenseManager(&this->arbitrator);
	this->informationManager = InformationManager::create();
	this->borderManager      = BorderManager::create();
	this->unitGroupManager   = UnitGroupManager::create();
	this->enhancedUI         = new EnhancedUI();

	this->supplyManager->setBuildManager(this->buildManager);
	this->supplyManager->setBuildOrderManager(this->buildOrderManager);
	this->techManager->setBuildingPlacer(this->buildManager->getBuildingPlacer());
	this->upgradeManager->setBuildingPlacer(this->buildManager->getBuildingPlacer());
	this->workerManager->setBaseManager(this->baseManager);
	this->workerManager->setBuildOrderManager(this->buildOrderManager);
	this->baseManager->setBuildOrderManager(this->buildOrderManager);
	this->baseManager->setBorderManager(this->borderManager);
	this->defenseManager->setBorderManager(this->borderManager);
}

MordinAIModule::~MordinAIModule()
{
	delete this->buildManager;
	delete this->techManager;
	delete this->upgradeManager;
	delete this->scoutManager;
	delete this->workerManager;
	delete this->supplyManager;
	delete this->buildOrderManager;
	delete this->baseManager;
	delete this->defenseManager;
	InformationManager::destroy();
	BorderManager::destroy();
	UnitGroupManager::destroy();
	delete this->enhancedUI;
}

void MordinAIModule::onEnd(bool isWinner)
{
	log("onEnd(%d)\n", isWinner);

	return;
}

void MordinAIModule::onFrame()
{
	if (Broodwar->isReplay()) 
		return;

	if (!this->analyzed) 
		return;

	this->buildManager->update();
	this->buildOrderManager->update();
	this->baseManager->update();
	this->workerManager->update();
	this->techManager->update();
	this->upgradeManager->update();
	this->supplyManager->update();
	this->scoutManager->update();
	this->enhancedUI->update();
	this->borderManager->update();
	this->defenseManager->update();
	this->arbitrator.update();

	if (Broodwar->getFrameCount() % 48 == 0)
		Broodwar->printf("Plan size: %d\n", buildOrderManager->getPlanSize());

	if (buildOrderManager->getPlanSize() < 3 && trained && !planningTime && !planningReturn)
	{
		planningTime = true;

		boost::thread planningThread(&MordinAIModule::createExtensionPlanThread, &planExtension, retriever, 
		encoder, Broodwar, buildManager, &games, &planningReturn, &planningTime);
	}

	if (planningReturn && !planningTime && trained)
	{
		for (int i = 0; i < (int)planExtension.size(); ++i)
		{
			char* command = planExtension[i];
			int commandLen = strlen(command);
			

			if (strncmp(command + commandLen - strlen("Count"), "Count", strlen("Count")) == 0)
			{
				std::string unit(command);
				unit.erase(unit.size() - strlen("Count"), strlen("Count"));

				if (strncmp(command, "Protoss_Nexus", strlen("Protoss_Nexus")) == 0)
				{
					baseManager->expand(80 - i);
					continue;
				}

				log("Unit: %s\n", unit.c_str());
				buildOrderManager->buildAdditional(1, UnitTypes::getUnitType(unit), 80 - i);
			}
			else if (TechTypes::getTechType(std::string(command)) != TechTypes::Unknown)
				buildOrderManager->research(TechTypes::getTechType(std::string(command)), 80 - i);
			else
			{
				UpgradeType upgrade = UpgradeTypes::getUpgradeType(std::string(command));
				buildOrderManager->upgrade(upgradeManager->getCompletedLevel(upgrade) + 1, upgrade, 80 - i);
			}
		}

		planningReturn = false;
	}
	

	std::set<Unit*> units = Broodwar->self()->getUnits();
	if (this->showManagerAssignments)
	{
		for(std::set<Unit*>::iterator i=units.begin(); i != units.end(); ++i)
		{
			if (this->arbitrator.hasBid(*i))
			{
				int x = (*i)->getPosition().x();
				int y = (*i)->getPosition().y();
				std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*, double>*, double> > bids = this->arbitrator.getAllBidders(*i);
				int y_off = 0;
				bool first = false;
				const char activeColor = '\x07', inactiveColor = '\x16';
				char color = activeColor;

				for(std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*,double>*, double> >::iterator j=bids.begin(); j != bids.end(); ++j)
				{
					Broodwar->drawTextMap(x, y + y_off, "%c%s: %d", color, j->first->getShortName().c_str(), (int)j->second);
					y_off += 15;
					color = inactiveColor;
				}
			}
		}
	}

	return;
}

void MordinAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) 
		return;

	this->arbitrator.onRemoveObject(unit);
	this->buildManager->onRemoveUnit(unit);
	this->techManager->onRemoveUnit(unit);
	this->upgradeManager->onRemoveUnit(unit);
	this->workerManager->onRemoveUnit(unit);
	this->scoutManager->onRemoveUnit(unit);
	this->defenseManager->onRemoveUnit(unit);
	this->informationManager->onUnitDestroy(unit);
	this->baseManager->onRemoveUnit(unit);

	return;
}

void MordinAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) 
		return;
  
	this->informationManager->onUnitDiscover(unit);
	this->unitGroupManager->onUnitDiscover(unit);

	return;
}

void MordinAIModule::onUnitEvade(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) 
		return;

	this->informationManager->onUnitEvade(unit);
	this->unitGroupManager->onUnitEvade(unit);

	return;
}

void MordinAIModule::onUnitMorph(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) 
		return;

	this->unitGroupManager->onUnitMorph(unit);

	return;
}
void MordinAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) 
		return;

	this->unitGroupManager->onUnitRenegade(unit);

	return;
}

void MordinAIModule::onSendText(std::string text)
{
	if (Broodwar->isReplay())
	{
		Broodwar->sendText("%s", text.c_str());

		return;
	}

	UnitType type = UnitTypes::getUnitType(text);
  
	if (text == "debug")
	{
		if (this->showManagerAssignments == false)
		{
			this->showManagerAssignments = true;
			this->buildOrderManager->setDebugMode(true);
			this->scoutManager->setDebugMode(true);
		}
		else
		{
			this->showManagerAssignments = false;
			this->buildOrderManager->setDebugMode(false);
			this->scoutManager->setDebugMode(false);
		}

		Broodwar->printf("%s", text.c_str());

		return;
	}

	if (text == "expand")
	{
		this->baseManager->expand();
		Broodwar->printf("%s", text.c_str());

		return;
	}

	if (type != UnitTypes::Unknown)
	{
		this->buildOrderManager->buildAdditional(1, type, 300);
	}

	else
	{
		TechType type = TechTypes::getTechType(text);

		if (type != TechTypes::Unknown)
			this->techManager->research(type);

		else
		{
			UpgradeType type = UpgradeTypes::getUpgradeType(text);
			
			if (type != UpgradeTypes::Unknown)
				this->upgradeManager->upgrade(type);

			else
				Broodwar->printf("You typed '%s'!", text.c_str());
		}
	}

	Broodwar->sendText("%s",text.c_str());

	return;
}


void MordinAIModule::trainCBRThread(GameEncoder* encoder, std::vector<Instances*>* pGames, TraceRetriever** pRetriever,
									bool* trained)
{
	log("TrainCBRThread start...\n");
	
	*pGames = GamesImporter::loadGames(encoder, "bwapi-data\\arffs\\tracesPvZ-Protoss.arff");
	*pRetriever = new TraceRetriever(pGames);
	*trained = true;

	log("TrainCBRThread end...\n");

	return;
}

void MordinAIModule::createExtensionPlanThread(std::vector<char*>* planExtension, TraceRetriever* retriever,
											   GameEncoder* encoder, BWAPI::Game* game, BuildManager* buildManager,
											   std::vector<Instances*>* games, bool* planningReturn, bool* planingTime)
{
	log("Start creating extension plan...\n");

	Instance* curInstance = encoder->encodeGame(game, buildManager);
	*planExtension = retriever->getPlan(encoder, curInstance, new BothUnitsTimingsResearchAndUpgradeFilter(encoder), 10);
	*planningReturn = true;
	*planingTime = false;

	for (int i = 0; i < (int)planExtension->size(); ++i)
		log("Step %d: %s\n", i, (*planExtension)[i]);

	log("End creating extension plan...\n");

	return;
}