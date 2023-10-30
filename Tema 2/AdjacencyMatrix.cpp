#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(std::ifstream& input):
	m_numberOfNodes{0}
{
	setInputMatrix(input);
	initializeAdjacencyMatrix();
	setAdjacencyMatrix();

}

AdjacencyMatrix::AdjacencyMatrix() = default;

void AdjacencyMatrix::initializeAdjacencyMatrix()
{
	for (int i = 0; i < m_numberOfNodes; i++) {
		std::vector<int> row(m_numberOfNodes, 0);
		m_adjacencyMatrix.push_back(row);
	}
}

void AdjacencyMatrix::setAdjacencyMatrix()
{
	for (int i = 1; i <= m_numberOfNodes; i++)
	{
		std::pair<bool, int> target(0, i);
		int rowPosition= 0;
		for (auto& row : m_inputMatrix)
		{
			
			const auto it = std::find_if(row.begin(), row.end(),
			                             [target](const std::pair<int, int>& element) {
				                             return element.second == target.second;
			                             });
			const int columnPosition = std::distance(row.begin(), it);
			if(it!=row.end())
			{
				if(rowPosition+1 < m_inputMatrix.size() && m_inputMatrix[rowPosition + 1][columnPosition].second)
				{
					m_adjacencyMatrix[i-1][m_inputMatrix[rowPosition + 1][columnPosition].second-1] = 1;
					m_adjacencyMatrix[m_inputMatrix[rowPosition + 1][columnPosition].second-1][i - 1] = 1;
				}
				if(rowPosition - 1 >= 0 && m_inputMatrix[rowPosition - 1 ][columnPosition].second)
				{
					m_adjacencyMatrix[i-1][m_inputMatrix[rowPosition - 1][columnPosition].second-1] = 1;
					m_adjacencyMatrix[m_inputMatrix[rowPosition - 1][columnPosition].second-1][i-1] = 1;
				}
				if (columnPosition + 1 < row.size() && m_inputMatrix[rowPosition][columnPosition+1].second)
				{
					m_adjacencyMatrix[i-1][m_inputMatrix[rowPosition][columnPosition + 1].second-1] = 1;
					m_adjacencyMatrix[m_inputMatrix[rowPosition][columnPosition + 1].second-1][i-1] = 1;
				}
				if (columnPosition - 1 >= 0 && m_inputMatrix[rowPosition][columnPosition - 1].second)
				{
					m_adjacencyMatrix[i-1][m_inputMatrix[rowPosition][columnPosition - 1].second-1] = 1;
					m_adjacencyMatrix[m_inputMatrix[rowPosition][columnPosition - 1].second-1][i-1] = 1;
				}
				break;
			}
			rowPosition++;
		}
	}
}

void AdjacencyMatrix::setInputMatrix(std::ifstream& input)
{
	std::string row;
	for (int i = 0; std::getline(input, row); i++)
	{
		std::vector<std::pair<int,int>> aux1;
		for (const auto& aux : row)
		{
			if (aux != 32)
			{
				aux1.emplace_back(aux - '0',0);
				if (aux != '0')
				{
					m_numberOfNodes++;
					aux1[aux1.size() - 1].second = m_numberOfNodes;
				}
				if(aux == '3')
				{
					m_valueNodeStart = m_numberOfNodes-1;
				}
				else if(aux=='2')
				{
					m_valueNodesExist.push_back(m_numberOfNodes-1);
				}
			}
			
		}
		m_inputMatrix.push_back(aux1);
	}
}

std::vector<std::vector<int>> AdjacencyMatrix::getAdjacencyMatrix() const
{
	return m_adjacencyMatrix;
}

std::vector<std::vector<std::pair<int, int>>> AdjacencyMatrix::getInputMatrix() const
{
	return m_inputMatrix;
}
