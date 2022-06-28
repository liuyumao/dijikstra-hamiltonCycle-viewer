#include "base.h"
#include "itemline.h"
#include <QBrush>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QStyleOption>
#include <QStyleOptionGraphicsItem>

ItemLine::ItemLine(QObject *parent)
    : QGraphicsItem()
{
    pen = QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap);
    rect = QRectF(0, 0, 2*RADIUS, 2*RADIUS);
}

ItemLine::~ItemLine()
{

}

QRectF ItemLine::boundingRect() const
{
    return rect;
}

void ItemLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawLine(p1, p2);
}

void ItemLine::setLine(QPoint p1, QPoint p2)
{
    this->p1 = {p1.x()+RADIUS, p1.y()+RADIUS};
    this->p2 = {p2.x()+RADIUS, p2.y()+RADIUS};

    rect = QRectF(Min(p1.x(), p2.x()), Min(p1.y(), p2.y()) ,
                  Abs(p1.x() -p2.x()), Abs(p1.y() -p2.y()));
}

void ItemLine::setPenStyle(QPen pen)
{
    this->pen = pen;
}
