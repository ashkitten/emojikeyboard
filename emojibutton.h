#ifndef EMOJIBUTTON_H
#define EMOJIBUTTON_H

#include <QPushButton>
#include <QJsonObject>

class EmojiButton : public QPushButton
{
    Q_OBJECT
public:
    EmojiButton(QWidget *parent, QJsonObject emoji);
    QJsonObject emoji;
};

#endif // EMOJIBUTTON_H
