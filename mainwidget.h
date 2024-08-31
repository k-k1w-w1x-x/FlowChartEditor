#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include<qmainwindow.h>
#include "flowrectelement.h"
#include "flowdiamondelement.h"
#include "flowparaelement.h"
#include "flowcircleelement.h"
#include "flowsubelement.h"

class Canvas;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    // void update();
    // void createRectangle();
    // void createDiamond();
    // void createLine();
    // void createArrow();

private:
    Ui::MainWidget *ui;
    Canvas *canvas;
    QVBoxLayout *sidebarLayout;
    QPushButton *rectangleButton;
    QPushButton *diamondButton;
    QPushButton *lineButton;
    QPushButton *arrowButton;
};
#endif // MAINWIDGET_H
