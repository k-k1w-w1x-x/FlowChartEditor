#ifndef FLOWELEMENT_H
#define FLOWELEMENT_H
#include<qgraphicsitem.h>
#include <QPainter>
#include <QPoint>
#include <QRect>

class FlowElement
{
public:
    virtual ~FlowElement() {}

    virtual void draw(QPainter &painter) = 0;
    virtual bool contains(const QPoint &point) const = 0;
    virtual void move(const QPoint &offset) = 0;
    virtual QGraphicsPathItem* updateMainItem();//根据边界点重新得到图形
private:
    QGraphicsPathItem *mainItem;
    QVector<QGraphicsRectItem> borderDots;
};

#endif // FLOWELEMENT_H
