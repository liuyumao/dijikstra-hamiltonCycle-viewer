#include <QtMath>
#include <QMessageBox>
#include <QFile>
#include "base.h"
#include "hamiltoncycle.h"
#include "ui_hamiltoncycle.h"

HamiltonCycle::HamiltonCycle(QWidget *parent)
    : QWidget(parent), Pi(3.1415926)
    , ui(new Ui::HamiltonCycle)
{
    ui->setupUi(this);
    setWindowTitle("哈密顿回路判断");
    initQssStyle();
    setMinimumSize(750, 580);

    ui->tedit_input->setText("6 10\n0 1\n0 2\n0 3\n0 4\n0 5\n1 2\n2 3\n2 4\n3 4\n4 5");
    ui->btn_start->setEnabled(false);

    modeInput = myInputMode::ordinaryMode;

    scene = new QGraphicsScene();
    mInput= new InputMartix();
    connect(mInput, &InputMartix::sucess, this, &HamiltonCycle::getDataSlot);
    ui->graphicsView->setScene(scene);

    this->resize(850, 700);
}

HamiltonCycle::~HamiltonCycle()
{
    delete ui;
}

void HamiltonCycle::initQssStyle()
{
    QFile qss(":/qss/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

void HamiltonCycle::translateList()
{
    for (auto& item : list) {
        hdata.push_back(item.toInt());
    }
}

void HamiltonCycle::initVexAndArc()
{
    vexNum = list[0].toInt();
    arcNum = list[1].toInt();
}

void HamiltonCycle::updateGraphics()
{
    for (auto& item: itemPointList) {
        item->setBrushStyle(QBrush(QColor(102, 51, 153),Qt::SolidPattern));
        item->setPenStyle(QPen(Qt::white,2.0,Qt::SolidLine,Qt::RoundCap));
    }
    for (auto& item: itemLineList) {
        item->setPenStyle(QPen(Qt::blue,2.0,Qt::SolidLine,Qt::RoundCap));
    }
    scene->update();
}

void HamiltonCycle::work()
{
    initHamiltonData();
    runHamiltonALGO();
}

void HamiltonCycle::draw()
{
    ui->btn_start->setEnabled(true);

    initListData();
    if (!checkData()) {
        QMessageBox::StandardButton btn = QMessageBox::information(this, "错误", "输入有误，请检查！\n是否清空？",
                                          QMessageBox::Ok, QMessageBox::Cancel);
        if (btn == QMessageBox::Ok) {
            ui->tedit_input->clear();
            ui->btn_start->setEnabled(false);
            clearData();
        }
        return;
    }
    initVexAndArc();
    locatePoints(vexNum);
    drawLine();
    drawPoint();
}

void HamiltonCycle::locatePoints(int n)
{
    posx.clear();
    posy.clear();

    int swidth  = ui->graphicsView->width();
    int sheight = ui->graphicsView->height();
    int r = Min(swidth, sheight) / 2 - 60;
    int step = 360 / n, angle = 0;

    for (int i = 0; i < n; i ++ ) {
        int x = r * qCos(angle * Pi / 180.0) - RADIUS; // 这里减去raduis即六边形点矩形的边长
        int y = r * qSin(angle * Pi / 180.0) - RADIUS; // 是为了使得所画的点能够在graphicsView中上下左右对称
        posx.push_back(x);
        posy.push_back(y);
        angle += step;
    }
}

void HamiltonCycle::initHamiltonData()
{
    ham.init(hdata);
}

void HamiltonCycle::runHamiltonALGO()
{
    if (ham.check()) {
        outText = "存在哈密顿回路，其中之一为：\n";
        outText += ham.getCycle() + "\n\n";
        ui->tedit_output->setText(outText);
        updateGraphics();
    } else {
          outText = "不存在哈密顿回路!";
    }
    ui->tedit_output->setText(outText);
    ui->btn_ok->setEnabled(true);
}

void HamiltonCycle::initListData()
{
    clearData();
    if (modeInput) {
        list = mInput->getStringList();
        ui->tedit_input->clear();
        ui->tedit_input->setText("矩阵模式已输入!\n点击开始即可");
        ui->btn_ok->setEnabled(false);
        modeInput = myInputMode::ordinaryMode;
    } else {
        QString reader = ui->tedit_input->document()->toPlainText();
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
                return;
            }
            tmp += reader[i];
        }
        if (tmp != "") list << tmp;
    }
    translateList();
}

void HamiltonCycle::clearData()
{
    ui->tedit_output->clear();
    scene->clear();
    list.clear();
    hdata.clear();
    itemPointList.clear();
    itemLineList.clear();
    posx.clear();
    posy.clear();
}

bool HamiltonCycle::checkData()
{
    if (list.size() < 2) return false;
    QString v1 = list[0], l1 = list[1];

    if (!v1.toInt() || !l1.toInt()) return false;

    int edges = l1.toInt();
    int ftvex = v1.toInt();

    if (2 * edges != list.size()-2) return false;
    for (int i = 2; i < list.size(); i ++) {
        int t = list[i].toInt();
        if (!t && list[i] != "0") return false;
        if (t >= ftvex) {
            //qDebug() << "q = " << t;
            QMessageBox::warning(this, "警告", "输入从0开始到n-1结束！");
            return false;
        }
    }
    return true;
}

void HamiltonCycle::drawPoint()
{
    for (int i = 0; i < vexNum; i ++) {
        ItemPoint* item = new ItemPoint();  
        item->setBrushStyle(QBrush(QColor(253, 121, 168), Qt::SolidPattern));
        //item->setPenStyle(QPen(Qt::white, 2.0, Qt::SolidLine, Qt::RoundCap));
        item->setVexInfo("v"+QString::number(i));
        itemPointList.push_back(item);
        scene->addItem(item);
        item->setPos(posx[i], posy[i]);
    }
}

void HamiltonCycle::drawLine()
{
    int cnt = 2;

    for (int i = 0; i < arcNum; i ++) {
        int v1 = list[cnt++].toInt(), v2 = list[cnt++].toInt();

        QPoint p1(posx[v1], posy[v1]);
        QPoint p2(posx[v2], posy[v2]);

        ItemLine* item = new ItemLine();

        item->setPenStyle(QPen(QColor(52, 73, 94), 2.0, Qt::SolidLine, Qt::RoundCap));
        item->setLine(p1, p2);
        itemLineList.push_back(item);
        scene->addItem(item);
        item->setPos(0, 0); // 这句加不加无所谓，默认子绘图在父亲的0.0位置
    }
    scene->update();
}


void HamiltonCycle::on_btn_ok_clicked()
{
    draw();
}


void HamiltonCycle::on_btn_mipt_clicked()
{
    clearData();
    mInput->clearWidgetTable();
    mInput->show();
}

void HamiltonCycle::getDataSlot()
{
    modeInput = myInputMode::matrixMode;
    draw();
    mInput->close();
}

void HamiltonCycle::on_btn_start_clicked()
{
    work();
}

void HamiltonCycle::on_btn_recover_clicked()
{
    ui->tedit_input->setText("6 10\n0 1\n0 2\n0 3\n0 4\n0 5\n1 2\n2 3\n2 4\n3 4\n4 5");
    ui->btn_ok->setEnabled(true);
    ui->btn_ok->click();
}


void HamiltonCycle::mousePressEvent(QMouseEvent* e)
{
    point = e->globalPos();
}

void HamiltonCycle::mouseMoveEvent(QMouseEvent* e)
{
    if (e->buttons() & Qt::LeftButton) {
        int dx = e->globalX() - point.x();
        int dy = e->globalY() - point.y();
        point = e->globalPos();
        move(x() + dx, y() + dy);
    }
}

void HamiltonCycle::mouseReleaseEvent(QMouseEvent* e)
{
        int dx=e->globalX()-point.x();
        int dy=e->globalY()-point.y();
        move(x()+dx,y()+dy);
}

void HamiltonCycle::resizeEvent(QResizeEvent *event)
{
    int x = ui->graphicsView->width();
    int y = ui->graphicsView->height();
    scene->setSceneRect(- x / 2, - y / 2, x, y);
}
