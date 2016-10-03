#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>

class SingleGame : public Board
{
    Q_OBJECT
public:
    SingleGame();
public:
    int deep = 4;
public:
    void clicked(int clickedID, int row, int col);
    Step* computerGetBestMove();
    void getAllPossibleMove(QVector<Step *> &steps);
    void fakeMove(Step *&step);//假走
    void unfakeMove(Step *&step);//假走后移动回去
    int calcScore();
    int getMinScore(int deep, int currentMinScore);
    int getMaxScore(int deep, int currentMaxScore);
public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
