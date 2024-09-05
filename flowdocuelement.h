#ifndef FLOWDOCUELEMENT_H
#define FLOWDOCUELEMENT_H
#include "flowelement.h"
class FlowDocuElement: public FlowElement
{
public:
    FlowDocuElement();
    void draw();
    void mySetScale(int index, double dx, double dy);
    FlowDocuElement *deepClone();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWDOCUELEMENT_H
