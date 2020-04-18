#include <iostream>
#include "Map.h"
#include "Game.h"
#include "ReadInput.h"
#include "Placement.h"
#include "ReactAgent.h"

int main()
{

	ReadInput::Initilize();
	Map::Initilize();

	auto startCell = Placement::GetPlacement();
	std::string pos = std::to_string(startCell.x) + " " + std::to_string(startCell.y);
	std::cout << pos << std::endl;

	Game lastGame;
	lastGame.players[0].path.push_back(startCell);
	while (true)
	{
		Game game = ReadInput::ReadRound(lastGame);

		ReactAgent agent(game);
		auto result = agent.think();
		std::cout << result << std::endl;

		lastGame = game;
	}
}