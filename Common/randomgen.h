#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <QList>


class RandomGen
{
private:
    QList<int> seq;
    int current = 0;
    int low;
    int high;

public:
    RandomGen(int low, int high);
    int next();
    int prev();
    void reset();

private:
    int genRand();
};

#endif // RANDOMGEN_H
