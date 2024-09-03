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
    int deltax[4]={-3,3,3,-3};
    int deltay[4]={-3,-3,3,3};
    bool isInBorder[2]={true,true};

    virtual QRectF boundingRect() const override; // 定义边界矩形
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; // 定义绘制操作
    virtual FlowElement* deepClone() ;
    virtual void mySetScale(int index,double dx,double dy) ; //放大缩小 重命名了scale()函数
    bool* inBorder(int idx);
    void calArrowDots();
    void resetArrowDots();

protected:

};

#endif // FLOWELEMENT_H
