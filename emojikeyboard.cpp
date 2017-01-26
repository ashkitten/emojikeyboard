#include "emojikeyboard.h"
#include "ui_emojikeyboard.h"
#include "flowlayout.h"
#include "emojicontainer.h"

#include <iostream>

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

using namespace std;

EmojiKeyboard::EmojiKeyboard(QWidget *parent) : QDialog(parent), ui(new Ui::EmojiKeyboard)
{
    ui->setupUi(this);

    QFile file(":emoji.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open emoji json file.");
    }
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));

    QJsonObject categories = doc.object()["categories"].toObject();

    for (QJsonObject::iterator iter = categories.begin(); iter != categories.end(); iter++) {
        QString iconPath = ":emoji/png_64/" + iter.value().toObject().value(iter.value().toObject().keys().at(0)).toObject()["unicode"].toString() + ".png";
        ui->tabWidget->addTab(new EmojiContainer(ui->tabWidget, iter.value().toObject()), QIcon(iconPath), iter.key());
    }
}

EmojiKeyboard::~EmojiKeyboard()
{
    delete ui;
}
