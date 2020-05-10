#pragma once
#include "Map.h"


class FloodFillService
{
public:
	static int FindOpenArea(Cell currentCell, std::vector<Cell>& path)
	{
		std::queue<int> q; // Nodes to explore
		std::unordered_set<int> visited;

		for (auto c : path)
			visited.insert(c.index());

		Cell curr = Map::GetCellByIndex(currentCell.index());
		q.push(curr.index());
		visited.insert(curr.index());

		while (!q.empty())
		{
			curr = Map::GetCellByIndex(q.front());
			q.pop();

			for (auto neigh : curr.neighbors)
			{
				Cell toFind = *neigh.second;
				
				if (visited.find(neigh.second->index()) != visited.end())
					continue;

				visited.insert(neigh.second->index());
				q.push(neigh.second->index());
			}
		}

		return visited.size();
	}
};

