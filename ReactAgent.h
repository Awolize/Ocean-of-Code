#pragma once
#include "Game.h"
#include <string>
#include <algorithm>

class ReactAgent
{
public:
	ReactAgent(Game game) : game(game), p1(game.players[0]), p2(game.players[1])
	{
	}
	std::string think() {
		std::string bestAction = "";

		for (auto neightbor : p1.cell.neighbors)
		{
			auto toFind = *neightbor.second;
			auto it = std::find_if(p1.path.begin(), p1.path.end(), [&](Cell cell) { return cell.x == toFind.x && cell.y == toFind.y; });
			if (it != p1.path.end())
				continue;

			return "MOVE " + neightbor.first;
		}
		return "SURFACE";
	}
private:
	const Game game;
	const Player p1;
	const Player p2;
};

