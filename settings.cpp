#include "settings.h"
#include "emojicontainer.h"
#include "util.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMenu>
#include <QClipboard>
#include <QApplication>

QJsonObject Settings::settings;
EmojiContainer *Settings::favoritesPage;
QMenu *Settings::favoritesTrayMenu;

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

    QJsonArray favoriteEmojis;
    for (QJsonValue val : settings["favorites"].toArray()) {
        favoriteEmojis.append(Util::emojiMap[val.toString()].toObject());
    }

    favoritesPage = new EmojiContainer(nullptr, favoriteEmojis);
    favoritesTrayMenu = new QMenu();
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

void Settings::putString(QString key, QString value)
{
    QJsonObject store = settings["store"].toObject();
    store[key] = value;
    settings["store"] = store;
}

void Settings::putInt(QString key, int value)
{
    QJsonObject store = settings["store"].toObject();
    store[key] = value;
    settings["store"] = store;
}

void Settings::putBool(QString key, bool value)
{
    QJsonObject store = settings["store"].toObject();
    store[key] = value;
    settings["store"] = store;
}

QString Settings::getString(QString key, QString def)
{
    return settings["store"].toObject().contains(key) ? settings["store"].toObject()[key].toString() : def;
}

int Settings::getInt(QString key, int def)
{
    return settings["store"].toObject().contains(key) ? settings["store"].toObject()[key].toInt() : def;
}

bool Settings::getBool(QString key, bool def)
{
    return settings["store"].toObject().contains(key) ? settings["store"].toObject()[key].toBool() : def;
}

void Settings::addFavorite(QJsonObject emoji)
{
    QJsonArray favorites = settings["favorites"].toArray();
    favorites.append(emoji["unicode"].toString());
    settings["favorites"] = favorites;

    favoritesPage->addEmoji(emoji);

    QAction *favoriteAction = favoritesTrayMenu->addAction(emoji["name"].toString().left(16) + ((emoji["name"].toString().length() > 16) ? "..." : ""));
    favoriteAction->setIcon(QIcon(":emoji/svg/" + emoji["unicode"].toString() + ".svg"));
    favoriteAction->setData(QVariant(emoji["unicode"].toString()));
    favoritesTrayMenu->connect(favoriteAction, &QAction::triggered, [emoji](bool checked) {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(emoji["characters"].toString());
    });
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

    for (QAction *action : favoritesTrayMenu->actions()) {
        if (action->data().toString() == emoji["unicode"].toString()) {
            favoritesTrayMenu->removeAction(action);
        }
    }
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
