#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRect>
class WinWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WinWidget(QWidget *parent = 0);
    WinWidget(int i);
private:
    int color;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // WINWIDGET_H
