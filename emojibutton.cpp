#include "emojibutton.h"
#include "emojipopup.h"

#include <iostream>

#include <QJsonObject>

using namespace std;

EmojiButton::EmojiButton(QWidget *parent, QJsonObject emoji) : QPushButton(parent)
{
    QIcon icon(":emoji/png_64/" + emoji["unicode"].toString() + ".png");
    setIcon(icon);

    connect(this, &QPushButton::clicked, [this, emoji]() {
        EmojiPopup *popup = new EmojiPopup(this, emoji);
        popup->show();
    });
}
