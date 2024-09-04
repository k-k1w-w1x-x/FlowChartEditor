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
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}

bool FlowElement::contains(const QPointF &point) const {
    return mainItem->contains(point);
}

void FlowElement::move(double dx,double dy) {
    // 先移动各个控制点（边界点）
    for(QGraphicsRectItem * borderDot : borderDots) {
        borderDot->moveBy(dx, dy);
        // qDebug()<<borderDot->pos();
    }
    // for(QGraphicsRectItem *arrowDot : arrowDots) {
    //     arrowDot->moveBy(dx, dy);
    // }
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

void FlowElement::mySetScale(int index,double dx,double dy)//默认4个控制点，如果不是需要重写，规定从左上角开始顺时针
{
    qDebug()<<"开始缩放";
    if(!inBorder(index)[0]||!inBorder(index)[1])//若越界
    {
        qDebug()<<"越界了";
        int oppIdx = (index+2) % 4;//对角点
        if((!inBorder(index)[0])&&(!inBorder(index)[1])){//xy都越界
            qDebug()<<"xy都越界";
            dx = deltax[index];
            dy = deltay[index];
            double x = controlDots.at(oppIdx)->scenePos().x();
            double y = controlDots.at(oppIdx)->scenePos().y();
            controlDots.at(index)->setPos(x+dx,y+dy);
            if(index==0){
                borderDots.at(1)->setPos(x+0, y+dy);
                borderDots.at(3)->setPos(x+dx, y+0);
            }
            if(index==1){
                borderDots.at(0)->setPos(x+0, y+dy);
                borderDots.at(2)->setPos(x+dx, y+0);
            }
            if(index==2){
                borderDots.at(3)->setPos(x+0, y+dy);
                borderDots.at(1)->setPos(x+dx, y+0);
            }
            if(index==3){
                borderDots.at(2)->setPos(x+0, y+dy);
                borderDots.at(0)->setPos(x+dx, y+0);
            }
        }
        else if(!inBorder(index)[0]&&inBorder(index)[1]){//仅x越界
            qDebug()<<"仅x越界";
            dx = deltax[index];
            double x = controlDots.at(oppIdx)->scenePos().x();
            double y = controlDots.at(index)->scenePos().y();
            double oppY = controlDots.at(oppIdx)->scenePos().y();
            controlDots.at(index)->setPos(x+dx,y+dy);
            if(index==0){
                borderDots.at(1)->setPos(x+0, y+dy);
                borderDots.at(3)->setPos(x+dx, oppY+0);
            }
            if(index==1){
                borderDots.at(0)->setPos(x+0, y+dy);
                borderDots.at(2)->setPos(x+dx, oppY+0);
            }
            if(index==2){
                borderDots.at(3)->setPos(x+0, y+dy);
                borderDots.at(1)->setPos(x+dx, oppY+0);
            }
            if(index==3){
                borderDots.at(2)->setPos(x+0, y+dy);
                borderDots.at(0)->setPos(x+dx, oppY+0);
            }
        }
        else if(inBorder(index)[0] && !inBorder(index)[1]){//仅y越界
            qDebug()<<"y越界";
            dy = deltay[index];
            double x=controlDots.at(index)->scenePos().x();
            double oppX=controlDots.at(oppIdx)->scenePos().x();
            double y=controlDots.at(oppIdx)->scenePos().y();
            controlDots.at(index)->setPos(x+dx,y+dy);
            if(index==0){
                borderDots.at(1)->setPos(oppX+0, y+dy);
                borderDots.at(3)->setPos(x+dx, y+0);
            }
            if(index==1){
                borderDots.at(0)->setPos(oppX+0, y+dy);
                borderDots.at(2)->setPos(x+dx, y+0);
            }
            if(index==2){
                borderDots.at(3)->setPos(oppX+0, y+dy);
                borderDots.at(1)->setPos(x+dx, y+0);
            }
            if(index==3){
                borderDots.at(2)->setPos(oppX+0, y+dy);
                borderDots.at(0)->setPos(x+dx, y+0);
            }
        }
        draw();
        return;
    }
    qDebug()<<"正常缩放";

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
// FlowElement* FlowElement::deepClone() {
//     FlowElement* clonedElement = new FlowElement();

//     clonedElement->contentColor = this->contentColor;
//     clonedElement->selected = this->selected;

//     clonedElement->mainItem->setPath(this->mainItem->path());
//     clonedElement->mainItem->setBrush(this->mainItem->brush());
//     clonedElement->mainItem->setPen(this->mainItem->pen());

//     for (QGraphicsRectItem* borderDot : this->borderDots) {
//         QGraphicsRectItem* newDot = new QGraphicsRectItem(borderDot->rect());
//         newDot->setBrush(borderDot->brush());
//         newDot->setPen(borderDot->pen());
//         newDot->setPos(borderDot->pos());
//         clonedElement->borderDots.append(newDot);
//     }

//     for (QGraphicsRectItem* controlDot : this->controlDots) {
//         QGraphicsRectItem* newDot = new QGraphicsRectItem(controlDot->rect());
//         newDot->setBrush(controlDot->brush());
//         newDot->setPen(controlDot->pen());
//         newDot->setPos(controlDot->pos());
//         clonedElement->controlDots.append(newDot);
//     }

//     clonedElement->setPos(this->pos());
//     clonedElement->setRotation(this->rotation());
//     clonedElement->setScale(this->scale());

//     return clonedElement;
// }
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

bool* FlowElement::inBorder(int idx){

    qDebug()<<"判断越界";
    int oppIdx = (idx+2) % 4;
    if(idx == 0){//左上
        isInBorder[0]= controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x();
        isInBorder[1]= controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y();
        return(isInBorder);
    }
    if(idx == 1){//右上
        isInBorder[0]= controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x();
        isInBorder[1]= controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y();
        return(isInBorder);
    }
    if(idx == 2){//右下
        isInBorder[0]=controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x();
        isInBorder[1]=controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y();
        qDebug()<<"true???"<<isInBorder[0]<<isInBorder[1];
        return(isInBorder);
    }
    if(idx == 3){//左下
        isInBorder[0]=controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x();
        isInBorder[1]=controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y();
        return(isInBorder);
    }
}
