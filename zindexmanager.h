#ifndef ZINDEXMANAGER_H
#define ZINDEXMANAGER_H

#include <QObject>
#include <QGraphicsItem>
#include <QMap>
#include<vector>
#include <flowelement.h>
#include<graphicstextitem.h>
class ZIndexManager : public QObject {
    Q_OBJECT

public:
    // 构造函数
    explicit ZIndexManager(QObject *parent = nullptr);

    // // 添加一个 QGraphicsItem，并设置它的 z-index
    void setHighestZindexForItem(FlowElement* flowelement);
    void setHighestZindexForItem(GraphicsTextItem* flowelement);
    // void adjustZIndexForAllElementOnCanvas(QList<FlowElement*>x,std::vector<GraphicsTextItem*>y);


private:
    int maxZIndex=0;
};

#endif // ZINDEXMANAGER_H
