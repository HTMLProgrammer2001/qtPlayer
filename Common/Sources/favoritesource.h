#ifndef FAVORITESOURCE_H
#define FAVORITESOURCE_H

#include "Interfaces/isource.h"
#include "Common/database.h"


class FavoriteSource: public ISource
{
public:
    FavoriteSource();
    QStringList getPaths() override;
};

#endif // FAVORITESOURCE_H
