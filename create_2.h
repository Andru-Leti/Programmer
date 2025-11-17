#ifndef CREATE_2_H
#define CREATE_2_H

#include <QDialog>

namespace Ui {
class create_2;
}

class create_2 : public QDialog
{
    Q_OBJECT

public:
    explicit create_2(QWidget *parent = nullptr);
    ~create_2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::create_2 *ui;
    static QMap<QString, QStringList> metroStation;
    void onBranchChang();
    void updateStation();

};

#endif // CREATE_2_H
