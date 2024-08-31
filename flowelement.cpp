#include <flowelement.h>
#include <QPainter>
#include <QDebug>

FlowElement::FlowElement() {
    mainItem = new QGraphicsPathItem();
}

void FlowElement::draw(QVector<QGraphicsRectItem*>* borderDotPositions)
{
    qDebug() << "draw";

    if (!borderDotPositions || borderDotPositions->size() < 2) {
        qDebug() << "Not enough border dots to draw.";
        return;
    }

    QPainterPath path;
    path.moveTo(borderDotPositions->at(0)->rect().center());

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 0; i < borderDotPositions->size() - 1; ++i) {
        qDebug() << "drawwwwwww";
        QPointF end = borderDotPositions->at(i + 1)->rect().center();
        path.lineTo(end);
    }

    path.closeSubpath();

    // 设置主图形项路径
    mainItem->setPath(path);

    // 设置默认线条宽度
    QPen pen(Qt::black);
    pen.setWidth(3);
    mainItem->setPen(pen);
}

bool FlowElement::contains(const QPointF &point) {
    // 检查点是否在 mainItem 的路径内
    if(mainItem->contains(point)){
        qDebug()<<"FlowElement::contains=True";
    }
    return mainItem->contains(point);
}
