#include <QApplication>
#include "MainWindow.h"
#include "DisplayCodeWindow.h"
#include <QMessageBox>

MainWindow::MainWindow() : QWidget()
{
    // CLass definition line edit
    m_className = new QLineEdit;
    m_parentClassName = new QLineEdit;

    // Options
    m_headerProtection = new QCheckBox("Protect the &header against multiples inclusions");
    m_defaultConstructor = new QCheckBox("Generate a default &constructor");
    m_generateDestructor = new QCheckBox("Generate a &destructor");

    // Comments
    m_author = new QLineEdit;
    m_creationDate = new QDateEdit;
    m_classDesc = new QTextEdit;

    // Buttons
    m_generateButton = new QPushButton("Generate");
    m_quitButton = new QPushButton("Quit");

    // Class definition form layout
    m_classDefFormLayout = new QFormLayout;
    m_classDefFormLayout->addRow("&Name:", m_className);
    m_classDefFormLayout->addRow("&Parent Class:", m_parentClassName);

    // Options vertical box layout
    m_optionsVBox = new QVBoxLayout;
    m_optionsVBox->addWidget(m_headerProtection);
    m_optionsVBox->addWidget(m_defaultConstructor);
    m_optionsVBox->addWidget(m_generateDestructor);

    // Comments form layout
    m_commentsFormLayout = new QFormLayout;
    m_commentsFormLayout->addRow("&Author:", m_author);
    m_commentsFormLayout->addRow("Da&te of creation:", m_creationDate);
    m_commentsFormLayout->addRow("D&escription:", m_classDesc);

    // Class definition groupbox
    m_classDefGroupBox = new QGroupBox("Class definition");
    m_classDefGroupBox->setLayout(m_classDefFormLayout);

    // Options groupbox
    m_optionsGroupBox = new QGroupBox("Options");
    m_optionsGroupBox->setLayout(m_optionsVBox);

    // Comments groupbox
    m_commentsGroupBox = new QGroupBox("Add comments");
    m_commentsGroupBox->setLayout(m_commentsFormLayout);
    m_commentsGroupBox->setCheckable(true);

    // Buttons Grid layout
    m_buttonsGridLayout = new QGridLayout;
    m_buttonsGridLayout->addWidget(m_generateButton, 0, 3);
    m_buttonsGridLayout->addWidget(m_quitButton, 0, 4);

    // Main vertical layout
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_classDefGroupBox);
    m_mainLayout->addWidget(m_optionsGroupBox);
    m_mainLayout->addWidget(m_commentsGroupBox);
    m_mainLayout->addLayout(m_buttonsGridLayout);

    // Assign main layout to MainWindow
    this->setLayout(m_mainLayout);

    QObject::connect(m_quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_generateButton, SIGNAL(clicked()), SLOT(generateCode()));
}

void MainWindow::generateCode()
{
    QString code;
    code = "QString";

    if (m_className->text().isEmpty()) {

        QMessageBox::critical(this, "Required field", "The name of class must be fill");

    } else {

        if (m_commentsGroupBox->isChecked()) {
            code = "/*\nAuthor: " + m_author->text() + "\nDate of creation: " + m_creationDate->date().toString() + "\n*/\n\n";
        }

        code += "class " + m_className->text() + "\n{\n\tpublic:\n\t\t" + m_className->text() + "();\n";

    m_codeWindow = new DisplayCodeWindow(code, this);
    m_codeWindow->exec();

    }
}
