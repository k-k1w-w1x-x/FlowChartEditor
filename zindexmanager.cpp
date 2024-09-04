#include "zindexmanager.h"

ZIndexManager::ZIndexManager(QObject *parent ) : QObject(parent) {}

void ZIndexManager::setHighestZindexForItem(FlowElement *flowelement)
{
    ++maxZIndex;
    flowelement->mainItem->setZValue(maxZIndex);
    if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(flowelement)){
        subElement->innerItem->setZValue(maxZIndex);
    }
    for(const auto&dot:flowelement->borderDots){
        dot->setZValue(maxZIndex);
    }
    for(const auto&dot:flowelement->arrowDots){
        dot->setZValue(maxZIndex);
    }
};
void ZIndexManager::setHighestZindexForItem(GraphicsTextItem *textelement)
{
    ++maxZIndex;
    textelement->setZValue(maxZIndex);
};
