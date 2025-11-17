#include "create_2.h"
#include "ui_create_2.h"
#include "data_base_2.h"
#include "bulletin_board.h"
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QMessageBox>


QMap<QString, QStringList> create_2::metroStation;

void create_2::onBranchChang() {
    QComboBox* branchComboBox = ui->color_st;
    QComboBox* stationComboBox = ui->stat;

    QString selectedBranch = branchComboBox->currentText();
    stationComboBox->clear();

    if (metroStation.contains(selectedBranch)) {
        stationComboBox->addItems(metroStation[selectedBranch]);
    }
}

create_2::create_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_2)
{
    ui->setupUi(this);
    metroStation["Красная ветка"] = red_line;
    metroStation["Синяя ветка"] = blue_line;
    metroStation["Зелёная ветка"] = green_line;
    metroStation["Оранжевая ветка"] = orange_line;
    metroStation["Фиолетовая ветка"] = purple_line;

    QComboBox* branchComboBox = ui->color_st;

    onBranchChang();

    connect(branchComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &create_2::onBranchChang);
}

create_2::~create_2()
{
    delete ui;
}

void create_2::on_pushButton_clicked()
{
    bool costOk;
    int costValue = ui->cost->text().toInt(&costOk);
    if (!costOk || costValue <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректную стоимость (число больше 0)");
        return;
    }

    // Проверка телефона
    QString phone = ui->phone->text().replace(" ", "").replace("-", "").replace("(", "").replace(")", "");
    if (!phone.startsWith("+7") && !phone.startsWith("8")) {
        QMessageBox::warning(this, "Ошибка", "Номер должен начинаться с +7 или 8");
        return;
    }

    if ((phone.startsWith("+7") && phone.length() != 12) ||
        (phone.startsWith("8") && phone.length() != 11)) {
        QMessageBox::warning(this, "Ошибка", "Некорректная длина номера");
        return;
    }

    loadJobs();
    Job newJob;

    newJob.id = ++count;

    newJob.type = ui->type->currentText();
    newJob.cost = costValue;
    newJob.hours = ui->time->currentText().toInt();
    newJob.metroStation = ui->stat->currentText();
    newJob.address = ui->addres->text().replace(",", "").trimmed();
    newJob.phone = phone;
    newJob.userId = g_currentUser.id;
    g_currentUser.adsCount++;
    g_currentUser.adsIds.append(newJob.id);

    jobs.append(newJob);
    saveJobs();

    qDebug() << "Объявление успешно создано! ID:" << newJob.id;
    obnov = 1;
    this->close();
}

