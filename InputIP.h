#ifndef INPUTIP_H
#define INPUTIP_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
class InputIP : public QDialog
{
    Q_OBJECT
public:
    InputIP();
public:
    QString IPstr;
    QHBoxLayout *layout;
    QLineEdit *edit;
    QPushButton *button;
public slots:
    void chooseIP();
};

#endif // INPUTIP_H
