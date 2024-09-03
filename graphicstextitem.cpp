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

GraphicsTextItem::GraphicsTextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    setSelected(true);
    setAcceptHoverEvents(true);
    setTextInteractionFlags(Qt::TextEditorInteraction);

    QRectF rect = boundingRect();
    topLeft = QRectF(rect.topLeft().x(), rect.topLeft().y(), 5, 5);
    topRight = QRectF(rect.topRight().x() - 5, rect.topRight().y(), 5, 5);
    bottomLeft = QRectF(rect.bottomLeft().x(), rect.bottomLeft().y() - 5, 5, 5);
    bottomRight = QRectF(rect.bottomRight().x() - 5, rect.bottomRight().y() - 5, 5, 5);

    top = QRectF(rect.topLeft().x() + 5, rect.topLeft().y(), rect.width() - 10, 5);
    bottom = QRectF(rect.bottomLeft().x() + 5, rect.bottomLeft().y() - 5, rect.width() - 10, 5);
    left = QRectF(rect.topLeft().x(), rect.topLeft().y() + 5, 5, rect.height() - 10);
    right = QRectF(rect.topRight().x() - 5, rect.topRight().y() + 5, 5, rect.height() - 10);

    scaling = resizing = 0;
}

GraphicsTextItem::~GraphicsTextItem() {}

QRectF GraphicsTextItem::boundingRect() const
{
    QRectF rect = QGraphicsTextItem::boundingRect();
    rect = rect.marginsAdded(QMarginsF(1, 1, 1, 1));
    return rect;
}

void GraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "!!!!";
    setPlainText(toPlainText());
    setTextInteractionFlags(Qt::NoTextInteraction);
    QGraphicsTextItem::focusOutEvent(event);
}

void GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction && event->button() == Qt::LeftButton)
    {
        qDebug() << "????";
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void GraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        setPlainText(toPlainText());
        setTextInteractionFlags(Qt::NoTextInteraction);
        setSelected(false);
        clearFocus();
    }
    QGraphicsTextItem::keyPressEvent(event);
}

void GraphicsTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();

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
            transform.scale(width / initialWidth * initialTransform.m11(), height / initialHeight * initialTransform.m22());
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
            transform.scale(width / initialWidth * initialTransform.m11(), height / initialHeight * initialTransform.m22());
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
            transform.scale(width / initialWidth * initialTransform.m11(), height / initialHeight * initialTransform.m22());
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
            transform.scale(width / initialWidth * initialTransform.m11(), height / initialHeight * initialTransform.m22());
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
    QGraphicsTextItem::mouseMoveEvent(event);
}

void GraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    scaling = resizing = 0;
    QGraphicsTextItem::mouseReleaseEvent(event);
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

#endif // GRAPHICSTEXTITEM_CPP
