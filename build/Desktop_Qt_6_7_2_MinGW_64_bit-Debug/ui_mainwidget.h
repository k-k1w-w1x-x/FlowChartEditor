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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *mainLayout;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *topLayout;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *leftLayout;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(800, 600);
        gridLayoutWidget = new QWidget(MainWidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 40, 741, 551));
        mainLayout = new QGridLayout(gridLayoutWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(MainWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 791, 41));
        topLayout = new QHBoxLayout(horizontalLayoutWidget);
        topLayout->setObjectName("topLayout");
        topLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(MainWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 40, 51, 551));
        leftLayout = new QVBoxLayout(verticalLayoutWidget);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
