#include "flowdiamondelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5

FlowDiamondElement::FlowDiamondElement(): FlowElement()
{
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 7, 7), this));  // 左
    borderDots.last()->setPos(150, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 7, 7), this));  // 上
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 7, 7), this));  // 右
    borderDots.last()->setPos(350, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 7, 7), this));  // 下
    borderDots.last()->setPos(250, 200);

    controlDots = borderDots;
    calArrowDots();

    // 绘制路径
    draw();
}

void FlowDiamondElement::draw() {
    // qDebug() << "draw";

    QPainterPath path;

    // 依次取出两个小矩形的中心点，并绘制线条
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 1; i < borderDots.size(); ++i) {
        path.lineTo(borderDots[i]->scenePos() + borderDots[i]->rect().center());
    }
    for(QGraphicsRectItem* borderDot : borderDots){
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

    path.closeSubpath();

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));
    // 设置默认线条宽度
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}

void FlowDiamondElement::mySetScale(int index, double dx, double dy)
{
    qDebug() << "开始缩放";
    if (index == 0) {  // 左
        controlDots.at(0)->moveBy(dx, 0);
        controlDots.at(3)->moveBy(dx*0.5, 0);
        controlDots.at(1)->moveBy(dx*0.5, 0);
    } else if (index == 1) {  // 上
        controlDots.at(1)->moveBy(0, dy);
        controlDots.at(2)->moveBy(0, dy*0.5);
        controlDots.at(0)->moveBy(0, dy*0.5);
    } else if (index == 2) {  // 右
        controlDots.at(2)->moveBy(dx, 0);
        controlDots.at(3)->moveBy(dx*0.5, 0);
        controlDots.at(1)->moveBy(dx*0.5, 0);
    }  else if (index == 3) {  // 下
        controlDots.at(3)->moveBy(0, dy);
        controlDots.at(2)->moveBy(0, dy*0.5);
        controlDots.at(0)->moveBy(0, dy*0.5);
    }

    // 重绘图形
    draw();
}
FlowDiamondElement *FlowDiamondElement::deepClone()
{
    FlowDiamondElement* clonedElement = new FlowDiamondElement();
    clonedElement->borderColor=this->borderColor;
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

void FlowDiamondElement::calArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    for(QGraphicsRectItem *controlDot : controlDots){
        arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
        arrowDots.last()->setPos(controlDot->pos());
    }
}

void FlowDiamondElement::resetArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    for(int i=0 ; i<arrowDots.size() ; i++){
        arrowDots[i]->setPos(controlDots[i]->pos());
    }
}
void FlowDiamondElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=6;
    out<<type;
    qDebug()<<type;
    ElementSerializer::serializeColor(element.contentColor,out);
    ElementSerializer::serializeColor(element.borderColor,out);
    out<<element.borderDots.size();
    for(auto dot:element.borderDots){
        ElementSerializer::serializeGraphicsRectItem(dot,out);
    }
}
FlowElement* FlowDiamondElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载

    FlowDiamondElement *cur = new FlowDiamondElement();
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

