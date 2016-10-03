#include "openWidget.h"
#include "ui_openWidget.h"
#include "Board.h"
#include "SingleGame.h"
#include "NetGame.h"
openWidget::openWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("中国象棋");
    ui->button2->setFocusPolicy(Qt::TabFocus);
    this->setMinimumSize(409, 583);
    this->setMaximumSize(409, 583);
    connect(ui->button1,SIGNAL(clicked(bool)),this,SLOT(button1Slot()));
    connect(ui->button2,SIGNAL(clicked(bool)),this,SLOT(button2Slot()));
    connect(ui->button3,SIGNAL(clicked(bool)),this,SLOT(button3Slot()));
}

openWidget::~openWidget()
{
    delete ui;
}

void openWidget::button1Slot()
{
    this->close();
    Board *board = new Board;
    board->show();
}

void openWidget::button2Slot()
{
    this->close();
    SingleGame *singleGame = new SingleGame;
    singleGame->show();
}

void openWidget::button3Slot()
{
    this->close();
    NetGame *netGame = new NetGame;
    netGame->show();
}
