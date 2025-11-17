#include "announcement.h"
#include "ui_announcement.h"
#include <bulletin_board.h>
#include <data_base_2.h>
#include <QDebug>

announcement::announcement(const Job &job, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::announcement)
{
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

announcement::~announcement()
{
    delete ui;
}


