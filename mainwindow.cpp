#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filePath = QDir::currentPath();

    int id = QFontDatabase::addApplicationFont(filePath + "/ofont.ru_Appetite.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    monospace.setPointSize(17);


    game_id = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    min = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    sec = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    game_name = {"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
    game_body = {"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};

//    QFile file("D:/Work/Qt_test_files/NG2023/games.csv");
    QFile file("games.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    int i = 0;

    QTextStream in(&file);
    in.setCodec("ANSI");
    while (!in.atEnd()) {
        QString line = in.readLine();
        game_id[i] = (line.split(';')[0].toInt());
        min[i] = (line.split(';')[1].toInt());
        sec[i] = (line.split(';')[2].toInt());
        game_name[i] = (line.split(';')[3]);
        game_body[i] = (line.split(';')[4]);
//        qDebug() << game_id[i] <<  min[i] << sec[i] << game_name[i] << game_body[i];
        i++;
    }



    window3 = new gamewindow();
    window3->setWindowIcon(QIcon(filePath + "/balloon.png"));
    window3->setWindowState(Qt::WindowFullScreen);

    games = {ui->pushButton_0, ui->pushButton_1, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4,
            ui->pushButton_5, ui->pushButton_6, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9,
            ui->pushButton_10, ui->pushButton_11, ui->pushButton_12, ui->pushButton_13, ui->pushButton_14,
            ui->pushButton_15, ui->pushButton_16, ui->pushButton_17, ui->pushButton_18, ui->pushButton_19,
            ui->pushButton_20, ui->pushButton_21, ui->pushButton_22, ui->pushButton_23, ui->pushButton_24};

    i =0;
    while(i < 25)
    {
        connect(games[i], SIGNAL(pressed()), this, SLOT(sound()));
        connect(games[i], SIGNAL(clicked()), this, SLOT(pBtn_game()));
        games[i]->setFont(monospace);
        i++;
    }

    ui->pushButton_26->setFont(monospace);
    ui->pushButton_exit->setFont(monospace);
    monospace.setPointSize(40);
    ui->label_5->setFont(monospace);
    ui->label_2->setFont(monospace);
    ui->lineEdit_score1->setFont(monospace);
    ui->lineEdit_score2->setFont(monospace);

    connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(pBtn_exit()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(score_null()));
    connect(this, SIGNAL(ongamewindow(int)), this, SLOT(open_game(int)));
    connect(window3->ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(change_score()));
    connect(window3, SIGNAL(close_window()), this, SLOT (start_sound()));
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


    positions = {QRect(0,0,150,150),QRect(110,150,150,150),QRect(0,300,150,150),QRect(110,450,150,150),QRect(0,600,150,150),QRect(110,750,150,150),
                QRect(0,0,150,150),QRect(110,150,150,150),QRect(0,300,150,150),QRect(110,450,150,150),QRect(0,600,150,150),QRect(110,750,150,150)};

    people = {ui->label_15, ui->label_16, ui->label_17, ui->label_18, ui->label_19, ui->label_20,
              ui->label_21, ui->label_22, ui->label_23, ui->label_24, ui->label_25, ui->label_26};


    random = {0,1,2,3,4,5,6,7,8,9,10,11};

    i = 0;
    while(i < 12)
    {
        people[i]->setGeometry(positions[random[i]]);
        i++;
    }

    score1 = 0; score2 = 0; ramzan_counter = 1; klokov_counter = 1; petrik_counter = 1; gunya_counter = 1; nikita_counter=1; lesha_counter = 1; drozd_counter = 1; anya_counter = 1; koshka_counter = 1; inna_counter = 1;
    angelina_flag = true; ksysha_flag = true, petrik_flag = true; gunya_flag = true; nikita_flag = true; lesha_flag = true; drozd_flag = true; anya_flag = true; elina_flag = true; inna_flag = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_people()
{
    int i = 0;
    while(i < 12)
    {
        if (random[i] < 6)
        {
            people[i]->setParent(ui->frame_2);
        }
        else {people[i]->setParent(ui->frame);}
        people[i]->setGeometry(positions[random[i]]);
        i++;
    }

}

void MainWindow::pBtn_game()
{
    emit stop_sound();
    int lmmn = 0;
    QPushButton *pPushButton = qobject_cast<QPushButton *>(sender());
    for (lmmn = 0; lmmn < 25; lmmn++)
        if (pPushButton == games[lmmn])
        {
            emit ongamewindow(lmmn);
            games[lmmn]->setStyleSheet("border-image: url(:/фоны/button12Gray.png) 0 0 0 0 stretch stretch;");
        }


//    window3->show();
//    qDebug() << index;
}

void MainWindow::open_game(int id)
{
    window3->ui->label_name->setText(game_name[id]);
    window3->ui->label_body->setText(game_body[id]);

    window3->score1 = 0;
    window3->score2 = 0;
    window3->ui->lineEdit_score1->setText(QString::number(window3->score1));
    window3->ui->lineEdit_score2->setText(QString::number(window3->score2));

    window3->start_min = min[id];
    window3->start_sec = sec[id];
    window3->pBtn_new();

    window3->random = random;
    window3->change_people();

//    games[id]->setEnabled(false);

    window3->show();
}

void MainWindow::pBtn_exit()
{
    QSound::play(filePath + "/button.wav");
//    QApplication::quit();
    this->hide();
}

void MainWindow::change_score()
{
    score1 = score1 + window3->score1;
    score2 = score2 + window3->score2;
    ui->lineEdit_score1->setText(QString::number(score1));
    ui->lineEdit_score2->setText(QString::number(score2));
}

void MainWindow::score_null()
{
    QSound::play(filePath + "/button.wav");

    score1 = 0;
    score2 = 0;
    ui->lineEdit_score1->setText(QString::number(score1));
    ui->lineEdit_score2->setText(QString::number(score2));
}

void MainWindow::sound()
{
    QSound::play(filePath + "/button.wav");
}

void MainWindow::start_sound()
{
    emit start_music();
}

void MainWindow::ramzan()
{
    QSound::play(filePath + "/ramzan" + QString::number(ramzan_counter) + ".wav");
    ramzan_counter++;
    if (ramzan_counter == 6) {ramzan_counter = 1;}

}

void MainWindow::ksysha()
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

void MainWindow::angelina()
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

void MainWindow::klokov()
{
    QSound::play(filePath + "/Lesha" + QString::number(klokov_counter) + ".wav");
    klokov_counter++;
    if (klokov_counter == 7) {klokov_counter = 1;}
}

void MainWindow::petrik()
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

void MainWindow::gunya()
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

void MainWindow::nikita()
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

void MainWindow::lesha()
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

void MainWindow::drozd()
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

void MainWindow::anya()
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

void MainWindow::elina()
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

void MainWindow::inna()
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
