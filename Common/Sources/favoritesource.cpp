#include "favoritesource.h"

FavoriteSource::FavoriteSource()
{}

QStringList FavoriteSource::getPaths()
{
    auto db = Database::getInstance();
    return db->getFavorites();
}
