#include "settings.h"
#include "emojicontainer.h"
#include "util.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

QJsonObject Settings::settings;
EmojiContainer *Settings::favoritesPage;

void Settings::loadSettings()
{
    QFile file("settings.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open settings file.");
        settings = QJsonObject();
    } else {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        settings = doc.object();
    }

    QJsonArray favorites;
    for (QJsonValue val : settings["favorites"].toArray()) {
        favorites.append(Util::emojiMap[val.toString()].toObject());
    }

    favoritesPage = new EmojiContainer(nullptr, favorites);
}

void Settings::saveSettings()
{
    QFile file("settings.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open settings file.");
        return;
    }
    QJsonDocument doc(settings);
    file.write(doc.toJson());
}

void Settings::addFavorite(QJsonObject emoji)
{
    QJsonArray favorites = settings["favorites"].toArray();
    favorites.append(emoji["unicode"].toString());
    settings["favorites"] = favorites;

    favoritesPage->addEmoji(emoji);
}

void Settings::removeFavorite(QJsonObject emoji)
{
    QJsonArray favorites = settings["favorites"].toArray();
    for (QJsonArray::iterator iter = favorites.begin(); iter != favorites.end(); iter++) {
        if (iter->toString() == emoji["unicode"].toString()) {
            favorites.erase(iter);
            break;
        }
    }
    settings["favorites"] = favorites;

    favoritesPage->removeEmoji(emoji);
}

bool Settings::isFavorite(QJsonObject emoji)
{
    QJsonArray favorites = settings["favorites"].toArray();
    for (QJsonArray::iterator iter = favorites.begin(); iter != favorites.end(); iter++) {
        if (iter->toString() == emoji["unicode"].toString()) {
            return true;
        }
    }
    return false;
}
