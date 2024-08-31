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

    // 设置窗口大小
    this->resize(800, 600);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色

    // 将 Canvas 添加到主布局的右侧部分
    ui->mainLayout->addWidget(canvas);

    // 创建一个 FlowRectElement 并将其添加到 Canvas (QGraphicsScene) 中
    FlowRectElement* rectElement = new FlowRectElement();
    canvas->addShape(rectElement);
    //菱形
    FlowDiamondElement* diamondElement = new FlowDiamondElement();
    canvas->addShape(diamondElement);
    FlowParaElement* paraElement = new FlowParaElement();
    canvas->addShape(paraElement);
    FlowCircleElement* circleElement = new FlowCircleElement();
    canvas->addShape(circleElement);
    FlowSubElement* subElement = new FlowSubElement();
    canvas->addShape(subElement);
}

MainWidget::~MainWidget()
{
    delete ui;
}
