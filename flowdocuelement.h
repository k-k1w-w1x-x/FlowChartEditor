#ifndef FLOWDOCUELEMENT_H
#define FLOWDOCUELEMENT_H
#include "flowelement.h"
class FlowDocuElement: public FlowElement
{
public:
    FlowDocuElement();
    void draw();
    void scale(int index, double dx, double dy);
};

#endif // FLOWDOCUELEMENT_H
