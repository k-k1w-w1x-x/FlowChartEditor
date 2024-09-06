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
#include "flowradiuselement.h"
#include "flowdocuelement.h"
#include "flowplaygroundelement.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QScrollBar>
#include <QScrollArea>

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
    Canvas *canvas;
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void init_left_button();
    void init_top_button();
    void init_menu_layout();
    void outputSvg();

    void onExportButtonClicked();
    void onImportButtonClicked();
private slots:
    // void update();
    // void createRectangle();
    // void createDiamond();
    // void createLine();
    // void createArrow();
    void onColorButtonClicked();
    void onBorderColorButtonClicked();
    // void onArrowButtonClicked();

    void on_searchButton_clicked();

signals:
    //arrow_flag为true
    void arrow_first_click();

    //arrow_flag为flase
    void arrow_second_click();

private:

    Ui::MainWidget *ui;

    bool arrow_flag = false;

    // QVBoxLayout *sidebarLayout;
    // QPushButton *rectangleButton;
    // QPushButton *diamondButton;
    // QPushButton *lineButton;
    // QPushButton *arrowButton;
    QPushButton *line_button;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *redoMenu;
    QMenu *undoMenu;

    QAction *exportAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *backgroundAction;
    QAction *back_returnAction;

    QAction *redoAction;
    QAction *undoAction;

    QGridLayout *mainLayout;
    QVBoxLayout *topLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;

};
#endif // MAINWIDGET_H
