#ifndef FLOWCIRCLEELEMENT_H
#define FLOWCIRCLEELEMENT_H
#include "flowelement.h"

class FlowCircleElement: public FlowElement
{
public:
    FlowCircleElement();
    void draw();
    FlowCircleElement *deepClone();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWCIRCLEELEMENT_H
