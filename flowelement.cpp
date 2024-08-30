#include <flowelement.h>
#include <QPainter>
#include <QDebug>
FlowElement::FlowElement(){}
void FlowElement::draw(QPainter &painter, QVector<QGraphicsRectItem*>* borderDotPositions)
{
    qDebug() << "draw";

    if (!borderDotPositions || borderDotPositions->size() < 2) {
        qDebug() << "Not enough border dots to draw.";
        return;
    }

    painter.setPen(Qt::black);  // 设置线条颜色

    // 依次取出两个小矩形的中心点，并绘制线条
    for (int i = 0; i < borderDotPositions->size() - 1; ++i) {
        QPointF start = borderDotPositions->at(i)->rect().center();
        QPointF end = borderDotPositions->at(i + 1)->rect().center();
        painter.drawLine(start, end);
    }
    painter.drawLine(borderDotPositions->last()->rect().center(), borderDotPositions->first()->rect().center());
}

