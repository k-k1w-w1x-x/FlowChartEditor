#include "zindexmanager.h"

ZIndexManager::ZIndexManager(QObject *parent ) : QObject(parent) {}

void ZIndexManager::setHighestZindexForItem(FlowElement *flowelement)
{
    ++maxZIndex;
    flowelement->mainItem->setZValue(maxZIndex);
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
