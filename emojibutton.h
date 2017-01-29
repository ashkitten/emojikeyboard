#ifndef EMOJIBUTTON_H
#define EMOJIBUTTON_H

#include <QPushButton>
#include <QJsonObject>

class EmojiButton : public QPushButton
{
    Q_OBJECT
public:
    EmojiButton(QWidget *parent, QJsonObject emoji, int size = 24);
    QJsonObject emoji;

public slots:
    void setEmojiSize(int size);
};

#endif // EMOJIBUTTON_H
