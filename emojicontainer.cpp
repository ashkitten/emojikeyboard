#include "emojicontainer.h"
#include "emojibutton.h"
#include "flowlayout.h"

#include <QScrollArea>
#include <QWidget>
#include <QJsonObject>

EmojiContainer::EmojiContainer(QWidget *parent, QJsonObject emojis) : QScrollArea(parent)
{
    FlowLayout *flowLayout = new FlowLayout();
    QWidget *flowWidget = new QWidget();
    flowWidget->setLayout(flowLayout);
    this->setWidget(flowWidget);
    this->setWidgetResizable(true);

    for (QJsonObject::iterator iter = emojis.begin(); iter != emojis.end(); iter++) {
        flowLayout->addWidget(new EmojiButton(flowWidget, iter.value().toObject()));
    }
}
