#include "base.h"
#include "inputmartix.h"
#include "ui_inputmartix.h"
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QMessageBox>

InputMartix::InputMartix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputMartix)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);
    setWindowTitle("顶点关系表");
    setMouseTracking(true); //开启鼠标追踪
    setMinimumSize(520,420);
    clearWidgetTable();
}

InputMartix::~InputMartix()
{
    delete ui;
}

QStringList InputMartix::getStringList()
{
    return list;
}

void InputMartix::clearWidgetTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->spinBox->setValue(0);
}


void InputMartix::on_btn_ok_clicked()
{
    int n = ui->spinBox->value();
    vexNum = n;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(n);
    ui->tableWidget->setRowCount(n);

    ui->tableWidget->horizontalHeader()->setFixedHeight(28);
    ui->tableWidget->verticalHeader()->setFixedWidth(30);

    for (int i = 0; i < n; i ++ ) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item->setText("v" + QString::number(i));
        ui->tableWidget->setHorizontalHeaderItem(i, item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item1->setText("v" + QString::number(i));
        //ui->tableWidget->setItem(i, 0, item1);
        ui->tableWidget->setVerticalHeaderItem(i, item1);
    }

    for (int i = 0; i < n; i ++ ) {
        QTableWidgetItem* spItem = new QTableWidgetItem("---");
        spItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i, i, spItem);
        for (int j = i+1; j < n; j ++ ) {
             QCheckBox *item = new QCheckBox(this);
             QWidget *wgt = new QWidget(this);
             QHBoxLayout *hLayout = new QHBoxLayout();
             hLayout->addWidget(item);
             hLayout->setSpacing(0);
             hLayout->setContentsMargins(10, 5, 10, 5);
             hLayout->setAlignment(item, Qt::AlignCenter);
             wgt->setLayout(hLayout);
             ui->tableWidget->setCellWidget(i, j, wgt);
        }
    }
    ui->btn_ok->setEnabled(false);
}



void InputMartix::on_btn_submit_clicked()
{
    arcNum = 0;
    list.clear();
    QStringList tmp;
    for (int i = 0; i < vexNum; i ++ ) {
        for (int j = i+1; j < vexNum; j ++ ) {
            if (QWidget *w = ui->tableWidget->cellWidget(i, j))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                if ( checkBox )
                {
                    if ( checkBox->checkState() == Qt::Checked ) {//选中
                        arcNum ++;
                        tmp << QString::number(i) << QString::number(j);
                    }
                }
            }
        }
    }
    list << QString::number(vexNum) << QString::number(arcNum);
    if (!tmp.empty()) list += tmp;

    makeFullTable();

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, tr("提示"), tr("确认吗?点击取消可回头修改"),
                                          QMessageBox::Ok | QMessageBox::Cancel);

    msgBox->button(QMessageBox::Ok)->setText("确认");
    msgBox->button(QMessageBox::Cancel)->setText("取消");

    int ret = msgBox->exec();

    delete msgBox;
    msgBox = nullptr;

    if (ret == QMessageBox::Ok) {
        ui->btn_ok->setEnabled(true);
        emit this->sucess();
    }
}

void InputMartix::makeFullTable()
{
    int n = vexNum;
    for (int i = 0; i < n; i ++ ) {
        for (int j = i+1; j < n; j ++ ) {
            QCheckBox *item = new QCheckBox(this);
            QWidget *wgt = new QWidget(this);
            QHBoxLayout *hLayout = new QHBoxLayout();
            hLayout->addWidget(item);
            hLayout->setSpacing(0);
            hLayout->setContentsMargins(10, 5, 10, 5);
            hLayout->setAlignment(item, Qt::AlignCenter);
            wgt->setLayout(hLayout);
            ui->tableWidget->setCellWidget(j, i, wgt);
            if (QWidget *w = ui->tableWidget->cellWidget(i, j))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                if ( checkBox )
                {
                    if ( checkBox->checkState() == Qt::Unchecked ) {//未选中
                        item->setCheckState(Qt::Unchecked);
                    } else {
                        item->setCheckState(Qt::Checked);
                    }
                }
            }
        }
    }
}

void InputMartix::on_spinBox_valueChanged(int)
{
    ui->btn_ok->setEnabled(true);
    ui->tableWidget->clear();
}


void InputMartix::on_btn_quit_clicked()
{
    this->close();
}

void InputMartix::mousePressEvent(QMouseEvent *e)
{
    point = e->globalPos();
}

void InputMartix::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) {
        int dx = e->globalX() - point.x();
        int dy = e->globalY() - point.y();
        point = e->globalPos();
        move(x() + dx, y() + dy);
    }
}

void InputMartix::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - point.x();
    int dy = e->globalY() - point.y();
    move(x() + dx, y() + dy);
}
