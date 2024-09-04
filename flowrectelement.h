#ifndef FLOWRECTELEMENT_H
#define FLOWRECTELEMENT_H

#include "flowelement.h"

class FlowRectElement : public FlowElement {
public:
    FlowRectElement();
    FlowRectElement* deepClone() override;
    void serialize(QDataStream& out, const FlowElement& element) override;
    static FlowElement* deSerialize(QDataStream& in) ;
};

#endif // FLOWRECTELEMENT_H
