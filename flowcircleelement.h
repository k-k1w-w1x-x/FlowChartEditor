#ifndef FLOWCIRCLEELEMENT_H
#define FLOWCIRCLEELEMENT_H
#include "flowelement.h"
#include <QPainter>
class FlowCircleElement: public FlowElement
{
public:
    FlowCircleElement();
    void draw();
};

#endif // FLOWCIRCLEELEMENT_H
