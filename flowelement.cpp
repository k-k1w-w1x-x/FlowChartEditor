#include<flowelement.h>
void FlowElement::draw(QPainter &painter)
{
    qDebug()<<"draw";
    painter.setPen(Qt::red);
    // painter.setPen(borderColor);
    // painter.setBrush(fillColor);
    painter.drawPath(*path);
}
