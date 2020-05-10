#pragma once
#include "Game.h"
#include "Map.h"
#include "FloodFillService.h"
#include <random>

class ReactAgent
{
public:
	ReactAgent(Game& game) : game(game), p1(game.players[0]), p2(game.players[1]),
		p2Possible(game.players[1].opponentTracking.possibleCells) {};

	std::string think() {
		std::cerr << "Current pos: " << p1.cell.x << " " << p1.cell.y << std::endl;

		std::string bestAction = "";
		int bestScore = -1000;
		Cell bestPosition;

		std::cerr << p1.cell.neighbors.size() << std::endl;
		for (auto neightbor : p1.cell.neighbors)
		{
			auto toFind = *(neightbor.second);
			auto it = std::find_if(p1.path.begin(), p1.path.end(),
				[&](Cell c) { return c.index() == toFind.index(); });

			if (it != p1.path.end())
				continue;

			int size = FloodFillService::FindOpenArea(Map::GetCell(toFind.x, toFind.y), p1.path);

			std::cerr << "Flood score: " << size << " for: " << neightbor.second->x << " " << neightbor.second->y << std::endl;
			if (size > bestScore)
			{
				bestScore = size;
				std::string s(1, neightbor.first);
				bestAction = MOVE + " " + s;
				bestPosition = *neightbor.second;
			}
		}

		if (!bestAction.empty())
		{
			p1.torpedoCooldown--;
			p1.cell = bestPosition;
			return bestAction + " " + getPower() + " " + getTorpedoTarget();
		}
		p1.path.clear();
		return SURFACE + " " + getTorpedoTarget();
	}

	std::string getPower()
	{
		return TORPEDO;
	}

	std::string getTorpedoTarget()
	{
		if (p1.torpedoCooldown > 0)	return "";

		std::vector<Cell*> shuffledList;
		for (auto c : p1.cell.torpedoTargets)
			shuffledList.push_back(c);
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(shuffledList.begin(), shuffledList.end(), g);

		for (Cell* target : shuffledList)
		{
			if (target->toDamage.find(&p1.cell) != target->toDamage.end()) continue;
			
			bool inRange = false;
			for (Cell* possibleTargetCell : p2Possible)
				if (possibleTargetCell->toDamage.find(&p1.cell) != possibleTargetCell->toDamage.end())
				{
					inRange = true;
					break;
				}

			if (!inRange) continue;

			return "| " + TORPEDO + " " + std::to_string(target->x) + " " + std::to_string(target->y);
		}
		return "";

	}
private:
	Game& game;
	Player& p1;
	Player& p2;
	std::unordered_set<Cell*> p2Possible;

	const std::string TORPEDO = "TORPEDO", MOVE = "MOVE", SURFACE = "SURFACE";
};

