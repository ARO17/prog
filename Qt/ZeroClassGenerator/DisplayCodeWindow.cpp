#include "DisplayCodeWindow.h"

DisplayCodeWindow::DisplayCodeWindow(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    m_textEdit =  new QTextEdit;
    m_textEdit->setText(code);

    m_button = new QPushButton("Close");

    m_vbox = new QVBoxLayout;
    m_vbox->addWidget(m_textEdit);
    m_vbox->addWidget(m_button);

    this->setLayout(m_vbox);

    QObject::connect(m_button, SIGNAL(clicked()), this, SLOT(close()));
}
