#pragma once
#include <vector>
#include <fstream>
#include <string>

class AdjacencyMatrix
{
public:
	AdjacencyMatrix(std::ifstream& input);
	AdjacencyMatrix();
	
	std::vector<std::vector<int>> getAdjacencyMatrix() const;
	std::vector<std::vector<std::pair<int, int>>> &getInputMatrix();
	int getStartNode() const;
	std::vector<int> getExistNodes() const;

private:
	void setInputMatrix(std::ifstream& input);
	void initializeAdjacencyMatrix();
	void setAdjacencyMatrix();


	std::vector<std::vector<int>> m_adjacencyMatrix;
	std::vector<std::vector<std::pair<int,int>>> m_inputMatrix;
	int m_numberOfNodes;
	int m_startNode;
	std::vector<int> m_exitNodes;
};

