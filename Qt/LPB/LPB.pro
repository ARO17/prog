QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LPB
TEMPLATE = app

CONFIG += mobility

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    TestPage1.cpp \
    HomePage.cpp

HEADERS += \
    MainWindow.h \
    TestPage1.h \
    HomePage.h
