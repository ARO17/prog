#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "HomePage.h"
#include "TestPage1.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

private:
    // Applications pages
    HomePage *m_homePage;
    TestPage1 *m_testPage1;

    // Stack of all pages
    QStackedWidget *m_stackedWidget;

    // Main layout
    QVBoxLayout *m_mainLayout;
};

#endif // MAINWINDOW_H
