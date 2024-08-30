#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "canvas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

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

}

MainWidget::~MainWidget()
{
    delete ui;
}
