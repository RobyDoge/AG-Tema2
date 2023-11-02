#pragma once
#include "AdjacencyMatrix.h"
#include <QtWidgets/QMainWindow>
#include "ui_Labyrinth.h"
#include <fstream>
#include <qradiobutton.h>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <string>
#include <sstream>

class Labyrinth : public QMainWindow
{
    Q_OBJECT

public:
    Labyrinth(QWidget *parent = nullptr);
    ~Labyrinth();

    virtual void paintEvent(QPaintEvent* event) override;
	

private:
    void drawLabyrinth(QPainter& painter);
    std::vector<std::pair<int, int>> drawGraphLabyrinth(QPainter& painter);
    void drawArchGraphLabyrinth(QPainter& painter, const std::vector<std::pair<int, int>>& nodeVector);

    static QBrush setBrushColor(const int specifier);
    static QColor setPenColor(const int specifier);

    static std::tuple<int, int, int, int> archDrawXYOfSet(const std::pair<int, int>& firstNode,const std::pair<int, int>& secondNode);



    Ui::LabyrinthClass ui;
	QRadioButton* m_startButton = findChild<QRadioButton*>("startButton");
    AdjacencyMatrix m_matrices;

    inline static int squareMeasurements = 30;
};
