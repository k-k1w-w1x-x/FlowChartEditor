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

void FlowDiamondElement::mySetScale(int index, double deltax, double deltay)
{
    QTransform transform;
    QTransform transform1;

    QPointF delta(deltax,deltay);

    // double x1 = controlDots.at(0)->x();
    // double y1 = controlDots.at(0)->y();
    // double x2 = controlDots.at(1)->x();
    // double y2 = controlDots.at(1)->y();

    // double costheta = 0 ;
    // costheta = (x1==x2 && y1==y2)?1:abs(x2 - x1) / (sqrt(pow((x1-x2),2)+pow(y1-y2,2)));
    // double radians = std::acos(costheta);
    // // 将弧度转换为角度
    // double theta = radians * (180.0 / M_PI);
    double theta = rotangle;
    qDebug()<<"theta"<<theta;
    transform.rotate(-theta);

    QPointF transformedPoint = transform.map(delta) ;

    double dx = transformedPoint.x();
    double dy = transformedPoint.y();

    QPointF q1(dx,0);
    QPointF q2(0,dy);

    transform1.rotate(theta);
    q1 = transform1.map(q1) ;
    q2 = transform1.map(q2) ;

    if(index==0){
        borderDots.at(0)->moveBy(q1.x(),q1.y());
        borderDots.at(1)->moveBy(0.5*q1.x(), 0.5*q1.y());
        borderDots.at(3)->moveBy(0.5*q1.x(), 0.5*q1.y());
    }
    if(index==1){
        borderDots.at(1)->moveBy(q2.x(),q2.y());
        borderDots.at(0)->moveBy(0.5*q2.x(), 0.5*q2.y());
        borderDots.at(2)->moveBy(0.5*q2.x(), 0.5*q2.y());
    }
    if(index==2){
        borderDots.at(2)->moveBy(q1.x(),q1.y());
        borderDots.at(3)->moveBy(0.5*q1.x(),0.5*q1.y());
        borderDots.at(1)->moveBy(0.5*q1.x(), 0.5*q1.y());
    }
    if(index==3){
        borderDots.at(3)->moveBy(q2.x(),q2.y());
        borderDots.at(0)->moveBy(0.5*q2.x(), 0.5*q2.y());
        borderDots.at(2)->moveBy(0.5*q2.x(), 0.5*q2.y());
    }
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
    ElementSerializer::serializeDouble(element.rotangle,out);
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

