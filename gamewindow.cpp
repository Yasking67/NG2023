#include "gamewindow.h"
#include "ui_gamewindow.h"

gamewindow::gamewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);

    filePath = QDir::currentPath();

    int id = QFontDatabase::addApplicationFont(filePath + "/ofont.ru_Appetite.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    monospace.setPointSize(17);

    ui->pushButton_start->setFont(monospace);
    ui->pushButton_pause->setFont(monospace);
    ui->label_body->setFont(monospace);
    monospace.setPointSize(14);
    ui->pushButton_new->setFont(monospace);
    ui->pushButton_exit->setFont(monospace);

    monospace.setPointSize(35);
    ui->pushButton_plus1->setFont(monospace);
    ui->pushButton_plus2->setFont(monospace);
    ui->pushButton_minus1->setFont(monospace);
    ui->pushButton_minus2->setFont(monospace);
    ui->lineEdit_score1->setFont(monospace);
    ui->lineEdit_score2->setFont(monospace);
    ui->label_name->setFont(monospace);
    monospace.setPointSize(70);
    ui->lineEdit_timer->setFont(monospace);


    pTimer_W = new QTimer();
    pTimer_W->setInterval(1000);
    pTimer_W->start();

    timer_flag = false;

    start_min = 1;
    start_sec = 0;
    score1 = 0; score2 = 0;

    connect(pTimer_W, SIGNAL(timeout()), this, SLOT(update_timer()));
    connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(pBtn_exit()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(pBtn_start()));
    connect(ui->pushButton_pause, SIGNAL(clicked()), this, SLOT(pBtn_pause()));
    connect(ui->pushButton_new, SIGNAL(clicked()), this, SLOT(pBtn_new()));
    connect(ui->pushButton_plus1, SIGNAL(clicked()), this, SLOT(pBtn_plus1()));
    connect(ui->pushButton_minus1, SIGNAL(clicked()), this, SLOT(pBtn_minus1()));
    connect(ui->pushButton_plus2, SIGNAL(clicked()), this, SLOT(pBtn_plus2()));
    connect(ui->pushButton_minus2, SIGNAL(clicked()), this, SLOT(pBtn_minus2()));
    connect(ui->label_21, SIGNAL(clicked()), this, SLOT(ramzan()));
    connect(ui->label_24, SIGNAL(clicked()), this, SLOT(ksysha()));
    connect(ui->label_18, SIGNAL(clicked()), this, SLOT(angelina()));
    connect(ui->label_23, SIGNAL(clicked()), this, SLOT(klokov()));
    connect(ui->label_25, SIGNAL(clicked()), this, SLOT(petrik()));
    connect(ui->label_26, SIGNAL(clicked()), this, SLOT(gunya()));
    connect(ui->label_15, SIGNAL(clicked()), this, SLOT(nikita()));
    connect(ui->label_20, SIGNAL(clicked()), this, SLOT(lesha()));
    connect(ui->label_17, SIGNAL(clicked()), this, SLOT(drozd()));
    connect(ui->label_22, SIGNAL(clicked()), this, SLOT(anya()));
    connect(ui->label_19, SIGNAL(clicked()), this, SLOT(elina()));
    connect(ui->label_16, SIGNAL(clicked()), this, SLOT(inna()));

    ui->lineEdit_score1->setValidator( new QIntValidator(0, 10, this) );
    ui->lineEdit_score2->setValidator( new QIntValidator(0, 10, this) );

    positions = {QRect(1420,100,175,175),QRect(1670,100,175,175),QRect(1420,325,175,175),QRect(1670,325,175,175),QRect(1420,550,175,175),QRect(1670,550,175,175),
                QRect(50,100,175,175),QRect(300,100,175,175),QRect(50,325,175,175),QRect(300,325,175,175),QRect(50,550,175,175),QRect(300,550,175,175)};

    people = {ui->label_15, ui->label_16, ui->label_17, ui->label_18, ui->label_19, ui->label_20,
              ui->label_21, ui->label_22, ui->label_23, ui->label_24, ui->label_25, ui->label_26};

    random = {0,1,2,3,4,5,6,7,8,9,10,11};

    ramzan_counter = 1; klokov_counter = 1; petrik_counter = 1; gunya_counter = 1; nikita_counter=1; lesha_counter = 1; drozd_counter = 1; anya_counter = 1; koshka_counter = 1; inna_counter = 1;
    angelina_flag = true; ksysha_flag = true, petrik_flag = true; gunya_flag = true; nikita_flag = true; lesha_flag = true; drozd_flag = true; anya_flag = true; elina_flag = true; inna_flag = true;
}

gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::pBtn_exit()
{
    QSound::play(filePath + "/button.wav");
    this->hide();
    timer_flag = false;
    emit close_window();
}

void gamewindow::pBtn_start()
{
    QSound::play(filePath + "/button.wav");
    timer_flag = true;
    if (cur_min == start_min && cur_sec == start_sec)
    {
        QSound::play(filePath + "/horn.wav");
    }
}

void gamewindow::pBtn_pause()
{
    timer_flag = false;
    QSound::play(filePath + "/button.wav");
}

void gamewindow::pBtn_new()
{
    QString input;
    timer_flag = false;
    cur_min = start_min;
    cur_sec = start_sec;
    if (cur_min < 10 && cur_sec < 10) {input = "0" + QString::number(cur_min) + ":" + "0" + QString::number(cur_sec);}
    if (cur_min < 10 && cur_sec >= 10) {input = "0" + QString::number(cur_min) + ":" + QString::number(cur_sec);}
    if (cur_min >= 10 && cur_sec < 10) {input = QString::number(cur_min) + ":" + "0" + QString::number(cur_sec);}
    if (cur_min >= 10 && cur_sec >= 10) {input = QString::number(cur_min) + ":" + QString::number(cur_sec);}
    ui->lineEdit_timer->setText(input);
}

void gamewindow::pBtn_plus1()
{
    QSound::play(filePath + "/button.wav");
    QString input = ui->lineEdit_score1->text();
    score1 = input.toInt();
    score1 += 1;
    ui->lineEdit_score1->setText(QString::number(score1));

}

void gamewindow::pBtn_minus1()
{
    QSound::play(filePath + "/button.wav");
    QString input = ui->lineEdit_score1->text();
    score1 = input.toInt();
    score1 -= 1;
    if (score1 < 0){score1 = 0;}
    ui->lineEdit_score1->setText(QString::number(score1));
}

void gamewindow::pBtn_plus2()
{
    QSound::play(filePath + "/button.wav");
    QString input = ui->lineEdit_score2->text();
    score2 = input.toInt();
    score2 += 1;
    ui->lineEdit_score2->setText(QString::number(score2));
}

void gamewindow::pBtn_minus2()
{
    QSound::play(filePath + "/button.wav");
    QString input = ui->lineEdit_score2->text();
    score2 = input.toInt();
    score2 -= 1;
    if (score2 < 0){score2 = 0;}
    ui->lineEdit_score2->setText(QString::number(score2));
}

void gamewindow::update_timer()
{
    if (timer_flag == true)
    {
        QString input = ui->lineEdit_timer->text();
        cur_min = input.split(":")[0].toInt();
        cur_sec = input.split(":")[1].toInt();
        cur_sec = cur_sec - 1;
        if (cur_sec < 0)
        {
            cur_min = cur_min - 1;
            if (cur_min >= 0)
            {
                cur_sec = 59;
            }
            else {cur_min = 0; cur_sec = 0;}
        }
        if (cur_min == 0 && cur_sec == 20) {QSound::play(filePath + "/MusicTik.wav");}
        if (cur_min < 10 && cur_sec < 10) {input = "0" + QString::number(cur_min) + ":" + "0" + QString::number(cur_sec);}
        if (cur_min < 10 && cur_sec >= 10) {input = "0" + QString::number(cur_min) + ":" + QString::number(cur_sec);}
        if (cur_min >= 10 && cur_sec < 10) {input = QString::number(cur_min) + ":" + "0" + QString::number(cur_sec);}
        if (cur_min >= 10 && cur_sec >= 10) {input = QString::number(cur_min) + ":" + QString::number(cur_sec);}
        ui->lineEdit_timer->setText(input);
//        qDebug() << input << " " << cur_min << " " << cur_sec;
    }
}

void gamewindow::change_people()
{
    int i = 0;
    while(i < 12)
    {
        people[i]->setGeometry(positions[random[i]]);
        i++;
    }

}

void gamewindow::ramzan()
{
    QSound::play(filePath + "/ramzan" + QString::number(ramzan_counter) + ".wav");
    ramzan_counter++;
    if (ramzan_counter == 6) {ramzan_counter = 1;}

}

void gamewindow::ksysha()
{
    if (ksysha_flag == true)
    {
        QSound::play(filePath + "/Koshka" + QString::number(koshka_counter) + ".wav");
        QPixmap mypix (filePath + "/Mika.png");
        ui->label_24->setPixmap(mypix);
        ksysha_flag = false;
        koshka_counter++;
        if (koshka_counter == 8) {koshka_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Ksyusha.png");
        ui->label_24->setPixmap(mypix);
        ksysha_flag = true;
    }

}

void gamewindow::angelina()
{
    if (angelina_flag == true)
    {
        QSound::play(filePath + "/Koshka" + QString::number(koshka_counter) + ".wav");
        QPixmap mypix (filePath + "/Astra.png");
        ui->label_18->setPixmap(mypix);
        angelina_flag = false;
        koshka_counter++;
        if (koshka_counter == 8) {koshka_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Angelina.png");
        ui->label_18->setPixmap(mypix);
        angelina_flag = true;
    }
}

void gamewindow::klokov()
{
    QSound::play(filePath + "/Lesha" + QString::number(klokov_counter) + ".wav");
    klokov_counter++;
    if (klokov_counter == 7) {klokov_counter = 1;}
}

void gamewindow::petrik()
{
    if (petrik_flag == true)
    {
        QSound::play(filePath + "/Petrik" + QString::number(petrik_counter) + ".wav");
        QPixmap mypix (filePath + "/Petrik2.png");
        ui->label_25->setPixmap(mypix);
        petrik_flag = false;
        petrik_counter++;
        if (petrik_counter == 5) {petrik_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Petrik.png");
        ui->label_25->setPixmap(mypix);
        petrik_flag = true;
    }
}

void gamewindow::gunya()
{
    if (gunya_flag == true)
    {
        QSound::play(filePath + "/Gunya" + QString::number(gunya_counter) + ".wav");
        QPixmap mypix (filePath + "/GunyaFat.png");
        ui->label_26->setPixmap(mypix);
        gunya_flag = false;
        gunya_counter++;
        if (gunya_counter == 5) {gunya_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Gunya.png");
        ui->label_26->setPixmap(mypix);
        gunya_flag = true;
    }
}

void gamewindow::nikita()
{
    if (nikita_flag == true)
    {
        QSound::play(filePath + "/Nikita" + QString::number(nikita_counter) + ".wav");
        QPixmap mypix (filePath + "/NikitaNG.png");
        ui->label_15->setPixmap(mypix);
        nikita_flag = false;
        nikita_counter++;
        if (nikita_counter == 4) {nikita_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Nikita.png");
        ui->label_15->setPixmap(mypix);
        nikita_flag = true;
    }
}

void gamewindow::lesha()
{
    if (lesha_flag == true)
    {
        QSound::play(filePath + "/Klokov" + QString::number(lesha_counter) + ".wav");
        QPixmap mypix (filePath + "/LeshaHm.png");
        ui->label_20->setPixmap(mypix);
        lesha_flag = false;
        lesha_counter++;
        if (lesha_counter == 4) {lesha_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Lesha2.png");
        ui->label_20->setPixmap(mypix);
        lesha_flag = true;
    }
}

void gamewindow::drozd()
{
    if (drozd_flag == true)
    {
        QSound::play(filePath + "/Drozd" + QString::number(drozd_counter) + ".wav");
        QPixmap mypix (filePath + "/DrozdRacoon.png");
        ui->label_17->setPixmap(mypix);
        drozd_flag = false;
        drozd_counter++;
        if (drozd_counter == 6) {drozd_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Drozd.png");
        ui->label_17->setPixmap(mypix);
        drozd_flag = true;
    }
}

void gamewindow::anya()
{
    if (anya_flag == true)
    {
        QSound::play(filePath + "/Anya" + QString::number(anya_counter) + ".wav");
        QPixmap mypix (filePath + "/AnyaBaby.png");
        ui->label_22->setPixmap(mypix);
        anya_flag = false;
        anya_counter++;
        if (anya_counter == 5) {anya_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Anya.png");
        ui->label_22->setPixmap(mypix);
        anya_flag = true;
    }
}

void gamewindow::elina()
{
    if (elina_flag == true)
    {
        QSound::play(filePath + "/Koshka" + QString::number(koshka_counter) + ".wav");
        QPixmap mypix (filePath + "/Koshka.png");
        ui->label_19->setPixmap(mypix);
        elina_flag = false;
        koshka_counter++;
        if (koshka_counter == 8) {koshka_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Elina.png");
        ui->label_19->setPixmap(mypix);
        elina_flag = true;
    }
}

void gamewindow::inna()
{
    if (inna_flag == true)
    {
        QSound::play(filePath + "/Chemistry" + QString::number(inna_counter) + ".wav");
        QPixmap mypix (filePath + "/Chemistry.png");
        ui->label_16->setPixmap(mypix);
        inna_flag = false;
        inna_counter++;
        if (inna_counter == 4) {inna_counter = 1;}
    }
    else
    {
        QPixmap mypix (filePath + "/Inna.png");
        ui->label_16->setPixmap(mypix);
        inna_flag = true;
    }
}
