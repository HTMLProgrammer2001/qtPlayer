#include "randomgen.h"
#include <QDateTime>

RandomGen::RandomGen(int low, int high): low(low), high(high)
{
    qsrand(QDateTime::currentDateTime().toSecsSinceEpoch());
}

int RandomGen::next()
{
    //increment pos
    this->current++;

    //return if go old way
    if(this->current < this->seq.size())
        return this->seq.at(this->current);

    //generate new random numb
    int randomVal = this->genRand();
    this->seq.append(randomVal);

    return randomVal;
}

int RandomGen::prev()
{
    //change index
    if(this->current == 0){
        int randomVal = this->genRand();
        this->seq.prepend(randomVal);
    }
    else
        this->current--;

    return this->seq.at(this->current);
}

int RandomGen::genRand()
{
    return qrand() % (this->high + 1 - this->low) + this->low;
}

void RandomGen::reset()
{
    this->seq = {};
    this->current = 0;
}
