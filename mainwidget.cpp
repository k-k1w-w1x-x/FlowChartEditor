#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "canvas.h"
#include "flowrectelement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QVector>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget), canvas(new Canvas(this))
{
    ui->setupUi(this);
    // 创建主布局管理器，将其设置为水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 左侧栏布局，用于放置按钮
    QVBoxLayout *leftLayout = new QVBoxLayout();

    // 设置窗口大小
    this->resize(800, 600);

    // 将左侧布局添加到主布局中
    mainLayout->addLayout(leftLayout);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色

    // 将 Canvas 添加到主布局的右侧部分
    mainLayout->addWidget(canvas);

    setLayout(mainLayout);  // 设置主布局为窗口的布局
    FlowRectElement* rectElement = new FlowRectElement();
    canvas->addShape(rectElement);
}

MainWidget::~MainWidget()
{
    delete ui;
}
