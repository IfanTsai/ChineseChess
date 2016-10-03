#ifndef CHOOSESERORCLI_H
#define CHOOSESERORCLI_H

#include <QDialog>

namespace Ui {
class ChooseSerOrCli;
}

class ChooseSerOrCli : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseSerOrCli(QWidget *parent = 0);
    ~ChooseSerOrCli();

private:
    Ui::ChooseSerOrCli *ui;

public:
    bool isServer;
public slots:
    void yesSlot();
    void noSlot();
};

#endif // CHOOSESERORCLI_H
