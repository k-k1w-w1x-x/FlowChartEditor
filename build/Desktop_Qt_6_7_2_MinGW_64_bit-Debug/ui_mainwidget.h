/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *mainLayout;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *leftLayout;
    QPushButton *rect4_button;
    QPushButton *rect3_button;
    QPushButton *rhombus_button;
    QPushButton *rect2_button;
    QPushButton *parallelogram_button;
    QPushButton *rect_button;
    QPushButton *circle_button;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *menu_layout;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(800, 600);
        gridLayoutWidget = new QWidget(MainWidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(60, 50, 731, 541));
        mainLayout = new QGridLayout(gridLayoutWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(MainWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 50, 58, 541));
        leftLayout = new QVBoxLayout(verticalLayoutWidget);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(0, 0, 0, 0);
        rect4_button = new QPushButton(verticalLayoutWidget);
        rect4_button->setObjectName("rect4_button");

        leftLayout->addWidget(rect4_button);

        rect3_button = new QPushButton(verticalLayoutWidget);
        rect3_button->setObjectName("rect3_button");

        leftLayout->addWidget(rect3_button);

        rhombus_button = new QPushButton(verticalLayoutWidget);
        rhombus_button->setObjectName("rhombus_button");

        leftLayout->addWidget(rhombus_button);

        rect2_button = new QPushButton(verticalLayoutWidget);
        rect2_button->setObjectName("rect2_button");

        leftLayout->addWidget(rect2_button);

        parallelogram_button = new QPushButton(verticalLayoutWidget);
        parallelogram_button->setObjectName("parallelogram_button");

        leftLayout->addWidget(parallelogram_button);

        rect_button = new QPushButton(verticalLayoutWidget);
        rect_button->setObjectName("rect_button");

        leftLayout->addWidget(rect_button);

        circle_button = new QPushButton(verticalLayoutWidget);
        circle_button->setObjectName("circle_button");

        leftLayout->addWidget(circle_button);

        horizontalLayoutWidget = new QWidget(MainWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 10, 791, 41));
        menu_layout = new QHBoxLayout(horizontalLayoutWidget);
        menu_layout->setObjectName("menu_layout");
        menu_layout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        rect4_button->setText(QString());
        rect3_button->setText(QString());
        rhombus_button->setText(QString());
        rect2_button->setText(QString());
        parallelogram_button->setText(QString());
        rect_button->setText(QString());
        circle_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
