#include "emojikeyboard.h"
#include "ui_emojikeyboard.h"
#include "flowlayout.h"
#include "emojicontainer.h"
#include "settings.h"
#include "util.h"

#include <QDialog>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

EmojiKeyboard::EmojiKeyboard(QWidget *parent) : QDialog(parent), ui(new Ui::EmojiKeyboard)
{
    ui->setupUi(this);

    Util::init();
    Settings::loadSettings();

    ui->tabs->addTab(Settings::favoritesPage, QIcon(":emoji/png_64/1f496.png"), "Favorites");

    for (QJsonArray::iterator iter = Util::categories.begin(); iter != Util::categories.end(); iter++) {
        QJsonArray category = Util::categoryMap[iter->toString()].toArray();
        QString iconPath = ":emoji/png_64/" + category.at(0).toObject()["unicode"].toString() + ".png";
        ui->tabs->addTab(new EmojiContainer(ui->tabs, category), QIcon(iconPath), iter->toString());
    }

    EmojiContainer *searchPage = new EmojiContainer(ui->stack, QJsonArray());
    ui->stack->addWidget(searchPage);

    connect(ui->searchBox, &QLineEdit::textChanged, [this, searchPage](QString text) {
        if (text.length() > 0) {
            ui->stack->setCurrentWidget(searchPage);
            searchPage->clear();

            for (QJsonObject::iterator iter = Util::emojiMap.begin(); iter != Util::emojiMap.end(); iter++) {
                QJsonObject emoji = iter.value().toObject();
                if (emoji["name"].toString().contains(text)) {
                    searchPage->addEmoji(emoji);
                }
            }
        } else {
            ui->stack->setCurrentWidget(ui->tabs);
        }
    });
}

EmojiKeyboard::~EmojiKeyboard()
{
    delete ui;
    Settings::saveSettings();
}
