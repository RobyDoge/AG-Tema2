#pragma once
#include <fstream>
#include <QMouseEvent>
#include <QPainter>
#include <qradiobutton.h>
#include <sstream>
#include <string>
#include <vector>
#include <QtWidgets/QMainWindow>
#include "AdjacencyMatrix.h"
#include "BreathFirstSearch.h"
#include "ui_Labyrinth.h"

class Labyrinth : public QMainWindow
{
    Q_OBJECT

public:
    Labyrinth(QWidget *parent = nullptr);
    ~Labyrinth();
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
	

private:
    void drawLabyrinth(QPainter& painter);
    std::vector<std::pair<int, int>> drawGraphLabyrinth(QPainter& painter);
    void drawArchGraphLabyrinth(QPainter& painter, const std::vector<std::pair<int, int>>& nodeVector);

    static QBrush setBrushColor(const int specifier);
    static QColor setPenColor(const int specifier);

    static std::tuple<int, int, int, int> archDrawXYOfSet(const std::pair<int, int>& firstNode,const std::pair<int, int>& secondNode);



    Ui::LabyrinthClass ui;
	//QRadioButton* m_startButton = findChild<QRadioButton*>("startButton");
    AdjacencyMatrix m_matrices;
    bool m_stageOfProgram;

    inline static int squareMeasurements = 30;
};
