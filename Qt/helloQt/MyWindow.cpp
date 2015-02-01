#include "MyWindow.h"

MyWindow::MyWindow()
{
    setFixedSize(200, 100);

    m_lcdNumber = new QLCDNumber(3, this);
    m_lcdNumber->setGeometry(10, 20, 60, 30);
    m_lcdNumber->setSegmentStyle(QLCDNumber::Flat);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(200, 600);
    m_slider->setGeometry(10, 60, 150, 20);

    // Slider increment LCDNUmber
    QObject::connect(m_slider, SIGNAL(valueChanged(int)), m_lcdNumber, SLOT(display(int)));
    // Slider modify width of this window
    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeWdith(int)));
    // This window call Application quit
    QObject::connect(this, SIGNAL(maxWidth()), qApp, SLOT(quit()));
}

// SLOT
void MyWindow::changeWdith(int width)
{
    setFixedSize(width, height());

    if (width == 600) {
        emit maxWidth();
    }
}
