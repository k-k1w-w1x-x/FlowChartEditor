#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QGraphicsScene>
#include "flowelement.h"
#include "graphicstextitem.h"

class Canvas : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    void addShape(FlowElement *element);
    void setGridSpacing(int spacing);  // 设置网格间隔
    void setGridColor(const QColor &color);  // 设置网格颜色
    // void mousePressEvent(QMouseEvent *event);

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    // void keyPressEvent(QKeyEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void mouseDoubleClicked(QGraphicsSceneMouseEvent *event);

private:
    void drawGrid(QPainter &painter);  // 绘制网格线
    QList<FlowElement*> elements;
    FlowElement *selectedElement;
    QPoint lastMousePosition;
    int activeControlPointIndex;

    int gridSpacing;  // 网格线的间隔
    QColor gridColor; // 网格线的颜色

    std::vector<GraphicsTextItem*> graphicTextItems;

    // FlowElement* getElementAt(const QPoint &pos);
};

#endif // CANVAS_H
