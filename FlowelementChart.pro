QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ElementSerializer.cpp \
    canvas.cpp \
    flowarrowelement.cpp \
    flowcircleelement.cpp \
    flowelement.cpp \
    flowdiamondelement.cpp \
    flowdocuelement.cpp \
    flowparaelement.cpp \
    flowplaygroundelement.cpp \
    flowradiuselement.cpp \
    flowrectelement.cpp \
    flowsubelement.cpp \
    graphicstextitem.cpp \
    keyeventfilter.cpp \
    main.cpp \
    mainwidget.cpp \
    zindexmanager.cpp

HEADERS += \
    ElementSerializer.h \
    canvas.h \
    flowarrowelement.h \
    flowcircleelement.h \
    flowdiamondelement.h \
    flowdocuelement.h \
    flowelement.h \
    graphicstextitem.h \
    keyeventFilter.h \
    mainwidget.h \
    flowparaelement.h \
    flowplaygroundelement.h \
    flowradiuselement.h \
    flowrectelement.h \
    flowsubelement.h \
    graphicstextitem.h \
    zindexmanager.h
FORMS += \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    type.qrc
