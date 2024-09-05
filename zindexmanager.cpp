#include "zindexmanager.h"

ZIndexManager::ZIndexManager(QObject *parent, QList<GraphicsTextItem*> *graphicTextItems)
    : QObject(parent), gTextItems(graphicTextItems){}

void ZIndexManager::setHighestZindexForItem(FlowElement *flowelement)
{
    maxZIndex += 2;
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
    for (auto i : *gTextItems)
        if (i->followElement == flowelement)
            i->setZValue(maxZIndex + 1);
};
void ZIndexManager::setHighestZindexForItem(GraphicsTextItem *textelement)
{
    if (textelement->followElement == nullptr)
    {
        maxZIndex += 2;
        textelement->setZValue(maxZIndex);
    }
};
