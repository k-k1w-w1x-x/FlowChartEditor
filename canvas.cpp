#include "canvas.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>

Canvas::Canvas(QWidget *parent)
    : QGraphicsView(parent), selectedElement(nullptr), gridSpacing(20),
    gridColor(Qt::lightGray), clickedSelectedElement(nullptr), isDragging(false)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::RubberBandDrag);

    // 创建一个垂直布局，用于在画布左侧放置按钮
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建按钮并添加到布局中
    QPushButton *colorButton = new QPushButton("Change Color", this);
    layout->addWidget(colorButton);

    // 连接按钮点击事件到槽函数
    connect(colorButton, &QPushButton::clicked, this, &Canvas::onColorButtonClicked);
}

void Canvas::setGridSpacing(int spacing)
{
    gridSpacing = spacing;
    scene->update();  // 更新场景，重新绘制网格线
}

void Canvas::setGridColor(const QColor &color)
{
    gridColor = color;
    scene->update();  // 更新场景，重新绘制网格线
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect)
{
    drawGrid(*painter, rect);
}

void Canvas::drawGrid(QPainter &painter, const QRectF &rect)
{
    painter.setPen(gridColor);

    // 绘制垂直线
    qreal left = int(rect.left()) - (int(rect.left()) % gridSpacing);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSpacing);

    QVector<QLineF> lines;
    for (qreal x = left; x < rect.right(); x += gridSpacing)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridSpacing)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter.drawLines(lines.data(), lines.size());
}

void Canvas::addShape(FlowElement *element)
{
    if (element && element->mainItem) {
        scene->addItem(element->mainItem);
        if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(element)){
            qDebug()<<"转型成功";
            scene->addItem(subElement->innerItem);
        }
        elements.append(element);
        for (auto controlDot : element->controlDots) {
            scene->addItem(controlDot);
            controlDot->setVisible(false);
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    QPointF clickedPoint = mapToScene(event->pos());
    clickedSelectedElement = nullptr;
    bool elementClicked = false;

    // 遍历所有元素，检查是否点击了某个元素
    for (FlowElement *element : elements) {
        if (element->mainItem->contains(clickedPoint)) {
            // 进入拖动模式
            if(element->selected){
                isDragging = true;
                lastMousePosition = clickedPoint;
                setDragMode(QGraphicsView::NoDrag);
            }
            qDebug()<<"clicked";
            clickedSelectedElement = element;
            elementClicked = true;

            // 如果选中元素，显示四个边界点
            for (auto controlDot : element->controlDots) {
                controlDot->setVisible(true);
            }
            element->selected = true;
        } else {
            // 如果未选中元素，隐藏边界点
            for (auto controlDot : element->controlDots) {
                controlDot->setVisible(false);
            }
            element->selected = false;
        }
    }

    if (!elementClicked) {
        clickedSelectedElement = nullptr;
    }

    // 更新场景以反映选中状态的变化
    scene->update();

    QGraphicsView::mousePressEvent(event);
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && clickedSelectedElement) {
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;

        clickedSelectedElement->move(offset.x(), offset.y());
        lastMousePosition = currentPosition;

        scene->update();
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
    setDragMode(QGraphicsView::RubberBandDrag);
    QGraphicsView::mouseReleaseEvent(event);
}

void Canvas::onColorButtonClicked()
{
    if (clickedSelectedElement) {
        QColor color = QColorDialog::getColor(clickedSelectedElement->contentColor, this, "Select Color");
        if (color.isValid()) {
            clickedSelectedElement->contentColor = color;  // 设置选中元素的颜色
            clickedSelectedElement->draw();
            scene->update();  // 触发重绘，将元素颜色更新
        }
    } else {
        qDebug() << "No element selected. Color change ignored.";
    }
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF pos = mapToScene(event->pos());
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem*>(scene->itemAt(pos, QTransform()));
    if (item == nullptr)
    {
        GraphicsTextItem *textItem = new GraphicsTextItem("Text here.");
        textItem->setPos(pos);
        scene->addItem(textItem);
        graphicTextItems.push_back(textItem);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}
