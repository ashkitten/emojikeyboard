#ifndef EMOJIKEYBOARD_H
#define EMOJIKEYBOARD_H

#include <QDialog>

namespace Ui {
class EmojiKeyboard;
}

class EmojiKeyboard : public QDialog
{
    Q_OBJECT
public:
    EmojiKeyboard(QWidget *parent = nullptr);
    ~EmojiKeyboard();

private:
    Ui::EmojiKeyboard *ui;
};

#endif // EMOJIKEYBOARD_H
