#include "flowsubelement.h"
#include <QGraphicsRectItem>
#include <QPainter>
#define DOT_SIZE 5

FlowSubElement::FlowSubElement() : FlowElement() {
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(150, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(250, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(250, 200);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(150, 200);

    controlDots = borderDots;
    calArrowDots();

    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左上角
    borderDots.last()->setPos(160, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右上角
    borderDots.last()->setPos(240, 100);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 右下角
    borderDots.last()->setPos(240, 200);
    borderDots.append(new QGraphicsRectItem(QRectF(0, 0, DOT_SIZE, DOT_SIZE), this));  // 左下角
    borderDots.last()->setPos(160, 200);


    // 绘制路径
    draw();
}

void FlowSubElement::draw(){

    QPainterPath path;
    QPainterPath path1;
    // 依次取出两个小矩形的中心点，并绘制线条
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 1; i < 4; ++i) {
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


    path1.moveTo(borderDots[4]->scenePos() + borderDots[4]->rect().center());
    path1.lineTo(borderDots[7]->scenePos() + borderDots[7]->rect().center());

    path1.lineTo(borderDots[6]->scenePos() + borderDots[6]->rect().center());
    path1.lineTo(borderDots[5]->scenePos() + borderDots[5]->rect().center());
    path1.closeSubpath();
    QPen pen(Qt::black);
    pen.setWidth(2);
    innerItem->setPath(path1);
    innerItem->setBrush(QBrush(contentColor));
    innerItem->setPen(pen);

    // 设置主图形项路径
    mainItem->setPath(path);
    mainItem->setBrush(QBrush(contentColor));

    // //设置两个线条
    // line1->setPath(path1);
    qDebug()<<"hahahahahahaha";
    // 设置默认线条宽度

    mainItem->setPen(pen);
}


void FlowSubElement::mySetScale(int index, double dx, double dy) {
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

                // 内部控制点的相应缩放
                borderDots.at(4)->setPos(x+dx * 0.9, y+dy);   // 内部左上角
                borderDots.at(5)->setPos(x+dx * 0.1, y+dy);       // 内部右上角
                borderDots.at(6)->setPos(x+dx * 0.1, y+0);        // 内部右下角
                borderDots.at(7)->setPos(x+dx * 0.9, y+0);    // 内部左下角
            }
            if(index==1){
                borderDots.at(0)->setPos(x+0, y+dy);
                borderDots.at(2)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(5)->setPos(x+dx * 0.9, y+dy);   // 内部右上角
                borderDots.at(4)->setPos(x+dx * 0.1, y+dy);       // 内部左上角
                borderDots.at(7)->setPos(x+dx * 0.1, y+0);        // 内部左下角
                borderDots.at(6)->setPos(x+dx * 0.9, y+0);    // 内部右下角
            }
            if(index==2){
                borderDots.at(3)->setPos(x+0, y+dy);
                borderDots.at(1)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(6)->setPos(x+dx * 0.9, y+dy);   // 内部右下角
                borderDots.at(7)->setPos(x+dx * 0.1, y+dy);       // 内部左下角
                borderDots.at(4)->setPos(x+dx * 0.1, y+0);        // 内部左上角
                borderDots.at(5)->setPos(x+dx * 0.9, y+0);    // 内部右上角
            }
            if(index==3){
                borderDots.at(2)->setPos(x+0, y+dy);
                borderDots.at(0)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(7)->setPos(x+dx * 0.9, y+dy);   // 内部左下角
                borderDots.at(6)->setPos(x+dx * 0.1, y+dy);       // 内部右下角
                borderDots.at(5)->setPos(x+dx * 0.1, y+0);        // 内部右上角
                borderDots.at(4)->setPos(x+dx * 0.9, y+0);    // 内部左上角
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

                // 内部控制点的相应缩放
                borderDots.at(4)->setPos(x+dx * 0.9, y+dy);   // 内部左上角
                borderDots.at(5)->setPos(x+dx * 0.1, y+dy);       // 内部右上角
                borderDots.at(6)->setPos(x+dx * 0.1, oppY+0);        // 内部右下角
                borderDots.at(7)->setPos(x+dx * 0.9, oppY+0);    // 内部左下角
            }
            if(index==1){
                borderDots.at(0)->setPos(x+0, y+dy);
                borderDots.at(2)->setPos(x+dx, oppY+0);

                // 内部控制点的相应缩放
                borderDots.at(5)->setPos(x+dx * 0.9, y+dy);   // 内部右上角
                borderDots.at(4)->setPos(x+dx * 0.1, y+dy);       // 内部左上角
                borderDots.at(7)->setPos(x+dx * 0.1, oppY+0);        // 内部左下角
                borderDots.at(6)->setPos(x+dx * 0.9, oppY+0);    // 内部右下角
            }
            if(index==2){
                borderDots.at(3)->setPos(x+0, y+dy);
                borderDots.at(1)->setPos(x+dx, oppY+0);

                // 内部控制点的相应缩放
                borderDots.at(6)->setPos(x+dx * 0.9, y+dy);   // 内部右下角
                borderDots.at(7)->setPos(x+dx * 0.1, y+dy);       // 内部左下角
                borderDots.at(4)->setPos(x+dx * 0.1, oppY+0);        // 内部左上角
                borderDots.at(5)->setPos(x+dx * 0.9, oppY+0);    // 内部右上角
            }
            if(index==3){
                borderDots.at(2)->setPos(x+0, y+dy);
                borderDots.at(0)->setPos(x+dx, oppY+0);

                // 内部控制点的相应缩放
                borderDots.at(7)->setPos(x+dx * 0.9, y+dy);   // 内部左下角
                borderDots.at(6)->setPos(x+dx * 0.1, y+dy);       // 内部右下角
                borderDots.at(5)->setPos(x+dx * 0.1, oppY+0);        // 内部右上角
                borderDots.at(4)->setPos(x+dx * 0.9, oppY+0);    // 内部左上角
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

                // 内部控制点的相应缩放
                borderDots.at(4)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+dy);   // 内部左上角
                borderDots.at(5)->setPos(0.9*oppX+0.1*x+dx * 0.1, y+dy);       // 内部右上角
                borderDots.at(6)->setPos(0.9*oppX+0.1*x+dx * 0.1, y+0);        // 内部右下角
                borderDots.at(7)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+0);    // 内部左下角
            }
            if(index==1){
                borderDots.at(0)->setPos(oppX+0, y+dy);
                borderDots.at(2)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(5)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+dy);   // 内部右上角
                borderDots.at(4)->setPos(0.1*x+0.9*oppX+dx * 0.1, y+dy);       // 内部左上角
                borderDots.at(7)->setPos(0.1*x+0.9*oppX+dx * 0.1, y+0);        // 内部左下角
                borderDots.at(6)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+0);    // 内部右下角
            }
            if(index==2){
                borderDots.at(3)->setPos(oppX+0, y+dy);
                borderDots.at(1)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(6)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+dy);   // 内部右下角
                borderDots.at(7)->setPos(0.1*x+0.9*oppX+dx * 0.1, y+dy);       // 内部左下角
                borderDots.at(4)->setPos(0.1*x+0.9*oppX+dx * 0.1, y+0);        // 内部左上角
                borderDots.at(5)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+0);    // 内部右上角
            }
            if(index==3){
                borderDots.at(2)->setPos(oppX+0, y+dy);
                borderDots.at(0)->setPos(x+dx, y+0);

                // 内部控制点的相应缩放
                borderDots.at(7)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+dy);   // 内部左下角
                borderDots.at(6)->setPos(0.9*oppX+0.1*x+dx * 0.1, y+dy);       // 内部右下角
                borderDots.at(5)->setPos(0.9*oppX+0.1*x+dx * 0.1, y+0);        // 内部右上角
                borderDots.at(4)->setPos(0.1*oppX+0.9*x+dx * 0.9, y+0);    // 内部左上角
            }
        }
        draw();
        return;
    }
    // 移动被选中的控制点
    controlDots.at(index)->moveBy(dx, dy);

    if (index == 0) {  // 左上角
        borderDots.at(1)->moveBy(0, dy);       // 右上角
        borderDots.at(3)->moveBy(dx, 0);       // 左下角

        // 内部控制点的相应缩放
        borderDots.at(4)->moveBy(dx * 0.9, dy);   // 内部左上角
        borderDots.at(5)->moveBy(dx * 0.1, dy);       // 内部右上角
        borderDots.at(6)->moveBy(dx * 0.1, 0);        // 内部右下角
        borderDots.at(7)->moveBy(dx * 0.9, 0);    // 内部左下角

    } else if (index == 1) {  // 右上角
        borderDots.at(0)->moveBy(0, dy);       // 左上角
        borderDots.at(2)->moveBy(dx, 0);       // 右下角

        // 内部控制点的相应缩放
        borderDots.at(5)->moveBy(dx * 0.9, dy);   // 内部右上角
        borderDots.at(4)->moveBy(dx * 0.1, dy);       // 内部左上角
        borderDots.at(7)->moveBy(dx * 0.1, 0);        // 内部左下角
        borderDots.at(6)->moveBy(dx * 0.9, 0);    // 内部右下角

    } else if (index == 2) {  // 右下角
        borderDots.at(3)->moveBy(0, dy);       // 左下角
        borderDots.at(1)->moveBy(dx, 0);       // 右上角

        // 内部控制点的相应缩放
        borderDots.at(6)->moveBy(dx * 0.9, dy);   // 内部右下角
        borderDots.at(7)->moveBy(dx * 0.1, dy);       // 内部左下角
        borderDots.at(4)->moveBy(dx * 0.1, 0);        // 内部左上角
        borderDots.at(5)->moveBy(dx * 0.9, 0);    // 内部右上角

    } else if (index == 3) {  // 左下角
        borderDots.at(2)->moveBy(0, dy);       // 右下角
        borderDots.at(0)->moveBy(dx, 0);       // 左上角

        // 内部控制点的相应缩放
        borderDots.at(7)->moveBy(dx * 0.9, dy);   // 内部左下角
        borderDots.at(6)->moveBy(dx * 0.1, dy);       // 内部右下角
        borderDots.at(5)->moveBy(dx * 0.1, 0);        // 内部右上角
        borderDots.at(4)->moveBy(dx * 0.9, 0);    // 内部左上角
    }

    // 重绘图形
    draw();
}
