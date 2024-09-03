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
    calArrowDots();

    // 绘制路径
    draw();
}

void FlowDiamondElement::draw() {
    // qDebug() << "draw";

    QPainterPath path;

    // 依次取出两个小矩形的中心点，并绘制线条
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 1; i < borderDots.size(); ++i) {
        path.lineTo(borderDots[i]->scenePos() + borderDots[i]->rect().center());
    }
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

    path.closeSubpath();

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));
    // 设置默认线条宽度
    QPen pen(Qt::black);
    pen.setWidth(2);
    mainItem->setPen(pen);
}

void FlowDiamondElement::scale(int index, double dx, double dy)
{
    qDebug() << "开始缩放";
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

void FlowDiamondElement::calArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    arrowDots = controlDots;
}

void FlowDiamondElement::resetArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    arrowDots = controlDots;
}

