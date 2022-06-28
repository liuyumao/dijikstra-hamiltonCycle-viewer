#ifndef ItemPointPOINT_H
#define ItemPointPOINT_H


#include <QObject>
#include <QGraphicsItem>

class ItemPoint : public QGraphicsItem
{
public:
    explicit ItemPoint(QObject *parent = nullptr);
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setVexInfo(QString text);
private:
    QString vexInfo;

    // QGraphicsItem interface
protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ItemPointPOINT_H
