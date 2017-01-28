#ifndef UTIL_H
#define UTIL_H

#include <QJsonObject>
#include <QJsonArray>

class Util
{
public:
    static void init();

    static QJsonArray categories;
    static QJsonObject categoryMap;
    static QJsonArray emojis;
    static QJsonObject emojiMap;
};

#endif // UTIL_H
