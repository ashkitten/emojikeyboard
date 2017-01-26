#ifndef EMOJIPOPUP_H
#define EMOJIPOPUP_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class EmojiPopup;
}

class EmojiPopup : public QDialog
{
    Q_OBJECT

public:
    explicit EmojiPopup(QWidget *parent, QJsonObject emoji);
    ~EmojiPopup();

private:
    Ui::EmojiPopup *ui;
};

#endif // EMOJIPOPUP_H
