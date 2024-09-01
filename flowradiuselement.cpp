#include "flowradiuselement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5
FlowRadiusElement::FlowRadiusElement() {
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(250, 200);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(150, 200);
    controlDots = borderDots;
    draw();
}

void FlowRadiusElement::draw() {
    qDebug() << "draw";
    for(QGraphicsRectItem* borderDot : borderDots){
        borderDot->setBrush(Qt::red);
        QPen pen(Qt::red);
        borderDot->setPen(pen);
    }

    QPainterPath path;

    // 假设我们使用 borderDots[0] 和 borderDots[2] 确定矩形的对角点
    QPointF topLeft = borderDots[0]->scenePos() + borderDots[0]->rect().center();
    QPointF bottomRight = borderDots[2]->scenePos() + borderDots[2]->rect().center();

    QRectF rect(topLeft, bottomRight);


    // 定义圆角的半径
    qreal radiusX = abs(borderDots[2]->scenePos().x()-borderDots[0]->scenePos().x())/5.0;  // X方向的圆角半径
    qreal radiusY = abs(borderDots[2]->scenePos().y()-borderDots[0]->scenePos().y())/5.0;  // Y方向的圆角半径

    // 在路径中添加圆角矩形
    path.addRoundedRect(rect, radiusX, radiusY);

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // 设置默认线条宽度
    QPen pen(Qt::black);
    pen.setWidth(2);
    mainItem->setPen(pen);
}
