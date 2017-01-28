#ifndef EMOJICONTAINER_H
#define EMOJICONTAINER_H

#include "flowlayout.h"

#include <QScrollArea>

class EmojiContainer : public QScrollArea
{
    Q_OBJECT
public:
    EmojiContainer(QWidget *parent, QJsonArray emojis);
    void addEmoji(QJsonObject emoji);
    void removeEmoji(QJsonObject emoji);
    bool hasEmoji(QJsonObject emoji);
    void clear();

private:
    FlowLayout *flowLayout;
    QWidget *flowWidget;

signals:

public slots:
};

#endif // EMOJICONTAINER_H
