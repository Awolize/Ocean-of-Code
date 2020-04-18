#pragma once
#include "Map.h"
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

