#ifndef FLOWPARAELEMENT_H
#define FLOWPARAELEMENT_H
#include "flowelement.h"
class FlowParaElement:public FlowElement
{
public:
    FlowParaElement();
    FlowParaElement *deepClone();
    void mySetScale(int index,double dx,double dy);
};

#endif // FLOWPARAELEMENT_H
