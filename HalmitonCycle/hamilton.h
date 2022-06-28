/* 这是哈密顿回路的具体算法，通关从外部传入QVector<int>& vct初始化信息
 * 之后，进行深度优先搜索，默认从0结点开始，因为如果存在哈密顿回路，一定包
 * 括v0点，所以输出也说明了，是“哈密顿回路其中之一为...”
 */
#ifndef HAMILTON_H
#define HAMILTON_H
#include <QVector>
#include "base.h"

class Hamilton
{
    typedef struct
    {
        int vexs[VEXNUM];
        int arcs[VEXNUM][VEXNUM];
        int vexnum, arcnum;
    }AMGraph;

public:
    Hamilton();
    void init(QVector<int>& vct);
    void clear();
    bool check();
    void DFS(AMGraph &G, int x, int cnt);
    QString getCycle();

private:
    int n, m;
    bool visited[VEXNUM+1];//标记数组，初始化为未访问false
    bool flag;
    QString sPath;
    QVector<QString> path;
    AMGraph G;
};

#endif // HAMILTON_H
