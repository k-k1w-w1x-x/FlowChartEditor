#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "canvas.h"
#include "flowrectelement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QGraphicsRectItem>
#include <QVector>
#include <QFileDialog>
#include <QLineEdit>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , canvas(new Canvas(this)), ui(new Ui::MainWidget)
{
    canvas->setSceneRect(0, 0, 1600, 1600);
    ui->setupUi(this);

    // 设置窗口大小
    this->resize(800, 600);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色
    // 将 Canvas 添加到主布局的右侧部分
    // setLayout(ui->mainLayout);
    ui->mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
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

    //初始化左侧按钮
    init_left_button();

    //初始化顶部布局
    init_menu_layout();

}

void MainWidget::outputSvg() {

}

void MainWidget::init_menu_layout() {

    ui->searchBox->setFixedSize(400, 35);
    ui->searchButton->setFixedSize(40, 40);
    ui->searchButton->setIcon(QIcon(":/menu/search.png"));
    //箭头没地方绑了先绑这儿
    connect(ui->searchButton, &QPushButton::clicked, [=](){
        canvas->isArrowing=!canvas->isArrowing;
        if(!canvas->isArrowing && !canvas->arrows.empty() && canvas->arrows.last()->endDot->scenePos().x() == 0 && canvas->arrows.last()->endDot->scenePos().y() == 0){
            //需要删除操作
            qDebug()<<"删除";
            FlowArrowElement *temp = canvas->arrows.last();
            canvas->arrows.removeLast();
            delete(temp->startDot);
            delete(temp->startElementDot);
            delete(temp->endDot);
            delete(temp->endElementDot);
            delete(temp);
        }
        if(canvas->isArrowing){
            for(FlowElement *element : canvas->dragSelectedElements){
                for(QGraphicsRectItem *controlDot:element->controlDots){
                    controlDot->setVisible(false);
                }
                for(QGraphicsRectItem *arrowDot:element->arrowDots){
                    arrowDot->setVisible(false);
                }
            }
        }
    });

    menuBar = new QMenuBar(this);
    ui->menuWidget->setLayout(ui->menu_layout);
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
    connect(openAction, &QAction::triggered, [=](){
        QString filePath = QFileDialog::getOpenFileName(this, "选择打开文件", "", "All Files (*)");
        if (!filePath.isEmpty()) {
            qDebug() << filePath;
        }
    });
    connect(newAction, &QAction::triggered, [=](){
        QString filePath = QFileDialog::getOpenFileName(this, "选择新建文件夹", "", "All Files (*)");
        if (!filePath.isEmpty()) {
            qDebug() << filePath;
        }
    });
    connect(saveAction, &QAction::triggered, [=](){
        QString filePath = QFileDialog::getOpenFileName(this, "选择保存位置", "", "All Files (*)");
        if (!filePath.isEmpty()) {
            qDebug() << filePath;
        }
    });

    //横线分隔
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // editmenu创建菜单项
    copyAction = new QAction(QIcon(":/menu/copy.png"),"Copy", this);
    pasteAction = new QAction(QIcon(":/menu/paste.png"),"Paste", this);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    //redo按钮信号!!!!
    //connect(redoMenu, &QMenu::aboutToShow, this, &QWidget::close);

    //Action按钮信号!!!
    //connect(saveAction, &QAction::triggered, this, &QWidget::close);
}

void MainWidget::init_left_button() {
    //设置左侧按钮

    //矩形
    ui->rect_button->setFixedSize(60,50);
    QIcon icon1(":/type/rect.png");
    ui->rect_button->setIcon(icon1);
    ui->rect_button->setIconSize(QSize(32, 32));
    connect(ui->rect_button, &QPushButton::clicked, [=](){
        FlowRectElement* rectElement = new FlowRectElement();
        canvas->addShape(rectElement);
    });

    //文档矩形
    ui->rect3_button->setFixedSize(60,50);
    QIcon icon2(":/type/rect3.png");
    ui->rect3_button->setIcon(icon2);
    ui->rect3_button->setIconSize(QSize(32, 32));
    connect(ui->rect3_button, &QPushButton::clicked, [=](){
        FlowDocuElement* documentElement = new FlowDocuElement();
        canvas->addShape(documentElement);
    });

    //菱形
    ui->rhombus_button->setFixedSize(60,50);
    QIcon icon3(":/type/rhombus.png");
    ui->rhombus_button->setIcon(icon3);
    ui->rhombus_button->setIconSize(QSize(32, 32));
    connect(ui->rhombus_button, &QPushButton::clicked, [=](){
        FlowDiamondElement* diamondElement = new FlowDiamondElement();
        canvas->addShape(diamondElement);
    });

    //平行四边形
    ui->parallelogram_button->setFixedSize(60,50);
    QIcon icon4(":/type/parallelogram.png");
    ui->parallelogram_button->setIcon(icon4);
    ui->parallelogram_button->setIconSize(QSize(32, 32));
    connect(ui->parallelogram_button, &QPushButton::clicked, [=](){
        FlowParaElement* paraElement = new FlowParaElement();
        canvas->addShape(paraElement);
    });

    //圆形
    ui->circle_button->setFixedSize(60,50);
    QIcon icon5(":/type/circle.png");
    ui->circle_button->setIcon(icon5);
    ui->circle_button->setIconSize(QSize(32, 32));
    connect(ui->circle_button, &QPushButton::clicked, [=](){
        FlowCircleElement* circleElement = new FlowCircleElement();
        canvas->addShape(circleElement);
    });

    //子流程矩形
    ui->rect2_button->setFixedSize(60,50);
    QIcon icon6(":/type/rect2.png");
    ui->rect2_button->setIcon(icon6);
    ui->rect2_button->setIconSize(QSize(40, 40));
    connect(ui->rect2_button, &QPushButton::clicked, [=](){
        FlowSubElement* subElement = new FlowSubElement();
        canvas->addShape(subElement);
    });


    //开始结束矩形
    ui->rect4_button->setFixedSize(60,50);
    QIcon icon7(":/type/rect4.png");
    ui->rect4_button->setIcon(icon7);
    ui->rect4_button->setIconSize(QSize(50, 50));
    connect(ui->rect4_button, &QPushButton::clicked, [=](){
        FlowPlaygroundElement* playgroundElement = new FlowPlaygroundElement();
        canvas->addShape(playgroundElement);
    });

    //color按钮
    ui->color_button->setFixedSize(60,50);
    connect(ui->color_button,&QPushButton::clicked,this,&MainWidget::onColorButtonClicked);
    QIcon icon8(":/menu/color_change.png");
    ui->color_button->setIcon(icon8);
    ui->color_button->setIconSize(QSize(32, 32));

    // 创建一个 FlowRectElement 并将其添加到 Canvas (QGraphicsScene) 中
    FlowRectElement* rectElement = new FlowRectElement();
    rectElement->move(-1000,-1000);
    canvas->addShape(rectElement);

}

void MainWidget::onColorButtonClicked() {
    // 调用Canvas的draw方法
    canvas->onColorButtonClicked();
    // // 创建一个 FlowRectElement 并将其添加到 Canvas (QGraphicsScene) 中
    // FlowRectElement* rectElement = new FlowRectElement();
    // canvas->addShape(rectElement);
    //菱形
    // FlowDiamondElement* diamondElement = new FlowDiamondElement();
    // canvas->addShape(diamondElement);
    // FlowParaElement* paraElement = new FlowParaElement();
    // canvas->addShape(paraElement);
    // FlowCircleElement* circleElement = new FlowCircleElement();
    // canvas->addShape(circleElement);
    // FlowSubElement* subElement = new FlowSubElement();
    // canvas->addShape(subElement);
}

MainWidget::~MainWidget()
{
    delete ui;
}
