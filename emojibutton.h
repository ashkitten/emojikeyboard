#ifndef EMOJIBUTTON_H
#define EMOJIBUTTON_H

#include <QPushButton>
#include <QJsonObject>

class EmojiButton : public QPushButton
{
public:
    explicit EmojiButton(QWidget *parent, QJsonObject emoji);
};

#endif // EMOJIBUTTON_H
