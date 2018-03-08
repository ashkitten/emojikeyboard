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
#include <QSpinBox>

#include <QDebug>

EmojiKeyboard::EmojiKeyboard(QWidget *parent) : QDialog(parent), ui(new Ui::EmojiKeyboard)
{
    ui->setupUi(this);

    Util::init();
    Settings::loadSettings();

    ui->emojiSize->setValue(Settings::getInt("emojiSize", 24));
    connect(ui->emojiSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [](int size) {
        Settings::putInt("emojiSize", size);
    });

    setWindowIcon(QIcon(":icon.png"));

    ui->tabs->addTab(Settings::favoritesPage, QIcon(":emoji/svg/1f496.svg"), "Favorites");
    connect(ui->emojiSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), Settings::favoritesPage, &EmojiContainer::setEmojiSize);

    for (QJsonArray::iterator iter = Util::categories.begin(); iter != Util::categories.end(); iter++) {
        QJsonArray category = Util::categoryMap[iter->toString()].toArray();
        QString iconPath = ":emoji/svg/" + category.at(0).toObject()["unicode"].toString() + ".svg";

        EmojiContainer *container = new EmojiContainer(ui->tabs, category);
        connect(ui->emojiSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), container, &EmojiContainer::setEmojiSize);
        ui->tabs->addTab(container, QIcon(iconPath), iter->toString().replace("&", "&&"));
    }

    EmojiContainer *searchPage = new EmojiContainer(ui->stack, QJsonArray());
    connect(ui->emojiSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), searchPage, &EmojiContainer::setEmojiSize);
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

            searchPage->addEmojis(searchResults);
        } else {
            ui->stack->setCurrentWidget(ui->tabs);
        }
    });

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        QMenu *menu = new QMenu();

        QAction *favoritesAction = menu->addAction("Favorites");
        favoritesAction->setMenu(Settings::favoritesTrayMenu);

        QAction *showAction = menu->addAction("Show");
        showAction->connect(showAction, &QAction::triggered, this, &EmojiKeyboard::showActionTriggered);

        QAction *quitAction = menu->addAction("Quit");
        connect(quitAction, &QAction::triggered, this, &EmojiKeyboard::quitActionTriggered);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(":icon.png"));
        trayIcon->setContextMenu(menu);
        trayIcon->setToolTip("Emoji Keyboard");
        trayIcon->show();

        connect(trayIcon, &QSystemTrayIcon::activated, this, &EmojiKeyboard::iconActivated);

        if (!Settings::getBool("notFirstRun")) {
            Settings::putBool("notFirstRun", true);
            trayIcon->showMessage("Emoji Keyboard", "Right click the tray icon for quick access.");
        }
    }

    ui->tabs->setCurrentIndex(1);

    connect(ui->settingsButton, &QPushButton::clicked, [this](bool checked) {
        ui->mainStack->setCurrentWidget(ui->settingsPage);
    });

    connect(ui->backButton, &QPushButton::clicked, [this](bool checked) {
        ui->mainStack->setCurrentWidget(ui->mainPage);
    });

    ui->searchBox->setFocus();
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

void EmojiKeyboard::showActionTriggered(bool checked)
{
    show();
}

void EmojiKeyboard::quitActionTriggered(bool checked)
{
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
