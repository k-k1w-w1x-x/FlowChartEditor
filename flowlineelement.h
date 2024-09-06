#ifndef FLOWLINEELEMENT_H
#define FLOWLINEELEMENT_H
#include "flowelement.h"
#include <QGraphicsLineItem>
#include <QPainter>
#include <flowarrowelement.h>

class FlowLineElement: public FlowArrowElement
{
public:
    FlowLineElement();
    void draw();
    FlowLineElement* deepClone();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWLINEELEMENT_H
