#ifndef EMOJICONTAINER_H
#define EMOJICONTAINER_H

#include "flowlayout.h"
#include "emojibutton.h"

#include <QScrollArea>

class EmojiContainer : public QScrollArea
{
    Q_OBJECT
public:
    EmojiContainer(QWidget *parent, QJsonArray emojis);
    EmojiButton *addEmoji(QJsonObject emoji);
    void removeEmoji(QJsonObject emoji);
    bool hasEmoji(QJsonObject emoji);
    void addEmojis(QList<QJsonObject> emojis);
    void clear();

public slots:
    void setEmojiSize(int size);

private:
    int emojiSize = 24;

    FlowLayout *flowLayout;
    QWidget *flowWidget;
};

#endif // EMOJICONTAINER_H
