#include "emojibutton.h"
#include "emojipopup.h"

#include <QJsonObject>
#include <QIcon>
#include <QPushButton>

EmojiButton::EmojiButton(QWidget *parent, QJsonObject emoji, int size) : QPushButton(parent)
{
    this->emoji = emoji;

    QIcon icon(":emoji/svg/" + emoji["unicode"].toString() + ".svg");
    setIcon(icon);
    setIconSize(QSize(size, size));

    connect(this, &QPushButton::clicked, [this, emoji]() {
        EmojiPopup *popup = new EmojiPopup(this, emoji);
        popup->show();
    });
}

void EmojiButton::setEmojiSize(int size)
{
    setIconSize(QSize(size, size));
}
