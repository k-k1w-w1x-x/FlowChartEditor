#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

class GraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    GraphicsTextItem(QGraphicsItem *parent = nullptr);
    GraphicsTextItem(const QString &text, QGraphicsItem *parent = nullptr);
    ~GraphicsTextItem();
    QRectF boundingRect() const override;

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRectF topLeft, topRight, bottomLeft, bottomRight, top, bottom, left, right;
    int scaling, resizing;
    QPointF initialScenePos, initialPos;
    QRectF initialRect;
    QTransform initialTransform;
};

#endif // GRAPHICSTEXTITEM_H
