#include "welcome.h"
#include "ui_welcome.h"
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDir>



welcome::welcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);

    filePath = QDir::currentPath();

//    playlist->addMedia(QUrl::fromLocalFile(filePath + "/welcome.wav"));

    player.setMedia(QUrl::fromLocalFile(filePath + "/welcome.wav"));
//    player.setMedia(QUrl::fromLocalFile(filePath + "/test2.wav"));
    player.setVolume(50);
    player.play();


    window2 = new MainWindow();
    window2->setWindowIcon(QIcon(filePath + "/balloon.png"));
    window2->setWindowState(Qt::WindowFullScreen);
//    window2->show();

    pTimer_W = new QTimer();
    pTimer_W->setInterval(30);
    pTimer_W->start();

    command_flag = false;
    sound_flag = true;
    moveflag = true;
    counter_ready = 0;

    connect(pTimer_W, SIGNAL(timeout()), this, SLOT(Timer_W_timeout()));
    connect(ui->pushButton_command, SIGNAL(clicked()), this, SLOT(pBtn_command()));
    connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(pBtn_exit()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(pBtn_start()));
    connect(window2, SIGNAL(stop_sound()), this, SLOT(stop_sound()));
    connect(window2, SIGNAL(start_music()), this, SLOT(start_sound()));
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
//    connect(this, SIGNAL(player.currentMediaChanged(const QMediaContent &media)), this, SLOT(pBtn_start()));

    alpha = 0;


    center_x = ui->pushButton_start->x() + (ui->pushButton_start->width() / 2);
    center_y = ui->pushButton_start->y() + (ui->pushButton_start->height() / 2);

    positions = {QRect(1350,0,200,200),QRect(1350,230,200,200),QRect(1350,460,200,200),QRect(1650,0,200,200),QRect(1650,230,200,200),QRect(1650,460,200,200),
                 QRect(50,0,200,200),QRect(50,230,200,200),QRect(50,460,200,200),QRect(350,0,200,200),QRect(350,230,200,200),QRect(350,460,200,200)};

    people = {ui->label_15, ui->label_16, ui->label_17, ui->label_18, ui->label_19, ui->label_20,
              ui->label_21, ui->label_22, ui->label_23, ui->label_24, ui->label_25, ui->label_26};

    counter = 0;

    random = {15,15,15,15,15,15,15,15,15,15,15,15};

    ramzan_counter = 1; klokov_counter = 1; petrik_counter = 1; gunya_counter = 1; nikita_counter=1; lesha_counter = 1; drozd_counter = 1; anya_counter = 1; koshka_counter = 1; inna_counter = 1;
    angelina_flag = true; ksysha_flag = true, petrik_flag = true; gunya_flag = true; nikita_flag = true; lesha_flag = true; drozd_flag = true; anya_flag = true; elina_flag = true; inna_flag = true;

}

welcome::~welcome()
{
    delete ui;
}

void welcome::Timer_W_timeout()
{  
    if (command_flag == false)
    {
        alpha += 0.012;
        int i = 0;
        while(i < 12)
        {
            people[i]->setGeometry(QRect((300 * qCos(alpha + (i * M_PI / 6)) + center_x - (people[i]->width() / 2)), ((300 * qSin(alpha + (i * M_PI / 6)) + center_y - (people[i]->height() / 2))), 130, 130));
            i++;
        }
    }
    if (command_flag == true)
    {
        if (moveflag == true)
        {
            QSound::play(filePath + "/move.wav");
            moveflag = false;
        }
        alpha += 0.012;
        QLabel *my_label = people[counter];
//        my_label->setDisabled(true);
        final_position = positions[random[counter]];
        float distance_x = final_position.x() - my_label->x();
        float distance_y = final_position.y() - my_label->y();
        float width = final_position.width() - my_label->width();
        float height = final_position.height() - my_label->height();
        my_label->setGeometry(QRect(my_label->x() + distance_x / 15, my_label->y() + distance_y / 10, my_label->width() + width / 10, my_label->height() + height / 10));

        if (qFabs(distance_x) < 15 && counter < 11)
        {
            counter += 1;
            moveflag = true;
        }
        int i = counter + 1;
        while(i < 12)
        {
            people[i]->setGeometry(QRect((300 * qCos(alpha + (i * M_PI / 6)) + center_x - (people[i]->width() / 2)), ((300 * qSin(alpha + (i * M_PI / 6)) + center_y - (people[i]->height() / 2))), 130, 130));
            i++;
        }
    }
    if (counter_ready > 0)
    {
        counter_ready++;
        if (counter_ready > 40)
        {
            ui->pushButton_start->setText("Начать игру");
            ui->pushButton_start->setStyleSheet("color : white");
            counter_ready = 0;
        }
    }

//    qint64 time = player.duration();
//    qDebug() << time;
    if (sound_flag == true) {player.play();}
}

void welcome::pBtn_command()
{
    QSound::play(filePath + "/button.wav");
    if (command_flag == true)
    {
        command_flag = false;
        counter = 0;
        random = {15,15,15,15,15,15,15,15,15,15,15,15};
        ui->pushButton_command->setText("Распределить \n команды");
    }
    else
    {
        int i = 0;
        int newitem;
        while(i < 12)
        {
            bool orig = true;
            newitem = QRandomGenerator::global()->bounded(12);
            int k = 0;
            while(k < 12)
            {
                if (random[k] == newitem)
                {
                    orig = false;
                }
                k++;
            }
            if (orig == true)
            {
                random[i] = newitem;
                i++;
            }
        }
        window2->random = random;
        command_flag = true;
        ui->pushButton_command->setText("Назад");

    }
}

void welcome::pBtn_exit()
{
    QSound::play(filePath + "/button.wav");
    QApplication::quit();
}

void welcome::pBtn_start()
{
    QSound::play(filePath + "/button.wav");
    if(counter>=11)
    {
        window2->change_people();
        window2->show();
    }
    else
    {
        ui->pushButton_start->setText("Команды \n не распределены");
        ui->pushButton_start->setStyleSheet("color : red");
        counter_ready = 1;
    }
}

void welcome::stop_sound()
{
    player.stop();
    sound_flag = false;
}

void welcome::start_sound()
{
    player.play();
    sound_flag = true;
}

void welcome::ramzan()
{
    QSound::play(filePath + "/ramzan" + QString::number(ramzan_counter) + ".wav");
    ramzan_counter++;
    if (ramzan_counter == 6) {ramzan_counter = 1;}

}

void welcome::ksysha()
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

void welcome::angelina()
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

void welcome::klokov()
{
    QSound::play(filePath + "/Lesha" + QString::number(klokov_counter) + ".wav");
    klokov_counter++;
    if (klokov_counter == 7) {klokov_counter = 1;}
}

void welcome::petrik()
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

void welcome::gunya()
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

void welcome::nikita()
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

void welcome::lesha()
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

void welcome::drozd()
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

void welcome::anya()
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

void welcome::elina()
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

void welcome::inna()
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
