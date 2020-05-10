#pragma once
#include "Map.h"
#include "OpponentTrackingService.h"

class Player
{
public:
	Player(int playerId) :
		playerId(playerId), torpedoCooldown(3),
		sonarCooldown(3), silenceCooldown(3), mineCooldown(3), x(0), y(0) { };
public:
	std::vector<Cell> path;
	Cell cell;
	int playerId;
	int health = 6;
	int x;
	int y;
	int torpedoCooldown;
	int sonarCooldown;
	int silenceCooldown;
	int mineCooldown;
	std::string output;
	OpponentTrackingService opponentTracking;
};

class Game
{
public:
	inline Game() : players{ Player(0), Player(1) } {};
public:
	Player players[2];
};


