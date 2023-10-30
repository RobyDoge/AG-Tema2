#include "Labyrinth.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Labyrinth w;
    w.show();
    return a.exec();
}
