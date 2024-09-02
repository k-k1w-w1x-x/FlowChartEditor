#include "flowparaelement.h"
#include <QGraphicsRectItem>
#define DOT_SIZE 5
FlowParaElement::FlowParaElement(): FlowElement()
{
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(225, 175);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(125, 175);

    controlDots = borderDots;
    calArrowDots();

    // 绘制路径
    draw();
}
void FlowParaElement::scale(int index,double dx,double dy)//默认4个控制点，如果不是需要重写，规定从左上角开始顺时针
{
    qDebug()<<"开始缩放";
    controlDots.at(index)->moveBy(dx, dy);
    if(index==0){
        borderDots.at(1)->moveBy(0, dy);
        borderDots.at(3)->moveBy(dx, 0);
    }
    if(index==1){
        borderDots.at(0)->moveBy(0, dy);
        borderDots.at(2)->moveBy(dx, 0);
    }
    if(index==2){
        borderDots.at(3)->moveBy(0, dy);
        borderDots.at(1)->moveBy(dx, 0);
    }
    if(index==3){
        borderDots.at(2)->moveBy(0, dy);
        borderDots.at(0)->moveBy(dx, 0);
    }
    draw();
}
