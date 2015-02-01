#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QDateEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include "DisplayCodeWindow.h"

class MainWindow : public QWidget
{

    Q_OBJECT

public:

    MainWindow();

public slots:

    void generateCode();

private:

    // Class definition
    QLineEdit *m_className;
    QLineEdit *m_parentClassName;

    // Options
    QCheckBox *m_headerProtection;
    QCheckBox *m_defaultConstructor;
    QCheckBox *m_generateDestructor;

    // Comments
    QLineEdit *m_author;
    QDateEdit *m_creationDate;
    QTextEdit *m_classDesc;

    // Buttons
    QPushButton *m_generateButton;
    QPushButton *m_quitButton;

    // Class definition form layout
    QFormLayout *m_classDefFormLayout;

    // Options vertical box layout
    QVBoxLayout *m_optionsVBox;

    // Comments form layout
    QFormLayout *m_commentsFormLayout;

    // Class definition groupbox
    QGroupBox *m_classDefGroupBox;

    // Options groupbox
    QGroupBox *m_optionsGroupBox;

    // Comments groupbox
    QGroupBox *m_commentsGroupBox;

    // Buttons grid layout
    QGridLayout *m_buttonsGridLayout;

    // Main vertical layout
    QVBoxLayout *m_mainLayout;

    // Display code window
    DisplayCodeWindow *m_codeWindow;

};

#endif // MAINWINDOW_H
