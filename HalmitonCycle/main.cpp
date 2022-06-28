#include <QtWidgets/QApplication>
#include <QIcon>
#include "hamiltoncycle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HamiltonCycle w;
    w.show();
    return a.exec();
}
