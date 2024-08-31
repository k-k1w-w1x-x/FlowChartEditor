#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "canvas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenuBar>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget), canvas(new Canvas(this))
{
    ui->setupUi(this);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色
    // 将 Canvas 添加到主布局的右侧部分
    ui->mainLayout->addWidget(canvas);

    QPainterPath *path = new QPainterPath();

    // 创建一个文档形状的路径
    path->moveTo(0, 0);
    path->lineTo(100, 0); // 上边
    path->lineTo(100, 80); // 右边
    path->cubicTo(90, 90, 60, 90, 50, 80); // 底部的波浪
    path->cubicTo(40, 70, 10, 70, 0, 80); // 波浪连接
    path->lineTo(0, 0); // 左边回到起点
    QVector<QGraphicsRectItem>*x = new QVector<QGraphicsRectItem>;

    FlowElement *test = new FlowElement(path,x);
    canvas->addShape(test);



    //初始化左侧按钮
    init_left_button();

    //初始化顶部布局
    init_menu_layout();
}

void MainWidget::init_menu_layout() {
    menuBar = new QMenuBar(this);
    ui->menu_layout->setMenuBar(menuBar);

    // 创建菜单
    fileMenu = menuBar->addMenu("File");
    editMenu = menuBar->addMenu("Edit");
    undoMenu = menuBar->addMenu(QIcon(":/menu/undo.png"),"");
    redoMenu = menuBar->addMenu(QIcon(":/menu/redo.png"),"");

    // filemenu创建菜单项
    newAction = new QAction(QIcon(":/menu/new.png"),"New", this);
    openAction = new QAction(QIcon(":/menu/open.png"),"Open", this);
    saveAction = new QAction(QIcon(":/menu/save.png"),"Save", this);
    exitAction = new QAction("Exit", this);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);

    //横线分隔
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // editmenu创建菜单项
    copyAction = new QAction(QIcon(":/menu/copy.png"),"Copy", this);
    pasteAction = new QAction(QIcon(":/menu/paste.png"),"Paste", this);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    //redo按钮信号
    //connect(redoMenu, &QMenu::aboutToShow, this, &QWidget::close);

}

void MainWidget::init_left_button() {
    //设置左侧按钮

    //矩形
    ui->rect_button->setFixedSize(60,50);
    QIcon icon1(":/type/rect.png");
    ui->rect_button->setIcon(icon1);
    ui->rect_button->setIconSize(QSize(32, 32));

    //文档矩形
    ui->rect3_button->setFixedSize(60,50);
    QIcon icon2(":/type/rect3.png");
    ui->rect3_button->setIcon(icon2);
    ui->rect3_button->setIconSize(QSize(32, 32));

    //菱形
    ui->rhombus_button->setFixedSize(60,50);
    QIcon icon3(":/type/rhombus.png");
    ui->rhombus_button->setIcon(icon3);
    ui->rhombus_button->setIconSize(QSize(32, 32));

    //平行四边形
    ui->parallelogram_button->setFixedSize(60,50);
    QIcon icon4(":/type/parallelogram.png");
    ui->parallelogram_button->setIcon(icon4);
    ui->parallelogram_button->setIconSize(QSize(32, 32));

    //圆形
    ui->circle_button->setFixedSize(60,50);
    QIcon icon5(":/type/circle.png");
    ui->circle_button->setIcon(icon5);
    ui->circle_button->setIconSize(QSize(32, 32));

    //子流程矩形
    ui->rect2_button->setFixedSize(60,50);
    QIcon icon6(":/type/rect2.png");
    ui->rect2_button->setIcon(icon6);
    ui->rect2_button->setIconSize(QSize(40, 40));

    //开始结束矩形
    ui->rect4_button->setFixedSize(60,50);
    QIcon icon7(":/type/rect4.png");
    ui->rect4_button->setIcon(icon7);
    ui->rect4_button->setIconSize(QSize(50, 50));

}

MainWidget::~MainWidget()
{
    delete ui;
}
