#ifndef FLOWRADIUSELEMENT_H
#define FLOWRADIUSELEMENT_H

#include "flowelement.h"
class FlowRadiusElement : public FlowElement
{
public:
    FlowRadiusElement();
    void draw();
    FlowRadiusElement *deepClone();
};

#endif // FLOWRADIUSELEMENT_H
