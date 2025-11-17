#ifndef ANNOUNCEMENT_H
#define ANNOUNCEMENT_H

#include <QDialog>
#include <data_base_2.h>

namespace Ui {
class announcement;
}

class announcement : public QDialog
{
    Q_OBJECT

public:
    explicit announcement(const Job &job, QWidget *parent = nullptr);
    ~announcement();

private slots:
    void on_pushButton_clicked();

private:
    Ui::announcement *ui;
};

#endif // ANNOUNCEMENT_H
