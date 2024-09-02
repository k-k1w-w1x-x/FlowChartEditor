#include "flowelement.h"
#include <QPainter>
#include <QDebug>
#define DOT_SIZE 5
FlowElement::FlowElement() {
    mainItem = new QGraphicsPathItem(this);
}

void FlowElement::draw() {
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

bool FlowElement::contains(const QPointF &point) const {
    return mainItem->contains(point);
}

void FlowElement::move(int dx, int dy) {
    // 先移动各个控制点（边界点）
    for(QGraphicsRectItem *borderDot : borderDots) {
        borderDot->moveBy(dx, dy);
    }
    for(QGraphicsRectItem *arrowDot : arrowDots) {
        arrowDot->moveBy(dx, dy);
    }
    // 重新绘制路径
    draw();
}

void FlowElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 绘制图形项的外观
    painter->setBrush(Qt::blue);  // 例如使用蓝色填充
    painter->drawRect(boundingRect());
}

QRectF FlowElement::boundingRect() const {
    // 返回项的边界矩形
    return QRectF(150, 100, 100, 100);  // 根据你的需求调整大小和位置
}

void FlowElement::scale(int index,double dx,double dy)//默认4个控制点，如果不是需要重写，规定从左上角开始顺时针
{
    qDebug()<<"开始缩放";
    if(!inBorder(index)){
        dx = deltax[index];
        dy = deltay[index];
    }
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

void FlowElement::calArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    for(int i=0 ;i < controlDots.size() ;i++){
        arrowDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));
        arrowDots.last()->setPos((controlDots[i]->scenePos()+controlDots[(i+1)%4]->scenePos())/2);
    }
}

void FlowElement::resetArrowDots(){
    if(controlDots.size() < 4){
        return;
    }
    for(int i=0 ;i < controlDots.size() ;i++){
        arrowDots.at(i)->setPos((controlDots[i]->scenePos()+controlDots[(i+1)%4]->scenePos())/2);
    }
}

bool FlowElement::inBorder(int idx){
    int oppIdx = (idx+2) % 4;
    if(idx == 0){
        return(controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x()
                & controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y());
    }
    if(idx == 1){
        return(controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x()
                & controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y());
    }
    if(idx == 2){
        return(controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x()
                & controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y());
    }
    if(idx == 3){
        return(controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x()
                & controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y());
    }

}
