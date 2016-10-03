#include "SingleGame.h"

SingleGame::SingleGame()
{
    int ret = QMessageBox::question(nullptr, "友情提示", "是否需要悔棋功能？");
    if(ret == QMessageBox::No)
    {
        this->backButton->hide();
    }
}
void SingleGame::clicked(int clickedID, int row, int col)
{
    if(!this->isRedTurn)//如果不是玩家走，玩家移动了也没用
    {
        return;
    }
    if(this->isRedTurn)
    {
        Board::clicked(clickedID, row, col);
    }
    if(!this->isRedTurn)//紧接着上面玩家走了之后，isRedTurn为false，该函数自动进入，轮到电脑走
    {
        QTimer::singleShot(100, this, SLOT(computerMove()));
    }
}
void SingleGame::computerMove()
{
    QTime time;
    time.start();
    Step *step = computerGetBestMove();
    this->saveStep(step->moveID, step->killID, step->rowTo, step->colTo, this->backSteps);
    /*qDebug()<<stone[this->backSteps[backSteps.size()-1]->moveID].name()<<"form"<<
                     this->backSteps[backSteps.size()-1]->rowFrom<<","<<
                     this->backSteps[backSteps.size()-1]->colFrom<<"to"<<
                     this->backSteps[backSteps.size()-1]->rowTo<<"," <<
                     this->backSteps[backSteps.size()-1]->colTo;*/
    this->moveStone(step->moveID, step->killID, step->rowTo, step->colTo);
    update();
    //int time_Diff = time.elapsed();
    //qDebug()<<"电脑思考了"<<time_Diff<<"ms";
    /*QFile file("C:\\Users\\caiyifan\\Desktop\\test.txt");
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream out(&file);//文本流
    out.setCodec("utf-8");
    out<<tr("电脑思考了")<<QString::number(time_Diff)<<"ms"<<endl;
    file.close();*/
    delete step;
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min = 0;
    int max = 16;
    if(this->isRedTurn)
    {
        min = 16;
        max = 32;
    }
    for(int i = min;i<max;i++)
    {
        if(stone[i].isDead)
        {
            continue;
        }
        int eachRowBegin = 0, eachRowEnd = 9, eachColBegin = 0, eachColEnd = 8;
        if(i == 5 || i == 21)//士优化
        {
            eachRowBegin = stone[i].row -1 ;
            eachRowEnd = stone[i].row + 1;
            eachColBegin = stone[i].col - 1;
            eachColEnd = stone[i].col + 1;
        }
        else if(i == 4 || i == 20)//将优化
        {
            eachRowBegin = stone[i].row -1 ;
            eachRowEnd = stone[i].row + 1;
            eachColBegin = stone[i].col - 1;
            eachColEnd = stone[i].col + 1;
            int killID = ( (i-16) > 0 ) ? (i - 16) : (i+16);
            if(!stone[killID].isDead)
            {
                if(this->canMove(i, stone[killID].row, stone[killID].col, killID))
                {
                    this->saveStep(i, killID, stone[killID].row, stone[killID].col ,
                                   steps);
                }
            }
        }
        else if(stone[i].type == Stone::BING)//兵优化
        {
            if(stone[i].isRed)
            {
                if(stone[i].row > 4)
                {
                    eachRowEnd =  eachRowBegin = stone[i].row - 1;
                    eachColBegin = eachColEnd = stone[i].col;
                }
                else
                {
                    eachRowBegin = eachRowEnd = stone[i].row - 1;
                    eachColBegin = stone[i].col - 1;
                    eachColEnd = stone[i].col + 1;
                }
            }
            else
            {
                if(stone[i].row < 5)
                {
                    eachRowEnd =  eachRowBegin = stone[i].row + 1;
                    eachColBegin = eachColEnd = stone[i].col;
                }
                else
                {
                    eachRowBegin = eachRowEnd = stone[i].row + 1;
                    eachColBegin = stone[i].col - 1;
                    eachColEnd = stone[i].col + 1;
                }
            }
        }
        else if(stone[i].type == Stone::XIANG)//象优化
        {
            if(stone[i].isRed)
            {
                eachRowBegin = 5;
                eachRowEnd = 9;
            }
            else
            {
                eachRowBegin = 0;
                eachRowEnd = 4;
            }
        }
        for(int row = eachRowBegin;row <= eachRowEnd;row++)
        {
            for(int col = eachColBegin;col <= eachColEnd;col++)
            {
                int killID = this->getStoneID(row, col);
                if(killID != -1)
                {
                    if(this->isRedTurn == stone[killID].isRed)
                    {
                        continue;
                    }
                }
                if(this->canMove(i, row, col, killID))
                {
                    this->saveStep(i, killID, row, col , steps);
                }
            }
        }
    }
}
void SingleGame::fakeMove(Step *&step)
{
    this->killStone(step->killID);
    this->moveStone(step->moveID, step->rowTo, step->colTo);
}

void SingleGame::unfakeMove(Step *&step)
{
    this->reviveStone(step->killID);
    this->moveStone(step->moveID, step->rowFrom, step->colFrom);
}

int SingleGame::calcScore()
{
    //enum TYPE{CHE, MA, XIANG, PAO ,JIANG, BING, SI};
    int chessScore[] = {52, 13, 6, 22, 208, 2, 6};
    int blackScore = 0;
    int redScore = 0;
    for(int i = 0;i<16;i++)
    {
        if(stone[i].isDead)
        {
            continue;
        }
        blackScore += chessScore[stone[i].type];
    }
    for(int i = 16;i<32;i++)
    {
        if(stone[i].isDead)
        {
            continue;
        }
        redScore += chessScore[stone[i].type];
    }
    int totalScore = blackScore - redScore;
    return totalScore;
}
int SingleGame::getMinScore(int deep, int currentMaxScore)
{
    if(!deep)
    {
        return calcScore();
    }
    QVector<Step *> steps;
    getAllPossibleMove(steps);
    int minScore = 100000;
    while(steps.count())
    {
        Step *step = steps.front();
        steps.removeFirst();
        fakeMove(step);
        int score = getMaxScore(deep - 1, minScore);
        unfakeMove(step);
        delete step;
        if(score <= currentMaxScore)
        {
            while(steps.count())
            {
                Step *step = steps.front();
                steps.removeFirst();
                delete step;
            }
            return score;
        }
        if(minScore > score)
        {
            minScore = score;
        }

    }
    return minScore;
}
int SingleGame::getMaxScore(int deep, int currentMinScore)
{
    if(!deep)
    {
        return calcScore();
    }
    /****************/
    /*int score = calcScore();
    if(score > 30)
    {
        return score;
    }*/
    /****************/
    QVector<Step *> steps;
    getAllPossibleMove(steps);
    int maxScore = -100000;
    while(steps.count())
    {
        Step *step = steps.front();
        steps.removeFirst();
        fakeMove(step);
        int score = getMinScore(deep - 1, maxScore);
        unfakeMove(step);
        delete step;
        if(score >= currentMinScore)
        {
            while(steps.count())
            {
                Step *step = steps.front();
                steps.removeFirst();
                delete step;
            }
            return score;
        }
        if(maxScore < score)
        {
            maxScore = score;
        }
    }
    return maxScore;
}

Step* SingleGame::computerGetBestMove()
{
    QVector<Step *> steps;
    getAllPossibleMove(steps);
    int maxScore = -100000;
    Step* bestStep = nullptr;
    while(steps.count())
    {
        Step *step = steps.front();
        steps.removeFirst();
        fakeMove(step);
        int score = getMinScore(deep - 1, maxScore);//获取第二步中分值最小的
        unfakeMove(step);
        if(score > maxScore)
        {
            maxScore = score;
            delete bestStep;
            bestStep = step;
        }
        else
        {
            delete step;
        }
    }
    return bestStep;
}
