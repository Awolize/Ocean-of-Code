#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <map>
#include <unordered_map>
#include <iomanip>

#include "Map.h"
#include "Game.h"
#include "ReadInput.h"
#include "Placement.h"
#include "ReactAgent.h"

#include <chrono> 
using namespace std::chrono;

int main()
{

	ReadInput::Initilize();
	Map::Initilize();
	
	auto startCell = Placement::GetPlacement();
	std::string pos = std::to_string(startCell.x) + " " + std::to_string(startCell.y);
	std::cout << pos << std::endl;

	Game lastGame;
	lastGame.players[0].path.push_back(startCell);

	for (Cell& c : Map::Board)
		if (c.type == '.')
			lastGame.players[1].opponentTracking.possibleCells.insert(&c);

	while (true)
	{
		//auto start = high_resolution_clock::now();
		Game game = ReadInput::ReadRound(lastGame);

		ReactAgent agent(game);
		std::string result = agent.think();
		
		std::cout << result << std::endl;

		lastGame = game;
		
		/*auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		std::cerr << "Time (ms): " << duration.count() << std::endl;*/
	}
}