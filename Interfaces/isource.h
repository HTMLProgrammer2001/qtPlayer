#ifndef ISOURCE_H
#define ISOURCE_H

#include<QStringList>


class ISource
{
public:
    ISource();
    virtual QStringList getPaths() = 0;
};

#endif // ISOURCE_H
