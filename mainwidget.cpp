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
#include <QSvgGenerator>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , canvas(new Canvas(this)), ui(new Ui::MainWidget)
{
    canvas->setSceneRect(0, 0, 1600, 1600);
    ui->setupUi(this);

    // 设置最小大小
    this->setMinimumSize(600, 500);
    // 设置窗口大小
    this->resize(1000, 800);

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

void MainWidget::init_menu_layout() {
    //填充color按钮
    ui->color_button->setFixedSize(40,40);
    connect(ui->color_button,&QPushButton::clicked,this,&MainWidget::onColorButtonClicked);
    QIcon icon1(":/menu/border_color.png");
    ui->color_button->setIcon(icon1);
    ui->color_button->setIconSize(QSize(25, 25));

    //边框color按钮
    ui->border_color_button->setFixedSize(40,40);
    connect(ui->border_color_button,&QPushButton::clicked,this,&MainWidget::onBorderColorButtonClicked);
    // 连接边框颜色改变
    // connect(ui->border_color_button,&QPushButton::clicked,this,&MainWidget::onColorButtonClicked);
    QIcon icon2(":/menu/color_change.png");
    ui->border_color_button->setIcon(icon2);
    ui->border_color_button->setIconSize(QSize(25, 25));

    ui->searchBox->setFixedSize(400, 35);
    ui->searchButton->setFixedSize(40, 40);
    ui->searchButton->setIcon(QIcon(":/menu/search.png"));
    connect(ui->searchButton, &QPushButton::clicked, [=](){

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
    exportAction = new QAction(QIcon(":/menu/export.png"),"Export", this);
    openAction = new QAction(QIcon(":/menu/open.png"),"Open", this);
    saveAction = new QAction(QIcon(":/menu/save.png"),"Save", this);
    exitAction = new QAction(QIcon(":/menu/exit.png"),"Exit", this);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(exportAction);
    connect(saveAction, &QAction::triggered, [=](){
        // QString filePath = QFileDialog::getSaveFileName(this, "保存", "", "All Files (*)");
        // if (!filePath.isEmpty()) {
        //     qDebug() << filePath;
        //     onExportButtonClicked();
        // }
        onExportButtonClicked();
    });
    connect(openAction, &QAction::triggered, [=](){
        // QString filePath = QFileDialog::getOpenFileName(this, "选择打开文件", "", "All Files (*)");
        // if (!filePath.isEmpty()) {
        //     qDebug() << filePath;
        //     onImportButtonClicked();
        // }
        onImportButtonClicked();
    });
    connect(exportAction, &QAction::triggered, [=](){
        QString filePath = QFileDialog::getSaveFileName(nullptr, "选择保存位置", "", "SVG Files (*.svg);;All Files (*)");
        if (!filePath.isEmpty()) {
            if (!filePath.endsWith(".svg", Qt::CaseInsensitive)) {
                filePath += ".svg";  // 确保文件路径有扩展名
            }

            // 创建 QSvgGenerator 对象
            QSvgGenerator svgGen;
            svgGen.setFileName(filePath);
            svgGen.setSize(canvas->size());  // 设置 SVG 的大小
            svgGen.setViewBox(canvas->viewport()->rect());  // 设置视图框
            svgGen.setTitle("GraphicsScene SVG Export");
            svgGen.setDescription("An SVG drawing created by exporting a QGraphicsScene.");

            // 使用 QPainter 将 QGraphicsScene 的内容绘制到 SVG 文件中
            QPainter painter;
            painter.begin(&svgGen);
            canvas->render(&painter);  // 将视图渲染到 QPainter
            painter.end();  // 完成绘制
        }
    });

    //横线分隔
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    //退出增加保存操作
    connect(exitAction, &QAction::triggered, [=](){
        //保存操作
    });

    // editmenu创建菜单项
    copyAction = new QAction(QIcon(":/menu/copy.png"),"Copy", this);
    pasteAction = new QAction(QIcon(":/menu/paste.png"),"Paste", this);
    backgroundAction = new QAction(QIcon(":/menu/background.png"),"Background",this);
    back_returnAction = new QAction(QIcon(":/menu/background_return.png"),"Grid Background",this);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(backgroundAction);
    editMenu->addAction(back_returnAction);

    connect(copyAction, &QAction::triggered, canvas, &Canvas::onCopy);
    connect(pasteAction, &QAction::triggered, canvas, &Canvas::onPaste);
    connect(backgroundAction, &QAction::triggered, [=](){
        QString filePath = QFileDialog::getOpenFileName(this,
            "选择背景图片",
            "",
            "Image Files (*.png *.jpg *.bmp *.jpeg)");
        if (!filePath.isEmpty()) {
            // qDebug() << filePath;
            canvas->background_path = filePath;
            canvas->background_set = true;
            canvas->update();//update会调用drawbackground方法
        }
    });
    connect(back_returnAction, &QAction::triggered, [=](){
        canvas->setBackgroundBrush(QBrush());
        canvas->background_set = false;
        canvas->update();
    });
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
    connect(ui->rect_button, &QPushButton::pressed, [=]() {
        ui->rect_button->setStyleSheet("background-color: lightgrey;");
    });
    connect(ui->rect_button, &QPushButton::pressed, [=]() {
        ui->rect_button->setStyleSheet("background-color: white;");
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

    //圆角矩形
    ui->roundrect_button->setFixedSize(60,50);
    QIcon icon8(":/type/round_rect.png");
    ui->roundrect_button->setIcon(icon8);
    ui->roundrect_button->setIconSize(QSize(32, 32));
    connect(ui->roundrect_button, &QPushButton::clicked, [=](){
        FlowRadiusElement* radiusElement = new FlowRadiusElement();
        canvas->addShape(radiusElement);
    });

    //arrow按钮
    ui->arrow_button->setFixedSize(60,50);
    QIcon icon9(":/type/arrow.png");
    ui->arrow_button->setIcon(icon9);
    ui->arrow_button->setIconSize(QSize(32, 32));
    connect(ui->arrow_button, &QPushButton::clicked, [=](){
        if (!arrow_flag) {
            ui->arrow_button->setStyleSheet("background-color: lightgrey;");
            arrow_flag = !arrow_flag;
        }
        else {
            ui->arrow_button->setStyleSheet("background-color: white;");
            arrow_flag = !arrow_flag;
        }

        canvas->isArrowing=!canvas->isArrowing;
        if(!canvas->isArrowing && !canvas->arrows.empty() && canvas->arrows.last()->endDot->scenePos().x() == 0 && canvas->arrows.last()->endDot->scenePos().y() == 0){
            //需要删除操作
            qDebug()<<"删除";
            FlowArrowElement *temp = canvas->arrows.last();
            canvas->arrows.removeLast();
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
            for(FlowArrowElement *dragSelectedArrow : canvas->dragSelectedArrows){
                if(dragSelectedArrow->startElementDot){
                    dragSelectedArrow->startElementDot->setVisible(false);
                }
                dragSelectedArrow->startDot->setVisible(false);
                if(dragSelectedArrow->endElementDot){
                    dragSelectedArrow->endElementDot->setVisible(false);
                }
                dragSelectedArrow->endDot->setVisible(false);
            }
        }
    });
}

void MainWidget::onColorButtonClicked() {
    // 调用Canvas的draw方法
    canvas->onColorButtonClicked();
}
void MainWidget::onBorderColorButtonClicked(){
    canvas->onBorderColorButtonClicked();
}

// void MainWidget::onArrowButtonClicked() {
//     if (arrow_flag) {
//         emit arrow_first_click();
//         arrow_flag = !arrow_flag;
//     }
//     else {
//         emit arrow_second_click();
//         arrow_flag = !arrow_flag;
//     }
// }
void MainWidget::onExportButtonClicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Export Elements", "", "Data Files (*.dat)");
    if (!filename.isEmpty()) {
        canvas->exportElements(filename); // 调用 Canvas 的导出方法
    }
}

void MainWidget::onImportButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Import Elements", "", "Data Files (*.dat)");
    if (!filename.isEmpty()) {
        canvas->importElements(filename); // 调用 Canvas 的 importElements 方法
    }
}
MainWidget::~MainWidget()
{
    delete ui;
}
