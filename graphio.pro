#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T10:38:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    coregraph.cpp \
    corevertex.cpp \
    grapharrowextend.cpp \
    graphpoint.cpp \
    graphscene.cpp \
    adjmat.cpp \
    coreedge.cpp \
    edglist.cpp \
    incmat.cpp \
    structadj.cpp \
    wmat.cpp \
    enterdialog.cpp \
    newadjmat.cpp \
    newincmat.cpp \
    newwmat.cpp \
    newedglist.cpp \
    newstructadj.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    coreedge.h \
    coregraph.h \
    corevertex.h \
    grapharrowextend.h \
    graphpoint.h \
    graphscene.h \
    adjmat.h \
    edglist.h \
    incmat.h \
    structadj.h \
    wmat.h \
    enterdialog.h \
    newadjmat.h \
    newincmat.h \
    newwmat.h \
    newedglist.h \
    newstructadj.h \
    helpdialog.h

RESOURCES += \
    graphio.qrc
