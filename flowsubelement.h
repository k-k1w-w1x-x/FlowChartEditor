#ifndef FLOWSUBELEMENT_H
#define FLOWSUBELEMENT_H

#include "flowelement.h"

class FlowSubElement : public FlowElement {
public:
    FlowSubElement();
    void draw();
    void scale(int index,double dx,double dy);
    QGraphicsPathItem *innerItem=new QGraphicsPathItem;
};

#endif // FLOWSUBELEMENT_H
