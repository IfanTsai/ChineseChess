#include "Stone.h"

Stone::Stone()
{

}

QString Stone::name()
{
    switch(this->type)
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
    default:
        return "错误";
    }
}

void Stone::init(int ID)
{
    struct
    {
        int row;
        int col;
        TYPE type;
    }pos[16] = {
    {0,0,Stone::CHE},
    {0,1,Stone::MA},
    {0,2,Stone::XIANG},
    {0,3,Stone::SI},
    {0,4,Stone::JIANG},
    {0,5,Stone::SI},
    {0,6,Stone::XIANG},
    {0,7,Stone::MA},
    {0,8,Stone::CHE},
    {2,1,Stone::PAO},
    {2,7,Stone::PAO},
    {3,0,Stone::BING},
    {3,2,Stone::BING},
    {3,4,Stone::BING},
    {3,6,Stone::BING},
    {3,8,Stone::BING} };

    if(ID<16)
    {
        this->row = pos[ID].row;
        this->col = pos[ID].col;
        this->type = pos[ID].type;
    }
    else
    {
        this->col = 8-pos[ID-16].col;
        this->row = 9-pos[ID-16].row;
        this->type = pos[ID-16].type;
    }
    this->ID = ID;
    this->isDead = false;
    this->isRed = (ID >= 16);
}
