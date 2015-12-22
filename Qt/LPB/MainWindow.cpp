#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    // Applications pages
    m_homePage = new HomePage;
    m_testPage1 = new TestPage1;

    QObject::connect();

    // Stack of all pages
    m_stackedWidget = new QStackedWidget;
    m_stackedWidget->addWidget(m_homePage);
    m_stackedWidget->addWidget(m_testPage1);

    // Assign main layout to MainWindow
    this->setCentralWidget(m_stackedWidget);
}

MainWindow::~MainWindow()
{
    delete m_stackedWidget;
    delete m_testPage1;
    delete m_homePage;
}
