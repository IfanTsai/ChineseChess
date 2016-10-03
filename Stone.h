#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();
public:
    enum TYPE{CHE, MA, XIANG, PAO ,JIANG, BING, SI};
    int row;//行
    int col;//列
    int ID;
    bool isRed;
    bool isDead;
    TYPE type;
public:
    QString name();
    void init(int ID);
};

#endif // STONE_H
