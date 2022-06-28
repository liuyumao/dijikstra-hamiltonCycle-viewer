#ifndef ITEMLINE_H
#define ITEMLINE_H


#include <QObject>
#include <QGraphicsItem>
#include <QPen>

class ItemLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ItemLine(QObject *parent = nullptr);
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setLine(QPoint p1, QPoint p2, QString dist);
    void setPenColor(QPen pen = QPen(Qt::black,2.0,Qt::SolidLine,Qt::RoundCap));
    void setLineRect(QRectF rect);
    void setLinesPath(QString s);
    void setTextMode(Qt::AlignmentFlag textmode);
private:
    QPoint p1, p2;
    QString dist;
    QPen pen;
    QRectF rect;
    QString sPath;
    Qt::AlignmentFlag textmode;
signals:
    void lineClicked(int _x, int _y, QString sPath);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ITEM_H
