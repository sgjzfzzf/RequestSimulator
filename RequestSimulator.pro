QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fileitemwidget.cpp \
    getdialog.cpp \
    jsonparserdialog.cpp \
    keyvalueitemwidget.cpp \
    main.cpp \
    menudialog.cpp \
    parse.cpp \
    postdialog.cpp \
    specialitemwidget.cpp

HEADERS += \
    fileitemwidget.h \
    getdialog.h \
    jsonparserdialog.h \
    keyvalueitemwidget.h \
    menudialog.h \
    parse.h \
    postdialog.h \
    specialitemwidget.h

FORMS += \
    menudialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    logo.qrc
