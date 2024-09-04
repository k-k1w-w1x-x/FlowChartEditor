#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "flowelement.h"
#include "flowsubelement.h"
#include "graphicstextitem.h"
#include"keyeventFilter.h"
#include "flowarrowelement.h"

class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    void onCopy();
    void onPaste();
    void onDelete();

    QList<FlowElement*> clipboard;
    QList<FlowArrowElement*> arrows;
    QGraphicsScene *scene;
    explicit Canvas(QWidget *parent = nullptr);
    void addShape(FlowElement *element);
    void setGridSpacing(int spacing);  // 设置网格间隔
    void setGridColor(const QColor &color);  // 设置网格颜色
    bool clickmove = false;
    bool clickscale = false;
    bool arrowclickmove = false;
    bool arrowclickscale = false;
    bool mouseclick = false;
    bool elementClicked = false;
    bool isArrowing = false;
    QList<FlowElement*> dragSelectedElements ;
    QList<FlowArrowElement*> dragSelectedArrows;
    double Manhattandis(QGraphicsRectItem *p1,QGraphicsRectItem *p2);
    bool isCross(FlowArrowElement *arrow1,FlowArrowElement*arrow2);
    double crossProduct(QPointF a,QPointF b);


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void drawArrows();

private:
    void drawGrid(QPainter &painter, const QRectF &rect);  // 绘制网格线

    int gridSpacing;  // 网格线的间隔
    QColor gridColor; // 网格线的颜色
    QList<FlowElement*> elements ;
    // QList<FlowElement*> dragSelectedElements ;
    KeyEventFilter *keyEventFilter;
    QPointF lastMousePosition;



    std::vector<GraphicsTextItem*> graphicTextItems;
    bool isDragging=false;
    bool isScaling=false;
    void onUndo();
    void onRedo();
    void onFind();
    FlowElement* clickedSelectedElement = nullptr;
    int clickedControlDot;
    int arrowClickedContronDot = 0;
public slots:
    void onColorButtonClicked();
    void setCross();
};

#endif // CANVAS_H
