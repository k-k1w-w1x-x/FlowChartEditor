#ifndef GRAPHICSTEXTITEM_CPP
#define GRAPHICSTEXTITEM_CPP

#include "graphicstextitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QCursor>

GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent) {}

GraphicsTextItem::GraphicsTextItem(const QString &text, QGraphicsItem *parent, FlowElement *follow, bool activeCreate)
    : QGraphicsTextItem(text, parent)
    , followElement(follow)
    , first(activeCreate)
{
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    setSelected(true);
    setAcceptHoverEvents(true);

    QTransform t;
    t.scale(1.5, 1.5);
    setTransform(t);

    scaling = resizing = 0;
}

GraphicsTextItem::~GraphicsTextItem() {}

QRectF GraphicsTextItem::boundingRect() const
{
    QRectF rect = QGraphicsTextItem::boundingRect();
    // rect = rect.marginsAdded(QMarginsF(1, 1, 1, 1));
    return rect;
}

void GraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    if (event->reason() != Qt::PopupFocusReason)
    {
        follow();
        qDebug() << "!!!!";
        setPlainText(toPlainText());
        setTextInteractionFlags(Qt::NoTextInteraction);
        emit leaveTextEditor();
        QGraphicsTextItem::focusOutEvent(event);
    } else setSelected(true);
}

void GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (first)
    {
        first = false;
        return;
    }
    if (textInteractionFlags() == Qt::NoTextInteraction && event->button() == Qt::LeftButton)
    {
        emit enterTextEditor();
        qDebug() << "????";
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void GraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    // if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    // {
    //     setPlainText(toPlainText());
    //     setTextInteractionFlags(Qt::NoTextInteraction);
    //     setSelected(false);
    //     clearFocus();
    // }
    QGraphicsTextItem::keyPressEvent(event);
    follow();
}

void GraphicsTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();

    QRectF rect = boundingRect();
    QRectF topLeft, topRight, bottomLeft, bottomRight, top, bottom, left, right;
    topLeft = QRectF(rect.topLeft().x(), rect.topLeft().y(), 5, 5);
    topRight = QRectF(rect.topRight().x() - 5, rect.topRight().y(), 5, 5);
    bottomLeft = QRectF(rect.bottomLeft().x(), rect.bottomLeft().y() - 5, 5, 5);
    bottomRight = QRectF(rect.bottomRight().x() - 5, rect.bottomRight().y() - 5, 5, 5);

    top = QRectF(rect.topLeft().x() + 5, rect.topLeft().y(), rect.width() - 10, 5);
    bottom = QRectF(rect.bottomLeft().x() + 5, rect.bottomLeft().y() - 5, rect.width() - 10, 5);
    left = QRectF(rect.topLeft().x(), rect.topLeft().y() + 5, 5, rect.height() - 10);
    right = QRectF(rect.topRight().x() - 5, rect.topRight().y() + 5, 5, rect.height() - 10);

    if (isSelected())
    {
        if (topLeft.contains(pos) || bottomRight.contains(pos))
            setCursor(Qt::SizeFDiagCursor);
        else
            if (bottomLeft.contains(pos) || topRight.contains(pos))
                setCursor(Qt::SizeBDiagCursor);
            else
                if (top.contains(pos) || bottom.contains(pos))
                    setCursor(Qt::SizeVerCursor);
                else
                    if (left.contains(pos) || right.contains(pos))
                        setCursor(Qt::SizeHorCursor);
                    else
                        setCursor(Qt::ArrowCursor);
    } else
        setCursor(Qt::ArrowCursor);

    QGraphicsTextItem::hoverEnterEvent(event);
}

void GraphicsTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QGraphicsTextItem::hoverLeaveEvent(event);
}

void GraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF rect = boundingRect();
    QRectF topLeft, topRight, bottomLeft, bottomRight, top, bottom, left, right;
    topLeft = QRectF(rect.topLeft().x(), rect.topLeft().y(), 5, 5);
    topRight = QRectF(rect.topRight().x() - 5, rect.topRight().y(), 5, 5);
    bottomLeft = QRectF(rect.bottomLeft().x(), rect.bottomLeft().y() - 5, 5, 5);
    bottomRight = QRectF(rect.bottomRight().x() - 5, rect.bottomRight().y() - 5, 5, 5);

    top = QRectF(rect.topLeft().x() + 5, rect.topLeft().y(), rect.width() - 10, 5);
    bottom = QRectF(rect.bottomLeft().x() + 5, rect.bottomLeft().y() - 5, rect.width() - 10, 5);
    left = QRectF(rect.topLeft().x(), rect.topLeft().y() + 5, 5, rect.height() - 10);
    right = QRectF(rect.topRight().x() - 5, rect.topRight().y() + 5, 5, rect.height() - 10);

    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        scaling = 0;
        resizing = 0;
        if (topLeft.contains(pos) || topRight.contains(pos) || bottomLeft.contains(pos) || bottomRight.contains(pos))
            scaling = 3;
        if (top.contains(pos) || bottom.contains(pos))
            scaling = 1;
        if (left.contains(pos) || right.contains(pos))
            scaling = 2;
        if (topLeft.contains(pos) || top.contains(pos) || left.contains(pos))
            resizing = 1;
        if (topRight.contains(pos) || right.contains(pos))
            resizing = 2;
        if (bottomLeft.contains(pos) || bottom.contains(pos))
            resizing = 3;
        if (bottomRight.contains(pos))
            resizing = 4;
        initialScenePos = event->scenePos();
        initialTransform = transform();
        initialWidth = boundingRect().width() * initialTransform.m11();
        initialHeight = boundingRect().height() * initialTransform.m22();
    }
    QGraphicsTextItem::mousePressEvent(event);
}

void GraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    if (resizing)
    {
        qreal width = initialWidth, height = initialHeight, deltax = initialTransform.m31(), deltay = initialTransform.m32();
        prepareGeometryChange();
        if (resizing == 1)
        {
            if (scaling & 2)
            {
                width += initialScenePos.x() - pos.x();
                deltax += pos.x() - initialScenePos.x();
            }
            if (scaling & 1)
            {
                height += initialScenePos.y() - pos.y();
                deltay += pos.y() - initialScenePos.y();
            }
            QTransform transform;
            transform.translate(deltax, deltay);
            transform.scale(qMax(width / initialWidth * initialTransform.m11(), 1.5),
                            qMax(height / initialHeight * initialTransform.m22(), 1.5));
            setTransform(transform);
            update();
        }
        if (resizing == 2)
        {
            if (scaling & 2)
            {
                width += pos.x() - initialScenePos.x();
            }
            if (scaling & 1)
            {
                height += initialScenePos.y() - pos.y();
                deltay += pos.y() - initialScenePos.y();
            }
            QTransform transform;
            transform.translate(deltax, deltay);
            transform.scale(qMax(width / initialWidth * initialTransform.m11(), 1.5),
                            qMax(height / initialHeight * initialTransform.m22(), 1.5));
            setTransform(transform);
            update();
        }
        if (resizing == 3)
        {
            if (scaling & 2)
            {
                width += initialScenePos.x() - pos.x();
                deltax += pos.x() - initialScenePos.x();
            }
            if (scaling & 1)
            {
                height += pos.y() - initialScenePos.y();
            }
            QTransform transform;
            transform.translate(deltax, deltay);
            transform.scale(qMax(width / initialWidth * initialTransform.m11(), 1.5),
                            qMax(height / initialHeight * initialTransform.m22(), 1.5));
            setTransform(transform);
            update();
        }
        if (resizing == 4)
        {
            if (scaling & 2)
                width += pos.x() - initialScenePos.x();
            if (scaling & 1)
                height += pos.y() - initialScenePos.y();
            QTransform transform;
            transform.translate(deltax, deltay);
            transform.scale(qMax(width / initialWidth * initialTransform.m11(), 1.5),
                            qMax(height / initialHeight * initialTransform.m22(), 1.5));
            setTransform(transform);
            update();
        }
    } else
        if (textInteractionFlags() == Qt::NoTextInteraction)
        {
            setCursor(Qt::SizeAllCursor);
            qreal deltax = initialTransform.m31() + pos.x() - initialScenePos.x(),
                deltay = initialTransform.m32() + pos.y() - initialScenePos.y();
            QTransform transform;
            transform.translate(deltax, deltay);
            transform.scale(initialTransform.m11(), initialTransform.m22());
            setTransform(transform);
            update();
        }
    follow();
    QGraphicsTextItem::mouseMoveEvent(event);
}

void GraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    scaling = resizing = 0;
    follow();
    QGraphicsTextItem::mouseReleaseEvent(event);
}

void GraphicsTextItem::follow()
{
    if (followElement != nullptr)
    {
        QPointF eps(boundingRect().width() * transform().m11() / 2,
                    boundingRect().height() * transform().m22() / 2);
        QTransform t;
        t.scale(transform().m11(), transform().m22());
        setTransform(t);
        setPos((followElement->controlDots.at(0)->pos() + followElement->controlDots.at(2)->pos()) / 2 - eps);
        setZValue(followElement->mainItem->zValue() + 1);
    }
}

void GraphicsTextItem::move(QPointF delta)
{
    qreal deltax = transform().m31() + delta.x(),
        deltay = transform().m32() + delta.y();
    QTransform t;
    t.translate(deltax, deltay);
    t.scale(transform().m11(), transform().m22());
    setTransform(t);
    update();
}

GraphicsTextItem* GraphicsTextItem::deepClone()
{
    GraphicsTextItem *ret = new GraphicsTextItem(toPlainText());
    ret->setTransform(transform());
    ret->setPos(this->pos());
    ret->setDefaultTextColor(this->defaultTextColor());
    return ret;
}

void GraphicsTextItem::serialize(QDataStream &out, const GraphicsTextItem &element)
{
    out << this->toPlainText();
    out << this->transform();
    out << this->pos();
    out << this->defaultTextColor();
    qDebug() << "serializeGraphicsTextItem:"
             << "Text:" << this->toPlainText()
             << "Transform:" << this->transform()
             << "Position:" << this->pos()
             << "Color:" << this->defaultTextColor();
}
GraphicsTextItem* GraphicsTextItem::deSerialize(QDataStream &in) {
    // 创建一个新的 GraphicsTextItem 对象
    GraphicsTextItem *cur = new GraphicsTextItem("");

    // 反序列化文本内容
    QString text;
    in >> text;
    cur->setPlainText(text);

    // 反序列化变换矩阵
    QTransform transform;
    in >> transform;
    cur->setTransform(transform);

    // 反序列化位置
    QPointF position;
    in >> position;
    cur->setPos(position);

    // 反序列化颜色
    QColor color;
    in >> color;
    cur->setDefaultTextColor(color);

    qDebug() << "deSerializeGraphicsTextItem:"
             << "Text:" << text
             << "Transform:" << transform
             << "Position:" << position
             << "Color:" << color;

    return cur;
}

#endif // GRAPHICSTEXTITEM_CPP
