#include "flowplaygroundelement.h"
#define DOT_SIZE 5

FlowPlaygroundElement::FlowPlaygroundElement() : FlowElement() {
    // 设置矩形的四个顶点
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(200, 100);

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(400, 100);

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(400, 200);

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(200, 200);

    controlDots = borderDots;
    calArrowDots();

    // 绘制路径
    draw();
}

void FlowPlaygroundElement::draw() {
    //给点填色
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

    QPainterPath path;


    QPointF v0 = 0.5*(borderDots.at(0)->pos().toPoint() + borderDots.at(3)->pos().toPoint()) ;
    QPointF vtemp = 0.5*(borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint()) ;
    QPointF v03 = borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v32 = borderDots.at(3)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v1(vtemp.y(),-vtemp.x());
    if(crossProduct(v03,v32)>0){
        v1=-v1;
    }
    QPointF v2 = v0 + v1;

    v0 = 0.5*(borderDots.at(1)->pos().toPoint() + borderDots.at(2)->pos().toPoint()) ;
    vtemp = -0.5*(borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint()) ;
    QPointF v12 = borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v23 = borderDots.at(2)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v1p(vtemp.y(),-vtemp.x());
    if(crossProduct(v12,v23)<0){
        v1p=-v1p;
    }
    QPointF v3 = v0 + v1p;

    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 连接矩形的底边
    path.lineTo(borderDots[1]->scenePos() + borderDots[1]->rect().center());

    path.quadTo(v3,borderDots[2]->scenePos() + borderDots[2]->rect().center());
    path.lineTo(borderDots[3]->scenePos() + borderDots[3]->rect().center());
    path.quadTo(v2,borderDots[0]->scenePos() + borderDots[0]->rect().center());
    path.closeSubpath();

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}

// void FlowPlaygroundElement::drawHalfCircle(QPainterPath &path, const QPointF &point1, const QPointF &point2) {
//     // 计算中点（半圆的圆心）
//     QPointF center = (point1 + point2) / 2.0;

//     // 计算半径
//     qreal radius = QLineF(point1, point2).length() / 2.0;

//     // 计算起始角度（以degree为单位）
//     qreal angle = std::atan2(point2.y() - point1.y(), point2.x() - point1.x()) * 180.0 / M_PI;

//     // 创建外接矩形
//     QRectF boundingRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);

//     // 绘制半圆（180度的弧线）
//     path.arcMoveTo(boundingRect, angle + 180);
//     path.arcTo(boundingRect, angle + 180, -180);
// }
FlowPlaygroundElement *FlowPlaygroundElement::deepClone()
{
    FlowPlaygroundElement* clonedElement = new FlowPlaygroundElement();
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
void FlowPlaygroundElement::calArrowDots(){
    if(controlDots.size() < 4){
        return;
    }

    QPointF v0 = 0.5*(borderDots.at(0)->pos().toPoint() + borderDots.at(3)->pos().toPoint()) ;
    QPointF vtemp = 0.5*(borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint()) ;
    QPointF v03 = borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v32 = borderDots.at(3)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v1(vtemp.y(),-vtemp.x());
    if(crossProduct(v03,v32)>0){
        v1=-v1;
    }
    v1 *= 0.5;
    v1 -= borderDots[3]->rect().center()/2;
    QPointF v2 = v0 + v1;

    v0 = 0.5*(borderDots.at(1)->pos().toPoint() + borderDots.at(2)->pos().toPoint()) ;
    vtemp = -0.5*(borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint()) ;
    QPointF v12 = borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v23 = borderDots.at(2)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v1p(vtemp.y(),-vtemp.x());
    if(crossProduct(v12,v23)<0){
        v1p=-v1p;
    }
    v1p *= 0.5;
    v1p -= borderDots[3]->rect().center()/2;
    QPointF v3 = v0 + v1p;

    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos((controlDots[0]->scenePos()+controlDots[1]->scenePos())/2);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos(v3);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos((controlDots[2]->scenePos()+controlDots[3]->scenePos())/2);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos(v2);
// ((controlDots[0]->scenePos()+controlDots[(1)%4]->scenePos())/2);
}
void FlowPlaygroundElement::resetArrowDots(){
    if(controlDots.size() < 4){
        return;
    }

    QPointF v0 = 0.5*(borderDots.at(0)->pos().toPoint() + borderDots.at(3)->pos().toPoint()) ;
    QPointF vtemp = 0.5*(borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint()) ;
    QPointF v03 = borderDots.at(0)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v32 = borderDots.at(3)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v1(vtemp.y(),-vtemp.x());
    if(crossProduct(v03,v32)>0){
        v1=-v1;
    }
    v1 *= 0.5;
    v1 -= borderDots[3]->rect().center()/2;
    QPointF v2 = v0 + v1;

    v0 = 0.5*(borderDots.at(1)->pos().toPoint() + borderDots.at(2)->pos().toPoint()) ;
    vtemp = -0.5*(borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint()) ;
    QPointF v12 = borderDots.at(1)->pos().toPoint() - borderDots.at(2)->pos().toPoint();
    QPointF v23 = borderDots.at(2)->pos().toPoint() - borderDots.at(3)->pos().toPoint();
    QPointF v1p(vtemp.y(),-vtemp.x());
    if(crossProduct(v12,v23)<0){
        v1p=-v1p;
    }
    v1p *= 0.5;
    v1p -= borderDots[3]->rect().center()/2;
    QPointF v3 = v0 + v1p;

    arrowDots.at(0)->setPos((controlDots[0]->scenePos()+controlDots[1]->scenePos())/2);
    arrowDots.at(1)->setPos(v3);
    arrowDots.at(2)->setPos((controlDots[2]->scenePos()+controlDots[3]->scenePos())/2);
    arrowDots.at(3)->setPos(v2);
}

double FlowPlaygroundElement::crossProduct(QPointF a,QPointF b){//叉乘
    return a.x() * b.y() - a.y() * b.x();
}
void FlowPlaygroundElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=3;
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
FlowElement* FlowPlaygroundElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载
    FlowPlaygroundElement *cur = new FlowPlaygroundElement();

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
