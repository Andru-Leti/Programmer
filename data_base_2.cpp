#include "data_base_2.h"
#include "ui_data_base_2.h"
#include <qstring.h>
#include <QFile>
#include <QDebug>
#include <QString>
#include <qfile.h>

Data_base_2::Data_base_2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Data_base_2)
{
    ui->setupUi(this);
}

Data_base_2::~Data_base_2()
{
    delete ui;
}
QList<User> users;
User g_currentUser;
QStringList red_line = {
    "Девяткино",
    "Гражданский проспект",
    "Академическая",
    "Политехническая",
    "Площадь Мужества",
    "Лесная",
    "Выборгская",
    "Площадь Ленина",
    "Чернышевская",
    "Площадь Восстания",
    "Владимирская",
    "Пушкинская",
    "Технологический институт (I)",
    "Балтийская",
    "Нарвская",
    "Кировский завод",
    "Автово",
    "Ленинский проспект",
    "Проспект Ветеранов"
};

QStringList blue_line = {
    "Парнас",
    "Проспект Просвещения",
    "Озерки",
    "Удельная",
    "Пионерская",
    "Чёрная речка",
    "Петроградская",
    "Горьковская",
    "Невский проспект",
    "Сенная площадь",
    "Технологический институт (II)",
    "Фрунзенская",
    "Московские ворота",
    "Электросила",
    "Парк Победы",
    "Московская",
    "Звёздная",
    "Купчино"
};

QStringList green_line = {
    "Беговая",
    "Зенит",
    "Приморская",
    "Василеостровская",
    "Гостиный двор",
    "Маяковская",
    "Площадь Александра Невского (I)",
    "Елизаровская",
    "Ломоносовская",
    "Пролетарская",
    "Обухово",
    "Рыбацкое",
    "Горный институт"
};

QStringList orange_line = {
    "Спасская",
    "Достоевская",
    "Лиговский проспект",
    "Площадь Александра Невского (II)",
    "Новочеркасская",
    "Ладожская",
    "Проспект Большевиков",
    "Улица Дыбенко"
};

QStringList purple_line = {
    "Комендантский проспект",
    "Старая Деревня",
    "Крестовский остров",
    "Чкаловская",
    "Спортивная",
    "Адмиралтейская",
    "Садовая",
    "Звенигородская",
    "Обводный канал",
    "Волковская",
    "Бухарестская",
    "Международная",
    "Проспект Славы",
    "Дунайская",
    "Шушары"
};

QList<Job> jobs;
const QString jobsFilename = "C:/Users/user/Desktop/untitled/posting.txt";
int count;


void loadJobs() {
    QFile file(jobsFilename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Файл с работами не найден или не может быть открыт";
        return;
    }

    jobs.clear(); // Очищаем список перед загрузкой новых данных
    QTextStream in(&file);
    in.setEncoding(QStringConverter::System);

    if (in.atEnd()) {
        file.close();
        return;
    }

    QString line = in.readLine();
    bool ok;
    count = line.toInt(&ok);

    if (!ok || count <= 0) {
        file.close();
        return;
    }


    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() >= 8) {
            Job job;
            job.id = parts[0].toInt();
            job.type = parts[1];
            job.cost = parts[2].toDouble();
            job.hours = parts[3].toInt();
            job.metroStation = parts[4];
            job.address = parts[5];
            job.phone = parts[6];
            job.userId = parts[7].toInt();

            jobs.append(job);
        }
    }

    file.close();
}

void saveJobs() {
    QFile file(jobsFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи";
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::System);

    // Записываю количество объявлений
    out << jobs.size() << "\n";

    for (const Job &job : jobs) {
        out << job.id << ","
            << job.type << ","
            << job.cost << ","
            << job.hours << ","
            << job.metroStation << ","
            << job.address << ","
            << job.phone << ","
            << job.userId << "\n";
    }

    file.close();
}
