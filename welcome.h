#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include "mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QMultimedia>
#include <QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QSound>
#include <QSoundEffect>

namespace Ui {
class welcome;
}

class welcome : public QWidget
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();
    MainWindow *window2;
    float alpha;
    int center_x, center_y;
    QRect final_position;
    bool command_flag;
    QList<QRect> positions;
    QList<QLabel *> people;
    int counter, counter_ready, ramzan_counter, klokov_counter, petrik_counter, gunya_counter, nikita_counter, lesha_counter, anya_counter, drozd_counter, koshka_counter, inna_counter;
    QList<int> random;
    Ui::welcome *ui;
    QMediaPlayer player;
    QMediaPlaylist *playlist;
    QString filePath;
    bool moveflag, sound_flag;
    bool angelina_flag, ksysha_flag, petrik_flag, gunya_flag, nikita_flag, lesha_flag, anya_flag, drozd_flag, elina_flag, inna_flag;


private:
    QTimer *pTimer_W;

public slots:
    void Timer_W_timeout(void);
    void pBtn_command(void);
    void pBtn_exit(void);
    void pBtn_start(void);
    void stop_sound(void);
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
};

#endif // WELCOME_H
