#include "announcement_2.h"
#include "ui_announcement_2.h"
#include <bulletin_board.h>
#include <data_base_2.h>
#include <QDebug>

announcement_2::announcement_2(const Job &job, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::announcement_2)
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->type_job->setText(QString("%1").arg(job.type));
    ui->type_job->setReadOnly(true); // Запрещаем редактирование

    ui->cost_job->setText(QString("%1").arg(job.cost));
    ui->cost_job->setReadOnly(true);

    ui->hour_job->setText(QString("%1 ч.").arg(job.hours));
    ui->hour_job->setReadOnly(true);

    ui->station_job->setText(QString("%1").arg(job.metroStation));
    ui->station_job->setReadOnly(true);

    ui->addres_job->setText(QString("%1").arg(job.address));
    ui->addres_job->setReadOnly(true);

    ui->phone_job->setText(QString("%1").arg(job.phone));
    ui->phone_job->setReadOnly(true);

    if(g_currentUser.id == job.userId){ ui->uuser->setText("Это Ваше объявление!");}
}

announcement_2::~announcement_2()
{
    delete ui;
}




void announcement_2::on_pushButton_clicked()
{
    this->close();
}

