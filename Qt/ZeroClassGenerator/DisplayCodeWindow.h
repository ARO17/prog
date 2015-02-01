#ifndef DISPLAYCODEWINDOW_H
#define DISPLAYCODEWINDOW_H

#include <QDialog>
#include <QString>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class DisplayCodeWindow : public QDialog
{

public :

    DisplayCodeWindow(QString &code, QWidget *parent);

private :

    QTextEdit *m_textEdit;
    QPushButton *m_button;

    QVBoxLayout *m_vbox;

};

#endif // DISPLAYCODEWINDOW_H
