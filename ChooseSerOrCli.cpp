// 用来选择是服务器还是客户端的对话框
#include "ChooseSerOrCli.h"
#include "ui_ChooseSerOrCli.h"

ChooseSerOrCli::ChooseSerOrCli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseSerOrCli)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint |
                         Qt::WindowMinimizeButtonHint |
                         Qt::WindowMaximizeButtonHint);    // 去掉对话框右上方关闭选项
    connect(ui->yseButton, SIGNAL(clicked(bool)), this, SLOT(yesSlot()));
    connect(ui->noButton, SIGNAL(clicked(bool)), this, SLOT(noSlot()));
}

ChooseSerOrCli::~ChooseSerOrCli()
{
    delete ui;
}

void ChooseSerOrCli::yesSlot()
{
    this->isServer = true;
    this->close();
}

void ChooseSerOrCli::noSlot()
{
    this->isServer = false;
    this->close();
}
