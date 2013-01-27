#include "TraceRetriever.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

#include <vector>

#include "..//Addons//Util.h"


const double TraceRetriever::e = 0.000001;

TraceRetriever::Triple::Triple()
{}

TraceRetriever::Triple::Triple(Instances* game, double dist, int index)
: game(game),
dist(dist),
index(index)
{}


TraceRetriever::TraceRetriever(std::vector<Instances*>* games, int k)
: games(games),
k(k)
{
	log("Init the tracer...\n");
}

/* Inserts the given game at the k-nearest games. */
void TraceRetriever::insertGame(std::vector<Triple>& nearestGames, Instances* game, double dist, int index)
{
	// Get the reciprocal distance, as the difference rises, the probability to be chosen should
	// lower. Add a small constance, due to the 0 difference and Infinity;
	Triple triple(game, 1.0 / (dist + e), index);
	dist = 1.0 / (dist + e);

	int l = -1, r = nearestGames.size();
	while (l + 1 < r)
	{
		int m = (int)((l + r) * 0.5);
		double diff = nearestGames[m].dist - dist;
		if (diff >= e)
			l = m;
		else
			r = m;
	}

	nearestGames.insert(nearestGames.begin() + r, triple);
	if (k < (int)nearestGames.size())
		nearestGames.pop_back();

	return;
}

/* Chooses one game with weighted probability on their difference. */
TraceRetriever::Triple TraceRetriever::chooseRandomly(GameEncoder* encoder, std::vector<Triple>& nearestGames)
{
	int n = nearestGames.size();
	double sum = 0.0;
	for (int i = 0; i < n; ++i)
		sum += nearestGames[i].dist;

	srand( (unsigned)time(NULL));
	double chance = (double)rand() / RAND_MAX;
	chance *= sum;
	int i = rand() % n;
	while (chance > e)
		chance -= nearestGames[i].dist;

	i = (i - 1 + n) % n;
	return nearestGames[i];
}

/* Returns a list of actions' names to be executed. */
std::vector<char*> TraceRetriever::getPlan(GameEncoder* encoder, Instance *instance, Filter *filter, int moves)
{
	log("Trace with k=%d retrieving start...\n", k);

	std::vector<Triple> nearestGames;

	// Finds the k-neareset instaces;
	for (int i = 0; i < (int)games->size(); ++i)
	{
		for (int j = 0; j < (*games)[i]->numInstances() - moves; ++j)
		{
			Instance* curInstance = (*games)[i]->getInstance(j);
			double dist = filter->findDistance(instance, curInstance);

			insertGame(nearestGames, (*games)[i], dist, j);
		}
	}

	// Choose with weighted probability one game;
	Triple theChosen = chooseRandomly(encoder, nearestGames);
	Instances* theGame = theChosen.game;
	int index = theChosen.index;

	log("%s\n", theGame->getInstance(index)->toString().c_str());

	// Write down the class values
	std::vector<char*> commands(moves);
	for (int i = 0; i < moves; ++i)
	{
		Instance* commandInstace = theGame->getInstance(index + i);
		int classIndex = commandInstace->getClassIndex();
		char* command = commandInstace->getStringValue(classIndex);
		commands[i] = command;
	}

	log("End trace retriever end...\n");

	return commands;
}