#include "BreathFirstSearch.h"
#include <queue>

std::vector<int> BreathFirstSearch::m_fatherNodeVector;

void BreathFirstSearch::alterInputMatrix(AdjacencyMatrix& matrix, const std::vector<std::vector<int>>& paths)
{
	for (const auto& path : paths)
	{
		for (const auto& nodeValue : path)
		{
			for (auto& row : matrix.getInputMatrix())
			{
				for(auto& rowElement:row)
				if (rowElement.first == 1&&rowElement.second==nodeValue+1)
				{
					rowElement.first = 4;
				}
			}
		}
	}
}

void BreathFirstSearch::createPathsToExits(AdjacencyMatrix& matrix)
{
	createFatherNodeVector(matrix.getAdjacencyMatrix(), matrix.getStartNode());
	alterInputMatrix(matrix,createPaths(matrix.getExistNodes(), matrix.getStartNode()));
}

void BreathFirstSearch::createFatherNodeVector(const std::vector<std::vector<int>>& adjacencyMatrix, const int startNode)
{
	std::vector<int> remainingNodes;
	std::queue<int> currentNodes;
	std::vector<int> visitedNodes;
	std::vector<int> lengthVector;

	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		if (i != startNode)
		{
			remainingNodes.emplace_back(i);
		}
		else
		{
			currentNodes.push(i);
		}
		m_fatherNodeVector.emplace_back(0);
		lengthVector.emplace_back(0);
	}

	while (!currentNodes.empty()) 
	{
		auto aux = remainingNodes.begin();
		while (aux != remainingNodes.end()) 
		{
			if (adjacencyMatrix[currentNodes.front()][*aux] == 1)
			{
				currentNodes.push(*aux);
				const int currentNode = *aux;
				aux = remainingNodes.erase(aux);
				m_fatherNodeVector[currentNode] = currentNodes.front();
				lengthVector[currentNode] = lengthVector[currentNodes.front()] + 1;
			}
			else 
			{
				++aux; 
			}
		}
		currentNodes.pop();
	}

}

std::vector<std::vector<int>> BreathFirstSearch::createPaths(const std::vector<int>& exitNodes, const int startNode)
{
	std::vector<std::vector<int>> paths;
	for(const auto aux:exitNodes)
	{
		std::vector<int> path;
		path.emplace_back(m_fatherNodeVector[aux]);
		while (path[path.size() - 1] != startNode)
		{
			path.emplace_back(m_fatherNodeVector[path[path.size()-1]]);
		}
		paths.emplace_back(path);
	}
	return paths;
}
