#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "graphicstextitem.h"
#include"keyeventFilter.h"
#include<zindexmanager.h>
#include<QFile>
#include<flowrectelement.h>
#include "flowarrowelement.h"
#include<flowradiuselement.h>
#include "flowelement.h"
#include "flowsubelement.h"
#include<flowcircleelement.h>
#include<flowdiamondelement.h>
#include<flowdocuelement.h>
#include<flowparaelement.h>
#include<flowplaygroundelement.h>
class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    bool background_set = false;
    QString background_path;

    void onCopy();
    void onPaste();
    void onDelete();
    void onCut();

    QList<FlowElement*> clipboard;
    QList<GraphicsTextItem*> textClipboard;
    QList<FlowArrowElement*> arrows;
    QGraphicsScene *scene;
    explicit Canvas(QWidget *parent = nullptr);
    void addShape(FlowElement *element);
    void addGraphicsTextItem(GraphicsTextItem *element);
    void setGridSpacing(int spacing);  // 设置网格间隔
    void setGridColor(const QColor &color);  // 设置网格颜色
    void exportElements(const QString& filename);
    void importElements(const QString& filename);
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
    void searchAndReplace(const QString &findStr, const QString &replaceStr);

    void pushAll();


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void removeFromCanvas(FlowElement *element);
protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void drawArrows();
    void updateTextItems();
    void recoverFromHistory();
    void autoAdsorption();

private:
    void drawGrid(QPainter &painter, const QRectF &rect);  // 绘制网格线
    void drawBack(QString filepath);
    int gridSpacing;  // 网格线的间隔
    QColor gridColor; // 网格线的颜色
    QList<FlowElement*> elements ;
    KeyEventFilter *keyEventFilter;
    QPointF lastMousePosition;
    QList<GraphicsTextItem*> graphicTextItems;
    bool isDragging=false;
    bool isScaling=false;
    void onUndo();
    void onRedo();
    void onFind();
    FlowElement* clickedSelectedElement = nullptr;
    int clickedControlDot ;
    ZIndexManager* zindexManager;
    int arrowClickedContronDot = 0;

    QList<QList<FlowElement*>> elementsHistory;
    QList<QList<FlowArrowElement*>> arrowsHistory;
    QList<QList<GraphicsTextItem*>> graphicTextItemsHistory;

    int currentHistoryIndex = -1;

    bool textEditing = false;

public slots:
    void onColorButtonClicked();
    void onBorderColorButtonClicked();
    void setCross();

};

#endif // CANVAS_H
