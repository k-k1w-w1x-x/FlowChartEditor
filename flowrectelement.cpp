#include "flowrectelement.h"
#include <QGraphicsRectItem>

FlowRectElement::FlowRectElement() : FlowElement() {
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 5, 5), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 5, 5), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 5, 5), this));  // 右下角
    borderDots.last()->setPos(250, 200);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, 5, 5), this));  // 左下角
    borderDots.last()->setPos(150, 200);

    // 绘制路径
    draw();
}
