// 这是一个描点类 可以可视化画出六边形点，如果需要其他形状，可以自行改写
#ifndef ITEMPOINT_H
#define ITEMPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QPolygon>
#include <QPen>

class ItemPoint : public QGraphicsItem
{
public:
    explicit ItemPoint(QObject *parent = nullptr);
    ~ItemPoint();

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setVexInfo(QString text);
    void setPenStyle(QPen pen = QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap));
    void setBrushStyle(QBrush brush);
    void initHexagonLine(); // 根据矩形大小计算画正六边形，矩形边长为RADIUS
private:
    double const sqrtThree;
private:
    QString vexInfo;
    QBrush brush;
    QPolygon plyg;
    QPen pen;
};

#endif // ITEMPOINT_H
