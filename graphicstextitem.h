#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include "flowelement.h"

class GraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    GraphicsTextItem(QGraphicsItem *parent = nullptr);
    GraphicsTextItem(const QString &text, QGraphicsItem *parent = nullptr, FlowElement *follow = nullptr);
    ~GraphicsTextItem();
    QRectF boundingRect() const override;
    void move(QPointF delta);
    GraphicsTextItem* deepClone();
    void serialize(QDataStream& out, const GraphicsTextItem& element);
    static GraphicsTextItem* deSerialize(QDataStream& in) ;
    FlowElement *followElement;
    void follow();

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


signals:
    void enterTextEditor();
    void leaveTextEditor();

private:
    int scaling, resizing;
    QPointF initialScenePos;
    QTransform initialTransform;
    qreal initialWidth, initialHeight;

};

#endif // GRAPHICSTEXTITEM_H
