#include "emojicontainer.h"
#include "emojibutton.h"
#include "flowlayout.h"
#include "settings.h"

#include <QScrollArea>
#include <QWidget>
#include <QJsonArray>

#include <QDebug>

EmojiContainer::EmojiContainer(QWidget *parent, QJsonArray emojis) : QScrollArea(parent)
{
    emojiSize = Settings::getInt("emojiSize", 24);

    flowLayout = new FlowLayout(this);
    flowWidget = new QWidget(this);
    flowWidget->setLayout(flowLayout);
    this->setWidget(flowWidget);
    this->setWidgetResizable(true);

    for (QJsonArray::iterator iter = emojis.begin(); iter != emojis.end(); iter++) {
        flowLayout->addWidget(new EmojiButton(flowWidget, iter->toObject(), emojiSize));
    }
}

EmojiButton *EmojiContainer::addEmoji(QJsonObject emoji)
{
    EmojiButton *button = new EmojiButton(flowWidget, emoji, emojiSize);
    flowLayout->addWidget(button);
    return button;
}

void EmojiContainer::removeEmoji(QJsonObject emoji)
{
    for (EmojiButton *button : flowWidget->findChildren<EmojiButton*>()) {
        if (button->emoji["unicode"].toString() == emoji["unicode"].toString()) {
            button->setParent(nullptr);
            return;
        }
    }
}

bool EmojiContainer::hasEmoji(QJsonObject emoji)
{
    for (EmojiButton *button : flowWidget->findChildren<EmojiButton*>()) {
        if (button->emoji["unicode"].toString() == emoji["unicode"].toString()) {
            return true;
        }
    }
    return false;
}

void EmojiContainer::addEmojis(QList<QJsonObject> emojis)
{
    hide();
    for (QJsonObject emoji : emojis) {
        addEmoji(emoji);
    }
    show();
}

void EmojiContainer::clear()
{
    qDeleteAll(flowWidget->findChildren<EmojiButton*>());
}

void EmojiContainer::setEmojiSize(int size)
{
    emojiSize = size;
    for (EmojiButton *button : flowWidget->findChildren<EmojiButton*>()) {
        button->setEmojiSize(size);
    }
}
