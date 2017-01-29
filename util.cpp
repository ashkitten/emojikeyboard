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

int Util::levenshtein(QString s1, QString s2)
{
    int s1len = s1.length();
    int s2len = s2.length();

    auto column_start = (decltype(s1len))1;

    auto column = new decltype(s1len)[s1len + 1];
    std::iota(column + column_start, column + s1len + 1, column_start);

    for (auto x = column_start; x <= s2len; x++) {
        column[0] = x;
        auto last_diagonal = x - column_start;
        for (auto y = column_start; y <= s1len; y++) {
            auto old_diagonal = column[y];
            auto possibilities = {
                column[y] + 1,
                column[y - 1] + 1,
                last_diagonal + (s1[y - 1] == s2[x - 1]? 0 : 1)
            };
            column[y] = std::min(possibilities);
            last_diagonal = old_diagonal;
        }
    }
    auto result = column[s1len];
    delete[] column;
    return result;
}
