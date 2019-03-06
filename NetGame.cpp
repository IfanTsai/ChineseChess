#include "NetGame.h"
int isRedStart;//用来表示谁先执红棋

/*
 * 报文结构：
 * buf的第一个字节表示命令，0表示谁执红旗，1表示走棋，2表示聊天内容
 * 且0为第一次发送数据，同时在文本浏览器里显示连接成功...
*/
NetGame::NetGame()
{
    /* 界面处理 */
    this->resize(800, 660);
    this->setMinimumSize(800, 660);
    this->setMaximumSize(800, 660);
    this->aboutButton->setGeometry(630, 66, 110, 40);
    this->returnButton->setGeometry(630, 540, 110, 40);
    textBrowser = new QTextBrowser(this);
    textBrowser->setGeometry(580, 150, 200, 250);
    sendEdit = new QLineEdit(this);
    sendButton = new QPushButton(this);
    sendEdit->setGeometry(580, 420, 200, 30);
    sendButton->setGeometry(720, 470, 60, 30);
    sendButton->setText("发送");
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(chatSlot()));
    connect(sendEdit, SIGNAL(returnPressed()), this, SLOT(chatSlot()));
    textBrowser->append("等待连接...");
    this->backButton->hide();   // 不显示悔棋按钮
    /* 程序主逻辑 */
    server = nullptr;
    socket = nullptr;
    choose = new ChooseSerOrCli;
    choose->exec();
    if(choose->isServer)
    {
        ChooseIP *choose = new ChooseIP;
        choose->exec();
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        isRedStart = qrand() % 2;   // 随机产生先手 (红方先手)
        if (!isRedStart)
        {
            this->initStone(true);
        }
        server = new QTcpServer(this);      // 创建服务器socket
        server->listen(QHostAddress(choose->IPstr), 10101);   // 监听
        // 当有新的连接来的时候，触发信号，调用槽函数
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
    }
    else
    {
        InputIP *input = new InputIP;
        input->exec();
        socket = new QTcpSocket(this);   // 创建客户端socket
        socket->connectToHost(QHostAddress(input->IPstr), 10101);   // 连接
        // 当有数据发送过来时，触发信号，调用槽函数
        connect(socket, SIGNAL(readyRead()), this, SLOT(recvSlot()));
    }
}

void NetGame::clicked(int clickedID, int row, int col)
{
    // 选择了对方的棋子
    if(selectedID == -1 && isRedTurn != isRedSide)
    {
        return;
    }
    Board::clicked(clickedID, row, col);
    char buf[4];
    buf[0] = 1;
    buf[1] = clickedID;
    buf[2] = 9 - row;
    buf[3] = 8 - col;
    socket->write(buf, 4);
}

void NetGame::newConnectionSlot()
{
    if(socket)
    {
        return;
    }
    // 接收连接，等同于C语言里的accept，返回值类似于C语言里的文件描述符
    socket = server->nextPendingConnection();
    textBrowser->append("连接成功...");
    // 当有客户端数据发送过来时，触发信号，调用槽函数
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvSlot()));
    char buf[2];
    buf[0] = 0;
    buf[1] = isRedStart;
    socket->write(buf, 2);
}
// 接收数据并处理
void NetGame::recvSlot()
{
    QByteArray buf = socket->readAll();
    char cmd = buf[0];
    if(cmd == 0)
    {
        textBrowser->append("连接成功...");
        if(buf[1])
        {
            this->initStone(true);
        }
    }
    else if(cmd == 1)
    {
        int ID = buf[1];
        int row = buf[2];
        int col = buf[3];
        Board::clicked(ID, row, col);
    }
    else if(cmd == 2)
    {
        QString str = buf;
        QString chatContent = str.remove(0, 1);
        textBrowser->append(chatContent);
    }
}

void NetGame::chatSlot()
{
    QString chatStr = sendEdit->text();
    sendEdit->clear();
    if (chatStr.isEmpty())
    {
        return;
    }
    if (choose->isServer)
    {
        chatStr = "Server:" + chatStr;
    }
    else
    {
        chatStr = "Client:" + chatStr;
    }
    textBrowser->append(chatStr);
    chatStr = 2 + chatStr;
    //const char *buf = chatStr.toStdString().c_str();
    //socket->write(buf, chatStr.length());
    socket->write(chatStr.toUtf8().data());
}
