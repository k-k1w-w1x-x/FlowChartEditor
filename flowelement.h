#ifndef FLOWELEMENT_H
#define FLOWELEMENT_H
#include<qgraphicsitem.h>
#include <QPainter>
#include <QPoint>
#include <QRect>

class FlowElement
{
public:
    // 带参数的构造函数
    FlowElement();
    void draw(QVector<QGraphicsRectItem*>* borderDotPositions);
    bool contains(const QPointF &point);
    bool selected = false;

    // // 虚析构函数，确保派生类正确清理
    // virtual ~FlowElement();

    // // 纯虚函数，要求派生类实现具体的绘制逻辑
    // virtual void draw(QPainter &painter) = 0;

    // // 纯虚函数，检查给定点是否包含在元素内
    // virtual bool contains(const QPoint &point) const = 0;

    // // 纯虚函数，用于移动元素
    // virtual void move(const QPoint &offset) = 0;

    // // 更新主图形项，根据边界点重新得到图形
    // virtual QGraphicsPathItem* updateMainItem()=0;

public:
    QGraphicsPathItem *mainItem = new QGraphicsPathItem;                // 主图形项
    QVector<QGraphicsRectItem*>* borderDots;    // 边界点的集合
    QPen pen ;
};

#endif // FLOWELEMENT_H
