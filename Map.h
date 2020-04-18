#pragma once
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
	inline Cell(): x(-1), y(-1), type('*') {};
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