#ifndef FLOWPARAELEMENT_H
#define FLOWPARAELEMENT_H
#include "flowelement.h"
class FlowParaElement:public FlowElement
{
public:
    FlowParaElement();
    FlowParaElement *deepClone();
};

#endif // FLOWPARAELEMENT_H
