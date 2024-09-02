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

    // 绘制路径
    draw();
}

void FlowCircleElement::draw() {
    qDebug() << "draw";

    QPainterPath path;

    // 获取控制点的外接矩形，并计算出圆的中心和半径
    if (borderDots.size() >= 2) {
        QPointF center = (borderDots[0]->scenePos() + borderDots[2]->scenePos()) / 2; // 计算圆心
        qreal radiusX = std::abs(borderDots[0]->scenePos().x() - borderDots[1]->scenePos().x()) / 2;
        qreal radiusY = std::abs(borderDots[0]->scenePos().y() - borderDots[3]->scenePos().y()) / 2;
        qreal radius = std::min(radiusX, radiusY);  // 取较小的值作为圆的半径
        center.rx()+=DOT_SIZE/2;
        center.ry()+=DOT_SIZE/2;
        // 在路径中添加圆形
        path.addEllipse(center, radius, radius);
    }

    // 设置控制点的外观
    for (QGraphicsRectItem* borderDot : borderDots) {
        borderDot->setBrush(Qt::red);
        QPen pen(Qt::red);
        borderDot->setPen(pen);
    }

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // 设置默认线条宽度
    QPen pen(Qt::black);
    pen.setWidth(2);
    mainItem->setPen(pen);
}
FlowCircleElement *FlowCircleElement::deepClone()
{
    FlowCircleElement* clonedElement = new FlowCircleElement();
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
