#ifndef ALLSOURCE_H
#define ALLSOURCE_H

#include "Common/database.h"
#include "Interfaces/isource.h"


class AllSource: public ISource
{
public:
    AllSource();
    QStringList getPaths() override;
    QStringList parseDir(QString);
};

#endif // ALLSOURCE_H
