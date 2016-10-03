#ifndef OPENWIDGET_H
#define OPENWIDGET_H

#include <QDialog>

namespace Ui {
class openWidget;
}

class openWidget : public QDialog
{
    Q_OBJECT

public:
    explicit openWidget(QWidget *parent = 0);
    ~openWidget();

private:
    Ui::openWidget *ui;
public slots:
    void button1Slot();
    void button2Slot();
    void button3Slot();
};

#endif // OPENWIDGET_H
