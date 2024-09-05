#ifndef FLOWPLAYGROUNDELEMENT_H
#define FLOWPLAYGROUNDELEMENT_H

#include "flowelement.h"
#include <QPainter>
class FlowPlaygroundElement: public FlowElement
{
public:
    FlowPlaygroundElement();
    void draw();
    void drawHalfCircle(QPainterPath &path, const QPointF &point1, const QPointF &point2);
    FlowPlaygroundElement *deepClone();
    void calArrowDots();
    void resetArrowDots();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWPLAYGROUNDELEMENT_H
