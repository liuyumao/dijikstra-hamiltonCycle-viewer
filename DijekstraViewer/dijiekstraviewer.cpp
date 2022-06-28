#include "dijiekstraviewer.h"
#include "ui_dijiekstraviewer.h"

#include <QDebug>
#include <QtMath>
#include <QMessageBox>
#include <QFile>
#pragma execution_character_set("utf-8")

double const Pi = 3.1415926;
bool flag = false;

DijiekstraViewer::DijiekstraViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DijiekstraViewer)
{
    ui->setupUi(this);
    setWindowTitle("迪杰斯特拉最短路径算法");
    scene = new QGraphicsScene();
    text = new QGraphicsTextItem();
    mInput = nullptr;
    ui->graphicsView->setScene(scene);
    initQssStyle();
}

DijiekstraViewer::~DijiekstraViewer()
{
    delete ui;
}

void DijiekstraViewer::initQssStyle()
{
    QFile qss(":/qss/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qDebug() << qss.readAll();
    qss.close();
}

void DijiekstraViewer::initListData()
{
    flag = false;
    QString reader = ui->tedit_input->document()->toPlainText();
    qDebug() << reader;
    QString tmp;

    for (int i = 0; i < reader.length(); i ++) {

        if (reader[i] == QChar(' ') || reader[i] == QChar('\n')) {
            if (tmp != "") {
                list << tmp;
                tmp = "";
            }
            continue;
        }
        if (reader[i] < QChar('0') || reader[i] > QChar('9')) {
            flag = true;
            return;
        }
        tmp += reader[i];
    }
    if (tmp != "") list << tmp;
    checkListData();
}

void DijiekstraViewer::initStartAndEndPoints(int n)
{
    ui->cbx_start->clear();
    ui->cbx_end->clear();
    for (int i = 0; i < n; i ++) {
        ui->cbx_start->addItem("v" + QString::number(i));
        ui->cbx_end->addItem("v" + QString::number(i));
    }
}

void DijiekstraViewer::runDijstelaALGO()
{
    QString s = ui->cbx_start->currentText();
    s.remove(0, 1);
    djs.setStartVex(s.toInt());
    djs.startWork();
    s = ui->cbx_end->currentText();
    s.remove(0, 1);
    djs.printPath(s.toInt());
    djs.markSelected();

    auto pt = djs.getPoints();
    QString sPath = "最短路径路线为:\n";
    for (int i = 0; i < pt.length(); i ++) {
        if (i) sPath += "->";
        sPath += "v" + QString::number(pt[i]);
    }
    sPath += "\n\n最短路径权值为:\n" + QString::number(djs.getShortPath(s.toInt()));
    ui->tedit_output->setText(sPath);
}

void DijiekstraViewer::locateItemPoints(int n)
{
    posx.clear();
    posy.clear();

    int swidth  = ui->graphicsView->width();
    int sheight = ui->graphicsView->height();
    int r = std::min(swidth, sheight) / 2 - 60;
    int step = 360 / n, angle = 0;

    for (int i = 0; i < n; i ++ ) {
        int x = r * std::cos(angle * Pi / 180.0);
        int y = r * std::sin(angle * Pi / 180.0);
        posx.push_back(x);
        posy.push_back(y);
        angle += step;
    }
}

void DijiekstraViewer::initDijstelaData()
{
    vexNum = list[0].toInt(), arcNum = list[1].toInt();
    djs.setVexAndArc(vexNum, arcNum);
    djs.init();
    djs.initArcs(list);
    initStartAndEndPoints(vexNum);
    locateItemPoints(vexNum);

    if (ui->checkBox->isChecked()) {
        drawEdgeLine2();
    }
    else drawEdgeLine1();
    drawVexPoint();

}

void DijiekstraViewer::clearInvalidData()
{
    scene->clear();
    list.clear();
    itemPointList.clear();
    itemLineList.clear();
    posx.clear();
    posy.clear();
}

void DijiekstraViewer::checkListData()
{
    if (list.empty()) {
        flag = true;
        return;
    }

    int Xarcs = list.length() - 2;
    if (Xarcs <= 0) flag = true;
    else {
        int vexs = list[0].toInt(), arcs = list[1].toInt();
        if (arcs * 3 != Xarcs) {
            flag = true;
            qDebug() << "位数不狗";
            //qDebug() << "cnt = " << cnt << " " << "arcs = " << arcs;
        }
        else {
            for (int i = 2; i < list.length(); i ++) {
                if (i % 3 == 1) continue;
                if (list[i].toInt() >= vexs) {
                    flag = true;
                    QMessageBox::critical(this, "错误", "注意顶点下标从0开始！");
                }
            }
        }
    }
}

void DijiekstraViewer::drawVexPoint()
{
    for (int i = 0; i < vexNum; i ++) {
        ItemPoint* item = new ItemPoint();
        item->setVexInfo("v"+QString::number(i));
        itemPointList.push_back(item);
        scene->addItem(item);
        item->setPos(posx[i], posy[i]);
    }

}

void DijiekstraViewer::showLineInfo(int _x, int _y, QString sp)
{
    qDebug() << "helloWorld" << "x = " << _x << "  " << "y = " << _y;

    if (sPath != "") return;
    sPath = sp;
    text->setPlainText("v1->v2");
    text->setDefaultTextColor(QColor(255, 102, 178));
    scene->addItem(text);
    text->setPos(_x, _y);

}

void DijiekstraViewer::drawEdgeLine1()
{
    int cnt = 2;

    for (int i = 0; i < arcNum; i ++) {
        int v1 = list[cnt++].toInt(), v2 = list[cnt++].toInt();
        QString value = list[cnt++];

        QPoint p1(posx[v1], posy[v1]);
        QPoint p2(posx[v2], posy[v2]);

        ItemLine* item = new ItemLine();
        QRectF rect = QRectF(std::min(posx[v1], posx[v2])+15, std::min(posy[v1], posy[v2])+15,
                             std::abs(posx[v2]-posx[v1]), std::abs(posy[v2]-posy[v1]));
        item->setLineRect(rect);
        if (mp[{v1, v2}] || mp[{v2, v1}]) {
            item->setTextMode(Qt::AlignRight);
            value = "/" + value;
            qDebug() << "cos";
        }
        mp[{v1, v2}] = mp[{v2, v1}] = 1;
        item->setLine(QPoint(posx[v1]+15, posy[v1]+15), QPoint(posx[v2]+15, posy[v2]+15), value);
        connect(item, &ItemLine::lineClicked, this, &DijiekstraViewer::showLineInfo);
        itemLineList.push_back(item);
        scene->addItem(item);
    }
}

void DijiekstraViewer::drawEdgeLine2()
{
    int cnt = 2;

    for (int i = 0; i < arcNum; i ++) {
        int v1 = list[cnt++].toInt(), v2 = list[cnt++].toInt();
        QString value = list[cnt++];

        QPoint p1(posx[v1], posy[v1]);
        QPoint p2(posx[v2], posy[v2]);

        ItemLine* item = new ItemLine();
        QRectF rect = QRectF(std::min(posx[v1], posx[v2])+15, std::min(posy[v1], posy[v2])+15,
                             std::abs(posx[v2]-posx[v1]), std::abs(posy[v2]-posy[v1]));
        item->setLineRect(rect);
        item->setLine(QPoint(posx[v1]+15, posy[v1]+15), QPoint(posx[v2]+15, posy[v2]+15), value);
        connect(item, &ItemLine::lineClicked, this, &DijiekstraViewer::showLineInfo);
        itemLineList.push_back(item);
        scene->addItem(item);
    }
}

void DijiekstraViewer::drawPicture1()
{
    ui->tedit_output->clear();
    clearInvalidData();
    initListData();
    if (flag) {
        QMessageBox::critical(this, "错误", "无效数据！");
        ui->tedit_output->setText("无效输入！");
        return;
    }
    initDijstelaData();
    scene->update();
}

void DijiekstraViewer::drawPicture2()
{
    ui->tedit_output->clear();
    ui->tedit_input->clear();
    clearInvalidData();
    list = mInput->getStringList();
    qDebug() << "list = " << list;
    checkListData();
    if (flag) {
        QMessageBox::critical(this, "错误", "无效数据！");
        ui->tedit_output->setText("无效输入！");
        mInput->clearWidgetTable();
        mInput->close();
        return;
    }
    initDijstelaData();
    scene->update();
    mInput->close();
}

void DijiekstraViewer::on_btn_start_clicked()
{
    if (flag) return;
    auto& pt = djs.getNumbers();
    auto& px = djs.getPoints();

    for (auto& idx : pt) {
        itemLineList.at(idx)->setPenColor();
    }
    scene->update();
    pt.clear();
    px.clear();

    runDijstelaALGO();
    qDebug() << "pt.size() = " << pt.size();
    qDebug() << "px.size() = " << px.size();
    for (auto& idx : pt) {
        qDebug() << "idx = " << idx;
        itemLineList.at(idx)->setPenColor(QPen(Qt::red,2.0,Qt::SolidLine,Qt::RoundCap));
    }
    scene->update();
}


void DijiekstraViewer::on_btn_ok_clicked()
{
    drawPicture1();
}


void DijiekstraViewer::on_btn_Minput_clicked()
{
    if (!mInput) {
        mInput = new InputMartix();
        connect(mInput, &InputMartix::sucess, this, &DijiekstraViewer::drawPicture2);
    }
    mInput->show();
}


