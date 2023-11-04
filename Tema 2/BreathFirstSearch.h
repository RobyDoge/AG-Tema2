#pragma once
#include <vector>
#include "AdjacencyMatrix.h"

class BreathFirstSearch
{
public:
	static void createPathsToExits(AdjacencyMatrix& matrix);

private:
	static void createFatherNodeVector(const std::vector<std::vector<int>>& adjacencyMatrix, const int startNode);
	static std::vector<std::vector<int>> createPaths(const std::vector<int>& exitNodes, const int startNode);
	static void alterInputMatrix(AdjacencyMatrix& matrix, const std::vector<std::vector<int>>& paths);

	static std::vector<int> m_fatherNodeVector;
};

