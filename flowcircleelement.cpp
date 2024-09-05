#include "flowcircleelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5
FlowCircleElement::FlowCircleElement(): FlowElement()
{
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
    // qDebug()<<"arrow:"<<arrowDots.size();

    // 绘制路径
    draw();
}

void FlowCircleElement::draw() {
    qDebug() << "draw";

    QPainterPath path;

    // 确保有足够的控制点
    if (borderDots.size() >= 4) {
        // 获取外接矩形的左上角和右下角点
        QPointF topLeft = borderDots[0]->scenePos();
        QPointF bottomRight = borderDots[2]->scenePos();

        // 计算外接矩形
        QRectF boundingRect(topLeft, bottomRight);

        // 添加外接矩形内的椭圆
        path.addEllipse(boundingRect);
    }

    // 设置控制点的外观
    for (QGraphicsRectItem* borderDot : borderDots) {
        borderDot->setBrush(Qt::red);
        QPen pen(Qt::red);
        borderDot->setPen(pen);
    }
    // 设置箭头点的外观
    resetArrowDots();
    for(QGraphicsRectItem* arrowDot : arrowDots){
        arrowDot->setBrush(Qt::black);
        QPen pen(Qt::black);
        arrowDot->setPen(pen);
    }
    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // 设置默认线条宽度
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}
FlowCircleElement *FlowCircleElement::deepClone()
{
    FlowCircleElement* clonedElement = new FlowCircleElement();

    clonedElement->borderDots.clear();
    clonedElement->controlDots.clear();
    clonedElement->borderColor=this->borderColor;
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
void FlowCircleElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=7;
    out<<type;
    qDebug()<<type;
    ElementSerializer::serializeColor(element.contentColor,out);
    ElementSerializer::serializeColor(element.borderColor,out);
    out<<element.borderDots.size();
    for(auto dot:element.borderDots){
        ElementSerializer::serializeGraphicsRectItem(dot,out);
    }
}
FlowElement* FlowCircleElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载

    FlowCircleElement *cur = new FlowCircleElement();
    cur->contentColor = ElementSerializer::deserializeColor(in);
    cur->borderColor = ElementSerializer::deserializeColor(in);
    qsizetype borderDotsSize;
    in>>borderDotsSize;
    qDebug()<<borderDotsSize<<" bordersize";
    cur->borderDots.clear();
    cur->controlDots.clear();
    int cont=0;
    for(int i=0;i<borderDotsSize;i++){
        cur->borderDots.append(ElementSerializer::deserializeGraphicsRectItem(in));
        if(cont<4){
            cont++;
            cur->controlDots.append(cur->borderDots.last());
        }
    }
    cur->resetArrowDots();
    cur->draw();

    return cur;
}
