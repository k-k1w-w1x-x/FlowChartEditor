#ifndef FLOWDIAMONDELEMENT_H
#define FLOWDIAMONDELEMENT_H
#include "flowelement.h"
class FlowDiamondElement: public FlowElement
{
public:
    FlowDiamondElement();
    void scale(int index, double dx, double dy);
};

#endif // FLOWDIAMONDELEMENT_H
