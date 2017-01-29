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

    static void putString(QString key, QString value);
    static void putInt(QString key, int value);
    static QString getString(QString key, QString default = "");
    static int getInt(QString key, int default = 0);

    static void addFavorite(QJsonObject emoji);
    static void removeFavorite(QJsonObject emoji);
    static bool isFavorite(QJsonObject emoji);
};

#endif // SETTINGS_H
