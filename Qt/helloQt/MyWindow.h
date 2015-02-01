#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow();

public slots:
    void changeWdith(int width);

signals:
    void maxWidth();

private:
    QSlider *m_slider;
    QLCDNumber *m_lcdNumber;

};

#endif // MYWINDOW_H
