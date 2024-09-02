#ifndef FLOWDIAMONDELEMENT_H
#define FLOWDIAMONDELEMENT_H
#include "flowelement.h"
class FlowDiamondElement: public FlowElement
{
public:
    FlowDiamondElement();
    void mySetScale(int index, double dx, double dy);
    FlowDiamondElement *deepClone();
};

#endif // FLOWDIAMONDELEMENT_H
