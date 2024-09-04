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

    path.moveTo(borderDots[3]->scenePos() + borderDots[3]->rect().center());

    // 画左边的半圆，逆时针绘制，使得半圆向左突出
    drawHalfCircle(path, borderDots[0]->scenePos() + borderDots[0]->rect().center(),
                   borderDots[3]->scenePos() + borderDots[3]->rect().center());

    // 连接矩形的底边
    path.lineTo(borderDots[1]->scenePos() + borderDots[1]->rect().center());

    // 画右边的半圆，顺时针绘制，使得半圆向右突出
    drawHalfCircle(path, borderDots[2]->scenePos() + borderDots[2]->rect().center(),
                   borderDots[1]->scenePos() + borderDots[1]->rect().center());

    // path.moveTo(borderDots[2]->scenePos() + borderDots[2]->rect().center());

    // path.closeSubpath();

    //连接矩形的顶边
    path.lineTo(borderDots[3]->scenePos() + borderDots[3]->rect().center());

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}

void FlowPlaygroundElement::drawHalfCircle(QPainterPath &path, const QPointF &point1, const QPointF &point2) {
    // 计算中点（半圆的圆心）
    QPointF center = (point1 + point2) / 2.0;

    // 计算半径
    qreal radius = QLineF(point1, point2).length() / 2.0;

    // 计算起始角度（以degree为单位）
    qreal angle = std::atan2(point2.y() - point1.y(), point2.x() - point1.x()) * 180.0 / M_PI;

    // 创建外接矩形
    QRectF boundingRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);

    // 绘制半圆（180度的弧线）
    path.arcMoveTo(boundingRect, angle + 180);
    path.arcTo(boundingRect, angle + 180, -180);
}
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
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos((controlDots[0]->scenePos()+controlDots[1]->scenePos())/2);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setX(controlDots[1]->scenePos().x() + (controlDots[2]->scenePos().y() - controlDots[1]->scenePos().y())/2);
    arrowDots.last()->setY((controlDots[2]->scenePos().y() + controlDots[1]->scenePos().y())/2);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setPos((controlDots[2]->scenePos()+controlDots[3]->scenePos())/2);
    arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
    arrowDots.last()->setX(controlDots[0]->scenePos().x() + (controlDots[0]->scenePos().y() - controlDots[3]->scenePos().y())/2);
    arrowDots.last()->setY((controlDots[0]->scenePos().y() + controlDots[3]->scenePos().y())/2);
// ((controlDots[0]->scenePos()+controlDots[(1)%4]->scenePos())/2);
}
void FlowPlaygroundElement::resetArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    arrowDots.at(0)->setPos((controlDots[0]->scenePos()+controlDots[1]->scenePos())/2);
    arrowDots.at(1)->setX(controlDots[1]->scenePos().x() + (controlDots[2]->scenePos().y() - controlDots[1]->scenePos().y())/2);
    arrowDots.at(1)->setY((controlDots[2]->scenePos().y() + controlDots[1]->scenePos().y())/2);
    arrowDots.at(2)->setPos((controlDots[2]->scenePos()+controlDots[3]->scenePos())/2);
    arrowDots.at(3)->setX(controlDots[0]->scenePos().x() + (controlDots[0]->scenePos().y() - controlDots[3]->scenePos().y())/2);
    arrowDots.at(3)->setY((controlDots[0]->scenePos().y() + controlDots[3]->scenePos().y())/2);
}
