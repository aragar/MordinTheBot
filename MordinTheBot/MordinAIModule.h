#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <Arbitrator.h>
#include <WorkerManager.h>
#include <SupplyManager.h>
#include <BuildManager.h>
#include <BuildOrderManager.h>
#include <TechManager.h>
#include <UpgradeManager.h>
#include <BaseManager.h>
#include <ScoutManager.h>
#include <DefenseManager.h>
#include <InformationManager.h>
#include <BorderManager.h>
#include <UnitGroupManager.h>
#include <EnhancedUI.h>

#include "Instances.h"
#include "GameEncoder.h"
#include "TraceRetriever.h"

#include <boost/thread.hpp>

#include <windows.h>
#include <vector>

class MordinAIModule : public BWAPI::AIModule
{
private:
	bool trained;
	bool planningTime;
	bool planningReturn;
	std::vector<char*> planExtension;

	static void trainCBRThread(GameEncoder* encoder, std::vector<Instances*>* games, TraceRetriever** retriever, 
		bool* trained);
	static void createExtensionPlanThread(std::vector<char*>* pPlanExtension, TraceRetriever* retriever,
		GameEncoder* encoder, Game* game, BuildManager* buildManager, std::vector<Instances*>* games, 
		bool* planningReturn, bool* planningTime);

public:
	virtual void onStart();
	virtual void onEnd(bool isWinner);
	virtual void onFrame();
	virtual void onUnitDiscover(BWAPI::Unit* unit);
	virtual void onUnitEvade(BWAPI::Unit* unit);
	virtual void onUnitMorph(BWAPI::Unit* unit);
	virtual void onUnitRenegade(BWAPI::Unit* unit);
	virtual void onUnitDestroy(BWAPI::Unit* unit);
	virtual void onSendText(std::string text);
	~MordinAIModule(); //not part of BWAPI::AIModule
	void showStats(); //not part of BWAPI::AIModule
	void showPlayers();
	void showForces();

	std::map<BWAPI::Unit*,BWAPI::UnitType> buildings;
	Arbitrator::Arbitrator<BWAPI::Unit*,double> arbitrator;
	WorkerManager* workerManager;
	SupplyManager* supplyManager;
	BuildManager* buildManager;
	TechManager* techManager;
	UpgradeManager* upgradeManager;
	BaseManager* baseManager;
	ScoutManager* scoutManager;
	BuildOrderManager* buildOrderManager;
	DefenseManager* defenseManager;
	InformationManager* informationManager;
	BorderManager* borderManager;
	UnitGroupManager* unitGroupManager;
	EnhancedUI* enhancedUI;

	bool showManagerAssignments;
	bool analyzed;
	bool analysis_just_finished;

	std::vector<Instances*> games;
	GameEncoder* encoder;
	TraceRetriever* retriever;

	BWAPI::Race selfRace;
	BWAPI::Race enemyRace;
};