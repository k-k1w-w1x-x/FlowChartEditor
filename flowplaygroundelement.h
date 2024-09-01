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
};

#endif // FLOWPLAYGROUNDELEMENT_H
