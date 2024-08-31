#include "flowelement.h"
#include <QPainter>
#include <QDebug>

FlowElement::FlowElement() {
    mainItem = new QGraphicsPathItem(this);
}

void FlowElement::draw() {
    qDebug() << "draw";

    QPainterPath path;

    // 依次取出两个小矩形的中心点，并绘制线条
    path.moveTo(borderDots[0]->scenePos() + borderDots[0]->rect().center());

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 1; i < borderDots.size(); ++i) {
        qDebug() << "drawwwwwww";
        path.lineTo(borderDots[i]->scenePos() + borderDots[i]->rect().center());
    }
    for(QGraphicsRectItem* borderDot : borderDots){
        borderDot->setBrush(Qt::red);
        QPen pen(Qt::red);
        borderDot->setPen(pen);
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

    // 然后移动主图形项
    mainItem->moveBy(dx, dy);

    // 重新绘制路径
    draw();
}
QRectF FlowElement::boundingRect() const {
    // 返回项的边界矩形
    return QRectF(150, 100, 100, 100);  // 根据你的需求调整大小和位置
}

void FlowElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 绘制图形项的外观
    painter->setBrush(Qt::blue);  // 例如使用蓝色填充
    painter->drawRect(boundingRect());
}
