#include "emojikeyboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("EmojiKeyboard");
    QApplication a(argc, argv);
    EmojiKeyboard w;
    w.show();

    return a.exec();
}
