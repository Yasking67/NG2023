#include "mainwindow.h"
#include "welcome.h"
#include "ui_welcome.h"
#include "gamewindow.h"
#include <QFontDatabase>
#include <QMultimedia>
#include <QtMultimedia/QMediaPlayer>

#include <QApplication>

//test

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filePath = QDir::currentPath();

    int id = QFontDatabase::addApplicationFont(filePath + "/ofont.ru_Appetite.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    monospace.setPointSize(19);

    welcome hello;
    hello.setWindowIcon(QIcon(filePath + "/balloon.png"));

    hello.ui->pushButton_command->setFont(monospace);
    hello.ui->pushButton_start->setFont(monospace);
    hello.ui->pushButton_exit->setFont(monospace);

    hello.setWindowState(Qt::WindowFullScreen);
    hello.show();

//    MainWindow test;
//    test.setWindowState(Qt::WindowFullScreen);
//    test.show();


    return a.exec();
}
