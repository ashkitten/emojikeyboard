#include "emojipopup.h"
#include "ui_emojipopup.h"

#include "settings.h"

#include <QClipboard>
#include <QSvgWidget>

using namespace std;

EmojiPopup::EmojiPopup(QWidget *parent, QJsonObject emoji) : QDialog(parent), ui(new Ui::EmojiPopup)
{
    ui->setupUi(this);

    setWindowTitle(emoji["name"].toString());

    ui->emojiName->setText(emoji["name"].toString());
    ui->emojiUnicode->setText("U+" + emoji["unicode"].toString().toUpper());

    QSvgWidget *emojiImage = new QSvgWidget(":emoji/svg/" + emoji["unicode"].toString() + ".svg");
    ui->gridLayout->addWidget(emojiImage, 2, 0, 1, 3);

    if (Settings::isFavorite(emoji)) {
        ui->favoriteButton->setIcon(QIcon(":images/ic_favorite_black_24px.svg"));
    } else {
        ui->favoriteButton->setIcon(QIcon(":images/ic_favorite_border_black_24px.svg"));
    }
    
    connect(ui->favoriteButton, &QPushButton::clicked, [this, emoji]() {
        if (Settings::isFavorite(emoji)) {
            Settings::removeFavorite(emoji);
            ui->favoriteButton->setIcon(QIcon(":images/ic_favorite_border_black_24px.svg"));
        } else {
            Settings::addFavorite(emoji);
            ui->favoriteButton->setIcon(QIcon(":images/ic_favorite_black_24px.svg"));
        }
    });

    connect(ui->copyButton, &QPushButton::clicked, [this, emoji]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(emoji["characters"].toString());
    });
}

EmojiPopup::~EmojiPopup()
{
    delete ui;
}
