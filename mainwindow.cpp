#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "registration.h"
#include "bulletin_board.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>
#include "data_base_2.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const QString filename = "C:/Users/user/Desktop/untitled/password.txt";

void loadUsers() {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {  // QIODevice::ReadOnly - открывает файл для чтения
        qDebug() << "Файл не найден";
        return;
    }

    users.clear();  // Очистка users, чтобы записать новые данные
    QByteArray line = file.readLine();
    int count = QString::fromUtf8(line).toInt();

    while (count-- && !file.atEnd()) {
        line = file.readLine();
        QStringList parts = QString::fromUtf8(line).split(',');

        if (parts.size() >= 5) {
            User user;
            user.id = parts[0].toInt();
            user.login = parts[1];
            user.password = parts[2];
            user.adsCount = parts[3].toInt();

            if (parts[4] != "0") {
                QStringList ids = parts[4].split(';');
                for (const QString &id : ids) {
                    user.adsIds.append(id.toInt());
                }
            }
            users.append(user);
        }
    }
    file.close();
}


void saveUsers() {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {  // Открыл файл для записи
        qDebug() << "Ошибка сохранения данных";
        return;
    }

    QString data = QString::number(users.count()) + "\n";   // QString::number преобразует int в QString
    file.write(data.toUtf8());

    for (const User &user : users) {
        QString userData = userData.asprintf("%d,%s,%s,%d,",      //asprintf - возвращает Qstring
                          user.id,
                          user.login.toUtf8().constData(),
                          user.password.toUtf8().constData(),
                          user.adsCount
                          );

        if (user.adsIds.isEmpty()) {           // isEmpty возвращает true, если строка QString не содержит ни одного символа, иначе — false
            userData += "0\n";
        } else {
            for (int i = 0; i < user.adsIds.size(); ++i) {
                if (i > 0) userData += ";"; { userData += QString::number(user.adsIds[i]); }
            }
            userData += "\n";}
        // Записываю строку о пользователе
        file.write(userData.toUtf8());
    }
    file.close();
}

void MainWindow::on_ent_clicked()
{
    loadUsers();

    QString inputLogin = ui->log->text().trimmed();
    QString inputPassword = ui->pas->text().trimmed();

    if(inputLogin.isEmpty() || inputPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    // Проверяем существование пользователя
    bool authSuccess = false;
    for(const User &user : users) {
        if(user.login == inputLogin && user.password == inputPassword) {
            authSuccess = true;
            g_currentUser = user;
            break;
        }
    }

    if(authSuccess) {
        QMessageBox::information(this, "Успех", "Авторизация прошла успешно!");
        saveUsers();
        bulletin_board window;
        window.setModal(true);
        window.exec();

    } else {
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль!");
    }
}


void MainWindow::on_regist_clicked()
{
    Registration window;
    window.setModal(true);
    window.exec();
}

