#ifndef FLOWARROWELEMENT_H
#define FLOWARROWELEMENT_H
#include "flowelement.h"
#include <QGraphicsLineItem>
#include <QPainter>

class FlowArrowElement: public FlowElement
{
public:
    FlowArrowElement();
    void draw();
    QGraphicsRectItem *startDot ;
    QGraphicsRectItem *endDot ;
    QGraphicsRectItem *startElementDot = nullptr;
    QGraphicsRectItem *endElementDot =nullptr;
    QPointF passingPoint;
    void move(double dx,double dy);
    void mySetScale(int index,double dx,double dy);
    void drawHalfCircle(QPainterPath &path,const QPointF &center, const QPointF &point1, const QPointF &point2);
};

#endif // FLOWARROWELEMENT_H
