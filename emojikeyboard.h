#ifndef EMOJIKEYBOARD_H
#define EMOJIKEYBOARD_H

#include <QDialog>
#include <QSystemTrayIcon>

namespace Ui {
class EmojiKeyboard;
}

class EmojiKeyboard : public QDialog
{
    Q_OBJECT
public:
    EmojiKeyboard(QWidget *parent = nullptr);
    void quit();
    void reject();
    ~EmojiKeyboard();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showActionTriggered(bool checked);
    void quitActionTriggered(bool checked);

private:
    Ui::EmojiKeyboard *ui;
    QSystemTrayIcon *trayIcon;
    bool _closing = false;
};

#endif // EMOJIKEYBOARD_H
