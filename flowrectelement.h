#ifndef FLOWRECTELEMENT_H
#define FLOWRECTELEMENT_H

#include "flowelement.h"

class FlowRectElement : public FlowElement {
public:
    FlowRectElement();
    FlowRectElement* deepClone();
};

#endif // FLOWRECTELEMENT_H
