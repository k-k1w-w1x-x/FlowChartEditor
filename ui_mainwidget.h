/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *all;
    QVBoxLayout *leftLayout;
    QPushButton *rect4_button;
    QPushButton *rect3_button;
    QPushButton *rhombus_button;
    QPushButton *rect2_button;
    QPushButton *parallelogram_button;
    QPushButton *rect_button;
    QPushButton *circle_button;
    QPushButton *roundrect_button;
    QPushButton *arrow_button;
    QGridLayout *mainLayout;
    QWidget *menuWidget;
    QGridLayout *menu_layout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *color_button;
    QPushButton *border_color_button;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchBox;
    QPushButton *searchButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(755, 626);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setObjectName("verticalLayout");
        all = new QGridLayout();
        all->setObjectName("all");
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName("leftLayout");
        rect4_button = new QPushButton(MainWidget);
        rect4_button->setObjectName("rect4_button");

        leftLayout->addWidget(rect4_button);

        rect3_button = new QPushButton(MainWidget);
        rect3_button->setObjectName("rect3_button");

        leftLayout->addWidget(rect3_button);

        rhombus_button = new QPushButton(MainWidget);
        rhombus_button->setObjectName("rhombus_button");

        leftLayout->addWidget(rhombus_button);

        rect2_button = new QPushButton(MainWidget);
        rect2_button->setObjectName("rect2_button");

        leftLayout->addWidget(rect2_button);

        parallelogram_button = new QPushButton(MainWidget);
        parallelogram_button->setObjectName("parallelogram_button");

        leftLayout->addWidget(parallelogram_button);

        rect_button = new QPushButton(MainWidget);
        rect_button->setObjectName("rect_button");

        leftLayout->addWidget(rect_button);

        circle_button = new QPushButton(MainWidget);
        circle_button->setObjectName("circle_button");

        leftLayout->addWidget(circle_button);

        roundrect_button = new QPushButton(MainWidget);
        roundrect_button->setObjectName("roundrect_button");

        leftLayout->addWidget(roundrect_button);

        arrow_button = new QPushButton(MainWidget);
        arrow_button->setObjectName("arrow_button");

        leftLayout->addWidget(arrow_button);


        all->addLayout(leftLayout, 2, 0, 1, 1);

        mainLayout = new QGridLayout();
        mainLayout->setObjectName("mainLayout");

        all->addLayout(mainLayout, 2, 1, 1, 1);

        menuWidget = new QWidget(MainWidget);
        menuWidget->setObjectName("menuWidget");
        menu_layout = new QGridLayout(menuWidget);
        menu_layout->setObjectName("menu_layout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        color_button = new QPushButton(menuWidget);
        color_button->setObjectName("color_button");

        horizontalLayout_2->addWidget(color_button);

        border_color_button = new QPushButton(menuWidget);
        border_color_button->setObjectName("border_color_button");

        horizontalLayout_2->addWidget(border_color_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        menu_layout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchBox = new QLineEdit(menuWidget);
        searchBox->setObjectName("searchBox");

        horizontalLayout->addWidget(searchBox, 0, Qt::AlignmentFlag::AlignLeft);

        searchButton = new QPushButton(menuWidget);
        searchButton->setObjectName("searchButton");

        horizontalLayout->addWidget(searchButton, 0, Qt::AlignmentFlag::AlignLeft);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        menu_layout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        menu_layout->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        all->addWidget(menuWidget, 0, 0, 1, 2);


        verticalLayout->addLayout(all);


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
        roundrect_button->setText(QString());
        arrow_button->setText(QString());
        color_button->setText(QString());
        border_color_button->setText(QString());
        searchButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
