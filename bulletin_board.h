#ifndef BULLETIN_BOARD_H
#define BULLETIN_BOARD_H

#include <QDialog>
#include <QStringListModel>
#include <QListView>


namespace Ui {
class bulletin_board;
}

class bulletin_board : public QDialog
{
    Q_OBJECT

public:
    explicit bulletin_board(QWidget *parent = nullptr);
    ~bulletin_board();

private slots:
    void on_build_clicked();
    void onJobClicked(const QModelIndex &index);
    void on_filter_clicked();

private:
    Ui::bulletin_board *ui;
    static QMap<QString, QStringList> metroStations;
    void onBranchChanged();
    void updateStations();
    QStringListModel *model;
    QListView *listView;
    void loadJob();
    void applyFilters();
};


extern int obnov;


#endif // BULLETIN_BOARD_H
