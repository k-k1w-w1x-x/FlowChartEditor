#include "canvas.h"
#include "rectangleelement.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), selectedElement(nullptr), activeControlPointIndex(-1),
    gridSpacing(20), gridColor(Qt::lightGray)
{
    setFocusPolicy(Qt::StrongFocus);  // 确保 Canvas 能接收键盘焦点
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

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制网格线
    drawGrid(painter);

    // 绘制图形元素
    for (FlowElement *element : elements) {
        element->draw(painter);

        // 只有当选中时才绘制控制点
        if (element == selectedElement) {
            painter.setPen(QPen(Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(element->boundingRect().adjusted(-5, -5, 5, 5));  // 绘制选中框

            // 绘制控制点
            RectangleElement *rectangle = dynamic_cast<RectangleElement*>(element);
            if (rectangle) {
                const QRect *controlPoints = rectangle->getControlPoints();
                painter.setBrush(Qt::black);
                for (int i = 0; i < 8; ++i) {
                    painter.drawRect(controlPoints[i]);
                }
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


void Canvas::keyPressEvent(QKeyEvent *event)  // 确保这个定义与.h中的声明匹配
{
    if (!selectedElement) {
        qDebug() << "No element selected";
        return;
    }

    if (event->key() == Qt::Key_Backspace) {
        qDebug() << "Deleting selected element";
        elements.removeOne(selectedElement);
        delete selectedElement;
        selectedElement = nullptr;
        update();  // 更新画布
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        selectedElement = getElementAt(event->pos());
        if (selectedElement) {
            lastMousePosition = event->pos();
            setFocus();  // 确保 Canvas 获得焦点以接收键盘事件
            qDebug() << "Element selected";

            // 检查是否点击了控制点
            RectangleElement *rectangle = dynamic_cast<RectangleElement*>(selectedElement);
            if (rectangle && rectangle->isControlPoint(event->pos(), activeControlPointIndex)) {
                qDebug() << "Control point selected at index:" << activeControlPointIndex;
            } else {
                activeControlPointIndex = -1;  // 未选中控制点
            }
        } else {
            qDebug() << "No element selected";
        }
        update();  // 更新画布以显示选中的状态
    } else if (event->button() == Qt::RightButton) {
        FlowElement *element = getElementAt(event->pos());
        if (element) {
            RectangleElement *rectangle = dynamic_cast<RectangleElement*>(element);
            if (rectangle) {
                QColor newBorderColor = QColorDialog::getColor(rectangle->getBorderColor(), this, "Select Border Color");
                if (newBorderColor.isValid()) {
                    rectangle->setBorderColor(newBorderColor);
                }
                QColor newFillColor = QColorDialog::getColor(rectangle->getFillColor(), this, "Select Fill Color");
                if (newFillColor.isValid()) {
                    rectangle->setFillColor(newFillColor);
                }
                update();  // 更新画布显示
            }
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (selectedElement && (event->buttons() & Qt::LeftButton)) {
        if (activeControlPointIndex != -1) {
            // 处理控制点的拖动以调整大小
            RectangleElement *rectangle = dynamic_cast<RectangleElement*>(selectedElement);
            if (rectangle) {
                rectangle->resize(activeControlPointIndex, event->pos());
                update();  // 更新画布以显示调整后的图形
            }
        } else {
            // 移动整个图形
            QPoint offset = event->pos() - lastMousePosition;
            selectedElement->move(offset);
            lastMousePosition = event->pos();
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        activeControlPointIndex = -1;  // 释放控制点
    }
}

FlowElement* Canvas::getElementAt(const QPoint &pos)
{
    for (FlowElement *element : elements) {
        if (element->contains(pos)) {
            return element;
        }
    }
    return nullptr;
}

void Canvas::addShape(FlowElement *element)
{
    elements.append(element);
    update();
}





