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
    void move(double dx,double dy) ;
    void mySetScale(int index,double dx,double dy);
    QPointF passingPoint;
    FlowArrowElement* deepClone();
    ~FlowArrowElement();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWARROWELEMENT_H
