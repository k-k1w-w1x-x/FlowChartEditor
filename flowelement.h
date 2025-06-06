#ifndef FLOWELEMENT_H
#define FLOWELEMENT_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPainter>
#include<ElementSerializer.h>
class FlowElement : public QGraphicsItem {
public:
    FlowElement();
    virtual ~FlowElement() {
        qDebug()<<"delete FlowElement";
            for (auto dot : this->borderDots) {
                delete dot;
                this->arrowDots.removeOne(dot);
            }
            for (auto dot : this->arrowDots) {
                delete dot;
            }
    }

    virtual void draw();
    virtual bool contains(const QPointF &point) const;
    virtual void move(double dx,double dy);  // 改为 delta 移动量
    QGraphicsPathItem *mainItem;
    QVector<QGraphicsRectItem*> borderDots;
    QVector<QGraphicsRectItem*> controlDots;
    QVector<QGraphicsRectItem*> arrowDots;
    bool selected = false;
    QColor contentColor = Qt::white;
    // int deltax[4]={-3,3,3,-3};
    // int deltay[4]={-3,-3,3,3};
    // bool isInBorder[2]={true,true};
    QColor borderColor = Qt::black;

    virtual QRectF boundingRect() const override; // 定义边界矩形
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; // 定义绘制操作
    virtual FlowElement* deepClone() =0;
    virtual void serialize(QDataStream& out, const FlowElement& element){};
    static FlowElement* deSerialize(QDataStream& in) ;
    virtual void mySetScale(int index,double dx,double dy) ; //放大缩小 重命名了scale()函数
    // bool* inBorder(int idx);
    void calArrowDots();
    void resetArrowDots();
    void myRotate(QPointF mousePos,QPointF *centerPos,double dx,double dy);
    void rotate(double angleDegrees);
    double rotangle;

protected:

};

#endif // FLOWELEMENT_H
