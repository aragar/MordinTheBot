#pragma once
#include "Instance.h"
#include "Instances.h"

#include "Filter.h"

#include <vector>

class TraceRetriever
{
private:
	std::vector<Instances*>*	games;
	int							k;

	static const double			e;

	// Helpers;
	class Triple
	{
	public:
		Instances*	game;
		double		dist;
		int			index;

		Triple();
		Triple(Instances* game, double dist, int index);
	};

	void		insertGame(std::vector<Triple>& nearestGames, Instances* game, double dist, int index);
	Triple	chooseRandomly(GameEncoder* encoder, std::vector<Triple>& nearestGames);
public:
	// Constructors;
	TraceRetriever(std::vector<Instances*>* games, int k = 1);

	// Methods;
	std::vector<char*> getPlan(GameEncoder* encoder, Instance* instance, Filter* filter, int moves);
};