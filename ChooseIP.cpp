// 用来服务器选择IP的对话框
#include "ChooseIP.h"

ChooseIP::ChooseIP()
{
    this->setWindowTitle("请选择一个IP作为服务器的IP");
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    box = new QComboBox(this);
    button = new QPushButton("确定");
    layout = new QHBoxLayout(this);
    layout->addWidget(box);
    layout->addWidget(button);
    QList<QHostAddress> addrList = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrList) {
        QString addrStr = QHostAddress(addr.toIPv4Address()).toString();
        if(addrStr == "0.0.0.0" || addrStr == "127.0.0.1")
            continue;
        box->addItem(addrStr);
    }
    connect(button, SIGNAL(clicked(bool)), this, SLOT(chooseAddr()));
}

void ChooseIP::chooseAddr()
{
    IPstr = box->currentText();
    this->close();
}
