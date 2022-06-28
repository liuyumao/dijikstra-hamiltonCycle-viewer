#include "hamilton.h"

Hamilton::Hamilton()
{

}

void Hamilton::init(QVector<int> &vct)
{
    clear();
    G.vexnum = vct.at(0);
    G.arcnum = vct.at(1);

    for (int i = 0; i < G.vexnum; i ++) {
        G.vexs[i] = i;
    }

    int count = 2;
    for (int i = 0; i < G.arcnum; i ++ )
    {
        int a = vct.at(count++);
        int b = vct.at(count++);
        G.arcs[a][b] = G.arcs[b][a] = 1;
    }
}

void Hamilton::clear()
{
    flag = false;
    for (int i = 0; i < VEXNUM; i ++) visited[i] = false;
    for (int i = 0; i < G.arcnum; i ++ ) {
        for (int j = 0; j < G.arcnum; j ++ ) {
            G.arcs[i][j] = 0;
        }
    }
    sPath.clear();
    path.clear();
}

bool Hamilton::check()
{
    DFS(G, 0, 0);
    return flag;
}

void Hamilton::DFS(AMGraph &G, int x, int cnt)
{
    if (flag) return;
    if (cnt == G.vexnum - 1) {

        if (G.arcs[x][0]) {
            path.push_back("v" + QString::number(x) + "->");
            path.push_back("v" + QString::number(0));
            for (auto& item : path) sPath += item;
            flag = true;
        }
        return;
    }

    for (int j = 0; j < G.vexnum; ++ j)
    {   //如果与下一个点有联系且没有访问，则访问下一个点
        //std::cout << "x = " << x << "y = " << j << " " << G.arcs[x][j] << std::endl;
        if (G.arcs[x][j] && !visited[j]) {
            visited[x] = true;
            path.push_back(QString("v" + QString::number(x) + "->"));
            DFS(G, G.vexs[j], cnt+1);
            visited[j] = false;
            if (path.size()) path.pop_back();
        }
    }

    return;
}

QString Hamilton::getCycle()
{
    return sPath;
}

