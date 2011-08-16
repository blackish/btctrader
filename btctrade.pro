#-------------------------------------------------
#
# Project created by QtCreator 2011-06-06T14:22:21
#
#-------------------------------------------------

QT       += core gui network script qca

TARGET = btctrade
TEMPLATE = app


SOURCES += main.cpp\
        btctrader.cpp \
    graphicwidget.cpp \
    orderswidget.cpp \
    orderitem.cpp \
    myorderstablewidget.cpp \
    passworddialog.cpp \
    preferencedialog.cpp \
    tradehistorywidget.cpp \
    historydialog.cpp \
    cancelordermenu.cpp

HEADERS  += btctrader.h \
    graphicwidget.h \
    orderswidget.h \
    orderitem.h \
    myorderstablewidget.h \
    passworddialog.h \
    preferencedialog.h \
    tradehistorywidget.h \
    historydialog.h \
    cancelordermenu.h

FORMS    += btctrader.ui \
    passworddialog.ui \
    preferencedialog.ui \
    historydialog.ui

LIBS += -lqca
