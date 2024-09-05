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
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(150, 150);
    controlDots = borderDots;
    calArrowDots();

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(225, 140);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(200, 150);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  //过渡点
    borderDots.last()->setPos(175, 160);

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
    // 设置箭头点的外观
    resetArrowDots();
    for(QGraphicsRectItem* arrowDot : arrowDots){
        arrowDot->setBrush(Qt::black);
        QPen pen(Qt::black);
        arrowDot->setPen(pen);
    }

    // 初始化绘制路径
    QPainterPath path;

    // 移动到第一个点（左上角）
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 连接第二个点（右上角）
    path.lineTo(borderDots[1]->scenePos() + borderDots[1]->rect().center());

    // 连接第三个点（右下角）
    path.lineTo(borderDots[2]->scenePos() + borderDots[2]->rect().center());

    path.quadTo(borderDots[4]->scenePos() + borderDots[3]->rect().center(),borderDots[5]->scenePos() + borderDots[4]->rect().center());
    path.quadTo(borderDots[6]->scenePos() + borderDots[5]->rect().center(),borderDots[3]->scenePos() + borderDots[6]->rect().center());
    // 关闭路径
    path.closeSubpath();

    // 设置主图形项的路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // 设置路径的线条样式
    QPen pen(borderColor);
    pen.setWidth(2);
    mainItem->setPen(pen);
}
void FlowDocuElement::mySetScale(int index, double deltax, double deltay)
{

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

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.25, y+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+0);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.75, y-dy * 0.2); // 过渡点3
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(x+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.75, y+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+0);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.25, y-dy * 0.2); // 过渡点3

    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(x+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.75, y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.25, y+dy * 1.2); // 过渡点3
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(x+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.25, y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.75, y+dy * 1.2); // 过渡点3
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

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.25, 0.2*y+0.8*oppY+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, oppY+0);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.75, 1.2*oppY-0.2*y-dy * 0.2); // 过渡点3
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(x+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, oppY+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.75, 0.2*y+0.8*oppY+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, oppY+0);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.25, 1.2*oppY-0.2*y-dy * 0.2); // 过渡点3
    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(x+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, oppY+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.75, 0.2*oppY+0.8*y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.25, 1.2*y-0.2*oppY+dy * 1.2); // 过渡点3
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(x+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, oppY+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(x+dx * 0.25, 0.2*oppY+0.8*y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(x+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(x+dx * 0.75, 1.2*y-0.2*oppY+dy * 1.2); // 过渡点3
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

    //             // 过渡点
    //             borderDots.at(4)->setPos(0.75*oppX+0.25*x+dx * 0.25, y+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(0.5*oppX+0.5*x+dx * 0.5, y+0);          // 过渡点2
    //             borderDots.at(6)->setPos(0.25*oppX+0.75*x+dx * 0.75, y-dy * 0.2); // 过渡点3
    //         }
    //         if(index==1){
    //             borderDots.at(0)->setPos(oppX+0, y+dy);
    //             borderDots.at(2)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(0.75*x+0.25*oppX+dx * 0.75, y+dy * 0.2);  // 过渡点1
    //             borderDots.at(5)->setPos(0.5*x+0.5*oppX+dx * 0.5, y+0);          // 过渡点2
    //             borderDots.at(6)->setPos(0.25*x+0.75*oppX+dx * 0.25, y-dy * 0.2); // 过渡点3
    //         }
    //         if(index==2){
    //             borderDots.at(3)->setPos(oppX+0, y+dy);
    //             borderDots.at(1)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(0.75*x+0.25*oppX+dx * 0.75, y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(0.5*x+0.5*oppX+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(0.25*x+0.75*oppX+dx * 0.25, y+dy * 1.2); // 过渡点3
    //         }
    //         if(index==3){
    //             borderDots.at(2)->setPos(oppX+0, y+dy);
    //             borderDots.at(0)->setPos(x+dx, y+0);

    //             // 过渡点
    //             borderDots.at(4)->setPos(0.75*oppX+0.25*x+dx * 0.25+dx * 0.25, y+dy * 0.8);  // 过渡点1
    //             borderDots.at(5)->setPos(0.5*oppX+0.5*x+dx * 0.5, y+dy);          // 过渡点2
    //             borderDots.at(6)->setPos(0.25*oppX+0.75*x+dx * 0.75, y+dy * 1.2); // 过渡点3
    //         }
    //     }
    //     draw();
    //     return;
    // }
    qDebug() << "开始缩放";
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

    QPointF q3(0.25*dx,0.2*dy);
    QPointF q4(0.5*dx,0);
    QPointF q5(0.75*dx,-0.2*dy);

    QPointF q6(0.75*dx,0.2*dy);
    QPointF q7(0.5*dx,0);
    QPointF q8(0.25*dx,-0.2*dy);

    QPointF q9(0.75*dx,0.8*dy);
    QPointF q10(0.5*dx,dy);
    QPointF q11(0.25*dx,1.2*dy);

    QPointF q12(0.25*dx,0.8*dy);
    QPointF q13(0.5*dx,dy);
    QPointF q14(0.75*dx,1.2*dy);

    transform1.rotate(theta);
    q1 = transform1.map(q1) ;
    q2 = transform1.map(q2) ;

    q3 = transform1.map(q3) ;
    q4 = transform1.map(q4) ;
    q5 = transform1.map(q5) ;

    q6 = transform1.map(q6) ;
    q7 = transform1.map(q7) ;
    q8 = transform1.map(q8) ;

    q9 = transform1.map(q9) ;
    q10 = transform1.map(q10) ;
    q11 = transform1.map(q11) ;

    q12 = transform1.map(q12) ;
    q13 = transform1.map(q13) ;
    q14 = transform1.map(q14) ;



    if(index==0){
        borderDots.at(1)->moveBy(q2.x(), q2.y());
        borderDots.at(3)->moveBy(q1.x(), q1.y());
        // 过渡点
        borderDots.at(4)->moveBy(q3.x(), q3.y());  // 过渡点1
        borderDots.at(5)->moveBy(q4.x(), q4.y());          // 过渡点2
        borderDots.at(6)->moveBy(q5.x(), q5.y()); // 过渡点3
    }
    if(index==1){
        borderDots.at(0)->moveBy(q2.x(), q2.y());
        borderDots.at(2)->moveBy(q1.x(), q1.y());
        // 过渡点
        borderDots.at(4)->moveBy(q6.x(), q6.y());  // 过渡点1
        borderDots.at(5)->moveBy(q7.x(), q7.y());          // 过渡点2
        borderDots.at(6)->moveBy(q8.x(), q8.y()); // 过渡点3
    }
    if(index==2){
        borderDots.at(3)->moveBy(q2.x(), q2.y());
        borderDots.at(1)->moveBy(q1.x(), q1.y());
        // 过渡点
        borderDots.at(4)->moveBy(q9.x(), q9.y());  // 过渡点1
        borderDots.at(5)->moveBy(q10.x(), q10.y());          // 过渡点2
        borderDots.at(6)->moveBy(q11.x(), q11.y()); // 过渡点3
    }
    if(index==3){
        borderDots.at(2)->moveBy(q2.x(), q2.y());
        borderDots.at(0)->moveBy(q1.x(), q1.y());

        // 过渡点
        borderDots.at(4)->moveBy(q12.x(), q12.y());  // 过渡点1
        borderDots.at(5)->moveBy(q13.x(), q13.y());          // 过渡点2
        borderDots.at(6)->moveBy(q14.x(), q14.y()); // 过渡点3
    }
    draw();

}
FlowDocuElement *FlowDocuElement::deepClone()
{
    FlowDocuElement* clonedElement = new FlowDocuElement();
    clonedElement->borderDots.clear();
    clonedElement->controlDots.clear();

    clonedElement->borderColor=this->borderColor;
    clonedElement->contentColor = this->contentColor;
    clonedElement->selected = this->selected;

    clonedElement->mainItem->setPath(this->mainItem->path());
    clonedElement->mainItem->setBrush(this->mainItem->brush());
    clonedElement->mainItem->setPen(this->mainItem->pen());
    clonedElement->rotangle = this->rotangle;

    int cont=0;
    for (QGraphicsRectItem* borderDot : this->borderDots) {
        QGraphicsRectItem* newDot = new QGraphicsRectItem(borderDot->rect());
        newDot->setBrush(borderDot->brush());
        newDot->setPen(borderDot->pen());
        newDot->setPos(borderDot->pos());
        clonedElement->borderDots.append(newDot);
        if(cont<4){
            clonedElement->controlDots.append(newDot);
            cont++;
        }
    }
    clonedElement->setPos(this->pos());
    clonedElement->setRotation(this->rotation());
    clonedElement->setScale(this->scale());

    return clonedElement;
}
void FlowDocuElement::serialize(QDataStream &out, const FlowElement &element)
{
    // out << element.pos() << element.rotation() << element.scale();
    // qDebug()<<element.pos() << element.rotation() << element.scale();

    int type=5;
    out<<type;
    qDebug()<<type;
    ElementSerializer::serializeDouble(element.rotangle,out);
    ElementSerializer::serializeColor(element.contentColor,out);
    ElementSerializer::serializeColor(element.borderColor,out);
    out<<element.borderDots.size();
    for(auto dot:element.borderDots){
        ElementSerializer::serializeGraphicsRectItem(dot,out);
    }
}
FlowElement* FlowDocuElement::deSerialize(QDataStream& in) {
    //此方法应在子类中被重载

    FlowDocuElement *cur = new FlowDocuElement();

    cur->rotangle = ElementSerializer::deserializeDouble(in);
    cur->contentColor = ElementSerializer::deserializeColor(in);
    cur->borderColor = ElementSerializer::deserializeColor(in);
    qsizetype borderDotsSize;
    in>>borderDotsSize;
    qDebug()<<borderDotsSize<<" bordersize";
    cur->borderDots.clear();
    cur->controlDots.clear();
    int cont=0;
    for(int i=0;i<borderDotsSize;i++){
        cur->borderDots.append(ElementSerializer::deserializeGraphicsRectItem(in));
        if(cont<4){
            cont++;
            cur->controlDots.append(cur->borderDots.last());
        }
    }
    cur->resetArrowDots();
    cur->draw();

    return cur;
}
