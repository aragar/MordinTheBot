#pragma once
#include <windows.h>

#include <BuildManager.h>

DWORD WINAPI UpdatePlanThread(LPVOID lpParam);

class TheGreatMind()
{
private:

public:
	void updatePlan(BuildManager* buildManager);
};