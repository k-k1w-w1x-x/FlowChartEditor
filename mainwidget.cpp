#include "mainwidget.h"
#include "canvas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), canvas(new Canvas(this))
{
    // 创建主布局管理器，将其设置为水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 左侧栏布局，用于放置按钮
    QVBoxLayout *leftLayout = new QVBoxLayout();

    // 创建按钮并设置大小为 100x40 像素
    QPushButton *button = new QPushButton("Rectangle", this);
    button->setFixedSize(100, 40);
    button->setIcon(QIcon(":/type/rect.png"));
    // connect(button, &QPushButton::clicked, this, &MainWidget::createRectangle);
    leftLayout->addWidget(button);

    this->resize(800, 600);


    // 将左侧布局添加到主布局中
    mainLayout->addLayout(leftLayout);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色

    // 将 Canvas 添加到主布局的右侧部分
    mainLayout->addWidget(canvas);

    setLayout(mainLayout);  // 设置主布局为窗口的布局

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

}

MainWidget::~MainWidget() {
    // 析构函数中清理资源（如果有）
}


