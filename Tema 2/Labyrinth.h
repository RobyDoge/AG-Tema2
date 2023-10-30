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
    virtual void paintEvent(QPaintEvent* event) override;

	~Labyrinth();

private:
    static QBrush setBrushColor(const int specifier);


    Ui::LabyrinthClass ui;
	QRadioButton* m_startButton = findChild<QRadioButton*>("startButton");
    AdjacencyMatrix m_matrices;

    inline static int squareMeasurements = 30;
};
