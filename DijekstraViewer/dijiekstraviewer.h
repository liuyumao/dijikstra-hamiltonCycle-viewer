#ifndef DIJIEKSTRAVIEWER_H
#define DIJIEKSTRAVIEWER_H

#include "itemPoint.h"
#include "itemLine.h"
#include "dijiekstra.h"
#include "inputmartix.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class DijiekstraViewer; }
QT_END_NAMESPACE

class DijiekstraViewer : public QWidget
{
    Q_OBJECT

public:
    DijiekstraViewer(QWidget *parent = nullptr);
    ~DijiekstraViewer();
    void initQssStyle();
    void initListData();
    void initStartAndEndPoints(int n);
    void locateItemPoints(int n);
    void initDijstelaData();
    void runDijstelaALGO();
    void clearInvalidData();
    void checkListData();
    void drawVexPoint();
    void drawEdgeLine1();
    void drawEdgeLine2();

private slots:
    void on_btn_start_clicked();
    void on_btn_ok_clicked();
    void on_btn_Minput_clicked();
    void drawPicture1();
    void drawPicture2();
    void showLineInfo(int _x, int _y, QString sp);

private:
    Ui::DijiekstraViewer  * ui;
    QGraphicsScene        * scene;
    QGraphicsTextItem     *text;
    InputMartix     * mInput;
    QList<ItemPoint *> itemPointList;
    QList<ItemLine  *> itemLineList;
    QVector<int> posx, posy;
    Dijiekstra djs;
    QStringList list;
    QString sPath;
    QMap<QPair<int, int>, int> mp;
    int vexNum, arcNum;
};
#endif // MANAGER_H
