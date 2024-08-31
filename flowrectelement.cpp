#include "flowrectelement.h"
#include <QGraphicsRectItem>

FlowRectElement::FlowRectElement()
    : FlowElement()
{
    // 创建四个小矩形，代表矩形的四个顶点
    QVector<QGraphicsRectItem*>* borderDotPositions = new QVector<QGraphicsRectItem*>;
    this->borderDots = borderDotPositions;
    borderDotPositions->append(new QGraphicsRectItem(QRectF(150, 100, 10, 10))); // 左上角
    borderDotPositions->append(new QGraphicsRectItem(QRectF(250, 100, 10, 10))); // 右上角
    borderDotPositions->append(new QGraphicsRectItem(QRectF(250, 200, 10, 10))); // 右下角
    borderDotPositions->append(new QGraphicsRectItem(QRectF(150, 200, 10, 10))); // 左下角
}
