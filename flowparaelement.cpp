#include "flowparaelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5
FlowParaElement::FlowParaElement(): FlowElement()
{
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(225, 175);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(125, 175);

    controlDots = borderDots;
    calArrowDots();

    // 绘制路径
    draw();
}
FlowParaElement *FlowParaElement::deepClone()
{
    FlowParaElement* clonedElement = new FlowParaElement();
    clonedElement->borderDots.clear();
    clonedElement->controlDots.clear();

    clonedElement->borderColor=this->borderColor;
    clonedElement->contentColor = this->contentColor;
    clonedElement->selected = this->selected;

    clonedElement->mainItem->setPath(this->mainItem->path());
    clonedElement->mainItem->setBrush(this->mainItem->brush());
    clonedElement->mainItem->setPen(this->mainItem->pen());
    clonedElement->rotangle = this->rotangle;

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
void FlowParaElement::mySetScale(int index,double dx,double dy)//默认4个控制点，如果不是需要重写，规定从左上角开始顺时针
{
    qDebug()<<"开始缩放";
    controlDots.at(index)->moveBy(dx, dy);
    if(index==0){
        borderDots.at(1)->moveBy(0, dy);
        borderDots.at(3)->moveBy(dx, 0);
    }
    if(index==1){
        borderDots.at(0)->moveBy(0, dy);
        borderDots.at(2)->moveBy(dx, 0);
    }
    if(index==2){
        borderDots.at(3)->moveBy(0, dy);
        borderDots.at(1)->moveBy(dx, 0);
    }
    if(index==3){
        borderDots.at(2)->moveBy(0, dy);
        borderDots.at(0)->moveBy(dx, 0);
    }
    draw();
}
void FlowParaElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=4;
    out<<type;
    qDebug()<<type;
    ElementSerializer::serializeDouble(element.rotangle,out);
    ElementSerializer::serializeColor(element.contentColor,out);
    ElementSerializer::serializeColor(element.borderColor,out);
    out<<element.borderDots.size();
    for(auto dot:element.borderDots){
        ElementSerializer::serializeGraphicsRectItem(dot,out);
    }
}
FlowElement* FlowParaElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载

    FlowParaElement *cur = new FlowParaElement();

    cur->rotangle = ElementSerializer::deserializeDouble(in);
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
