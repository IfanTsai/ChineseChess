#ifndef CHOOSEIP_H
#define CHOOSEIP_H
#include <QDialog>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QNetworkInterface>
#include <QString>
class ChooseIP : public QDialog
{
    Q_OBJECT
public:
    ChooseIP();
public:
    QString IPstr;
    QHBoxLayout *layout;
    QComboBox *box;
    QPushButton *button;
public slots:
    void chooseAddr();
};

#endif // CHOOSEIP_H
