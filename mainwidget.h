#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include<qmainwindow.h>

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
    void init_left_button();
    void init_top_button();
    void init_menu_layout();

private:
    Ui::MainWidget *ui;
    Canvas *canvas;
    QVBoxLayout *sidebarLayout;
    QPushButton *rectangleButton;
    QPushButton *diamondButton;
    QPushButton *lineButton;
    QPushButton *arrowButton;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *redoMenu;
    QMenu *undoMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;

};
#endif // MAINWIDGET_H
