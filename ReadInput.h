#pragma once
#include <iostream>
#include <string>
#include "Game.h"
#include "Map.h"


class ReadInput
{
public:
	inline static void Initilize()
	{
		int width;
		int height;
		int myId;
		std::cin >> width >> height >> myId; std::cin.ignore();
		for (int y = 0; y < height; y++) {
			std::string line;
			getline(std::cin, line);
			for (int x = 0; x < line.size(); x++)
			{
				Map::AddCell(Cell(x, y, line[x]));
			}
		}
	}

	inline static Game ReadRound(Game lastGame)
	{
		Game game;
		int x;
		int y;
		int myLife;
		int oppLife;
		int torpedoCooldown;
		int sonarCooldown;
		int silenceCooldown;
		int mineCooldown;
		std::cin >> x >> y >> myLife >> oppLife >> torpedoCooldown >> sonarCooldown >> silenceCooldown >> mineCooldown; std::cin.ignore();
		std::string sonarResult;
		std::cin >> sonarResult; std::cin.ignore();
		std::string opponentOrders;
		getline(std::cin, opponentOrders);

		game.players[0].cell = Map::GetCell(x, y);
		game.players[0].health = myLife;
		game.players[0].torpedoCooldown = torpedoCooldown;
		game.players[0].sonarCooldown = sonarCooldown;
		game.players[0].silenceCooldown = silenceCooldown;
		game.players[0].mineCooldown = mineCooldown;
		std::copy(lastGame.players[0].path.begin(), lastGame.players[0].path.end(), std::back_inserter(game.players[0].path));
		game.players[0].path.push_back(Map::GetCell(x, y));
		game.players[1].health = oppLife;
		game.players[1].output = opponentOrders;
		game.players[1].opponentTracking.possibleCells = lastGame.players[1].opponentTracking.possibleCells;
		game.players[1].opponentTracking.power = lastGame.players[1].opponentTracking.power;
		game.players[1].opponentTracking.track(opponentOrders);

		return game;
	}

	inline static std::string ReadLine()
	{
		std::string s;
		std::getline(std::cin, s);
		std::cerr << s << std::endl;
		return s;
	}
};

