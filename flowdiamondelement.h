#ifndef FLOWDIAMONDELEMENT_H
#define FLOWDIAMONDELEMENT_H
#include "flowelement.h"
class FlowDiamondElement: public FlowElement
{
public:
    FlowDiamondElement();
    void mySetScale(int index, double dx, double dy);
    FlowDiamondElement *deepClone();
    void calArrowDots();
    void resetArrowDots();
    void draw();
    void serialize(QDataStream &out, const FlowElement &element);
    static FlowElement* deSerialize(QDataStream& in);
};

#endif // FLOWDIAMONDELEMENT_H
