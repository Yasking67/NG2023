#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include <QIntValidator>
#include <QDebug>
#include <QDir>
#include <QSound>
#include <QFontDatabase>
#include <QLabel>

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
    ~gamewindow();
    Ui::gamewindow *ui;
    bool timer_flag;
    int start_min, start_sec;
    int cur_min, cur_sec;
    int score1, score2, ramzan_counter, klokov_counter, petrik_counter, gunya_counter, nikita_counter, lesha_counter, anya_counter, drozd_counter, koshka_counter, inna_counter;
    QString filePath;
    QList<QLabel *> people;
    QList<QRect> positions;
    QList<int> random;
    bool angelina_flag, ksysha_flag, petrik_flag, gunya_flag, nikita_flag, lesha_flag, anya_flag, drozd_flag, elina_flag, inna_flag;

private:
    QTimer *pTimer_W;

public slots:
    void pBtn_exit(void);
    void pBtn_start(void);
    void pBtn_pause(void);
    void pBtn_new(void);
    void pBtn_plus1(void);
    void pBtn_minus1(void);
    void pBtn_plus2(void);
    void pBtn_minus2(void);
    void update_timer(void);
    void change_people(void);
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
    void close_window();
};

#endif // GAMEWINDOW_H
