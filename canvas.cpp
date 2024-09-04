#include "canvas.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>
#include<keyeventFilter.h>
#include <qgraphicsitem.h>
#include <float.h>

Canvas::Canvas(QWidget *parent)
    : QGraphicsView(parent),  gridSpacing(20),
    gridColor(Qt::lightGray), clickedSelectedElement(nullptr), isDragging(false)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scene = new QGraphicsScene(this);
    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    // setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::RubberBandDrag);

    // // 创建一个垂直布局，用于在画布左侧放置按钮
    // QVBoxLayout *layout = new QVBoxLayout(this);

    // // 创建按钮并添加到布局中
    // QPushButton *colorButton = new QPushButton("Change Color", this);
    // layout->addWidget(colorButton);

    // 连接按钮点击事件到槽函数
    // connect(colorButton, &QPushButton::clicked, this, &Canvas::onColorButtonClicked);
    // 初始化并安装 KeyEventFilter
    keyEventFilter = new KeyEventFilter(this);
    this->installEventFilter(keyEventFilter);

    // 初始化ZIndexManager
    zindexManager = new ZIndexManager();

    // 连接 KeyEventFilter 的信号到相应的槽函数
    connect(keyEventFilter, &KeyEventFilter::copyTriggered, this, &Canvas::onCopy);
    connect(keyEventFilter, &KeyEventFilter::pasteTriggered, this, &Canvas::onPaste);
    connect(keyEventFilter, &KeyEventFilter::undoTriggered, this, &Canvas::onUndo);
    connect(keyEventFilter, &KeyEventFilter::redoTriggered, this, &Canvas::onRedo);
    connect(keyEventFilter, &KeyEventFilter::findTriggered, this, &Canvas::onFind);
    connect(keyEventFilter, &KeyEventFilter::deleteTriggered, this, &Canvas::onDelete);

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
    if (!background_set) this->drawGrid(*painter, rect);
    else {
        // 加载背景图片
        QPixmap background(background_path);

        // 缩放背景图片以适应视图大小
        painter->drawPixmap(this->rect(), background.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    }
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
        if (FlowArrowElement* arrowElement = dynamic_cast<FlowArrowElement*>(element)){
            scene->addItem(arrowElement->mainItem);
            arrowElement->mainItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene->addItem(arrowElement->startDot);
            scene->addItem(arrowElement->endDot);
            arrows.append(arrowElement);
            setCross();
            return;
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
    qDebug()<<"mousePress!";
    if(isArrowing){
        return;
    }
    clickmove = false;
    clickscale = false;
    mouseclick = true;
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
    if((isDragging && dragSelectedElements.size() > 1) || (dragSelectedElements.empty() && dragSelectedArrows.size()>1)){
        bool clicksuccess = false;
        for(FlowElement *dragSelectedElement:dragSelectedElements){
            if(dragSelectedElement->mainItem->contains(clickedPoint)){
                clicksuccess = true;
            }
        }
        for(FlowArrowElement *dragSelectedArrow : dragSelectedArrows){
            if(!dragSelectedArrow->startElementDot && !dragSelectedArrow->endElementDot){
                if(dragSelectedArrow->mainItem->contains(clickedPoint)){
                    clicksuccess = true;
                }
            }
        }
        if(clicksuccess){
            lastMousePosition = clickedPoint;
            qDebug()<<"进入拖动模式";
        }
        else{
            for(FlowElement *dragSelectedElement:dragSelectedElements){
                for(QGraphicsRectItem *controlDot : dragSelectedElement->controlDots){
                    controlDot->setVisible(false);
                }
            }
            dragSelectedElements.clear();
            for(FlowArrowElement *dragSelectedArrow : dragSelectedArrows){
                if(!dragSelectedArrow->startElementDot && !dragSelectedArrow->endElementDot){
                    dragSelectedArrow->startDot->setVisible(false);
                    dragSelectedArrow->endDot->setVisible(false);
                }
            }
            dragSelectedArrows.clear();
            qDebug()<<"拖动失败";
        }
    }

    if(dragSelectedElements.empty() && dragSelectedArrows.size() == 1){
        FlowArrowElement *clickedArrow = dragSelectedArrows.at(0);
        QPointF localstPoint;
        QPointF localendPoint;
        if(clickedArrow->mainItem->contains(clickedPoint)){
            qDebug()<<"至少能平移";
            lastMousePosition = clickedPoint;
            arrowClickedContronDot = 3;
        }
        if(clickedArrow->startElementDot){
            localstPoint = clickedArrow->startElementDot->mapFromScene(clickedPoint);
        }
        else{
            localstPoint = clickedArrow->startDot->mapFromScene(clickedPoint);
        }

        if(clickedArrow->endElementDot){
            localendPoint = clickedArrow->endElementDot->mapFromScene(clickedPoint);
        }
        else{
            localendPoint = clickedArrow->endDot->mapFromScene(clickedPoint);
        }
        if(!clickedArrow->startElementDot && clickedArrow->startDot->contains(localstPoint)){
            qDebug()<<"点到起点1";
            arrowClickedContronDot = 1;
            lastMousePosition = clickedPoint;
        }
        if(clickedArrow->startElementDot && clickedArrow->startElementDot->contains(localstPoint)){
            qDebug()<<"点到起点2";
            arrowClickedContronDot = 1;
            lastMousePosition = clickedPoint;
        }
        if(!clickedArrow->endElementDot && clickedArrow->endDot->contains(localendPoint)){
            qDebug()<<"点到终点1";
            arrowClickedContronDot = 2;
            lastMousePosition = clickedPoint;
        }
        if(clickedArrow->endElementDot && clickedArrow->endElementDot->contains(localendPoint)){
            qDebug()<<"点到终点2";
            arrowClickedContronDot = 2;
            lastMousePosition = clickedPoint;
        }
    }
    // 更新场景以反映选中状态的变化
    scene->update();

    QGraphicsView::mousePressEvent(event);
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{

    if(isArrowing){
        return;
    }
    if(!mouseclick){
        QGraphicsView::mouseMoveEvent(event);
        return;
    }
    if( isScaling && dragSelectedElements.size() == 1 ){
        // qDebug()<<"点点点点";
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
            clickedSelectedElement->mySetScale(clickedControlDot,offset.x(), offset.y());
            drawArrows();
            lastMousePosition = currentPosition;
            setCross();
            scene->update();
        }
    }
    if(isDragging)
    {
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;
        for (auto i : graphicTextItems)
            if (i->isSelected())
                i->move(offset);
    }
    if(isDragging && dragSelectedElements.size() == 1){
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;
        clickedSelectedElement = dragSelectedElements.at(0);
        bool canmove = false;
        for(FlowArrowElement *dragSelectedArrow : dragSelectedArrows){
            if(!dragSelectedArrow->startElementDot && !dragSelectedArrow->endElementDot){
                if(dragSelectedArrow->contains(lastMousePosition)){
                    canmove = true;
                }
            }
        }
        if(clickedSelectedElement->contains(lastMousePosition) || canmove){
            // qDebug()<<"1个！选中才能动！"<<isDragging;
            clickedSelectedElement->move(offset.x(), offset.y());
            for(FlowArrowElement *dragSelectedArrow : dragSelectedArrows){
                if(!dragSelectedArrow->startElementDot && !dragSelectedArrow->endElementDot){
                    dragSelectedArrow->move(offset.x(),offset.y());
                }
            }
            drawArrows();
            setCross();
            clickmove = true;
            lastMousePosition = currentPosition;
            scene->update();
        }
        QGraphicsView::mouseMoveEvent(event);
        return;
    }
    if ((isDragging && dragSelectedElements.size() > 1) || (dragSelectedElements.empty() && dragSelectedArrows.size()>1)) {
        setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
        qDebug()<<"多元素托拽";
        QPointF currentPosition = mapToScene(event->pos());
        QPointF offset = currentPosition - lastMousePosition;
        for(FlowElement *dragSelectedElement:dragSelectedElements){
            clickedSelectedElement = dragSelectedElement;
            clickedSelectedElement->move(offset.x(), offset.y());
            drawArrows();
            clickmove = true;
        }
        for(FlowArrowElement *dragSelectedArrow : dragSelectedArrows){
            if(!dragSelectedArrow->startElementDot && !dragSelectedArrow->endElementDot){
                dragSelectedArrow->move(offset.x(),offset.y());
                arrowclickmove = true;
            }
        }
        lastMousePosition = currentPosition;
        setCross();
        scene->update();
        setDragMode(QGraphicsView::RubberBandDrag);//启用拖拽框
        QGraphicsView::mouseMoveEvent(event);
        return;
    }
    if(dragSelectedElements.empty() && dragSelectedArrows.size() == 1 && arrowClickedContronDot){
        qDebug()<<"单箭头操作";
        if(arrowClickedContronDot != 3){
            setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
            qDebug()<<"托拽箭头";
            QPointF currentPosition = mapToScene(event->pos());
            QPointF offset = currentPosition - lastMousePosition;
            qDebug()<<offset;
            dragSelectedArrows.at(0)->mySetScale(arrowClickedContronDot,offset.x(),offset.y());
            lastMousePosition = currentPosition;
            setDragMode(QGraphicsView::RubberBandDrag);//启用拖拽框
            QGraphicsView::mouseMoveEvent(event);
            arrowclickscale = true;
            setCross();
        }
        else{
            qDebug()<<"只能平移了";
            setDragMode(QGraphicsView::NoDrag);//禁用拖拽框
            QPointF currentPosition = mapToScene(event->pos());
            QPointF offset = currentPosition - lastMousePosition;
            dragSelectedArrows.at(0)->move(offset.x(),offset.y());
            lastMousePosition = currentPosition;
            setDragMode(QGraphicsView::RubberBandDrag);//启用拖拽框
            QGraphicsView::mouseMoveEvent(event);
            arrowclickmove = true;
            setCross();
        }
        return;
    }
    QGraphicsView::mouseMoveEvent(event);

}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    //储存被选中的箭头
    if(!clickmove && !clickscale &&!isArrowing){
        dragSelectedArrows.clear();
        arrowClickedContronDot = 0;
        for(FlowArrowElement *arrow : arrows){
            if(arrow->mainItem->isSelected() ){
                qDebug()<<"add arrow";
                dragSelectedArrows.append(arrow);
                if(!arrow->startElementDot && !arrow->endElementDot){
                    qDebug()<<"可见";
                    arrow->startDot->setVisible(true);
                    arrow->endDot->setVisible(true);
                }

            }
        }
        qDebug()<<"arrowsize:"<<arrows.size();
    }


    if(isArrowing){
        if( arrows.empty() || (!arrows.last()->endDot->scenePos().x() == 0 && !arrows.last()->endDot->scenePos().y() == 0) ){
            qDebug()<<"开始画箭头";
            arrows.append(new FlowArrowElement);
            arrows.last()->startDot->setPos( mapToScene(event->pos()));
        }
        else{
            arrows.last()->endDot->setPos( mapToScene(event->pos()));
            arrows.last()->draw();
            scene->addItem(arrows.last()->mainItem);
            arrows.last()->mainItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene->addItem(arrows.last()->startDot);
            scene->addItem(arrows.last()->endDot);
            arrows.last()->startDot->setVisible(false);
            arrows.last()->endDot->setVisible(false);
            setCross();
        }
        return;
    }

    mouseclick = false;
    qDebug()<<"mouseRelease!";
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
    for (auto it = dragSelectedElements.rbegin(); it != dragSelectedElements.rend(); ++it) {
        zindexManager->setHighestZindexForItem(*it);
    }
    for(const auto element:graphicTextItems){
        if(element->isSelected())
        zindexManager->setHighestZindexForItem(element);
    }
    if(dragSelectedElements.empty() && dragSelectedArrows.size() == 1){
        FlowArrowElement *clickedArrow = dragSelectedArrows.at(0);
        qDebug()<<"only one arrow";
        //只有一个箭头被选中
        if(!clickedArrow->startElementDot){
            clickedArrow->startDot->setVisible(true);
        }
        else{
            clickedArrow->startDot->setVisible(false);
            clickedArrow->startElementDot->setVisible(true);
        }
        if(!clickedArrow->endElementDot){
            clickedArrow->endDot->setVisible(true);
        }
        else{
            clickedArrow->endDot->setVisible(false);
            clickedArrow->endElementDot->setVisible(true);
        }

    }
    else if(dragSelectedElements.empty() && dragSelectedArrows.empty()){
        for(FlowArrowElement *arrow : arrows){
            if(!arrow->startElementDot){
                arrow->startDot->setVisible(false);
            }
            else{
                arrow->startDot->setVisible(false);
                arrow->startElementDot->setVisible(false);
            }
            if(!arrow->endElementDot){
                arrow->endDot->setVisible(false);
            }
            else{
                arrow->endDot->setVisible(false);
                arrow->endElementDot->setVisible(false);
            }
        }
    }
    scene->update();
}

void Canvas::onColorButtonClicked()
{
    if(!clickedSelectedElement){
        qDebug() << "No element selected. Color change ignored.";
        return;
    }
    QColor color = QColorDialog::getColor(clickedSelectedElement->contentColor, this, "Select Color");
    for(const auto&dragselectedElement:dragSelectedElements){
        // QColor color = QColorDialog::getColor(dragselectedElement->contentColor, this, "Select Color");
        if (color.isValid()) {
            dragselectedElement->contentColor = color;  // 设置选中元素的颜色
            dragselectedElement->draw();
            scene->update();  // 触发重绘，将元素颜色更新
        }
    }
    // if (clickedSelectedElement) {
    //     QColor color = QColorDialog::getColor(clickedSelectedElement->contentColor, this, "Select Color");
    //     if (color.isValid()) {
    //         clickedSelectedElement->contentColor = color;  // 设置选中元素的颜色
    //         clickedSelectedElement->draw();
    //         scene->update();  // 触发重绘，将元素颜色更新
    //     }
    // } else {
    //     qDebug() << "No element selected. Color change ignored.";
    // }
}


void Canvas::onBorderColorButtonClicked()
{
    if(dragSelectedElements.empty() && dragSelectedArrows.empty()){
        qDebug() << "No element selected. Color change ignored.";
        return;
    }
    QColor color = QColorDialog::getColor(Qt::black, this, "Select Color");
    for(const auto&dragselectedElement:dragSelectedElements){
        // QColor color = QColorDialog::getColor(dragselectedElement->contentColor, this, "Select Color");
        if (color.isValid()) {
            dragselectedElement->borderColor = color;  // 设置选中元素的颜色
            dragselectedElement->draw();
            scene->update();  // 触发重绘，将元素颜色更新
        }
    }
    for(const auto&dragselectedArrow:dragSelectedArrows){
        // QColor color = QColorDialog::getColor(dragselectedElement->contentColor, this, "Select Color");
        if (color.isValid()) {
            dragselectedArrow->borderColor = color;  // 设置选中元素的颜色
            dragselectedArrow->draw();
            scene->update();  // 触发重绘，将元素颜色更新
        }
    }
    // if (clickedSelectedElement) {
    //     QColor color = QColorDialog::getColor(clickedSelectedElement->contentColor, this, "Select Color");
    //     if (color.isValid()) {
    //         clickedSelectedElement->contentColor = color;  // 设置选中元素的颜色
    //         clickedSelectedElement->draw();
    //         scene->update();  // 触发重绘，将元素颜色更新
    //     }
    // } else {
    //     qDebug() << "No element selected. Color change ignored.";
    // }
}
//键盘操作

// 添加一个剪切板列表


void Canvas::onCopy()
{
    qDebug() << "onCopy() called";



    // 获取选中的元素
    QList<FlowElement *> SelectedElementTemp = this->dragSelectedElements;
    for(FlowElement *dragSelectedArrow : dragSelectedArrows){
        SelectedElementTemp.append(dragSelectedArrow);
    }

    // if (SelectedElementTemp.empty()) {
    //     return; // 如果没有选中任何元素，则直接返回
    // }
    for(const auto&item:clipboard){
        delete(item);
    }
    clipboard.clear();
    textClipboard.clear();



    // 遍历选中的图形项，并将它们深拷贝
    for (const auto &item : SelectedElementTemp) {
        FlowElement *clonedElement = item->deepClone(); // 深拷贝元素
        clonedElement->move(10,10);
        clipboard.append(clonedElement);
    }

    for (auto i : graphicTextItems)
        if (i->isSelected())
        {
            textClipboard.push_back(i->deepClone());
            qDebug() << 11111;
        }

/*
    // 此时，selectedElements 列表中包含了深拷贝的元素
    // qDebug() << "复制了" << selectedItems.size() << "个元素";
    if (clickedSelectedElement) {
        FlowElement* SelectedElement = clickedSelectedElement->deepClone(); // 深拷贝元素
        if (SelectedElement) {
            clipboard.clear(); // 清空剪切板
            clipboard.append(SelectedElement); // 将深拷贝的元素加入剪切板
            qDebug() << "复制了一个元素到剪切板";
        }
    } else {
        qDebug() << "没有选中任何元素，无法复制";
    }
*/

}


void Canvas::onPaste() {
    qDebug() << "Paste action triggered";

    if (clipboard.isEmpty()) {
        qDebug() << "剪切板为空，无法粘贴";
    }

    // 遍历剪切板中的元素
    QList<FlowElement*>deleteElements,appendElements;
    for (FlowElement* element : clipboard) {
        FlowElement* clonedElement = element->deepClone(); // 深拷贝元素
        deleteElements.append(element);
        appendElements.append(clonedElement);
        // clipboard.removeOne(element);
        // clipboard.append(clonedElement);
        if (clonedElement) {
            // 将粘贴的元素稍微偏移位置
            clonedElement->move(10, 10); // 向右下偏移 10 像素
            addShape(element); // 将深拷贝的元素添加到场景中
            qDebug() << "粘贴了一个元素";
        } else {
            qDebug() << "deepClone 失败，无法粘贴该元素";
        }
    }
    for(const auto&u:deleteElements){
        clipboard.removeOne(u);
    }
    for(const auto&u:appendElements){
        clipboard.append(u);
    }

    qDebug() << textClipboard.size();
    for (auto i : textClipboard)
    {
        i->setSelected(false);
        scene->addItem(i);
        graphicTextItems.push_back(i);
    }
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"doubleclick";
    mouseclick = false;
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

void Canvas::onUndo() {
    qDebug() << "Undo action triggered";
    // 具体的撤销操作
}

void Canvas::onRedo() {
    qDebug() << "Redo action triggered";
    // 具体的重做操作
}

void Canvas::onFind() {
    qDebug() << "Find action triggered";
    // 具体的查找操作
}
void Canvas::removeFromCanvas(FlowElement* element){
    scene->removeItem(element->mainItem);
    if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(element)){
        scene->removeItem(subElement->innerItem);
    }
    for (auto dot : element->borderDots) {
        scene->removeItem(dot);
    }
    for (auto dot : element->arrowDots) {
        scene->removeItem(dot);
    }
    elements.removeOne(element);
    dragSelectedElements.removeOne(element);
}
void Canvas::onDelete() {
    qDebug() << "Delete action triggered";
    for (auto element : dragSelectedElements) {
        // scene->removeItem(element->mainItem);
        // if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(element)){
        //     scene->removeItem(subElement->innerItem);
        // }
        // for (auto dot : element->borderDots) {
        //     scene->removeItem(dot);
        // }
        // for (auto dot : element->arrowDots) {
        //     scene->removeItem(dot);
        // }
        // elements.removeOne(element);
        // dragSelectedElements.removeOne(element);
        removeFromCanvas(element);
        delete element;
    }
    for (auto i : graphicTextItems)
        if (i->isSelected())
        {
            scene->removeItem(i);
            graphicTextItems.removeOne(i);
            delete i;
        }
}
void Canvas::exportElements(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);

        // 写入元素数量
        out << elements.size();
        // qDebug()<<"elementsize"<<elements.size();
        // // 遍历并序列化每个元素
        for (FlowElement* element : elements) {
            element->serialize(out,*element);
        }

        file.close();
    } else {
        qWarning("Could not open file for writing.");
    }
}



void Canvas::importElements(const QString& filename) { // 实现 importElements 方法
    QFile file(filename);

    qDebug()<<"start import1";
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        for (auto element : elements) {
            scene->removeItem(element->mainItem);
            if(FlowSubElement* subElement = dynamic_cast<FlowSubElement*>(element)){
                scene->removeItem(subElement->innerItem);
            }
            for (auto dot : element->borderDots) {
                scene->removeItem(dot);
            }
            for (auto dot : element->arrowDots) {
                scene->removeItem(dot);
            }

            elements.removeOne(element);
            dragSelectedElements.removeOne(element);
            delete element;
        }
        for (auto i : graphicTextItems){
                scene->removeItem(i);
                graphicTextItems.removeOne(i);
                delete i;
        }
        qsizetype elementCount;
        in >> elementCount;
        // qDebug()<<elementCount;
        for (int i = 0; i < elementCount; ++i) {
            int type;
            in>>type;
            FlowElement* element;
            if(type==0){
                element = FlowRectElement::deSerialize(in);
            }
            // FlowElement* element = new FlowElement();  // 需要根据实际类型创建适当的子类对象
            // in >> *element;  // 使用重载的 >> 操作符进行反序列化

            addShape(element);
            // scene->addItem(element->mainItem);
        }

        file.close();
    } else {
        qWarning("Could not open file for reading.");
    }
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {

        qDebug() << "Shift key pressed!";
        for(FlowArrowElement *arrow : arrows){
            if(arrow->mainItem->isSelected()){
                qDebug()<<"看看锁谁的";
                //排序锁头
                double stman = DBL_MAX;
                double endman = DBL_MAX;
                FlowElement *stelement = nullptr;
                for(FlowElement *element:elements){
                    for(QGraphicsRectItem *arrowDot:element->arrowDots){
                        double tempstman = Manhattandis(arrowDot,arrow->startDot);
                        if( tempstman < stman){
                            stman = tempstman;
                            arrow->startElementDot = arrowDot;
                            stelement = element;
                        }
                    }
                }

                for(FlowElement *element:elements){
                    if(stelement == element){
                        qDebug()<<elements.size();
                        continue;
                    }
                    for(QGraphicsRectItem *arrowDot:element->arrowDots){
                        double tempendman = Manhattandis(arrowDot,arrow->endDot);
                        if( tempendman < endman){
                            endman = tempendman;
                            arrow->endElementDot = arrowDot;
                        }
                    }
                }
                //没找到合适的，不画
                if(arrow->startElementDot && arrow->endElementDot){
                    qDebug()<<"小开不算开";
                    arrow->draw();
                    arrow->startDot->setVisible(false);
                    arrow->startElementDot->setVisible(true);
                    arrow->endDot->setVisible(false);
                    arrow->endElementDot->setVisible(true);
                }
                else{
                    qDebug()<<"没找到合适的";
                    arrow->startElementDot = nullptr;
                    arrow->endElementDot = nullptr;
                }
            }
        }
        setCross();
    }
}

double Canvas::Manhattandis(QGraphicsRectItem *p1,QGraphicsRectItem *p2){
    return(abs(p1->scenePos().x()-p2->scenePos().x()) + abs(p1->scenePos().y()-p2->scenePos().y()));
}

void Canvas::drawArrows(){
    for(FlowArrowElement *arrow:arrows){
        arrow->draw();
    }
}

void Canvas::setCross(){
    qDebug()<<"调用setCross";
    for(int i = 0; i <= arrows.size() - 1; i++){
        int flag = 0;
        for(int j = 0; j <= arrows.size() - 1; j++){
            if(i!=j && isCross(arrows[i],arrows[j])){
                flag++;
                qDebug()<<"计算交点";
                double x1 = arrows[i]->startDot->x();
                double y1 = arrows[i]->startDot->y();
                double x2 = arrows[i]->endDot->x();
                double y2 = arrows[i]->endDot->y();
                if(arrows[i]->startElementDot){
                    x1=arrows[i]->startElementDot->x();
                    y1=arrows[i]->startElementDot->y();
                }
                if(arrows[i]->endElementDot){
                    x2=arrows[i]->endElementDot->x();
                    y2=arrows[i]->endElementDot->y();
                }

                double k1 = (y1 - y2)/(x1 - x2);
                double b1 = y1 - k1 * x1;

                double x3 = arrows[j]->startDot->x();
                double y3 = arrows[j]->startDot->y();
                double x4 = arrows[j]->endDot->x();
                double y4 = arrows[j]->endDot->y();
                if(arrows[j]->startElementDot){
                    x3=arrows[j]->startElementDot->x();
                    y3=arrows[j]->startElementDot->y();
                }
                if(arrows[j]->endElementDot){
                    x4=arrows[j]->endElementDot->x();
                    y4=arrows[j]->endElementDot->y();
                }
                double k2 = (y3 - y4)/(x3 - x4);
                double b2 = y3 - k2 * x3;
                double x = (b2 - b1)/(k1 - k2);
                double y = k1 * x + b1;
                qDebug()<<"x1:"<<x1<<",y1"<<y1;
                qDebug()<<"x2:"<<x2<<",y2"<<y2;
                qDebug()<<"x3:"<<x3<<",y3"<<y3;
                qDebug()<<"x4:"<<x4<<",y4"<<y4;
                qDebug()<<"k1:"<<k1<<",k2"<<k2;
                qDebug()<<"b1:"<<b1<<",b2"<<b2;
                qDebug()<<"交点:"<<x<<","<<y;

                arrows[i]->passingPoint.setX(x);
                arrows[i]->passingPoint.setY(y);
                arrows[j]->passingPoint.setX(x);
                arrows[j]->passingPoint.setY(y);
            }
            arrows[i]->draw();
            arrows[j]->draw();
        }
        if(flag==0){//没人和我相交
            qDebug()<<"没人和我相交";
            arrows[i]->passingPoint.setX(0);
            arrows[i]->passingPoint.setY(0);
            arrows[i]->draw();
        }
    }

}

bool Canvas::isCross(FlowArrowElement *arrow1,FlowArrowElement*arrow2){//判断是否相交
    qDebug()<<"调用isCross";
    QPointF a = arrow1->startDot->scenePos().toPoint();
    QPointF b = arrow1->endDot->scenePos().toPoint();
    QPointF c = arrow2->startDot->scenePos().toPoint();
    QPointF d = arrow2->endDot->scenePos().toPoint();

    if(arrow1->startElementDot){
        a=arrow1->startElementDot->scenePos();
    }
    if(arrow1->endElementDot){
        b=arrow1->endElementDot->scenePos();
    }
    if(arrow2->startElementDot){
        c=arrow2->startElementDot->scenePos();
    }
    if(arrow2->endElementDot){
        d=arrow2->endElementDot->scenePos();
    }

    if(fmax(c.x(),d.x())<fmin(a.x(),b.x())||fmax(a.x(),b.x())<fmin(c.x(),d.x())||fmax(c.y(),d.y())<fmin(a.y(),b.y())||fmax(a.y(),b.y())<fmin(c.y(),d.y()))
    {
        qDebug()<<"没交1";
        return false;
    }
    if(crossProduct(b-d,c-d)*crossProduct(a-c,c-d) > 0||crossProduct(d-b,a-b)*crossProduct(c-b,a-b)>0){
        qDebug()<<"没交2";
        return false;
    }
    qDebug()<<"交了";
    return true;
}
double Canvas::crossProduct(QPointF a,QPointF b){//叉乘
    return a.x() * b.y() - a.y() * b.x();
}
