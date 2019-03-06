#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QTextOption>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QVector>
#include <QFontDatabase>
#include <cmath>
#include "Stone.h"
#include "WinWidget.h"
#include "Step.h"
#include "openWidget.h"
class Board : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *);        // 绘图事件
    void mouseReleaseEvent(QMouseEvent *); // 鼠标释放事件

public:
    QPushButton *backButton;    // 悔棋按钮
    QPushButton *aboutButton;   // 关于按钮
    QPushButton *returnButton;  // 返回按钮
    int r;   // 棋子半径
    Stone stone[32];
    int selectedID;  // 用来标记某个棋子被选择了
    bool isRedTurn;  // 标记轮到哪一方
    QVector<Step *> backSteps;   // 用来保存悔棋步骤
    bool isRedSide;  // 用来表示是否红棋在下方

public:
    Board(QWidget *parent = nullptr);
    ~Board();
    QPoint translate(int ID);            // 获取棋子的坐标
    QPoint translate(int row, int col);  // 上面函数的重载
    void drawStone(QPainter *&painter, int ID);       // 画棋子
    bool getRowCol(QPoint point, int &row, int &col); // 获取鼠标点击的坐标，并判断是否点击在棋盘内
    int  getStoneID(int row, int col);
    void moveStone(int selectedID, int row, int col);
    void moveStone(int selectedID, int killID, int row, int col);
    void killStone(int killID);
    void reviveStone(int killID);    // 复活棋子
    bool isLineNull(int moveID, int row, int col); // 用来判断车和炮移动时之间有无棋子
    void initStone(bool isReverse);  // 初始化棋子

    bool canMove(int moveID, int row, int col, int killID);
    bool canMoveJIANG(int moveID, int row, int col);
    bool canMoveSI(int moveID, int row, int col);
    bool canMoveBING(int moveID, int row, int col);
    bool canMoveCHE(int moveID, int row, int col);
    bool canMoveXIANG(int moveID, int row, int col);
    bool canMoveMA(int moveID, int row, int col);
    bool canMovePAO(int moveID, int row, int col, int killID);

    void paintWin();   // 胜利窗口
    virtual void clicked(int clickedID, int row, int col);
    void saveStep(int moveID, int killID, int rowTo,
                  int colTo, QVector<Step*> &steps);

public slots:
    void aboutSlot();
    void backSlot();
    void returnSlot();
};

#endif // BOARD_H
