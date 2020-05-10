#pragma once
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
#include <cmath>

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
	inline Cell() : x(-1), y(-1), type('*') {};
	inline Cell(int x, int y, char type) : x(x), y(y), type(type) {};
	inline int index() { return x + (y * 15); }
	inline operator std::string() const { return x + " " + y; };
	inline bool DealsDamageTo(Cell cell) { return std::abs(x - cell.x) <= 1 && std::abs(y - cell.y) < 1; };
	inline bool canMove(char dir, int length) 
	{ 
		auto curr = this;
		for (size_t i = 0; i < length; i++)
		{
			if (curr->neighbors.find(dir) != curr->neighbors.end())
			{
				return false;
			}
			curr = curr->neighbors[dir];
		}
		return true;
	};

	inline Cell* move(char dir, int length)
	{
		auto curr = this;
		for (size_t i = 0; i < length; i++)
		{
			curr = curr->neighbors[dir];
		}
		return curr;
	};

public:
	int x;
	int y;
	char type;
	std::unordered_map<char, Cell*> neighbors;
	std::unordered_set<Cell*> torpedoTargets;
	std::unordered_set<Cell*> toDamage;
};

class dire
{
public:
	dire(int x, int y, char d) : dx(x), dy(y), dir(d) {};
	int dx,
		dy;
	char dir;
};

class Map
{
public:
	static Cell GetCell(int x, int y) { return Board[x + (y * width)]; };
	static Cell GetCellByIndex(int index) { return Board[index]; };
	static Cell& GetCellRef(int x, int y) { return Board[x + (y * width)]; };
	static void AddCell(Cell cell) { Board.push_back(cell); };
	static bool IsValid(int x, int y) { return (x >= 0 && y >= 0 && x < 15 && y < 15); };
	static void Initilize()
	{
		for (auto& cell : Board)
		{
			if (cell.type == '.')
				SetupCell(cell);
		}

		for (auto& cell : Board)
		{
			if (cell.type == '.')
			{
				SetupTorpedo(cell);
				SetupDamage(cell);
			}
		}

		std::cerr << "Torpedo range: " << std::endl;
		for (size_t y = 0; y < 15; y++)
		{
			for (size_t x = 0; x < 15; x++)
			{
				auto curr = GetCell(x, y);
				if (curr.type == '.')
					std::cerr << std::setw(3) << curr.torpedoTargets.size() << " ";
				else
					std::cerr << std::setw(3) << "-" << " ";
			}
			std::cerr << std::endl;
		}
	}
private:
	static void SetupTorpedo(Cell& cell)
	{
		for (size_t i = 0; i < 3; i++)
		{
			std::unordered_set<Cell*> toAdd;

			for (Cell* curr : cell.torpedoTargets)
			{
				for (auto neigh : curr->neighbors)
				{
					toAdd.insert(neigh.second);
				}
			}

			for (Cell* curr : toAdd)
				cell.torpedoTargets.insert(curr);
		}
	};
	static void SetupCell(Cell& cell)
	{
		dire neighbors[4] = { dire(0,-1,'N'), dire(0,1,'S'), dire(-1,0,'W'), dire(1,0,'E') };
		for (size_t i = 0; i < 4; i++)
		{
			int x = cell.x + neighbors[i].dx;
			int y = cell.y + neighbors[i].dy;
			if (IsValid(x, y))
				if (GetCell(x, y).type == '.')
				{
					cell.neighbors[neighbors[i].dir] = &GetCellRef(x, y);
					cell.torpedoTargets.insert(&GetCellRef(x, y));
				}

		}
	}
	static void SetupDamage(Cell& cell)
	{
		for (auto& c : Board)
		{
			if (c.DealsDamageTo(cell))
			{
				cell.toDamage.insert(&c);
			}
		}
	}
public:
	static std::vector<Cell> Board;
	static const int width = 15;
	static const int height = 15;
};