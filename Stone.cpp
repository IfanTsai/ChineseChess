#include "Stone.h"

Stone::Stone()
{

}

QString Stone::name()
{
    switch (this->type)
    {
    case Stone::PAO:
        return "炮";
    case Stone::BING:
        return "兵";
    case Stone::CHE:
        return "车";
    case Stone::JIANG:
        return "将";
    case Stone::MA:
        return "马";
    case Stone::SI:
        return "士";
    case Stone::XIANG:
        return "相";
    }
}

void Stone::init(int ID)
{
    // 棋盘左下角定义为（row, col） = （0, 0）
    // ID:
    //   0 - 15 红方   16 - 31 黑方
    if (ID < 16)
    {
        this->row = pos[ID].row;
        this->col = pos[ID].col;
        this->type = pos[ID].type;
    }
    else
    {
        this->row = 9 - pos[ID - 16].row;
        this->col = 8 - pos[ID - 16].col;
        this->type = pos[ID - 16].type;
    }
    this->ID = ID;
    this->isDead = false;
    this->isRed = (ID >= 16);
}
