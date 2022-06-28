#ifndef DIJIEKSTRA_H
#define DIJIEKSTRA_H

#include <QObject>
#include <QMap>

#define N 100

class Dijiekstra
{
    typedef struct
    {
        int vex[N];
        int arcs[N][N];
        int vexnum, arcnum;

    }AMGraph;
public:
    Dijiekstra();
    void setVexAndArc(int vex, int arc);
    void init();
    void initArcs(QStringList& list);
    void startWork();
    void setStartVex(int v);
    void printPath(int);
    void markSelected();
    QVector<int>& getNumbers();
    QVector<int>& getPoints();
    int getShortPath(int i);
    void clearVector();
private:
    int vex, arc;
    AMGraph G;
    int st;
    QMap<QPair<int, int>, int> mp;
    QVector<int> numbers;
    QVector<int> points;
};

#endif // DIJIEKSTRA_H
