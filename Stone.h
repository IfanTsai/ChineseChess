#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();
public:
    enum TYPE{CHE, MA, XIANG, PAO ,JIANG, BING, SI};
    int row; // 行
    int col; // 列
    int ID;
    bool isRed;
    bool isDead;
    TYPE type;

    struct {
        int row;
        int col;
        TYPE type;
    } pos[16] = {
    {0, 0, Stone::CHE},
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},
    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},
    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING} };

public:
    QString name();
    void init(int ID);
};

#endif // STONE_H
