#include "Labyrinth.h"

Labyrinth::Labyrinth(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.startButton->setCheckable(true);
	std::ifstream input("inputMatrix.txt");
	AdjacencyMatrix auxMatrix(input);
	m_matrices = auxMatrix;
    m_stageOfProgram = false;
	update();
}

Labyrinth::~Labyrinth()
{
}

void Labyrinth::mouseReleaseEvent(QMouseEvent* event)
{
	if(ui.startButton->isChecked())
	{
        m_stageOfProgram = true;
        update();
        m_stageOfProgram = false;
        ui.startButton->setEnabled(false);
        BreathFirstSearch::createPathsToExits(m_matrices);
        update();
	}
}

void Labyrinth::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (m_stageOfProgram)
    {
        return;
    }
	drawLabyrinth(painter);
	const std::vector<std::pair<int, int>> nodeVector = drawGraphLabyrinth(painter);
	drawArchGraphLabyrinth(painter, nodeVector);
    
}

void Labyrinth::drawLabyrinth(QPainter& painter)
{
    int yIterator = 0;
    for (const auto& aux1 : m_matrices.getInputMatrix())
    {
        int xIterator = 0;
        for (const auto aux2 : aux1)
        {
            constexpr int yButtonOffSet = 35;
            painter.setBrush(setBrushColor(aux2.first));
            painter.drawRect(0 + xIterator * squareMeasurements,
                yButtonOffSet + yIterator * squareMeasurements,
                squareMeasurements, squareMeasurements);
            xIterator++;
        }
        yIterator++;
    }
    painter.setBrush(Qt::white);
}

std::vector<std::pair<int, int>> Labyrinth::drawGraphLabyrinth(QPainter& painter)
{
    int yIterator = 0;
    int currentNodeNumber = 0;
    std::vector<std::pair<int, int>> nodeVector; //first-x   second-y

    for (const auto& aux1 : m_matrices.getInputMatrix())
    {
        int xIterator = 0;
        const int xLabyrinthOffSet = aux1.size() * squareMeasurements + 40;
        for (const auto& aux2 : aux1)
        {
            if (aux2.first)
            {
	            constexpr int yButtonOffSet = 35;
	            constexpr int spaceBetweenNodes = 15;
                QRect r(xLabyrinthOffSet + xIterator * squareMeasurements + spaceBetweenNodes * xIterator,
                    yButtonOffSet + yIterator * squareMeasurements + spaceBetweenNodes * yIterator,
                    squareMeasurements, squareMeasurements);
                nodeVector.emplace_back(xLabyrinthOffSet + xIterator * squareMeasurements + spaceBetweenNodes * xIterator,
                    yButtonOffSet + yIterator * squareMeasurements + spaceBetweenNodes * yIterator);
                QPen nodeColor;
                nodeColor.setColor(setPenColor(aux2.first));
                nodeColor.setWidth(2);
                painter.setPen(nodeColor);
                painter.drawEllipse(r);
                QString s;
                s.setNum(currentNodeNumber);
                painter.drawText(r, Qt::AlignCenter, s);
                currentNodeNumber++;
            }
            xIterator++;
        }
        yIterator++;
    }
    return nodeVector;
}

void Labyrinth::drawArchGraphLabyrinth(QPainter& painter, const std::vector<std::pair<int, int>>& nodeVector)
{
    for (int i = 0; i < nodeVector.size(); i++) {
        for (int j = 0; j < nodeVector.size(); j++)
        {
            if (nodeVector[i] != nodeVector[j])
            {
                if (m_matrices.getAdjacencyMatrix()[i][j] == 1)
                {
                    painter.drawLine(nodeVector[i].first + std::get<0>(archDrawXYOfSet(nodeVector[i], nodeVector[j])),
                        nodeVector[i].second + std::get<1>(archDrawXYOfSet(nodeVector[i], nodeVector[j])),
                        nodeVector[j].first + std::get<2>(archDrawXYOfSet(nodeVector[i], nodeVector[j])),
                        nodeVector[j].second + std::get<3>(archDrawXYOfSet(nodeVector[i], nodeVector[j])));
                }
            }
        }
    }
}

QBrush Labyrinth::setBrushColor(const int specifier)
{
    switch (specifier)
    {
    case 0:
    {
        return Qt::black;

    }
    case 1:
    {
        return Qt::gray;
    }
    case 2:
    {
        return Qt::red;
    }
    case 4:
    {
        return Qt::darkGreen;
    }
    default:
    {
        return Qt::blue;
    }
    }
}

QColor Labyrinth::setPenColor(const int specifier)
{
    switch (specifier)
    {
    case 0:
    {
        return Qt::white;

    }
    case 1:
    {
        return Qt::black;
    }
    case 2:
    {
        return Qt::red;
    }
    case 4:
    {
        return Qt::darkGreen;
    }
    default:
    {
        return Qt::blue;
    }
    }
}

std::tuple<int, int, int, int> Labyrinth::archDrawXYOfSet(const std::pair<int, int>& firstNode, const std::pair<int, int>& secondNode)
{

    if(firstNode.first==secondNode.first)
    {
        if (firstNode.second - secondNode.second < 0)
	    {
            return{ squareMeasurements / 2,squareMeasurements,squareMeasurements / 2,0 };
	    }
    	return{ squareMeasurements / 2,0,squareMeasurements/2,squareMeasurements};
        
    }
	if (firstNode.first - secondNode.first < 0)
	{
        return{ squareMeasurements,squareMeasurements / 2,0,squareMeasurements / 2 };
	}
    
    return { 0,squareMeasurements/2,squareMeasurements,squareMeasurements/2 };
}
