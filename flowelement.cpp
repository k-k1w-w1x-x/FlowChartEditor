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

void FlowElement::mySetScale(int index,double deltax,double deltay)//默认4个控制点，如果不是需要重写，规定从左上角开始顺时针
{
    qDebug()<<"开始缩放";
    // if(!inBorder(index)[0]||!inBorder(index)[1])//若越界
    // {
    //     qDebug()<<"越界了";
    //     int oppIdx = (index+2) % 4;//对角点
    //     if((!inBorder(index)[0])&&(!inBorder(index)[1])){//xy都越界
    //         qDebug()<<"xy都越界";
    //         dx = deltax[index];
    //         dy = deltay[index];
    //         double x = controlDots.at(oppIdx)->scenePos().x();
    //         double y = controlDots.at(oppIdx)->scenePos().y();
    //         controlDots.at(index)->setPos(x+dx,y+dy);
    //         if(index==0){
    //             borderDots.at(1)->setPos(x+0, y+dy);
    //             borderDots.at(3)->setPos(x+dx, y+0);
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(x+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, y+0);
    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(x+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, y+0);
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(x+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, y+0);
    //         }
    //     }
    //     else if(!inBorder(index)[0]&&inBorder(index)[1]){//仅x越界
    //         qDebug()<<"仅x越界";
    //         dx = deltax[index];
    //         double x = controlDots.at(oppIdx)->scenePos().x();
    //         double y = controlDots.at(index)->scenePos().y();
    //         double oppY = controlDots.at(oppIdx)->scenePos().y();
    //         controlDots.at(index)->setPos(x+dx,y+dy);
    //         if(index==0){
    //             borderDots.at(1)->setPos(x+0, y+dy);
    //             borderDots.at(3)->setPos(x+dx, oppY+0);
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(x+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, oppY+0);
    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(x+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, oppY+0);
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(x+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, oppY+0);
    //         }
    //     }
    //     else if(inBorder(index)[0] && !inBorder(index)[1]){//仅y越界
    //         qDebug()<<"y越界";
    //         dy = deltay[index];
    //         double x=controlDots.at(index)->scenePos().x();
    //         double oppX=controlDots.at(oppIdx)->scenePos().x();
    //         double y=controlDots.at(oppIdx)->scenePos().y();
    //         controlDots.at(index)->setPos(x+dx,y+dy);
    //         if(index==0){
    //             borderDots.at(1)->setPos(oppX+0, y+dy);
    //             borderDots.at(3)->setPos(x+dx, y+0);
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(oppX+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, y+0);
    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(oppX+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, y+0);
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(oppX+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, y+0);
    //         }
    //     }
    //     draw();
    //     return;
    // }
    qDebug()<<"index:"<<index;
    borderDots.at(index)->moveBy(deltax,deltay);

    QTransform transform;
    QTransform transform1;

    QPointF delta(deltax,deltay);

    // double x1 = controlDots.at(0)->x();
    // double y1 = controlDots.at(0)->y();
    // double x2 = controlDots.at(1)->x();
    // double y2 = controlDots.at(1)->y();

    // double costheta = 0 ;
    // costheta = (x1==x2 && y1==y2)?1:abs(x2 - x1) / (sqrt(pow((x1-x2),2)+pow(y1-y2,2)));
    // double radians = std::acos(costheta);
    // // 将弧度转换为角度
    // double theta = radians * (180.0 / M_PI);
    double theta = rotangle;
    qDebug()<<"theta"<<theta;
    transform.rotate(-theta);

    QPointF transformedPoint = transform.map(delta) ;

    double dx = transformedPoint.x();
    double dy = transformedPoint.y();

    QPointF q1(dx,0);
    QPointF q2(0,dy);
    transform1.rotate(theta);
    q1 = transform1.map(q1) ;
    q2 = transform1.map(q2) ;

    if(index==0){
        borderDots.at(1)->moveBy(q2.x(), q2.y());
        borderDots.at(3)->moveBy(q1.x(), q1.y());
    }
    if(index==1){
        borderDots.at(0)->moveBy(q2.x(), q2.y());
        borderDots.at(2)->moveBy(q1.x(), q1.y());
    }
    if(index==2){
        borderDots.at(3)->moveBy(q2.x(), q2.y());
        borderDots.at(1)->moveBy(q1.x(), q1.y());
    }
    if(index==3){
        borderDots.at(2)->moveBy(q2.x(), q2.y());
        borderDots.at(0)->moveBy(q1.x(), q1.y());
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

// bool* FlowElement::inBorder(int idx){

//     qDebug()<<"判断越界";
//     int oppIdx = (idx+2) % 4;
//     if(idx == 0){//左上
//         isInBorder[0]= controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x();
//         isInBorder[1]= controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y();
//         return(isInBorder);
//     }
//     if(idx == 1){//右上
//         isInBorder[0]= controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x();
//         isInBorder[1]= controlDots[idx]->scenePos().y() <= controlDots[oppIdx]->scenePos().y();
//         return(isInBorder);
//     }
//     if(idx == 2){//右下
//         isInBorder[0]=controlDots[idx]->scenePos().x() >= controlDots[oppIdx]->scenePos().x();
//         isInBorder[1]=controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y();
//         qDebug()<<"true???"<<isInBorder[0]<<isInBorder[1];
//         return(isInBorder);
//     }
//     if(idx == 3){//左下
//         isInBorder[0]=controlDots[idx]->scenePos().x() <= controlDots[oppIdx]->scenePos().x();
//         isInBorder[1]=controlDots[idx]->scenePos().y() >= controlDots[oppIdx]->scenePos().y();
//         return(isInBorder);
//     }
// }

void FlowElement::myRotate(QPointF mousePos,QPointF *centerPos,double dx,double dy){
    bool fail = false;
    double sqr1 = pow((mousePos.x()- centerPos->x()),2) + pow((mousePos.y()- centerPos->y()),2);
    double sqr2 = pow((mousePos.x()+ dx - centerPos->x()),2) + pow((mousePos.y() + dy - centerPos->y()),2);
    double sqr3 = pow(dx,2) + pow(dy,2);
    if(sqr1*sqr2 == 0){
        return;
    }
    double costheta = (sqr1 + sqr2 - sqr3) / (2 * sqrt(sqr1 * sqr2));
    double sintheta = sqrt(1 - costheta*costheta);
    double radians = std::acos(costheta);
    // 将弧度转换为角度
    double theta = radians * (180.0 / M_PI);
    rotate(theta);
    qDebug()<<"dx:"<<dx<<"dy:"<<dy;
    qDebug()<<"centerx:"<<centerPos->x()<<"centery:"<<centerPos->y();
    // for(QGraphicsRectItem *borderDot : borderDots){
    //     double x1=centerPos->x()-borderDot->x();
    //     double y1=borderDot->y()-centerPos->y();
    //     double r = sqrt(pow(x1,2)+pow(y1,2));
    //     if(r == 0){
    //         fail =true;
    //     }
    //     qDebug()<<"x1:"<<borderDot->x()<<"y1:"<<borderDot->y();
    //     double cosalpha = x1 / r;
    //     double sinalpha = y1 / r;
    //     qDebug()<<"cosalpha:"<<cosalpha<<"sinalpha:"<<sinalpha;
    //     double costhetaplusalpha = costheta*cosalpha - sintheta*sinalpha;
    //     double sinthetaplusalpha = sintheta*cosalpha + costheta*sinalpha;
    //     qDebug()<<"costhetaplusalpha:"<<costhetaplusalpha<<"sinthetaplusalpha:"<<sinthetaplusalpha;
    //     double newdx = x1 - r*costhetaplusalpha;
    //     double newdy = r*sinthetaplusalpha - y1;
    //     qDebug()<<"newdx:"<<newdx<<"newdy:"<<newdy;
    //     borderDot->moveBy(newdx,newdy);
    // }
    // if(!fail){
    //     draw();
    // }

}


void FlowElement::rotate(double angleDegrees) {
    // 计算图形的中心
    QPointF center(0, 0);
    for (QGraphicsRectItem *dot : controlDots) {
        center += dot->scenePos();
    }
    center /= controlDots.size();  // 平均值作为中心
    QTransform transform;

    transform.translate(center.x(), center.y());  // 平移到中心点
    transform.rotate(angleDegrees);               // 旋转
    transform.translate(-center.x(), -center.y());  // 平移回原始坐标系
    rotangle += angleDegrees;
    // 旋转所有控制点
    // for (QGraphicsRectItem *dot : controlDots) {
    //     QPointF newPos = transform.map(dot->scenePos());
    //     dot->setPos(newPos);
    // }

    // 旋转所有边界点
    for (QGraphicsRectItem *dot : borderDots) {
        QPointF newPos = transform.map(dot->scenePos());
        dot->setPos(newPos);
    }

    // 重新绘制图形
    draw();
}

