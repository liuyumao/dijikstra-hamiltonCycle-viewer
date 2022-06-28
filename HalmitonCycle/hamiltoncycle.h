/* 这个是哈密顿回路的主程序，包含逻辑交互，描点画点，画线，以及更新2D绘图
 * 主要封装了work和draw两个函数方法，draw来绘图，work来计算哈密顿回路
 */

#ifndef HAMILTONCYCLE_H
#define HAMILTONCYCLE_H

#include <QWidget>
#include <QGraphicsScene>
#include "itempoint.h"
#include "itemline.h"
#include "hamilton.h"
#include "inputmartix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HamiltonCycle; }
QT_END_NAMESPACE

class HamiltonCycle : public QWidget
{
    Q_OBJECT
private:
    enum myInputMode {
        ordinaryMode = 0,
        matrixMode   = 1
    };
private:
    double const Pi;
public:
    HamiltonCycle(QWidget *parent = nullptr);
    ~HamiltonCycle();
    void work(); // 作用是：使hamilton算法
    void draw(); // 作用是：画出无向图

protected:
    void locatePoints(int n);
    void initHamiltonData();
    void runHamiltonALGO();
    void initListData();
    void clearData();
    bool checkData();
    void drawPoint();
    void drawLine();
    void initQssStyle();
    void translateList();
    void initVexAndArc();
    void updateGraphics();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btn_ok_clicked();
    void on_btn_mipt_clicked();
    void on_btn_start_clicked();
    void on_btn_recover_clicked();
    void getDataSlot();

private:
    Ui::HamiltonCycle * ui;
    QGraphicsScene    * scene;
    InputMartix       * mInput;
    QList<ItemPoint   *> itemPointList;
    QList<ItemLine    *> itemLineList;
    QVector<int> posx, posy, hdata;
    QStringList list;
    QString outText;
    QPoint point;
    Hamilton ham;
    myInputMode modeInput;
    int vexNum, arcNum;
};

#endif // HamiltonCycle_H
