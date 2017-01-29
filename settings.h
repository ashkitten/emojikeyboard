#ifndef SETTINGS_H
#define SETTINGS_H

#include "emojicontainer.h"

#include <QJsonObject>

class Settings
{
public:
    static QJsonObject settings;
    static EmojiContainer *favoritesPage;
    static QMenu *favoritesTrayMenu;

    static void loadSettings();
    static void saveSettings();

    static void putString(QString key, QString value);
    static void putInt(QString key, int value);
    static void putBool(QString key, bool value);

    static QString getString(QString key, QString def = "");
    static int getInt(QString key, int def = 0);
    static bool getBool(QString key, bool def = false);

    static void addFavorite(QJsonObject emoji);
    static void removeFavorite(QJsonObject emoji);
    static bool isFavorite(QJsonObject emoji);
};

#endif // SETTINGS_H
