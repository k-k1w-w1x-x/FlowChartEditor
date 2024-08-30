#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include "flowelement.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    void addShape(FlowElement *element);
    void setGridSpacing(int spacing);  // 设置网格间隔
    void setGridColor(const QColor &color);  // 设置网格颜色

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void drawGrid(QPainter &painter);  // 绘制网格线
    QList<FlowElement*> elements;
    FlowElement *selectedElement;
    QPoint lastMousePosition;
    int activeControlPointIndex;

    int gridSpacing;  // 网格线的间隔
    QColor gridColor; // 网格线的颜色

    FlowElement* getElementAt(const QPoint &pos);
};

#endif // CANVAS_H
