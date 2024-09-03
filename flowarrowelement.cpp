#include <flowarrowelement.h>
#include <QPen>
#include <cmath>
#define DOT_SIZE 5
FlowArrowElement::FlowArrowElement(): FlowElement(){
    startDot = new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this);
    endDot = new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this);
}
void FlowArrowElement::draw()  {
    // 创建一个 QPainterPath 来绘制箭头
    QPainterPath path;
    QPointF startPoint = startDot->scenePos() + startDot->rect().center();
    QPointF endPoint = endDot->scenePos() + endDot->rect().center();
    //锁头优先
    if(startElementDot){
        startPoint = startElementDot->scenePos() + startElementDot->rect().center();
    }
    if(endElementDot){
        endPoint = endElementDot->scenePos() + endElementDot->rect().center();
    }
    if(passingPoint.x()==0&&passingPoint.y()==0){
        path.moveTo(startPoint);
        path.lineTo(endPoint);
    }
    else{
        qDebug()<<"在draw里面passingPoint:"<<passingPoint.x()<<","<<passingPoint.y();
        double passSize = 5;
        if(endPoint.x()<startPoint.x()){
            passSize=-5;
        }
        double k = (endPoint.y()-startPoint.y())/(endPoint.x()-startPoint.x());
        QPointF passingPoint1(passingPoint.x() - passSize,passingPoint.y() - passSize * k);
        QPointF passingPoint2(passingPoint.x() + passSize,passingPoint.y() + passSize * k);
        path.moveTo(startPoint);
        path.lineTo(passingPoint1);
        drawHalfCircle(path,passingPoint,passingPoint1,passingPoint2);
        path.lineTo(endPoint);
    }
    // 箭头的头部宽度和长度
    const double arrowHeadSize = 10.0;

    // 计算箭头的角度
    double angle = std::atan2(endPoint.y() - startPoint.y(), endPoint.x() - startPoint.x());

    // 计算箭头的两个侧翼点
    QPointF arrowP1 = endPoint - QPointF(std::cos(angle - M_PI / 6) * arrowHeadSize,
                                         std::sin(angle - M_PI / 6) * arrowHeadSize);
    QPointF arrowP2 = endPoint - QPointF(std::cos(angle + M_PI / 6) * arrowHeadSize,
                                         std::sin(angle + M_PI / 6) * arrowHeadSize);

    // 将箭头侧翼添加到路径
    path.moveTo(arrowP1);
    path.lineTo(endPoint);
    path.lineTo(arrowP2);

    // 创建一个 QGraphicsPathItem 来显示箭头
    mainItem->setPath(path);
    mainItem->setPen(QPen(Qt::black, 2));  // 设置箭头的颜色和宽度
}
void FlowArrowElement::move(double dx,double dy)
{
    //解绑全部锁头
    if(startElementDot){
        //把锁头时的值赋给位置点
        startDot->scenePos() = startElementDot->scenePos();
        //解除锁头
        startElementDot = nullptr;
    }
    if(endElementDot){
        endDot->scenePos() = endElementDot->scenePos();
        endElementDot = nullptr;
    }
    startDot->moveBy(dx,dy);
    endDot->moveBy(dx,dy);
    draw();
}

void FlowArrowElement::mySetScale(int index,double dx,double dy){
    if(index==1){
        //解绑start
        if(startElementDot){
            //把锁头时的值赋给位置点
            startDot->scenePos() = startElementDot->scenePos();
            //解除锁头
            startElementDot = nullptr;
        }
        startDot->moveBy(dx,dy);
    }
    if(index==2){
        //解绑end
        if(endElementDot){
            //把锁头时的值赋给位置点
            endDot->scenePos() = endElementDot->scenePos();
            //解除锁头
            endElementDot = nullptr;
        }
        endDot->moveBy(dx,dy);
    }
    draw();
}

void FlowArrowElement::drawHalfCircle(QPainterPath &path,const QPointF &center, const QPointF &point1, const QPointF &point2) {
    // 计算半径
    qreal radius = QLineF(point1, point2).length() / 2.0;

    // 计算起始角度
    qreal angle = std::atan2(point2.y() - point1.y(), point2.x() - point1.x()) * 180.0 / M_PI;

    // 创建外接矩形
    QRectF boundingRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);

    // 绘制半圆（180度的弧线）
    path.arcMoveTo(boundingRect, angle + 180);
    path.arcTo(boundingRect, angle + 180, -180);
}
