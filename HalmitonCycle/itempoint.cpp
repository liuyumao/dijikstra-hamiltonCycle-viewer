#include "base.h"
#include "itempoint.h"
#include <QBrush>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPalette>
#include <QStyleOption>
#include <QStyleOptionGraphicsItem>
#include <QtMath>

ItemPoint::ItemPoint(QObject *parent)
    : QGraphicsItem(), sqrtThree(1.7320508)
{
    brush = QBrush(QColor(243,104,224),Qt::SolidPattern);
    initHexagonLine();
}

ItemPoint::~ItemPoint()
{

}

QRectF ItemPoint::boundingRect() const
{
    return QRectF(0, 0, 2*RADIUS, 2*RADIUS);
}

void ItemPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->setBrush(brush);//QBrush(Qt::yellow,Qt::SolidPattern)
    painter->drawConvexPolygon(plyg);
    painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter->drawText(QRectF(0, 0, 2*RADIUS, 2*RADIUS), Qt::AlignCenter, vexInfo);
}

void ItemPoint::setVexInfo(QString text)
{
    vexInfo  = text;
}

void ItemPoint::setPenStyle(QPen pen)
{
    this->pen = pen;
}

void ItemPoint::setBrushStyle(QBrush brush)
{
    this->brush = brush;
}

void ItemPoint::initHexagonLine()
{
    int x = RADIUS / 2;
    int x3 = 3 * x, x4 = 4 * x;
    int y1 = floor(sqrtThree * x);
    int y2 = floor(sqrtThree * 2 * x);

    plyg.setPoints(6, x, 0, x3, 0, x4, y1, x3, y2, x, y2, 0, y1);
}


