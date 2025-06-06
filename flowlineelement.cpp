#include <flowlineelement.h>
#include <QPen>
#include <cmath>
#define DOT_SIZE 8
FlowLineElement::FlowLineElement(): FlowArrowElement(){
    startDot = new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this);
    endDot = new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this);
}
void FlowLineElement::draw()  {
    // 创建一个 QPainterPath 来绘制箭头
    QPainterPath path;
    QPointF startPoint = startDot->scenePos() + startDot->rect().center();
    QPointF endPoint = endDot->scenePos() + endDot->rect().center();

    //锁头优先
    if(startElementDot){
        qDebug()<<"startElementDot is no null";
        startPoint = startElementDot->scenePos() + startElementDot->rect().center();
        startDot->setX(startElementDot->scenePos().x() + startElementDot->rect().center().x());
        startDot->setY(startElementDot->scenePos().y() + startElementDot->rect().center().y());
        qDebug()<<"startDot:"<<startDot->scenePos().x()<<","<<startDot->scenePos().y();
    }
    if(endElementDot){
        qDebug()<<"endElementDot is no null";
        endPoint = endElementDot->scenePos() + endElementDot->rect().center();
        endDot->setX(endElementDot->scenePos().x() + endElementDot->rect().center().x());
        endDot->setY(endElementDot->scenePos().y() + endElementDot->rect().center().y());
    }
    if(passingPoint.x()==0&&passingPoint.y()==0){
        qDebug()<<"没passingPoint";
        path.moveTo(startPoint);
        path.lineTo(endPoint);
    }
    else{
        qDebug()<<"在draw里面passingPoint:"<<passingPoint.x()<<","<<passingPoint.y();
        double passSize = 7.0;
        double x1 = startPoint.x();
        double y1 = startPoint.y();
        double x2 = endPoint.x();
        double y2 = endPoint.y();
        double passX = passSize * (x1-x2)/sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        double passY = passSize * (y1-y2)/sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        QPointF passingPoint1(passingPoint.x() + passX, passingPoint.y() + passY);
        QPointF passingPoint2(passingPoint.x() - passX, passingPoint.y() - passY);
        QPointF passingPoint0(passingPoint.x() - passY, passingPoint.y() + passX);
        path.moveTo(startPoint);
        path.lineTo(passingPoint1);
        path.quadTo(passingPoint0,passingPoint2);
        path.lineTo(endPoint);
    }
    // // 箭头的头部宽度和长度
    // const double LineHeadSize = 10.0;

    // // 计算箭头的角度
    // double angle = std::atan2(endPoint.y() - startPoint.y(), endPoint.x() - startPoint.x());

    // // 计算箭头的两个侧翼点
    // QPointF arrowP1 = endPoint - QPointF(std::cos(angle - M_PI / 6) * arrowHeadSize,
    //                                      std::sin(angle - M_PI / 6) * arrowHeadSize);
    // QPointF arrowP2 = endPoint - QPointF(std::cos(angle + M_PI / 6) * arrowHeadSize,
    //                                      std::sin(angle + M_PI / 6) * arrowHeadSize);

    // // 将箭头侧翼添加到路径
    // path.moveTo(arrowP1);
    // path.lineTo(endPoint);
    // path.lineTo(arrowP2);

    // 创建一个 QGraphicsPathItem 来显示箭头
    mainItem->setPath(path);
    mainItem->setPen(QPen(borderColor, 3));    // 设置箭头的颜色和宽度


    QPen pen(Qt::red,1);
    startDot->setBrush(Qt::red);
    startDot->setPen(pen);
    endDot->setBrush(Qt::red);
    endDot->setPen(pen);
    if(startElementDot){
        startElementDot->setBrush(Qt::red);
        startElementDot->setPen(pen);
    }
    if(endElementDot){
        endElementDot->setBrush(Qt::red);
        endElementDot->setPen(pen);
    }
    qDebug()<<"draw结束";
}
FlowLineElement *FlowLineElement::deepClone()
{
    FlowLineElement* clonedElement = new FlowLineElement();
    clonedElement->borderColor=this->borderColor;
    clonedElement->contentColor = this->contentColor;
    clonedElement->selected = this->selected;

    clonedElement->mainItem->setPath(this->mainItem->path());
    // clonedElement->mainItem->setBrush(this->mainItem->brush());
    clonedElement->mainItem->setPen(this->mainItem->pen());

    clonedElement->startElementDot = nullptr;
    clonedElement->endElementDot = nullptr;

    QGraphicsRectItem* newStartDot = new QGraphicsRectItem(startDot->rect());
    QGraphicsRectItem* newEndDot = new QGraphicsRectItem(endDot->rect());
    newStartDot->setBrush(startDot->brush());
    newStartDot->setPen(startDot->pen());
    newStartDot->setPos(startDot->pos());
    newStartDot->setVisible(newStartDot->isVisible());
    newEndDot->setBrush(endDot->brush());
    newEndDot->setPen(endDot->pen());
    newEndDot->setPos(endDot->pos());
    newEndDot->setVisible(newEndDot->isVisible());
    clonedElement->startDot = newStartDot;
    clonedElement->endDot = newEndDot;

    QPointF newPassingPoint(0,0);
    clonedElement->passingPoint = newPassingPoint;
    qDebug()<<"brush:"<<clonedElement->startDot->brush();

    clonedElement->setPos(this->pos());
    clonedElement->setRotation(this->rotation());
    clonedElement->setScale(this->scale());

    return clonedElement;
}
void FlowLineElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=9;
    out<<type;
    qDebug()<<type;
    ElementSerializer::serializeColor(element.borderColor,out);
    // out<<element.borderDots.size();
    ElementSerializer::serializeGraphicsRectItem(this->startDot,out);
    ElementSerializer::serializeGraphicsRectItem(this->endDot,out);
}
FlowElement* FlowLineElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载

    FlowLineElement *cur = new FlowLineElement();
    cur->borderColor = ElementSerializer::deserializeColor(in);
    // qsizetype borderDotsSize;
    // in>>borderDotsSize;
    // qDebug()<<borderDotsSize<<" bordersize";
    cur->startDot = ElementSerializer::deserializeGraphicsRectItem(in);
    cur->endDot = ElementSerializer::deserializeGraphicsRectItem(in);
    cur->startDot->setVisible(false);
    cur->endDot->setVisible(false);
    cur->draw();

    return cur;
}





