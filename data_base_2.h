#ifndef DATA_BASE_2_H
#define DATA_BASE_2_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Data_base_2;
}

class Data_base_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Data_base_2(QWidget *parent = nullptr);
    ~Data_base_2();

private:
    Ui::Data_base_2 *ui;
};
#include <QString>
#include <QList>

struct User {
    int id;
    QString login;
    QString password;
    int adsCount;
    QList<int> adsIds;
};

struct Job {
    int id;
    QString type;
    int cost;
    int hours;
    QString metroStation;
    QString address;
    QString phone;
    int userId;
};

extern QList<Job> jobs;
extern const QString jobsFilename;

extern QList<User> users;
extern User g_currentUser;
void loadJobs();
void saveJobs();
extern int count;

extern QStringList red_line;
extern QStringList blue_line;
extern QStringList green_line;
extern QStringList orange_line;
extern QStringList purple_line;

#endif // DATA_BASE_2_H
