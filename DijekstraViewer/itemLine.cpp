#include "itemLine.h"
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

ItemLine::ItemLine(QObject *parent)
    : QGraphicsItem()
{
    pen = QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap);
    this->setAcceptHoverEvents(true);
    rect = QRectF(0, 0, 30, 30);
    sPath = "v1->v2";
    textmode = Qt::AlignLeft;
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
//    painter->set


    int cx = (p1.x() + p2.x()) / 2, cy = (p1.y() + p2.y()) / 2;
//    painter->drawRect(QRectF(cx-15, cy-15, 30, 30));
    painter->drawText(QRectF(cx-15, cy-15, 30, 30), textmode, dist);

}

void ItemLine::setLine(QPoint p1, QPoint p2, QString dist)
{
    this->p1 = p1;
    this->p2 = p2;
    this->dist = dist;
}

void ItemLine::setPenColor(QPen pen)
{
    this->pen = pen;

}

void ItemLine::setLineRect(QRectF rect)
{
    this->rect = rect;
}

void ItemLine::setLinesPath(QString s)
{
    sPath = s;
}

void ItemLine::setTextMode(Qt::AlignmentFlag textmode)
{
    this->textmode = textmode;
}


void ItemLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit lineClicked((p1.x()+p2.x())/2-15, (p1.y() + p2.y())/2, sPath);
}
