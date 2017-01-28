#ifndef SETTINGS_H
#define SETTINGS_H

#include "emojicontainer.h"

#include <QJsonObject>

class Settings
{
public:
    static QJsonObject settings;
    static EmojiContainer *favoritesPage;

    static void loadSettings();
    static void saveSettings();

    static void addFavorite(QJsonObject emoji);
    static void removeFavorite(QJsonObject emoji);
    static bool isFavorite(QJsonObject emoji);
};

#endif // SETTINGS_H
