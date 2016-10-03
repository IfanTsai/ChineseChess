#ifndef NETGAME_H
#define NETGAME_H
#include "Board.h"
#include "ChooseSerOrCli.h"
#include "ChooseIP.h"
#include "InputIP.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <cmath>
#include <QTime>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
class NetGame : public Board
{
    Q_OBJECT
public:
    NetGame();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    ChooseSerOrCli *choose;
    QTextBrowser *textBrowser;
    QLineEdit *sendEdit;
    QPushButton *sendButton;
public:
    void clicked(int clickedID, int row, int col);

public slots:
    void newConnectionSlot();
    void recvSlot();
    void chatSlot();
};

#endif // NETGAME_H
