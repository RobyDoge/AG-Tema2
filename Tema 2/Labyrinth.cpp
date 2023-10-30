#include "Labyrinth.h"

Labyrinth::Labyrinth(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.startButton->setCheckable(true);
	std::ifstream input("inputMatrix.txt");
	AdjacencyMatrix auxMatrix(input);
	m_matrices = auxMatrix;
    
	update();
}

void Labyrinth::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if(!ui.startButton->isChecked())
    {
        int yIterator = 0;
        for(const auto& aux1: m_matrices.getInputMatrix())
        {
            int xIterator = 0;
	        for(const auto aux2:aux1)
	        {
		        constexpr int yButtonOffSet = 35;
		        painter.setBrush(setBrushColor(aux2.first));
                painter.drawRect(0 + xIterator * squareMeasurements, yButtonOffSet + yIterator * squareMeasurements, squareMeasurements, squareMeasurements);
                xIterator++;
	        }
            yIterator++;
        }
    }
}

Labyrinth::~Labyrinth()
{
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
    default:
    {
        return Qt::blue;
    }
    }
}
