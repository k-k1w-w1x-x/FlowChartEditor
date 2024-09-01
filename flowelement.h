#ifndef FLOWELEMENT_H
#define FLOWELEMENT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QVector>

class FlowElement : public QGraphicsItem {
public:
    FlowElement();
    virtual ~FlowElement() {}

    virtual void draw();
    virtual bool contains(const QPointF &point) const;
    void move(int dx, int dy);  // 改为 delta 移动量
    QGraphicsPathItem *mainItem;
    QVector<QGraphicsRectItem*> borderDots;
    QVector<QGraphicsRectItem*> controlDots;
    bool selected = false;
    QColor contentColor = Qt::white;

    virtual QRectF boundingRect() const override; // 定义边界矩形
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; // 定义绘制操作
protected:

};

#endif // FLOWELEMENT_H
