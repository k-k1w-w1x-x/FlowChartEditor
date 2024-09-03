#include "canvas.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>
bool clickmove = false;
bool clickscale = false;
bool elementClicked = false;
Canvas::Canvas(QWidget *parent)
    : QGraphicsView(parent),  gridSpacing(20),
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
        element->mainItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(element)){
            qDebug()<<"转型成功";
            scene->addItem(subElement->innerItem);
        }
        elements.append(element);
        for (auto controlDot : element->controlDots) {
            scene->addItem(controlDot);
            controlDot->setVisible(false);
        }
        for (auto arrowDot : element->arrowDots) {
            scene->addItem(arrowDot);
            arrowDot->setVisible(false);
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    clickmove = false;
    clickscale = false;
    elementClicked = false;
    QPointF clickedPoint = mapToScene(event->pos());
    if(isScaling && dragSelectedElements.size() == 1 ){
        qDebug()<<"判断一下";
        clickedSelectedElement = dragSelectedElements.at(0);
        int index = 0;
        for(QGraphicsRectItem* controlDot : clickedSelectedElement->controlDots){
            QPointF localPoint = controlDot->mapFromScene(clickedPoint);
            if(controlDot->contains(localPoint)){//若在选中状态下有控制点被点击
                qDebug()<<"进入缩放模式111";
                clickedControlDot = index;//标记哪个dot被选中了
                qDebug()<<"index:"<<index;
                setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
                elementClicked = true;
                break;
            }
            index++;
        }
        qDebug()<<"clickedSelectedElement = dragSelectedElements.at(0);"<<clickedControlDot;
    }

    // // clickedSelectedElement = nullptr;
    // bool elementClicked = false;

    // if(clickedSelectedElement){
        // int index = 0;//标记哪个dot被选中了
        // for(QGraphicsRectItem* controlDot : clickedSelectedElement->controlDots){
        //     QPointF localPoint = controlDot->mapFromScene(clickedPoint);
        //     if(controlDot->contains(localPoint)){//若在选中状态下有控制点被点击
        //         qDebug()<<"进入缩放模式";
        //         isScaling = true;
        //         clickedControlDot = index;//标记哪个dot被选中了
        //         lastMousePosition = clickedPoint;
        //         setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
        //         elementClicked = true;
        //         break;
        //     }
        //     index++;
        // }
    // }

    // else{
    //     qDebug()<<"not change";
    //     // 遍历所有元素，检查是否点击了某个元素
    bool clean = true;
    for(FlowElement *dragSelectedElement:dragSelectedElements){
        if(dragSelectedElement->mainItem->contains(clickedPoint)){
            clean = false;
        }
    }


    // if (!elementClicked) {
    //     clickedSelectedElement = nullptr;
    // }
    if(isScaling){
        lastMousePosition = clickedPoint;
        qDebug()<<"进入缩放模式";
    }
    if(isDragging){
        lastMousePosition = clickedPoint;
        qDebug()<<"进入拖动模式";
    }

    // 更新场景以反映选中状态的变化
    scene->update();

    QGraphicsView::mousePressEvent(event);
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(isScaling && dragSelectedElements.size() == 1 ){
        qDebug()<<"点点点点";
        clickedSelectedElement = dragSelectedElements.at(0);

        // int index = 0;//标记哪个dot被选中了
        // for(QGraphicsRectItem* controlDot : clickedSelectedElement->controlDots){
        //     QPointF localPoint = controlDot->mapFromScene(lastMousePosition);
        //     if(controlDot->contains(localPoint)){//若在选中状态下有控制点被点击
        //         qDebug()<<"进入缩放模式";
        //         // clickedControlDot = index;//标记哪个dot被选中了
        //         // qDebug()<<"index:"<<index;
        //         setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
        //         elementClicked = true;
        //         break;
        //     }
        //     // index++;
        // }
        if(elementClicked){
            qDebug()<<"缩放且鼠标移动";
            clickscale = true;
            QPointF currentPosition = mapToScene(event->pos());
            QPointF offset = currentPosition - lastMousePosition;
            qDebug()<<"clickedSelectedElement"<<clickedControlDot;
            clickedSelectedElement->mySetScale(clickedControlDot,offset.x(), offset.y());
            lastMousePosition = currentPosition;

            scene->update();
        }
    }
    if(isDragging && dragSelectedElements.size() == 1){
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;
        clickedSelectedElement = dragSelectedElements.at(0);
        if(clickedSelectedElement->contains(lastMousePosition)){
            qDebug()<<"1个！选中才能动！";
            clickedSelectedElement->move(offset.x(), offset.y());
            clickmove = true;
            lastMousePosition = currentPosition;
            scene->update();
        }
    }
    if (isDragging && dragSelectedElements.size() > 1) {
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;
        for(FlowElement *dragSelectedElement:dragSelectedElements){
            clickedSelectedElement = dragSelectedElement;
            clickedSelectedElement->move(offset.x(), offset.y());
            clickmove = true;
        }
        lastMousePosition = currentPosition;
        scene->update();
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF releasedPoint = mapToScene(event->pos());
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        isScaling = false;
    }
    setDragMode(QGraphicsView::RubberBandDrag);
    QGraphicsView::mouseReleaseEvent(event);

    if(!clickmove && !clickscale){
        for(FlowElement *dragSelectedElement:dragSelectedElements){
            dragSelectedElement->selected = false;
            for (auto controlDot : dragSelectedElement->controlDots) {
                controlDot->setVisible(false);
            }
            for (auto arrowDot : dragSelectedElement->arrowDots) {
                arrowDot->setVisible(false);
            }
        }
        dragSelectedElements.clear();
        qDebug()<<"这里的size"<<dragSelectedElements.size();
    }

    for (int i = elements.size() - 1; i >= 0; i-- ) {
        FlowElement *element = elements[i];
        if (element->mainItem->isSelected() && !clickmove && !clickscale) {
            dragSelectedElements.append(element);
        }
    }
    qDebug()<<dragSelectedElements.size();
    if(dragSelectedElements.size()>1){
        isDragging = true;
        setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
        for (int i = elements.size() - 1; i >= 0; i-- ) {
            FlowElement *element = elements[i];
            if (element->mainItem->isSelected()) {
                for (auto controlDot : element->controlDots) {
                    controlDot->setVisible(true);
                }
                for (auto arrowDot : element->arrowDots) {
                    scene->addItem(arrowDot);
                    arrowDot->setVisible(false);
                }
                element->selected = true;
            }
        }
    }
    if(dragSelectedElements.size()==1){
        isDragging = true;
        isScaling = true;
        setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
        FlowElement *element = dragSelectedElements.at(0);
        if (element->mainItem->isSelected()) {
            // 进入拖动模式
            qDebug()<<"clicked";
            clickedSelectedElement = element;
            // elementClicked = true;

            // 如果选中元素，显示四个边界点
            for (auto controlDot : element->controlDots) {
                controlDot->setVisible(true);
            }
            for (auto arrowDot : element->arrowDots) {
                scene->addItem(arrowDot);
                arrowDot->setVisible(true);
            }
            element->selected = true;
        }
    }
    scene->update();
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
