#ifndef FLOWSUBELEMENT_H
#define FLOWSUBELEMENT_H

#include "flowelement.h"

class FlowSubElement : public FlowElement {
public:
    FlowSubElement();
    virtual ~FlowSubElement(){
        delete this->innerItem;
        qDebug()<<"delete FlowSubElement";
    }
    void draw();
    void mySetScale(int index,double dx,double dy);
    FlowSubElement* deepClone();
    QGraphicsPathItem *innerItem=new QGraphicsPathItem(this);
};

#endif // FLOWSUBELEMENT_H
