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
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>

#include <QDebug>

EmojiKeyboard::EmojiKeyboard(QWidget *parent) : QDialog(parent), ui(new Ui::EmojiKeyboard)
{
    ui->setupUi(this);

    Util::init();
    Settings::loadSettings();

    setWindowIcon(QIcon(":icon.png"));

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

            QList<QJsonObject> searchResults;
            for (QJsonObject::iterator iter = Util::emojiMap.begin(); iter != Util::emojiMap.end(); iter++) {
                QJsonObject emoji = iter.value().toObject();

                if (emoji["name"].toString().contains(text) || emoji["keywords"].toString().contains(text)) {
                    searchResults.append(emoji);
                }
            }

            std::sort(searchResults.begin(), searchResults.end(), [text](QJsonObject v1, QJsonObject v2) {
                return Util::levenshtein(v1["name"].toString(), text) < Util::levenshtein(v2["name"].toString(), text);
            });

            for (QJsonObject emoji : searchResults) {
                searchPage->addEmoji(emoji);
            }
        } else {
            ui->stack->setCurrentWidget(ui->tabs);
        }
    });

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        QMenu *menu = new QMenu();

        QAction *showAction = menu->addAction("Show");
        showAction->connect(showAction, &QAction::triggered, this, &EmojiKeyboard::showActionTriggered);

        QAction *quitAction = menu->addAction("Quit");
        connect(quitAction, &QAction::triggered, this, &EmojiKeyboard::quitActionTriggered);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(":icon.png"));
        trayIcon->setContextMenu(menu);
        trayIcon->setToolTip("Emoji Keyboard");
        trayIcon->show();

        connect(trayIcon, &QSystemTrayIcon::activated, this, &EmojiKeyboard::iconActivated);
    }
}

EmojiKeyboard::~EmojiKeyboard()
{
    delete ui;
    Settings::saveSettings();
}

void EmojiKeyboard::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::ActivationReason::Trigger) {
        show();
    }
}

void EmojiKeyboard::showActionTriggered(bool checked) {
    show();
}

void EmojiKeyboard::quitActionTriggered(bool checked) {
    quit();
}

void EmojiKeyboard::quit()
{
    this->_closing = true;
    this->close();
}

void EmojiKeyboard::reject()
{
    if (this->_closing) {
        QDialog::reject();
    } else {
        this->hide();
    }
}
