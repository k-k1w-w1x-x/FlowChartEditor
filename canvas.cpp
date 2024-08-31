#include "canvas.h"
// #include "rectangleelement.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

Canvas::Canvas(QWidget *parent)
    : QGraphicsScene(parent), selectedElement(nullptr), activeControlPointIndex(-1),
    gridSpacing(20), gridColor(Qt::lightGray)
{
    // setFocusPolicy(Qt::StrongFocus);  // 确保 Canvas 能接收键盘焦点
}

void Canvas::setGridSpacing(int spacing)
{
    gridSpacing = spacing;
    update();  // 更新画布，重新绘制网格线
}

void Canvas::setGridColor(const QColor &color)
{
    gridColor = color;
    update();  // 更新画布，重新绘制网格线
}

void Canvas::drawBackground(QPainter* painter, const QRectF& rect)
{
    // 绘制网格线
    drawGrid(*painter);

    // 绘制图形元素
    for (FlowElement *element : elements) {
        element->draw(element->borderDots);

        painter->setPen(element->pen);
        painter->drawPath(element->mainItem->path());
        if (element->selected) {
            QPen pen(Qt::red);
            pen.setWidth(3);
            painter->setPen(pen);

            for (QGraphicsRectItem *borderDotPosition : *element->borderDots) {
                QRectF rect = borderDotPosition->rect();
                painter->drawRect(rect);
            }
        }
    }
}

void Canvas::drawGrid(QPainter &painter)
{
    painter.setPen(gridColor);

    // 绘制垂直线
    for (int x = gridSpacing; x < width(); x += gridSpacing) {
        painter.drawLine(x, 0, x, height());
    }

    // 绘制水平线
    for (int y = gridSpacing; y < height(); y += gridSpacing) {
        painter.drawLine(0, y, width(), y);
    }
}



void Canvas::addShape(FlowElement *element)
{
    elements.append(element);
    qDebug()<<"addShape";
    update();
}

// void Canvas::mousePressEvent(QMouseEvent *event)
// {
//     QPointF clickedPoint = event->pos();
//     bool elementClicked = false;
//     qDebug() << "mousePressEvent";
//     for (FlowElement* element : elements) {
//         if (element->contains(clickedPoint)) {
//             qDebug() << "clicked";

//             // 标记选中的元素
//             element->selected=true;
//             elementClicked = true;
//         } else {
//             qDebug() << "no-clicked";
//             element->selected=false;
//         }
//     }

//     if (elementClicked) {
//         update();  // 触发重绘
//     }
// }

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem*>(itemAt(event->scenePos(), QTransform()));
    if (item == nullptr)
    {
        GraphicsTextItem *textItem = new GraphicsTextItem("Text here.");
        textItem->setPos(event->scenePos());
        this->addItem(textItem);
        graphicTextItems.push_back(textItem);
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}
