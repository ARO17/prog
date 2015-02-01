TEMPLATE = app
TARGET = helloQt

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    MyWindow.cpp \
    Main.cpp

HEADERS += \
    MyWindow.h
