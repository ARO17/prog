#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();

private:
    // Buttons
    QPushButton *m_test1Button;
    QPushButton *m_test2Button;

    // Main layout
    QVBoxLayout *m_mainLayout;
};

#endif // HOMEPAGE_H
