#include "flowdocuelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5

FlowDocuElement::FlowDocuElement(): FlowElement()
{
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(250, 150);

    controlDots = borderDots;

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(225, 140);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(200, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(175, 160);

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(150, 150);

    controlDots.append(borderDots.last());
    // 绘制路径
    draw();
}

void FlowDocuElement::draw() {
    // 设置每个控制点的外观
    for (QGraphicsRectItem* borderDot : borderDots) {
        borderDot->setBrush(Qt::red);
        QPen pen(Qt::red);
        borderDot->setPen(pen);
    }

    // 初始化绘制路径
    QPainterPath path;

    // 移动到第一个点（左上角）
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 连接第二个点（右上角）
    path.lineTo(borderDots[1]->scenePos() + borderDots[1]->rect().center());

    // 连接第三个点（右下角）
    path.lineTo(borderDots[2]->scenePos() + borderDots[2]->rect().center());

    path.quadTo(borderDots[3]->scenePos() + borderDots[3]->rect().center(),borderDots[4]->scenePos() + borderDots[4]->rect().center());
    path.quadTo(borderDots[5]->scenePos() + borderDots[5]->rect().center(),borderDots[6]->scenePos() + borderDots[6]->rect().center());
    // 关闭路径
    path.closeSubpath();

    // 设置主图形项的路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // 设置路径的线条样式
    QPen pen(Qt::black);
    pen.setWidth(2);
    mainItem->setPen(pen);
}


