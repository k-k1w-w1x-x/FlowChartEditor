#include "flowrectelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5

FlowRectElement::FlowRectElement() : FlowElement() {
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(250, 200);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(150, 200);

    controlDots = borderDots;
    calArrowDots();

    // 绘制路径
    draw();
}

FlowRectElement *FlowRectElement::deepClone()
{
    FlowRectElement* clonedElement = new FlowRectElement();
    clonedElement->borderDots.clear();
    clonedElement->controlDots.clear();

    clonedElement->contentColor = this->contentColor;
    clonedElement->selected = this->selected;

    clonedElement->mainItem->setPath(this->mainItem->path());
    clonedElement->mainItem->setBrush(this->mainItem->brush());
    clonedElement->mainItem->setPen(this->mainItem->pen());

    int cont=0;
    for (QGraphicsRectItem* borderDot : this->borderDots) {
        QGraphicsRectItem* newDot = new QGraphicsRectItem(borderDot->rect());
        newDot->setBrush(borderDot->brush());
        newDot->setPen(borderDot->pen());
        newDot->setPos(borderDot->pos());
        clonedElement->borderDots.append(newDot);
        if(cont<4){
            clonedElement->controlDots.append(newDot);
            cont++;
        }
    }

    clonedElement->setPos(this->pos());
    clonedElement->setRotation(this->rotation());
    clonedElement->setScale(this->scale());

    return clonedElement;
}

void FlowRectElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    // 获取 QGraphicsPathItem 以序列化 QPainterPath、QPen 和 QBrush
    int type=0;
    out<<type;
    if (element.mainItem) { // 假设 mainItem 是指向 QGraphicsPathItem 的指针
        ElementSerializer::serializePainterPath(element.mainItem->path(), out); // 序列化路径
        ElementSerializer::serializePen(element.mainItem->pen(), out); // 序列化画笔
        ElementSerializer::serializeBrush(element.mainItem->brush(), out); // 序列化画刷
    }
    out<<element.borderDots.size();
    for(auto dot:element.borderDots){
        ElementSerializer::serializeGraphicsRectItem(dot,out);
    }
}
FlowElement* FlowRectElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载
    // QPointF pos;
    // qreal rotation;
    // qreal scale;

    // 反序列化通用属性
    // in >> pos >> rotation >> scale;
    // qDebug()<<pos << rotation << scale;
    // 获取 QGraphicsPathItem 以反序列化 QPainterPath、QPen 和 QBrush

    FlowRectElement *cur = new FlowRectElement();
    if (cur->mainItem) {
        QPainterPath path = ElementSerializer::deserializePainterPath(in);
        cur->mainItem->setPath(path);

        QPen pen = ElementSerializer::deserializePen(in);
        cur->mainItem->setPen(pen);

        QBrush brush = ElementSerializer::deserializeBrush(in);
        cur->mainItem->setBrush(brush);
    }
    qsizetype borderDotsSize;
    in>>borderDotsSize;
    cur->borderDots.clear();

    for(int i=0;i<borderDotsSize;i++){
        cur->borderDots.append(ElementSerializer::deserializeGraphicsRectItem(in));
    }
    cur->controlDots = cur->borderDots;//只对正方形成立

    // element.setPos(pos);
    // element.setRotation(rotation);
    // element.setScale(scale);

    return cur;
}




