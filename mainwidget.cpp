#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "canvas.h"
#include "flowrectelement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QVector>
#include <QLineEdit>
#include <QTimer>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget), canvas(new Canvas())
{
    ui->setupUi(this);
    // // 创建主布局管理器，将其设置为水平布局 以后这段通过ui实现
    // QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // // 左侧栏布局，用于放置按钮
    // QVBoxLayout *leftLayout = new QVBoxLayout();

    // 设置窗口大小
    this->resize(800, 600);

    // 将左侧布局添加到主布局中
    // ui->mainLayout->addLayout(leftLayout);

    // 设置 Canvas 的网格属性
    canvas->setGridSpacing(20);  // 设置网格间隔为 20 像素
    canvas->setGridColor(Qt::lightGray);  // 设置网格颜色为浅灰色

    QGraphicsView *view = new QGraphicsView(canvas);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 将 Canvas 添加到主布局的右侧部分
    ui->mainLayout->addWidget(view);

    QSize viewportSize = view->viewport()->size();
    canvas->setSceneRect(0, 0, viewportSize.width(), viewportSize.height());

    QGraphicsRectItem *test = new QGraphicsRectItem();
    test->setRect(20, 20, 100, 100);
    test->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    canvas->addItem(test);

    setLayout(ui->mainLayout);  // 设置主布局为窗口的布局
}

MainWidget::~MainWidget()
{
    delete ui;
}
