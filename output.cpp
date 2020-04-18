/*-- #include "Codin Game - Ocean of Code - Backup\Game.h" start --*/
#include <vector>
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/
// va
#include <unordered_map>
#include <string>
#include <vector>

class Direction
{
public:
	Direction(int dx, int dy, char dir) : dx(dx), dy(dy), dir(dir) {};

	bool operator==(const Direction& p) const {
		return dx == p.dx && dy == p.dy && dir == p.dir;
	}
public:
	const int dx, dy;
	const char dir;
};


class Cell
{
public:
	inline Cell(){};
	inline Cell(int x, int y, char type) : x(x), y(y), type(type) {};
	inline operator std::string() const { return x + " " + y; };
public:
	int x;
	int y;
	char type;
	std::unordered_map<char, Cell*> neighbors;
};

class dire
{
public:
	dire(int x, int y, char d) : dx(x), dy(y), dir(d) {};
	int dx, dy;
	char dir;
};

class Map
{
public:
	static Cell GetCell(int x, int y) { return Board[x + y * width]; };
	static Cell& GetCellRef(int x, int y) { return Board[x + y * width]; };
	static void AddCell(Cell cell) { Board.push_back(cell); };
	static bool IsValid(int x, int y) { return (x >= 0 && y >= 0 && x < 15 && y < 15); };
	static void Initilize()
	{
		for (auto& cell : Board)
		{
			SetupCell(cell);
		}
	}
	static void SetupCell(Cell& cell)
	{
		dire neighbors[4] = { dire(0,1,'N'), dire(0,-1,'S'), dire(-1,0,'W'), dire(1,0,'E') };
		for (size_t i = 0; i < 4; i++)
		{
			int x = cell.x + neighbors[i].dx;
			int y = cell.y + neighbors[i].dy;
			if (IsValid(x, y))
				cell.neighbors[neighbors[i].dir] = &GetCellRef(x, y);
		}
	}

public:
	static std::vector<Cell> Board;
	static const int width = 15;
	static const int height = 15;
};

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
};

class Game
{
public:
	inline Game() : players{ Player(0), Player(1) } {};
public:
	Player players[2];
};



/*-- File: Codin Game - Ocean of Code - Backup\main.cpp start --*/
#include <iostream>
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Game.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\ReadInput.h" start --*/
#include <iostream>
#include <string>
/*-- #include "Codin Game - Ocean of Code - Backup\Game.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/


class ReadInput
{
public:
	inline static void Initilize()
	{
		int width;
		int height;
		int myId;
		std::cin >> width >> height >> myId; std::cin.ignore();
		for (int i = 0; i < height; i++) {
			std::string line;
			getline(std::cin, line);
			for (int j = 0; j < line.size(); j++)
			{
				Map::AddCell(Cell(i, j, line[j]));
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


/*-- #include "Codin Game - Ocean of Code - Backup\Placement.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/
#include <string>
class Placement
{
public:
	static Cell GetPlacement() {
		int x = 5;
		int y = 5;
		Cell cell = Map::GetCell(x, y);

		for (Cell cell : Map::Board)
		{
			if (cell.type != '.')
				continue;
			else
				return cell;
		}
	}
};


/*-- #include "Codin Game - Ocean of Code - Backup\ReactAgent.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Game.h" start --*/
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
/*-- File: Codin Game - Ocean of Code - Backup\main.cpp end --*/
/*-- File: Codin Game - Ocean of Code - Backup\Map.cpp start --*/
#include <vector>
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/

std::vector<Cell> Map::Board;
/*-- File: Codin Game - Ocean of Code - Backup\Map.cpp end --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Map.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\Placement.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\ReactAgent.h" start --*/
/*-- #include "Codin Game - Ocean of Code - Backup\ReadInput.h" start --*/
