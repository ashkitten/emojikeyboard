#ifndef EMOJICONTAINER_H
#define EMOJICONTAINER_H

#include <QScrollArea>


class EmojiContainer : public QScrollArea
{
    Q_OBJECT
public:
    explicit EmojiContainer(QWidget *parent, QJsonObject emojis);

signals:

public slots:
};

#endif // EMOJICONTAINER_H
