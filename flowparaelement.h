#ifndef FLOWPARAELEMENT_H
#define FLOWPARAELEMENT_H
#include "flowelement.h"
class FlowParaElement:public FlowElement
{
public:
    FlowParaElement();
    FlowParaElement *deepClone();
    void mySetScale(int index,double dx,double dy);
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWPARAELEMENT_H
