#include "flowdiamondelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5

FlowDiamondElement::FlowDiamondElement(): FlowElement()
{
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左
    borderDots.last()->setPos(150, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 上
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右
    borderDots.last()->setPos(350, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 下
    borderDots.last()->setPos(250, 200);

    controlDots = borderDots;

    // 绘制路径
    draw();
}
void FlowDiamondElement::mySetScale(int index, double dx, double dy)
{
    qDebug() << "开始缩放";
    if(!inBorder(index)){
        dx = deltax[index];
        dy = deltay[index];
    }
    if (index == 0) {  // 左
        controlDots.at(0)->moveBy(dx, 0);
        controlDots.at(3)->moveBy(dx*0.5, 0);
        controlDots.at(1)->moveBy(dx*0.5, 0);
    } else if (index == 1) {  // 上
        controlDots.at(1)->moveBy(0, dy);
        controlDots.at(2)->moveBy(0, dy*0.5);
        controlDots.at(0)->moveBy(0, dy*0.5);
    } else if (index == 2) {  // 右
        controlDots.at(2)->moveBy(dx, 0);
        controlDots.at(3)->moveBy(dx*0.5, 0);
        controlDots.at(1)->moveBy(dx*0.5, 0);
    }  else if (index == 3) {  // 下
        controlDots.at(3)->moveBy(0, dy);
        controlDots.at(2)->moveBy(0, dy*0.5);
        controlDots.at(0)->moveBy(0, dy*0.5);
    }

    // 重绘图形
    draw();
}

