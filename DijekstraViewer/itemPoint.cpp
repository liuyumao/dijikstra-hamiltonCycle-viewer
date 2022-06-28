#include "itemPoint.h"
#include <QBrush>
#include <QTime>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QStyleOption>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

ItemPoint::ItemPoint(QObject *parent)
    : QGraphicsItem()
{

}

QRectF ItemPoint::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void ItemPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap));
    painter->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
    painter->drawEllipse(0, 0, 30, 30);
    painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter->drawText(QRectF(0, 0, 30, 30), Qt::AlignCenter, vexInfo);

}

void ItemPoint::setVexInfo(QString text)
{
    vexInfo = text;
}

//void ItemPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "mmm" ;
//}


