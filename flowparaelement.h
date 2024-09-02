#ifndef FLOWPARAELEMENT_H
#define FLOWPARAELEMENT_H
#include "flowelement.h"
class FlowParaElement:public FlowElement
{
public:
    FlowParaElement();
    void scale(int index,double dx,double dy);
};

#endif // FLOWPARAELEMENT_H
