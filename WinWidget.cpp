#include "WinWidget.h"

WinWidget::WinWidget(QWidget *parent) : QWidget(parent)
{
}

WinWidget::WinWidget(int i)
{
    this->resize(480,320);
    this->color = i;
}

void WinWidget::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    if(this->color)
    {
        painter->setPen(Qt::red);
        this->setWindowTitle("红方胜出，黑方战败");
    }
    else
    {
        painter->setPen(Qt::black);
        this->setWindowTitle("黑方胜出，红方战败");
    }
    painter->setFont(QFont("华文行楷",100,50));
    QRect rect = QRect(30,10,400,300);
    painter->drawText(rect,"Win!",QTextOption(Qt::AlignCenter));
}
