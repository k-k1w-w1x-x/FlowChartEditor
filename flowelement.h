#ifndef FLOWELEMENT_H
#define FLOWELEMENT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPainter>

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
    QVector<QGraphicsRectItem*> arrowDots;
    bool selected = false;
    QColor contentColor = Qt::white;
    int deltax[4]={-1,1,1,-1};
    int deltay[4]={-1,-1,1,1};
    bool isInBorder[2]={true,true};

    virtual QRectF boundingRect() const override; // 定义边界矩形
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; // 定义绘制操作
    virtual void scale(int index,double dx,double dy) ; //放大缩小
    bool inBorder(int idx);
    void calArrowDots();
    void resetArrowDots();

protected:

};

#endif // FLOWELEMENT_H
