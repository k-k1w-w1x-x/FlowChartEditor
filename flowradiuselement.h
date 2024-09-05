#ifndef FLOWRADIUSELEMENT_H
#define FLOWRADIUSELEMENT_H

#include "flowelement.h"
class FlowRadiusElement : public FlowElement
{
public:
    FlowRadiusElement();
    void draw();
    FlowRadiusElement *deepClone();
    static FlowElement *deSerialize(QDataStream &in);
    void serialize(QDataStream &out, const FlowElement &element);
};

#endif // FLOWRADIUSELEMENT_H
