#pragma once
#include <unordered_set>
#include <sstream>
#include <string>
#include "Const.h"

class OpponentTrackingService
{
public:
	void track(std::string command) {
		std::vector<std::string> commands;
		{
			std::stringstream ss(command);
			std::string token;
			while (std::getline(ss, token, '|')) {
				commands.push_back(token);
			}
		}

		for (auto cmd : commands)
		{
			std::vector<std::string> cmdPart;
			std::stringstream ss(command);
			std::string token;
			while (std::getline(ss, token, ' ')) {
				cmdPart.push_back(token);
			}

			if (find(cmdPart.begin(), cmdPart.end(), "MOVE") != cmdPart.end())
			{
				char dir = cmdPart[1][0];
				std::cerr << "enemy went: " << dir << std::endl;
				power++;
				trackMovement(dir);
			}
			else if (find(cmdPart.begin(), cmdPart.end(), "SILENCE") != cmdPart.end())
			{
				trackSilence();
			}
		}
		std::cerr << "Possible: " << possibleCells.size() << std::endl;
		if (possibleCells.size() < 5)
		{
			for (auto c : possibleCells)
				std::cerr << c->x << " " << c->y << " or ";
			std::cerr << std::endl;
		}
	}

private:
	void trackSilence()
	{
		std::unordered_set<Cell*> next;
		for (auto c : possibleCells)
		{
			for (auto dir : c->neighbors)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (!c->canMove(dir.first, i)) break;
					Cell* endpoint = c->move(dir.first, i);
					next.insert(endpoint);
				}
			}
		}
		possibleCells = next;
	}
	void trackMovement(char dir)
	{
		std::unordered_set<Cell*> next;
		for (auto c : possibleCells)
		{
			for (auto neigh : c->neighbors)
			{
				if (neigh.first != dir)
					continue;

				next.insert(neigh.second);
			}
		}
		possibleCells = next;
	}

public:
	std::unordered_set<Cell*> possibleCells;
	int power;

};

