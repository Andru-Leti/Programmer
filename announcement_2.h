#ifndef ANNOUNCEMENT_2_H
#define ANNOUNCEMENT_2_H

#include <QDialog>
#include <data_base_2.h>

namespace Ui {
class announcement_2;
}

class announcement_2 : public QDialog
{
    Q_OBJECT

public:
    explicit announcement_2(const Job &job, QWidget *parent = nullptr);
    ~announcement_2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::announcement_2 *ui;
};

#endif // ANNOUNCEMENT_2_H
