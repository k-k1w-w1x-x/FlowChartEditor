#ifndef FLOWCIRCLEELEMENT_H
#define FLOWCIRCLEELEMENT_H
#include "flowelement.h"

class FlowCircleElement: public FlowElement
{
public:
    FlowCircleElement();
    void draw();
    FlowCircleElement *deepClone();
};

#endif // FLOWCIRCLEELEMENT_H
