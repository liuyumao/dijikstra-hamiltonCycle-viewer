#include "dijiekstra.h"
#include <QDebug>
const int INF = 0x3f3f3f3f;
int D[N], S[N];
int Path[N];


Dijiekstra::Dijiekstra()
{
    st = 0;
}

void Dijiekstra::setVexAndArc(int vex, int arc)
{
    G.vexnum = vex;
    G.arcnum = arc;
}

void Dijiekstra::init()
{
    for (int i = 0; i < G.vexnum; ++ i) G.vex[i] = i;
    for (int i = 0; i < G.vexnum; ++ i) {
        for (int j = 0; j < G.vexnum; ++ j)
            G.arcs[i][j] = INF;
    }
}

void Dijiekstra::initArcs(QStringList& list)
{
    int x, y, w, cnt = 2;
    for (int i = 0; i < G.arcnum; ++ i) {
        x = list[cnt++].toInt();
        y = list[cnt++].toInt();
        w = list[cnt++].toInt();
        G.arcs[x][y] = w;//这是一个有向图
        mp[QPair<int, int>{x, y}] = i;
    }
}

void Dijiekstra::startWork()
{
    for (int i = 0; i < N; i ++) D[i] = S[i] = 0;
    for (int i = 0; i < G.vexnum; ++ i) {
        D[i] = G.arcs[st][i];
        if (D[i] < INF) Path[i] = st;
        else Path[i] = -1;
    }
    D[st] = 0; S[st] = 1; //st为起点，初始时到自身距离为0，并<-->并入集合中
    for (int i = 0; i < G.vexnum; ++ i) {
        int v = -1, m = INF;
        for (int k = 0; k < G.vexnum; ++ k) {
            if (!S[k] && D[k] < m) {
                v = k; m = D[k];
            }
        }
        if (v == -1) continue;
        S[v] = 1;//将v并入集合中
        for (int k = 0; k < G.vexnum; ++ k) {
            if (!S[k] && D[v] + G.arcs[v][k] < D[k]) {
                D[k] = D[v] + G.arcs[v][k];
                Path[k] = v;
                // cout << "Path["<< k << "] = " << v << '\n';
            }

        }
    }
}

void Dijiekstra::setStartVex(int v)
{
    st = v;
}

void Dijiekstra::printPath(int v)
{
    if (v == -1) return;
    printPath(Path[v]);
    points.push_back(G.vex[v]);
    qDebug() << "B>" << G.vex[v];
}

void Dijiekstra::markSelected()
{
    qDebug() << "points = " << points.length();
    for (int i = 0; i < points.length()-1; i ++) {
        numbers.push_back(mp[QPair<int, int>{points[i], points[i+1]}]);
        if (mp[QPair<int, int>{points[i+1], points[i]}]) {
            numbers.push_back(mp[QPair<int, int>{points[i+1], points[i]}]);
        }
    }
}

QVector<int> &Dijiekstra::getNumbers()
{
    return numbers;
}

QVector<int> &Dijiekstra::getPoints()
{
    return points;
}

int Dijiekstra::getShortPath(int i)
{
    return D[i];
}

void Dijiekstra::clearVector()
{
    while (!numbers.empty()) numbers.pop_back();
    while (!points.empty()) points.pop_back();

}

//void printPath(int v, AMGraph &G)
//{
//    if (v == -1) return;
//    printPath(Path[v], G);
//    cout << 'v' << G.vex[v] << "->";
//}
/*
6 8
0 2 10
0 4 30
0 5 100
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60
*/
