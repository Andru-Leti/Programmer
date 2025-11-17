#include "bulletin_board.h"
#include "ui_bulletin_board.h"
#include <QLabel>
#include <QPixmap>
#include "data_base_2.h"
#include <QComboBox>
#include <QDialog>
#include "create_2.h"
#include <QFile>
#include <QTextStream>
#include <qdebug.h>
#include <QListView>
#include <QStringListModel>
#include "now.h"
#include <QMessageBox>
#include <QSlider>

QMap<QString, QStringList> bulletin_board::metroStations;
int obnov;
QStringList jobDescriptions;
QList<Job> jobs_2;
int k = 0;

bulletin_board::bulletin_board(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bulletin_board)
{
    ui->setupUi(this);

    QString imagePath = "C:/Users/user/Desktop/untitled/build/images.png";
    QPixmap pixmap(imagePath);
    ui->picture->setPixmap(pixmap.scaled(ui->picture->size(), Qt::KeepAspectRatio));
    ui->name_user->setText(g_currentUser.login);


    metroStations["Красная ветка"] = red_line;
    metroStations["Синяя ветка"] = blue_line;
    metroStations["Зелёная ветка"] = green_line;
    metroStations["Оранжевая ветка"] = orange_line;
    metroStations["Фиолетовая ветка"] = purple_line;

    QComboBox* branchComboBox = ui->color;


    onBranchChanged();

    // Подключение сигнала
    connect(branchComboBox,   // Жду изменение от branchComboBox
            QOverload<int>::of(&QComboBox::currentIndexChanged),  // Сигнал, что-то изменилось
            this,
            &bulletin_board::onBranchChanged);  // функция, которая обработает этот сигнад

    QLabel *priceLabel = ui->price;
    QSlider *priceSlider = ui->slider_price;


    priceSlider->setRange(0, 5000);  // диапазон цен
    priceSlider->setValue(0);        // начальное значение
    priceSlider->setPageStep(500);   // шаг при клике по полосе

    connect(priceSlider,
            &QSlider::valueChanged,this,  [priceLabel](int value) {       // [] лямбда функция
        priceLabel->setText(QString("Цена за работу от %1 руб.").arg(value));
    });

    QLabel *timeLabel = ui->time;
    QSlider *timeSlider = ui->slider_time;

    timeSlider->setRange(0, 6);
    timeSlider->setValue(0);
    timeSlider->setPageStep(1);

    connect(timeSlider,
            &QSlider::valueChanged, this, [timeLabel](int value) {
        timeLabel->setText(QString("Часы работы %1").arg(value));
    });


    model = new QStringListModel(this); //QStringListModel -  контейнер для хранения текстовых строк
    listView = new QListView(this);  // Создание списка для отображения данных

    listView->setModel(model); // связываю модель и список
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers); // делаю список для чтения

    listView->setStyleSheet(R"(
    QListView::item {
        border: 2px solid #0078D4; /* Голубая рамка */
        border-radius: 5px; /* Округлённые углы */
        padding: 5px; /* Внутренние поля вокруг текста */
        margin: 5px 0; /* Отступ сверху и снизу (увеличивает расстояние между элементами) */
        background-color: white; /* Цвет фона */
        min-height: 40px; /* Минимальная высота элемента */
    }

    QListView::item:selected { /* Стиль для выделенного элемента */
        background-color: #D3D3D3; /* Серый фон при выделении */
        color: black; /* Цвет текста при выделении */
    }
)");
    ui->ob->addWidget(listView);

    loadJob();
    connect(listView, &QListView::clicked, this, &bulletin_board::onJobClicked);
}

void bulletin_board::loadJob()
{
    int expectedJobCount;
    jobs_2.clear();
    jobDescriptions.clear();
    QFile file("C:/Users/user/Desktop/untitled/posting.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.setEncoding(QStringConverter::System);  // для того,что ANSI читался правильно
        QString firstLine = in.readLine().trimmed();
        expectedJobCount = firstLine.toInt();
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                QStringList parts = line.split(',');
                if (parts.size() == 8) {
                    bool btype = 0;
                    bool bstation = 0;
                    bool bhours = 0;
                    bool bprice = 0;
                    Job job;
                    job.id = parts[0].toInt();
                    job.type = parts[1];
                    if (ui->type->currentText() == "Без фильтров"){btype = 1;}
                    else if(ui->type->currentText() == job.type){btype = 1;}
                    else {btype = 0;}

                    job.cost = parts[2].toInt();
                    if (ui->slider_price->value() == 0){bprice = 1;}
                    else if (job.cost >= ui->slider_price->value()){bprice = 1;}
                    else{bprice = 0;}

                    job.hours = parts[3].toInt();
                    if (ui->slider_time->value() == 0) {bhours = 1;}
                    else if (job.hours == ui->slider_time->value()) {bhours = 1;}
                    else {bhours = 0;}

                    job.metroStation = parts[4];
                    if (ui->color->currentText() == "Без фильтров"){bstation = 1;}
                    else if (ui->station->currentText() == job.metroStation){bstation = 1;}
                    else{bstation  = 0;}

                    job.address = parts[5];
                    job.phone = parts[6];
                    job.userId = parts[7].toInt();

                    if (btype + bprice + bhours + bstation == 4){
                        jobs_2.append(job);
                        QString displayText = QString("%1 (%2 руб.)\n"
                                                      "ст.м. %3 %4 ч. ").arg(job.type).arg(job.cost).arg(job.metroStation).arg(job.hours);
                        jobDescriptions << displayText;
                    }

                }else {
                    qDebug() << "Ошибка: некорректная строка в файле:" << line;
                }
            }
        }
        file.close();
    } else {
        qDebug() << "Не удалось открыть файл:";
        return;
    }

    model->setStringList(jobDescriptions);
    qDebug() << "Количество элементов в модели:" << expectedJobCount;
}

void bulletin_board::onBranchChanged()
{
    QComboBox* branchComboBox = ui->color;
    QComboBox* stationComboBox = ui->station;

    QString selectedBranch = branchComboBox->currentText();
    stationComboBox->clear();

    if (metroStations.contains(selectedBranch)) { // проверяет, есть ли какая-то ветка
        stationComboBox->addItems(metroStations[selectedBranch]);
    }
}


void bulletin_board::onJobClicked(const QModelIndex &index) {
    int row = index.row();
    if (row < 0 || row >= jobs_2.size()) {
        qDebug() << "Некорректный индекс объявления:" << row;
        return;
    }
    Job job = jobs_2[row];

    now window(job);
    window.setModal(true);
    window.exec();
}

bulletin_board::~bulletin_board()
{
    delete ui;
}

void bulletin_board::on_build_clicked()
{
    create_2 window;
    window.setModal(true);
    window.exec();
    if (obnov == 1) {loadJob();}
}


void bulletin_board::on_filter_clicked()
{
    loadJob();
}

