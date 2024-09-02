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
    QPen pen(Qt::black);
    pen.setWidth(2);
    mainItem->setPen(pen);
}
