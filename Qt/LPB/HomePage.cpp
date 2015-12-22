#include "HomePage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    // Buttons
    m_test1Button = new QPushButton;
    m_test1Button->setText("Test 1");
    m_test2Button = new QPushButton;
    m_test2Button->setText("Test 2");

    // Main layout
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_test1Button);
    m_mainLayout->addWidget(m_test2Button);

    // Assign main layout to MainWindow
    this->setLayout(m_mainLayout);
}

HomePage::~HomePage()
{
    delete m_test1Button;
    delete m_test2Button;
    delete m_mainLayout;
}

