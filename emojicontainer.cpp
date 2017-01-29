#include "emojicontainer.h"
#include "emojibutton.h"
#include "flowlayout.h"

#include <QScrollArea>
#include <QWidget>
#include <QJsonArray>

#include <QDebug>

EmojiContainer::EmojiContainer(QWidget *parent, QJsonArray emojis) : QScrollArea(parent)
{
    flowLayout = new FlowLayout(this);
    flowWidget = new QWidget(this);
    flowWidget->setLayout(flowLayout);
    this->setWidget(flowWidget);
    this->setWidgetResizable(true);

    for (QJsonArray::iterator iter = emojis.begin(); iter != emojis.end(); iter++) {
        flowLayout->addWidget(new EmojiButton(flowWidget, iter->toObject()));
    }
}

void EmojiContainer::addEmoji(QJsonObject emoji)
{
    flowLayout->addWidget(new EmojiButton(flowWidget, emoji));
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

void EmojiContainer::clear()
{
    qDeleteAll(flowWidget->findChildren<EmojiButton*>());
}
