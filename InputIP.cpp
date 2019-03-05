// 用来客户端输入IP的对话框
#include "InputIP.h"

InputIP::InputIP()
{
    this->setWindowTitle("请输入一个IP用来连接服务器");
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    edit = new QLineEdit(this);
    button = new QPushButton("确定");
    layout = new QHBoxLayout(this);
    layout->addWidget(edit);
    layout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(chooseIP()));
}
void InputIP::chooseIP()
{
    IPstr = edit->text();
    this->close();
}
