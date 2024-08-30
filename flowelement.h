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
    FlowElement( QPainterPath* initialPath,
                 QVector<QGraphicsRectItem>* borderDotPositions);
    void draw(QPainter &painter);

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

protected:
    QGraphicsPathItem *mainItem;                // 主图形项
    QVector<QGraphicsRectItem>* borderDots;      // 边界点的集合
    QPainterPath *path;                         // 用于绘制的路径
};

inline FlowElement::FlowElement( QPainterPath *initialPath,  QVector<QGraphicsRectItem> *borderDotPositions)
{
    this->borderDots = borderDotPositions;
    this->path = initialPath;
}

#endif // FLOWELEMENT_H
