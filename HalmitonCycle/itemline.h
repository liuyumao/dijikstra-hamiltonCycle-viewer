// 这是一个 连线类 用于画结点之间的连线
#ifndef ITEMLINE_H
#define ITEMLINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>

class ItemLine : public QGraphicsItem
{
public:
    explicit ItemLine(QObject *parent = nullptr);
    ~ItemLine();

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget  *widget);
    void setLine(QPoint p1, QPoint p2);
    void setPenStyle(QPen pen = QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap));

private:
    QPoint p1, p2;
    QString dist;
    QPen pen;
    QRectF rect;
};

#endif // ITEMLINE_H
