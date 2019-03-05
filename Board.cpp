#include "Board.h"

Board::Board(QWidget *parent)
    : QWidget(parent)
{
    this->resize(720, 660);
    this->setMinimumSize(720, 660);
    this->setMaximumSize(720, 660);
    initStone(false);
    aboutButton = new QPushButton(this);
    aboutButton->setText("关于");
    aboutButton->setGeometry(600, 66, 80, 40);
    backButton = new QPushButton(this);
    backButton->setText("悔棋");
    backButton->setGeometry(600, 310, 80, 40);
    returnButton = new QPushButton(this);
    returnButton->setText("返回");
    returnButton->setGeometry(600, 554, 80, 40);
    connect(aboutButton, SIGNAL(clicked(bool)), this, SLOT(aboutSlot()));
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(backSlot()));
    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(returnSlot()));
    selectedID = -1;
    isRedTurn = true;

    // 按钮样式
    setStyleSheet("QPushButton"
                            "{"
                            "color: white;"
                            "background-color: #ab88ed;"
                            "border:none;"
                            "padding: 3px;"
                            "font-family: 'Verdana';"
                            "font-size: 15px;"
                            "text-align: center;"
                            "border-radius:8px;"
                            "}");
    QString style =  "QPushButton:hover"
                          "{"
                          "font-size: 20px;"
                          "color: #6900de;"
                          "background-color: #8d59dd;"
                          "}";
    aboutButton->setStyleSheet(style);
    backButton->setStyleSheet(style);
    returnButton->setStyleSheet(style);

    // 设置背景图
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    QBrush brush(QPixmap(":/new/prefix1/chess/bg.jpeg").scaled(this->size(),
                                                               Qt::IgnoreAspectRatio,
                                                               Qt::SmoothTransformation));
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
}
Board::~Board()
{
}
// 初始化棋子
void Board::initStone(bool isReverse)
{
    for (int i = 0; i < 32; i++)
    {
        this->stone[i].init(i);
    }
    if (isReverse)
    {
        for (int i = 0;i<32;i++)
        {
            this->stone[i].row = 9 - stone[i].row;
            this->stone[i].col = 8 - stone[i].col;
        }
        update();
    }
    isRedSide = !isReverse;
}

void Board::paintEvent(QPaintEvent *)
{
    // paint board
    QPainter *painter = new QPainter(this);
    painter->setBrush(QBrush("brown"));
    painter->setPen(QColor("red"));
    // 直径
    int d = 60;
    this->r = d / 2;
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
             painter->drawRect(i * d, j * d, d, d);
        }
    }
    painter->drawRect(d, 5 * d, 8 * d, d);
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 6; j <= 9; j++)
        {
             painter->drawRect(i * d, j * d, d, d);
        }
    }
    painter->drawLine(QPoint(4 * d, d), QPoint(6 * d,3 * d));
    painter->drawLine(QPoint(6 * d, d), QPoint(4 * d, 3 * d));
    painter->drawLine(QPoint(4 * d, 8 * d), QPoint(6 * d, 10 * d));
    painter->drawLine(QPoint(6 * d, 8 * d), QPoint(4 * d, 10 * d));

    QRect rect = QRect(d, 5 * d, 8 * d, d);

    painter->setFont(QFont("华文行楷", 40, 50));
    painter->setPen(Qt::white);
    painter->drawText(rect,tr(" 楚河    汉界"), QTextOption(Qt::AlignCenter));
    if (stone[4].isDead)   // 胜负判断
    {
        this->close();
        WinWidget *win = new WinWidget(1);
        win->show();
    }
    else if (stone[20].isDead) // 胜负判断
    {
        this->close();
        WinWidget *win = new WinWidget(0);
        win->show();
    }
    // paint stone
    for (int i = 0; i < 32; i++)
    {
        this->drawStone(painter, i);
    }
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
    {
        return;
    }
    QPoint point = ev->pos();
    int row, col;
    if (getRowCol(point, row ,col) == false)   // click on the outside of the board
    {
        return;
    }
    //qDebug()<<"row,col = "<<row<<col;
    int clickedID = getStoneID(row, col);
    clicked(clickedID, row, col);
}
void Board::drawStone(QPainter *&painter, int ID)
{
    if (stone[ID].isDead)
    {
        return;
    }
    if (selectedID == ID)
    {
        painter->setBrush(QColor(64, 224, 205));
    }
    else
    {
        QBrush brush(stone[ID].isRed ?  QColor(Qt::yellow) : QColor(135, 206, 250));
        painter->setBrush(brush);
    }
    QPen pen(Qt::white, 2);
    painter->setPen(pen);
    painter->drawEllipse(translate(ID), r, r);
    painter->setPen(Qt::black);
    if (stone[ID].isRed)
    {
        painter->setPen(Qt::red);
    }
    QPoint point = translate(ID);
    QRect rect = QRect(point.x() - r, point.y() - r, r * 2, r * 2);
    painter->drawText(rect, stone[ID].name(), QTextOption(Qt::AlignCenter));
}

// get stone's coordinate
QPoint Board::translate(int ID)
{
    QPoint point;
    point.rx() = (this->stone[ID].col + 1) * r * 2;   // 注意坐标与行列的关系，x对应列，y对应行
    point.ry() = (this->stone[ID].row + 1) * r * 2;
    return point;
}
// 获取棋子坐标的函数重载
QPoint Board::translate(int row, int col)
{
    QPoint point;
    point.rx() = (col + 1) * r * 2;     //  注意坐标与行列的关系，x对应列，y对应行
    point.ry() = (row + 1)* r * 2;
    return point;
}
// 获取鼠标点击的坐标，并判断是否点击在棋盘内
bool Board::getRowCol(QPoint point, int &row, int &col)
{
    // 简单直接，易于理解，但效率不高
    /*for(row = 0;row<10;row++)
    {
        for(col = 0;col<9;col++)
        {
            QPoint p = translate(row, col);
            int dx = p.x() - point.x();
            int dy = p.y() - point.y();
            int distance = dx*dx + dy*dy;
            if(distance <= r*r)
            {
                return true;
            }
        }
    }
    return false;  // 点击在棋盘外*/

    // 注意将像素坐标先+r再转换为行列值
    //（注：+r再除是类比了四舍五入的想法，圆心在行列交叉处，点击在圆心上方应该向大于它的数取整）
    //（   而int类型默认向比它的小的数取整）
    row = (point.y()+r)/(2*r) - 1;
    col = (point.x()+r)/(2*r) - 1;
    return (row <=9 && col <= 8) ? true : false;
}

bool Board::canMove(int moveID, int row, int col, int killID)
{
    if (stone[moveID].isRed == stone[killID].isRed)    // 如果要吃掉的棋子不是敌方的
    {
        selectedID = killID;   // 换选择
        update();
        return false;
    }
    else
    {
        switch (stone[moveID].type)
        {
        case Stone::JIANG:
            return canMoveJIANG(moveID, row, col);
        case Stone::SI:
            return canMoveSI(moveID, row, col);
        case Stone::BING:
            return canMoveBING(moveID, row, col);
        case Stone::CHE:
            return canMoveCHE(moveID, row, col);
        case Stone::XIANG:
            return canMoveXIANG(moveID, row, col);
        case Stone::MA:
            return canMoveMA(moveID, row, col);
        case Stone::PAO:
            return canMovePAO(moveID, row, col, killID);
        default:
            return false;
        }
    }
}
bool Board::canMovePAO(int moveID, int row, int col, int killID)
{
    if ( !(stone[moveID].row == row || stone[moveID].col == col) )
    {
        return false;
    }
    if (killID == -1)
    {
        if (isLineNull(moveID, row, col))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int count1 = 0;//用来计算要移动的棋子和要被吃的棋子之间棋子的个数
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    /*for(int i = 0;i<32;i++)
    {
        if(stone[i].isDead)
        {
            continue;
        }
        if(stone[moveID].row == stone[killID].row )
        {
            if(stone[killID].row > stone[moveID].col)
            {
                if(stone[i].row == stone[killID].row
                        && stone[moveID].col < stone[i].col
                        && stone[i].col < stone[killID].col)
                {
                    count1++;
                }
            }
            else
            {
                if(stone[i].row == row
                        && stone[moveID].col > stone[i].col
                        && stone[i].col > stone[killID].col)
                {
                    count2++;
                }
            }
        }
        if(stone[moveID].col == stone[killID].col )
        {
            if(row > stone[moveID].row)
            {
                if(stone[i].col == stone[killID].col
                        && stone[moveID].row < stone[i].row
                        && stone[i].row < stone[killID].row)
                {
                    count3++;
                }
            }
            else
            {
                if(stone[i].col == stone[killID].col
                        && stone[moveID].row > stone[i].row
                        && stone[i].row > stone[killID].row)
                {
                    count4++;
                }
            }
        }
    }*/
    if (stone[moveID].row == row )
    {
        if (col > stone[moveID].col)
        {
            for (int i = stone[moveID].col + 1;i<col;i++)
            {
                if (getStoneID(row, i) != -1)
                {
                    count1++;
                }
            }
        }
        else
        {
            for (int i = col + 1; i < stone[moveID].col; i++)
            {
                if (getStoneID(row, i) != -1)
                {
                    count2++;
                }
            }
        }
    }
    else if (stone[moveID].col == col)
    {
        if (row > stone[moveID].row)
        {
            for (int i = stone[moveID].row + 1; i < row; i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    count3++;
                }
            }
        }
        else
        {
            for (int i = row + 1; i < stone[moveID].row; i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    count4++;
                }
            }
        }
    }
    return  ( count1 == 1 || count2 == 1 ||count3 == 1 || count4 == 1 ) ? true : false;
}

bool Board::canMoveMA(int moveID, int row, int col)
{
    int rowDistance = abs(stone[moveID].row - row);
    int colDistance = abs(stone[moveID].col - col);
    if (rowDistance == 2)    // 在行上别马腿
    {
        int centerRow = (stone[moveID].row + row) / 2;
        int centerCol = stone[moveID].col;
        if (getStoneID(centerRow, centerCol) != -1)
        {
            return false;
        }
    }
    if (colDistance == 2)  // 在列上别马腿
    {
        int centerCol = (stone[moveID].col + col)/2;
        int centerRow = stone[moveID].row;
        if (getStoneID(centerRow, centerCol) != -1)
        {
            return false;
        }
    }
    int dr = stone[moveID].row - row;
    int dc = stone[moveID].col - col;
    int d = abs(dr) * 10 + abs(dc);
    return ( d == 21 || d == 12 ) ? true : false;
}

bool Board::canMoveXIANG(int moveID, int row, int col)
{
    // 去了对方位置
    if(stone[moveID].isRed == isRedSide)
    {
        if (row < 5)
        {
            return false;
        }
    }
    else
    {
        if (row > 4)
        {
            return false;
        }
    }
    // 判断是否田字中心有棋
    int centerRow = (stone[moveID].row + row) / 2;
    int centerCol = (stone[moveID].col + col) / 2;
    if (getStoneID(centerRow, centerCol) != -1)
    {
        return false;
    }
    int dr = stone[moveID].row - row;
    int dc = stone[moveID].col - col;
    int d = abs(dr) * 10 + abs(dc);
    return d == 22 ? true : false;
}

bool Board::canMoveCHE(int moveID, int row, int col)
{
    if( !(stone[moveID].row == row || stone[moveID].col == col) )
    {
        return false;
    }
    // 判断移动后和移动前的位置之间是否有棋子
    return isLineNull(moveID, row, col) ? true : false;
}

bool Board::canMoveBING(int moveID, int row, int col)
{
    if (stone[moveID].isRed == isRedSide)
    {
        if (row > stone[moveID].row)   // 往回走
        {
            return false;
        }
        if (stone[moveID].row > 4)
        {
            if (stone[moveID].col != col) // 限定只能直走
            {
                return false;
            }
        }
    }
    else
    {
        if (row < stone[moveID].row)  // back off
        {
            return false;
        }
        if (stone[moveID].row < 5)
        {
            if (stone[moveID].col != col) // 限定只能直走
            {
                return false;
            }
        }
    }
    int dr = stone[moveID].row - row;
    int dc = stone[moveID].col - col;
    int d = abs(dr)*10 + abs(dc);
    return ( d == 1 || d == 10 ) ? true : false;
}

bool Board::canMoveJIANG(int moveID, int row, int col)
{
    if (stone[moveID].isRed == isRedSide)
    {
        if (stone[4].row == row && stone[4].col == col && stone[4].col == stone[20].col)
        {
            for (int i = stone[4].row + 1; i < stone[20].row; i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    else
    {
        if (stone[20].row == row && stone[20].col == col && stone[4].col == stone[20].col)
        {
            for (int i = stone[4].row + 1;i<stone[20].row;i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    if (stone[moveID].isRed == isRedSide)
    {
        if (row < 7 || row > 9)
        {
            return false;
        }
    }
    else
    {
        if (row > 2 || row < 0)
        {
            return false;
        }
    }
    if (col < 3 || col > 5)
    {
        return false;
    }
    int dr = stone[moveID].row - row;
    int dc = stone[moveID].col - col;
    int d = abs(dr) * 10 + abs(dc);
    return (d == 1 || d == 10) ? true : false;
}

bool Board::canMoveSI(int moveID, int row, int col)
{
    if (stone[moveID].isRed == isRedSide)
    {
        if (row < 7 || row > 9)
        {
            return false;
        }
    }
    else
    {
        if (row > 2 || row < 0)
        {
            return false;
        }
    }
    if (col < 3 || col > 5)
    {
        return false;
    }
    int dr = stone[moveID].row - row;
    int dc = stone[moveID].col - col;
    int d = abs(dr) * 10 + abs(dc);
    return d == 11 ? true : false;
}

void Board::clicked(int clickedID, int row, int col)
{
    if (selectedID == -1)   // 假设是第一次被点击，那么selectedID应该被重新赋值
    {
        if (clickedID != -1) // 在上一个假设后，这一次假设点击的地方是有棋子的
        {
            if (stone[clickedID].isRed == isRedTurn)  // 再在上一次假设后，点击的棋子是轮到的一方的
            {
                selectedID = clickedID;   // 经上面全部假设后，那么该棋子被选中
                update();
            }
        }
    }
    else    // 已经在上一次点击的时候选择了棋子,那么这时候应该移动棋子
    {
        if (canMove(selectedID, row, col, clickedID))
        {
            this->saveStep(selectedID, clickedID, row, col, this->backSteps);
           /* qDebug()<<stone[this->backSteps[backSteps.size()-1]->moveID].name()<<"form"<<
                             this->backSteps[backSteps.size()-1]->rowFrom<<","<<
                             this->backSteps[backSteps.size()-1]->colFrom<<"to"<<
                             this->backSteps[backSteps.size()-1]->rowTo<<"," <<
                             this->backSteps[backSteps.size()-1]->colTo;*/
            moveStone(selectedID, row, col);
            selectedID = -1;    // clear selected flag
            killStone(clickedID);
            update();
        }
    }
}
bool Board::isLineNull(int moveID, int row, int col)
{
    if (stone[moveID].row == row )
    {
        if (col > stone[moveID].col)
        {
            for (int i = stone[moveID].col + 1; i < col; i++)
            {
                if (getStoneID(row, i) != -1)
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            for (int i = col + 1; i<stone[moveID].col; i++)
            {
                if (getStoneID(row, i) != -1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    else if (stone[moveID].col == col )
    {
        if (row > stone[moveID].row)
        {
            for (int i = stone[moveID].row + 1; i < row; i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            for (int i = row + 1; i < stone[moveID].row; i++)
            {
                if (getStoneID(i, col) != -1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return true;
}

void Board::moveStone(int selectedID, int row, int col)
{
    stone[selectedID].row = row;
    stone[selectedID].col = col;
    isRedTurn = !isRedTurn;      // 轮到另一方下棋
}
void Board::moveStone(int selectedID, int killID, int row, int col)
{
    stone[selectedID].row = row;
    stone[selectedID].col = col;
    killStone(killID);
    isRedTurn = !isRedTurn;    // 轮到另一方下棋
}

void Board::killStone(int killID)
{
    if (killID == -1)        // 这次点击的地方没有棋子
    {
       return;
    }
    else   // 这次点击的地方有棋子
    {
        stone[killID].isDead = true;    // 上面的棋子被吃掉
    }
}

void Board::reviveStone(int killID)
{
    if (killID != -1)
    {
        if (stone[killID].isDead)
        {
            stone[killID].isDead = false;
        }
    }
}

void Board::saveStep(int moveID, int killID, int rowTo, int colTo,
                     QVector<Step*> &steps)
{
    int rowFrom, colFrom;
    getRowCol(translate(moveID), rowFrom, colFrom);
    Step *step = new Step;

    step->moveID = moveID;
    step->killID = killID;
    step->rowFrom = rowFrom;
    step->colFrom = colFrom;
    step->rowTo = rowTo;
    step->colTo = colTo;

    steps.append(step);
}
int Board::getStoneID(int row, int col)
{
    int i = 0;
    for ( ; i < 32; i++)   // 用循环后i代表被点击的棋子的ID
    {
        if (stone[i].row == row && stone[i].col == col && stone[i].isDead == false)
        {
            break;
        }
    }
    int clickedID = -1;   // 每次点击棋子后clickedID会被重新赋值
    if(i<32)              // 表示点击的地方是有棋子的
    {
        clickedID = i;
    }
    return clickedID;
}

void Board::aboutSlot()
{
    QMessageBox::information(this,"关于","       作者：Ifan Tsai\n  "
                                        "        版本：2.0\n"
                                        "Coder will change the world ! ");
}

void Board::backSlot()
{
    if (this->backSteps.size() < 2)
    {
        return;
    }
    Step *step = this->backSteps.back();
    this->backSteps.removeLast();
    this->moveStone(step->moveID, step->rowFrom, step->colFrom);
    this->reviveStone(step->killID);
    delete step;

    step = this->backSteps.back();
    this->backSteps.removeLast();
    this->moveStone(step->moveID, step->rowFrom, step->colFrom);
    this->reviveStone(step->killID);
    delete step;

    this->selectedID = -1;
    update();
}

void Board::returnSlot()
{
    int ret = QMessageBox::warning(this, "返回", "确定要放弃当前棋局返回主界面？",
                         QMessageBox::No | QMessageBox::Yes);
    if (ret == QMessageBox::Yes)
    {
        openWidget *w = new openWidget;
        w->show();
        this->close();
        this->destroy();
    }
    else
    {
        return;
    }
}
