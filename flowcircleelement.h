#ifndef FLOWCIRCLEELEMENT_H
#define FLOWCIRCLEELEMENT_H
#include "flowelement.h"

class FlowCircleElement: public FlowElement
{
public:
    FlowCircleElement();
    void draw();
    // void scale(int index,double dx,double dy);
};

#endif // FLOWCIRCLEELEMENT_H
