#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QFile>
#include <QStringList>
#include <QFontDatabase>
#include <QSound>
#include <QDir>
#include <QHBoxLayout>
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "windows.h"
#include "clickablelabel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    gamewindow *window3;

    QList<QRect> positions;
    QList<int> random;
    QList<QLabel *> people;
    QList<QPushButton *> games;

    QList<int> game_id;
    QList<int> min;
    QList<int> sec;
    QList<QString> game_name;
    QList<QString> game_body;
    int score1, score2, ramzan_counter, klokov_counter, petrik_counter, gunya_counter, nikita_counter, lesha_counter, anya_counter, drozd_counter, koshka_counter, inna_counter;
    QString filePath;
    bool angelina_flag, ksysha_flag, petrik_flag, gunya_flag, nikita_flag, lesha_flag, anya_flag, drozd_flag, elina_flag, inna_flag;

private:
    Ui::MainWindow *ui;

public slots:
    void change_people(void);
    void pBtn_game(void);
    void pBtn_exit(void);
    void open_game(int);
    void change_score(void);
    void score_null(void);
    void sound(void);
    void start_sound(void);
    void ramzan(void);
    void ksysha(void);
    void angelina(void);
    void klokov(void);
    void petrik(void);
    void gunya(void);
    void nikita(void);
    void lesha(void);
    void anya(void);
    void drozd(void);
    void elina(void);
    void inna(void);

signals:
    void ongamewindow(int);
    void stop_sound(void);
    void start_music(void);
};
#endif // MAINWINDOW_H
