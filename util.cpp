#include "util.h"

#include <QFile>
#include <QJsonDocument>

QJsonArray Util::categories;
QJsonObject Util::categoryMap;
QJsonArray Util::emojis;
QJsonObject Util::emojiMap;

void Util::init()
{
    QFile file(":emoji.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open emoji json file.");
    }
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));

    categories = doc.object()["categories"].toArray();
    categoryMap = doc.object()["categoryMap"].toObject();
    emojis = doc.object()["emojis"].toArray();
    emojiMap = doc.object()["emojiMap"].toObject();
}
