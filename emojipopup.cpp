#include "emojipopup.h"
#include "ui_emojipopup.h"

#include <QClipboard>

using namespace std;

EmojiPopup::EmojiPopup(QWidget *parent, QJsonObject emoji) : QDialog(parent), ui(new Ui::EmojiPopup)
{
    ui->setupUi(this);

    ui->emojiName->setText(emoji["name"].toString());
    ui->emojiUnicode->setText("U+" + emoji["unicode"].toString().toUpper());

    QPixmap pixmap(":emoji/png_512/" + emoji["unicode"].toString() + ".png");
    ui->emojiImage->setPixmap(pixmap);

    connect(ui->copyButton, &QPushButton::clicked, [emoji]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(emoji["characters"].toString());
    });
}

EmojiPopup::~EmojiPopup()
{
    delete ui;
}
